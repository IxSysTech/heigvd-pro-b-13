#include "dispatcher.h"
#include "GALGO/Galgo.hpp"

// Get the appropriate number of bits for each transition
#define MASK_TRANSITIONS 0x000000000000000F
// Get only the last 2 bits 0 for NOTHING, 1 for YES and 2 for NO
#define MASK_STATE_ACTION 0x3

std::multimap<std::string, bool>* Dispatcher::sequences;

Dispatcher::Dispatcher(int crossMode, int selectMode, int mutMode, double crossOverRate, double mutationRate, double selectivePressureRate, double toleranceRate, unsigned int stateNb, unsigned int popsize, unsigned int maxAlert, unsigned int genNb, QObject *parent) :
    crossMode(crossMode), selectMode(selectMode), mutMode(mutMode), crossOverRate(crossOverRate), mutationRate(mutationRate), selectivePressureRate(selectivePressureRate), toleranceRate(toleranceRate), stateNb(stateNb), maxAlert(maxAlert), genNb(genNb), popsize(popsize), QObject(parent)
{

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
    //Test with hardcoded params
    /*galgo::Parameter<float,32> par1({0.0, std::numeric_limits<float>::max()});
    galgo::Parameter<float,32> par2({0.0, std::numeric_limits<float>::max()});
    galgo::Parameter<float,32> par3({0.0, std::numeric_limits<float>::max()});
    galgo::Parameter<float,32> par4({0.0, std::numeric_limits<float>::max()});
    galgo::Parameter<float,32> par5({0.0, std::numeric_limits<float>::max()});
    galgo::Parameter<float,32> par6({0.0, std::numeric_limits<float>::max()});
    galgo::Parameter<float,32> par7({0.0, std::numeric_limits<float>::max()});
    galgo::Parameter<float,32> par8({0.0, std::numeric_limits<float>::max()});
    galgo::Parameter<float,32> par9({0.0, std::numeric_limits<float>::max()});
    galgo::Parameter<float,32> par10({0.0, std::numeric_limits<float>::max()});
    galgo::Parameter<float,32> par11({0.0, std::numeric_limits<float>::max()});
    galgo::Parameter<float,32> par12({0.0, std::numeric_limits<float>::max()});
    galgo::Parameter<float,32> par13({0.0, std::numeric_limits<float>::max()});
    galgo::Parameter<float,32> par14({0.0, std::numeric_limits<float>::max()});
    galgo::Parameter<float,32> par15({0.0, std::numeric_limits<float>::max()});
    galgo::Parameter<float,32> par16({0.0, std::numeric_limits<float>::max()});
*/
    std::vector<galgo::Parameter<float,32>> parameters;
    //std::tuple<const Parameter<T,N>&...> tp;

    for(int i = 0; i < this->stateNb; ++i)
        parameters.push_back(galgo::Parameter<float,32>({0.0, std::numeric_limits<float>::max()}));


    // initiliazing genetic algorithm
    //galgo::GeneticAlgorithm<float> ga(this->mutMode,this->crossMode,this->selectMode,Dispatcher::objective<float>,this->popsize,this->genNb,true,par1,par2,par3,par4,par5,par6,par7,par8,par9,par10,par11,par12,par13,par14,par15,par16);
    galgo::GeneticAlgorithm<float> ga(this->mutMode, this->crossMode, this->selectMode, this->crossOverRate, this->mutationRate, this->selectivePressureRate, Dispatcher::objective<float>, this->popsize, this->genNb, true, tp);

    // running genetic algorithm
    ga.run();
    ga.result();
    emit finished();
}

template <typename T>
std::vector<T> Dispatcher::objective(const std::vector<T>& x){
    QTextStream out(stdout);

    // Construction d'une machine de test
    std::vector<StateDescriptor> *theTestMachine = new std::vector<StateDescriptor>();

    size_t nbStates = x.size();
    for(size_t i = 0; i < nbStates; ++i){
        converter test;
        test.value = x.at(i);
        uint32_t binRepresentation = test.converted;
        out << "State : " << i << " : " << endl;
        StateDescriptor *currentState = new StateDescriptor;
        currentState->transitions = std::vector<StateDescriptor::Transition>();
        for(int begin = 0; begin != 5; begin++){
            out << begin << " -> " << (binRepresentation & MASK_TRANSITIONS) << endl;
            StateDescriptor::Transition currentTrans = {
                .signal = static_cast<StateDescriptor::Transition::signalType>(begin),
                .destinationState = (int)(binRepresentation & MASK_TRANSITIONS)
            };
            currentState->transitions.push_back(currentTrans);
            // on bouge de 3bits (nécessaire pour encoder les états)
            binRepresentation >>= 4;
        }
        currentState->stateAction = static_cast<StateDescriptor::stateActionType>((binRepresentation & MASK_STATE_ACTION) % 3);
        out << "State action ID is : " << (binRepresentation & MASK_STATE_ACTION)% 3 << endl;
        theTestMachine->push_back(*currentState);
        out << "---------------------------------------" << endl;
    }

    std::vector<std::vector<StateDescriptor>> *theMachines = new std::vector<std::vector<StateDescriptor>>();
    std::vector<int> *scores = new std::vector<int>(1, 0);
    theMachines->push_back(*theTestMachine);
    MegaMachineManager *manager = new MegaMachineManager(sequences,*theMachines, scores);

    QEventLoop loop;
    QObject::connect(manager, SIGNAL (finished()), &loop, SLOT (quit()));
    QTimer::singleShot(0, manager, &MegaMachineManager::runMachines);
    loop.exec();

    return {static_cast<float>(scores->at(0))};
}
