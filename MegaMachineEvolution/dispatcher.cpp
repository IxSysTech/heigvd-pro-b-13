#include "dispatcher.h"
#include "GALGO/Galgo.hpp"

#include <QJsonDocument>
#include <QFile>

// Get only the last 2 bits 0 for NOTHING, 1 for YES and 2 for NO
#define MASK_STATE_ACTION 0x3

// static initialisations
unsigned int Dispatcher::maxAlert;
bool Dispatcher::debugMachines;
std::multimap<std::string, bool> * Dispatcher::currentSequences;

Dispatcher::Dispatcher(unsigned int stateNb, unsigned int maxAlert, const gaParameters& gaParam, const QString& sequencesFile, bool debugMachines, const QString& logFileLocation, QObject *parent) :
    QObject(parent), stateNb(stateNb), logFileLocation(logFileLocation), gaParam(gaParam)
{
    this->maxAlert = maxAlert;
    this->debugMachines = debugMachines;
    this->initSequences(sequencesFile);
}

Dispatcher::Dispatcher(const QString& sequencesFile, bool debugMachines, const QString& machineFile, QObject *parent) :
    QObject(parent), logFileLocation(machineFile)
{
    this->debugMachines = debugMachines;
    this->initSequences(sequencesFile);
}

//TODO: Add source
std::vector<std::string> Dispatcher::split(const std::string& s, char delimiter)
{
   std::vector<std::string> tokens;
   std::string token;
   std::istringstream tokenStream(s);
   while (std::getline(tokenStream, token, delimiter))
   {
      tokens.push_back(token);
   }
   return tokens;
}

void Dispatcher::initSequences(const QString& sequencesFile){
    sequences = new std::multimap<int, std::string>();

    // Because of sequencesFile being a QString we need to convert it for ifstream
    std::ifstream test(sequencesFile.toStdString());
    std::string line;
    std::vector<std::string> tokens;
    char delimiter = ';';
    while(std::getline(test, line)){
        tokens = split(line, delimiter);
        // We add the sequences to a multimap ordering by IDs
        sequences->insert(std::pair<int, std::string>(std::atoi(tokens[1].c_str()), tokens[0]));
    }
}

void Dispatcher::runOneMachine() {
    QFile machineFile(logFileLocation);
    machineFile.open(QIODevice::ReadOnly | QIODevice::Text);

    QString content = machineFile.readAll();
    QJsonDocument doc = QJsonDocument::fromJson(content.toUtf8());
    QJsonArray rootElement = doc.array();
    std::vector<StateDescriptor> machine;

    for(QJsonValue state : rootElement) {
        StateDescriptor *currentState = new StateDescriptor;
        currentState->stateAction = static_cast<StateDescriptor::stateActionType>(state.toObject().value("stateAction").toInt());
        currentState->transitions = std::vector<StateDescriptor::Transition>();

        for(QJsonValue transition : state.toObject().value("transitions").toArray()) {
            currentState->transitions.push_back(
                        StateDescriptor::Transition(
                            static_cast<StateDescriptor::Transition::signalType>(transition.toObject().value("signal").toInt()),
                            static_cast<unsigned int>(transition.toObject().value("destinationState").toInt())
                        )
            );
        }

        machine.push_back(*currentState);
    }

    std::vector<int> keys;
    for(auto it = sequences->begin(); it != sequences->end(); it = sequences->upper_bound(it->first))
        keys.push_back(it->first);

    currentSequences = new std::multimap<std::string, bool>();
    // TODO: Retrieve which ID the machine is designed to detect
    auto range = sequences->equal_range(1);

    for(auto it = range.first; it != range.second; ++it) {
        currentSequences->insert(std::pair<std::string, bool>(it->second, true));
    }
    /*
    for (int key : keys) {
        //TODO : change 1 by ID that machine can detect
        if(key == 1)
            continue;
        range = sequences->equal_range(0);

        for(auto it = range.first; it != range.second; ++it) {
            currentSequences->insert(std::pair<std::string, bool>(it->second, false));
        }
    }
    */

    QTextStream debug(stdout);

    std::vector<std::vector<StateDescriptor>> * theMachines = new std::vector<std::vector<StateDescriptor>>({machine});
    std::vector<int> *scores = new std::vector<int>(1, 0);

    MegaMachineManager *manager = new MegaMachineManager(currentSequences, *theMachines, scores, maxAlert, debugMachines);

    QEventLoop loop;
    QObject::connect(manager, SIGNAL (finished()), &loop, SLOT (quit()));
    QTimer::singleShot(0, manager, &MegaMachineManager::runMachines);
    loop.exec();

    debug << "Score : " << static_cast<float>(scores->at(0)) << endl;
    delete theMachines;
}

