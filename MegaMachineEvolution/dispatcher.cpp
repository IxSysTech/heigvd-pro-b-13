#include "dispatcher.h"
#include "GALGO/Galgo.hpp"

// Get only the last 2 bits 0 for NOTHING, 1 for YES and 2 for NO
#define MASK_STATE_ACTION 0x3

unsigned int Dispatcher::maxAlert;
bool Dispatcher::debugMachines;
union Dispatcher::converter Dispatcher::c;
std::multimap<std::string, bool> * Dispatcher::currentSequences;
//std::vector<std::vector<StateDescriptor>> * Dispatcher::getMachine(const std::vector<float> &machine);

Dispatcher::Dispatcher(unsigned int stateNb, unsigned int maxAlert, const gaParameters& gaParam, const QString& filePath, bool debugMachines, QObject *parent) :
    QObject(parent), stateNb(stateNb), gaParam(gaParam)
{
    this->maxAlert = maxAlert;
    this->debugMachines = debugMachines;
    this->initSequences(filePath);
}

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

void Dispatcher::initSequences(const QString& filePath){
    sequences = new std::multimap<int, std::string>();

    // Because of filePath being a QString we need to convert it for ifstream
    std::ifstream test(filePath.toStdString());
    std::string line;
    std::vector<std::string> tokens;
    char delimiter = ';';
    while(std::getline(test, line)){
        tokens = split(line, delimiter);
        sequences->insert(std::pair<int, std::string>(std::atoi(tokens[1].c_str()), tokens[0]));
    }
}


void Dispatcher::run() {
    int nbKey = 0;
    for(auto it = sequences->begin(); it != sequences->end(); it = sequences->upper_bound(it->first))
        nbKey++;

    for(int i = 0; i < nbKey; ++i) {
        // Announce the current Analysis
        emit sendAnalysis(i + 1, nbKey);
        currentSequences = new std::multimap<std::string, bool>();
        auto range = sequences->equal_range(i);

        int k = 0;
        for(auto it = range.first; it != range.second && k++ < 100; ++it) {
            currentSequences->insert(std::pair<std::string, bool>(it->second, true));
        }

        // Getting sequences of other IDs to perform analysis

        int nbSeq = currentSequences->size();
        int randomKey = 0;
        for(int j = 0; j < nbSeq; ++j) {
            if(randomKey % nbKey == i) randomKey++;

            auto randomElement = sequences->find(randomKey % nbKey);

            std::advance(randomElement, std::rand() % sequences->count(randomKey % nbKey));
            currentSequences->insert(
                        std::pair<std::string, bool>(
                            randomElement->second,
                            false
                        )
            );

            randomKey++;
        }

        std::vector<galgo::Parameter<float,32>> parameters(
                    this->stateNb,
                    galgo::Parameter<float,32>({0.0, std::numeric_limits<float>::max()})
        );

        Emitter *gaEmitter = new Emitter();

        // initiliazing genetic algorithm
        galgo::GeneticAlgorithm<float> ga(gaEmitter, gaParam, Dispatcher::objective<float>, true, parameters);

        QObject::connect(gaEmitter, SIGNAL(incrementProgress(double)), this, SLOT(relay(double)));
        QObject::connect(gaEmitter, SIGNAL(stateInfo(uint,double,double)), this, SLOT(relayState(uint,double,double)));

        // running genetic algorithm
        ga.run();
        std::vector<float> bestMachine = ga.result()->getParam();
        std::vector<std::vector<StateDescriptor>> * theBestMachine = getMachine(bestMachine);
        // TODO JSON Stringify this vector to log bestMachine
        delete currentSequences;
    }

    emit finished();
}

std::vector<std::vector<StateDescriptor>> * Dispatcher::getMachine(const std::vector<float> &machine) {
    QTextStream debug(stdout);

    // Construction d'une machine de test
    size_t stateNb = machine.size();

    std::vector<StateDescriptor> *theTestMachine = new std::vector<StateDescriptor>();
    unsigned int nbBitState = static_cast<unsigned int>(ceil(log2(stateNb))),
                 MASK_TRANSITIONS = static_cast<unsigned int>(pow(2, nbBitState) -1);

    for(size_t i = 0; i < machine.size(); ++i){
        c.value = machine.at(i);
        uint32_t binRepresentation = c.converted;

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

        theTestMachine->push_back(*currentState);
    }

    std::vector<std::vector<StateDescriptor>> *theMachines = new std::vector<std::vector<StateDescriptor>>();
    theMachines->push_back(*theTestMachine);
    return theMachines;
}

template <typename T>
std::vector<T> Dispatcher::objective(const std::vector<T>& x){
    QTextStream debug(stdout);

    std::vector<std::vector<StateDescriptor>> * theMachines = getMachine(x);
    std::vector<int> *scores = new std::vector<int>(1, 0);

    MegaMachineManager *manager = new MegaMachineManager(currentSequences, *theMachines, scores, maxAlert, debugMachines);

    QEventLoop loop;
    QObject::connect(manager, SIGNAL (finished()), &loop, SLOT (quit()));
    QTimer::singleShot(0, manager, &MegaMachineManager::runMachines);
    loop.exec();

    //TODO: Uncomment
    //if(debugMachines)
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
    delete sequences;
}
