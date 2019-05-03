#include "dispatcher.h"
#include "Galgo.hpp"
#include "megamachinemanager.h"
#include "utils.h"
#include <QObject>
#include <vector>

#include <QTimer>

// Get the appropriate number of bits for each transition
#define MASK_TRANSITIONS 0x000000000000000F
// Get only the last 2 bits 0 for NOTHING, 1 for YES and 2 for NO
#define MASK_STATE_ACTION 0x3

Dispatcher::Dispatcher(QObject *parent) : QObject(parent)
{
    //TODO: Receive all the configs necessary to the statemachines and the genetical algorithm
}

void Dispatcher::run() {

    //Test with hardcoded params
    galgo::Parameter<double,64> par1({0.0, std::numeric_limits<double>::max()});
    galgo::Parameter<double,64> par2({0.0, std::numeric_limits<double>::max()});
    galgo::Parameter<double,64> par3({0.0, std::numeric_limits<double>::max()});
    galgo::Parameter<double,64> par4({0.0, std::numeric_limits<double>::max()});
    galgo::Parameter<double,64> par5({0.0, std::numeric_limits<double>::max()});
    galgo::Parameter<double,64> par6({0.0, std::numeric_limits<double>::max()});
    galgo::Parameter<double,64> par7({0.0, std::numeric_limits<double>::max()});
    galgo::Parameter<double,64> par8({0.0, std::numeric_limits<double>::max()});
    galgo::Parameter<double,64> par9({0.0, std::numeric_limits<double>::max()});
    galgo::Parameter<double,64> par10({0.0, std::numeric_limits<double>::max()});
    galgo::Parameter<double,64> par11({0.0, std::numeric_limits<double>::max()});
    galgo::Parameter<double,64> par12({0.0, std::numeric_limits<double>::max()});
    galgo::Parameter<double,64> par13({0.0, std::numeric_limits<double>::max()});
    galgo::Parameter<double,64> par14({0.0, std::numeric_limits<double>::max()});
    galgo::Parameter<double,64> par15({0.0, std::numeric_limits<double>::max()});
    galgo::Parameter<double,64> par16({0.0, std::numeric_limits<double>::max()});

    // initiliazing genetic algorithm
    galgo::GeneticAlgorithm<double> ga(Dispatcher::objective<double>,10,500,true,par1,par2,par3,par4,par5,par6,par7,par8,par9,par10,par11,par12,par13,par14,par15,par16);

    // running genetic algorithm
    ga.run();
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
        uint64_t binRepresentation = test.converted;
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
    MegaMachineManager *manager = new MegaMachineManager(*theMachines, scores);

    QEventLoop loop;
    QObject::connect(manager, SIGNAL (finished()), &loop, SLOT (quit()));
    QTimer::singleShot(0, manager, &MegaMachineManager::runMachines);
    loop.exec();

    return {static_cast<double>(scores->at(0))};
}