void Dispatcher::run() {
    // Vector to keep all the keys given on the sequences file (It's IDs it can be chaotic)
    std::vector<int> keys;
    // Add each key
    for(auto it = sequences->begin(); it != sequences->end(); it = sequences->upper_bound(it->first))
        keys.push_back(it->first);

    for(size_t i = 0; i < keys.size(); ++i) {
        // Announce the current Analysis
        emit sendAnalysis(static_cast<unsigned int>(i + 1), static_cast<unsigned int>(keys.size()));

        currentSequences = new std::multimap<std::string, bool>();
        auto range = sequences->equal_range(keys[i]);

        //TODO: user option for k limit
        int k = 0;
        // We first get the current analyzed ID, 100 first sequences at most
        for(auto it = range.first; it != range.second && k++ < 100; ++it) {
            currentSequences->insert(std::pair<std::string, bool>(it->second, true));
        }

        // Getting sequences of other IDs to perform analysis
        size_t nbSeq = currentSequences->size();
        for(size_t j = 0; j < nbSeq; ++j) {
            size_t currentKey = std::rand() % keys.size();
            if(keys[currentKey] == keys[i])
                currentKey = (currentKey + 1) % keys.size();

            auto randomElement = sequences->find(keys[currentKey]);

            std::advance(randomElement, std::rand() % sequences->count(keys[currentKey]));
            currentSequences->insert(
                        std::pair<std::string, bool>(
                            randomElement->second,
                            false
                        )
            );
        }

        // We create a Parameter for each state of the StateMachines (see Doc)
        std::vector<galgo::Parameter<float,32>> parameters(
                    this->stateNb,
                    galgo::Parameter<float,32>({0.0, std::numeric_limits<float>::max()})
        );

        // This emitter is just a way for the GA to perform signals
        Emitter *gaEmitter = new Emitter();

        // initiliazing genetic algorithm
        galgo::GeneticAlgorithm<float> ga(gaEmitter, gaParam, Dispatcher::objective<float>, true, parameters);

        QObject::connect(gaEmitter, SIGNAL(incrementProgress(double)), this, SLOT(relay(double)));
        QObject::connect(gaEmitter, SIGNAL(stateInfo(uint,double,double)), this, SLOT(relayState(uint,double,double)));

        // running genetic algorithm
        ga.run();
        std::vector<float> bestMachine = ga.result()->getParam();
        std::vector<StateDescriptor> * theBestMachine = getMachine(bestMachine);

        // JSON Stringify this vector to log bestMachine
        QJsonArray jsonMachine;
        for(StateDescriptor sd : *theBestMachine) {
            jsonMachine.push_back(sd.toJson());
        }

        // We put the JSON representation of the machine to a file
        // TODO: We need to pot his best result and the ID for which it's OK to use
        FILE* machine = std::fopen(strcat(logFileLocation.toLocal8Bit().data(), QString("/bestmachineAnalysis%1.machine").arg(i).toLocal8Bit().data()), "w+");
        QTextStream(machine) << QJsonDocument(jsonMachine).toJson();

        delete currentSequences;
    }

    emit finished();
}

uint32_t Dispatcher::convert(float from) {
    union {
        float value;
        uint32_t converted;
    } c32;

    c32.value = from;
    return c32.converted;
}

uint64_t Dispatcher::convert(double from) {
    union {
        double value;
        uint64_t converted;
    } c64;

    c64.value = from;
    return c64.converted;
}

template <typename T>
std::vector<StateDescriptor> * Dispatcher::getMachine(const std::vector<T> &machine) {
    QTextStream debug(stdout);

    // Construction d'une machine de test
    size_t stateNb = machine.size();

    std::vector<StateDescriptor> *theMachine = new std::vector<StateDescriptor>();
    unsigned int nbBitState = static_cast<unsigned int>(ceil(log2(stateNb))),
                 MASK_TRANSITIONS = static_cast<unsigned int>(pow(2, nbBitState) -1);

    for(size_t i = 0; i < machine.size(); ++i){
        auto binRepresentation = convert(machine.at(i));

        if(debugMachines)
            debug << "State : " << i << " : " << endl;

        StateDescriptor *currentState = new StateDescriptor;
        currentState->transitions = std::vector<StateDescriptor::Transition>();

        for(int i = 0; i < StateDescriptor::Transition::signalType::Count; i++){
            if(debugMachines)
                debug << i << " -> " << ((binRepresentation & MASK_TRANSITIONS) % stateNb) << endl;

            currentState->transitions.push_back(
                        StateDescriptor::Transition(
                            static_cast<StateDescriptor::Transition::signalType>(i),
                            (binRepresentation & MASK_TRANSITIONS) % stateNb
                        )
            );

            // shift du nombre de bits nécessaire pour encoder un état pour passer à la prochaine transition
            binRepresentation >>= nbBitState;
        }

        currentState->stateAction = static_cast<StateDescriptor::stateActionType>((binRepresentation & 0x3) % 3);
        if(debugMachines) {
            debug << "State action ID is : " << (binRepresentation & MASK_STATE_ACTION) % 3 << endl;
            debug << "---------------------------------------" << endl;
        }

        theMachine->push_back(*currentState);
    }

    return theMachine;
}

template <typename T>
std::vector<T> Dispatcher::objective(const std::vector<T>& x){
    QTextStream debug(stdout);

    std::vector<std::vector<StateDescriptor>> * theMachines = new std::vector<std::vector<StateDescriptor>>({*getMachine(x)});
    std::vector<int> *scores = new std::vector<int>(1, 0);

    MegaMachineManager *manager = new MegaMachineManager(currentSequences, *theMachines, scores, maxAlert, debugMachines);

    // We start MegaMachineManager inside Event loops because QStateMachines needs them to execute correctly
    QEventLoop loop;
    QObject::connect(manager, SIGNAL (finished()), &loop, SLOT (quit()));
    QTimer::singleShot(0, manager, &MegaMachineManager::runMachines);
    loop.exec();

    debug << "Score : " << static_cast<float>(scores->at(0)) << endl;
    delete theMachines;

    return {static_cast<float>(scores->at(0))};
}

void Dispatcher::relay(double percent) {
    emit incrementProgress(percent);
}

void Dispatcher::relayState(unsigned int genNb, double maxFit, double meanFit ) {
    emit sendState(genNb, maxFit, meanFit);
}

Dispatcher::~Dispatcher() {
    // We avoid a memory leak
    delete sequences;
}
