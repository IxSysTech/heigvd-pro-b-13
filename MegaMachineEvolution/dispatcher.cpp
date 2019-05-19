#include "dispatcher.h"
#include "GALGO/Galgo.hpp"

// Get only the last 2 bits 0 for NOTHING, 1 for YES and 2 for NO
#define MASK_STATE_ACTION 0x3

std::multimap<std::string, bool>* Dispatcher::sequences;
unsigned int Dispatcher::maxAlert;
bool Dispatcher::debugMachines;
union Dispatcher::converter Dispatcher::c;

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
    if(sequences != NULL)
        delete sequences;

    sequences = new std::multimap<std::string, bool>();
    // Because of filePath being a QString we need to convert it for ifstream
    std::ifstream test(filePath.toStdString());
    std::string line;
    std::vector<std::string> tokens;
    char delimiter = ';';
    while(std::getline(test, line)){
        tokens = split(line, delimiter);
        sequences->insert(std::pair<std::string, bool>(tokens[0], tokens[1] == "0" ? true : false));
    }
}


void Dispatcher::run() {
    std::vector<galgo::Parameter<float,32>> parameters(
                this->stateNb,
                galgo::Parameter<float,32>({0.0, std::numeric_limits<float>::max()})
    );

    Emitter *gaEmitter = new Emitter();

    // initiliazing genetic algorithm
    galgo::GeneticAlgorithm<float> ga(gaEmitter, gaParam, Dispatcher::objective<float>, true, parameters);

    QObject::connect(gaEmitter, SIGNAL(incrementProgress(double)), this, SLOT(relay(double)));

    // running genetic algorithm
    ga.run();

    // TODO: recup best fit :
    // ga.result();

    emit finished();
}

template <typename T>
std::vector<T> Dispatcher::objective(const std::vector<T>& x){
    QTextStream out(stdout);

    // Construction d'une machine de test
    size_t stateNb = x.size();

    std::vector<StateDescriptor> *theTestMachine = new std::vector<StateDescriptor>();
    unsigned int nbBitState = static_cast<unsigned int>(ceil(log2(stateNb))),
                 MASK_TRANSITIONS = static_cast<unsigned int>(pow(2, nbBitState) -1);

    for(size_t i = 0; i < x.size(); ++i){
        c.value = x.at(i);
        uint32_t binRepresentation = c.converted;

        out << "State : " << i << " : " << endl;

        StateDescriptor *currentState = new StateDescriptor;
        currentState->transitions = std::vector<StateDescriptor::Transition>();

        for(int i = 0; i < StateDescriptor::Transition::signalType::Count; i++){
            out << i << " -> " << ((binRepresentation & MASK_TRANSITIONS) % stateNb) << endl;

            currentState->transitions.push_back(
                        StateDescriptor::Transition(
                            static_cast<StateDescriptor::Transition::signalType>(i),
                            (binRepresentation & MASK_TRANSITIONS) % stateNb
                        )
            );

            // shift du nombre de bits nécessaire pour encoder un état pour passer à la prochaine transition
            binRepresentation >>= nbBitState;
        }

        currentState->stateAction = static_cast<StateDescriptor::stateActionType>((binRepresentation & MASK_STATE_ACTION) % 3);

        out << "State action ID is : " << (binRepresentation & MASK_STATE_ACTION) % 3 << endl;
        out << "---------------------------------------" << endl;

        theTestMachine->push_back(*currentState);
    }

    std::vector<std::vector<StateDescriptor>> *theMachines = new std::vector<std::vector<StateDescriptor>>();
    std::vector<int> *scores = new std::vector<int>(1, 0);
    theMachines->push_back(*theTestMachine);

    MegaMachineManager *manager = new MegaMachineManager(sequences, *theMachines, scores, maxAlert, debugMachines);

    QEventLoop loop;
    QObject::connect(manager, SIGNAL (finished()), &loop, SLOT (quit()));
    QTimer::singleShot(0, manager, &MegaMachineManager::runMachines);
    loop.exec();

    out << "Score : " << static_cast<float>(scores->at(0)) << endl;
    return {static_cast<float>(scores->at(0))};
}

void Dispatcher::relay(double percent) {
    QTextStream out(stdout);
    out << "Signal emitted from dispacther, percent : " << percent << endl;
    emit incrementProgress(percent);
}
