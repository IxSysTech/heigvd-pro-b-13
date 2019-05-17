#include "dispatcher.h"
#include "GALGO/Galgo.hpp"

// Get only the last 2 bits 0 for NOTHING, 1 for YES and 2 for NO
#define MASK_STATE_ACTION 0x3

std::multimap<std::string, bool>* Dispatcher::sequences;
unsigned int Dispatcher::maxAlert, Dispatcher::nbBitState, Dispatcher::MASK_TRANSITIONS;

Dispatcher::Dispatcher(int crossMode, int selectMode, int mutMode, double crossOverRate, double mutationRate, double selectivePressureRate, double toleranceRate, unsigned int stateNb, unsigned int popsize, unsigned int maxAlert, unsigned int genNb, unsigned int elitpop, QObject *parent) :
    crossMode(crossMode), selectMode(selectMode), mutMode(mutMode), crossOverRate(crossOverRate), mutationRate(mutationRate), selectivePressureRate(selectivePressureRate), toleranceRate(toleranceRate), stateNb(stateNb), genNb(genNb), popsize(popsize), elitpop(elitpop), QObject(parent)
{
    this->maxAlert = maxAlert;

    nbBitState = static_cast<unsigned int>(ceil(log2(stateNb)));
    MASK_TRANSITIONS = static_cast<unsigned int>(pow(2, nbBitState) -1);
    //TODO: Receive all the configs necessary to the statemachines and the genetical algorithm
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

void Dispatcher::initSequences(){
    sequences = new std::multimap<std::string, bool>();
    std::ifstream test("gattacaTest");
    std::string line;
    std::vector<std::string> tokens;
    char delimiter = ';';
    while(std::getline(test, line)){
        tokens = split(line, delimiter);
        sequences->insert(std::pair<std::string, bool>(tokens[0], tokens[1] == "0" ? true : false));
    }
}

void Dispatcher::run() {

    this->initSequences();

    std::vector<galgo::Parameter<float,32>> parameters(
                this->stateNb,
                galgo::Parameter<float,32>({0.0, std::numeric_limits<float>::max()})
    );

    Emitter *test = new Emitter();

    // initiliazing genetic algorithm
    galgo::GeneticAlgorithm<float> ga(
                test,
                this->mutMode,
                this->crossMode,
                this->selectMode,
                static_cast<float>(this->crossOverRate),
                static_cast<float>(this->mutationRate),
                static_cast<float>(this->selectivePressureRate),
                Dispatcher::objective<float>,
                static_cast<int>(this->popsize),
                static_cast<int>(this->genNb),
                static_cast<int>(this->elitpop),
                true,
                parameters
    );

    QObject::connect(test, SIGNAL(incrementProgress(double)), this, SLOT(relay(double)));

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
    std::vector<StateDescriptor> *theTestMachine = new std::vector<StateDescriptor>();
    converter c;

    for(size_t i = 0; i < x.size(); ++i){
        c.value = x.at(i);
        uint32_t binRepresentation = c.converted;

        out << "State : " << i << " : " << endl;

        StateDescriptor *currentState = new StateDescriptor;
        currentState->transitions = std::vector<StateDescriptor::Transition>();

        for(int begin = 0; begin < StateDescriptor::Transition::signalType::Count; begin++){
            out << begin << " -> " << (binRepresentation & MASK_TRANSITIONS) << endl;

            currentState->transitions.push_back(
                        StateDescriptor::Transition(
                            static_cast<StateDescriptor::Transition::signalType>(begin),
                            static_cast<int>(binRepresentation & MASK_TRANSITIONS)
                        )
            );

            // shift du nombre de bits par transition (nb nécessaire pour encoder une transition)
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

    MegaMachineManager *manager = new MegaMachineManager(sequences,*theMachines, scores, maxAlert);

    QEventLoop loop;
    QObject::connect(manager, SIGNAL (finished()), &loop, SLOT (quit()));
    QTimer::singleShot(0, manager, &MegaMachineManager::runMachines);
    loop.exec();

    return {static_cast<float>(scores->at(0))};
}

void Dispatcher::relay(double percent) {
    QTextStream out(stdout);
    out << "Signal emitted from dispacther, percent : " << percent << endl;
    emit incrementProgress(percent);
}
