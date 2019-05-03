#include "dispatcher.h"
#include "Galgo.hpp"
#include "megamachinemanager.h"
#include "utils.h"
#include <QObject>
#include <vector>

// Get the appropriate number of bits for each transition
#define MASK_TRANSITIONS 0x0000000000000007
// Get only the last 2 bits 0 for NOTHING, 1 for YES and 2 for NO
#define MASK_STATE_ACTION 0x3

Dispatcher::Dispatcher(QObject *parent) : QObject(parent)
{
    //TODO: Receive all the configs necessary to the statemachines and the genetical algorithm
}

void Dispatcher::run() {

    //Test with hardcoded params
    galgo::Parameter<double,64> par1({std::numeric_limits<double>::min(), std::numeric_limits<double>::max()});
    galgo::Parameter<double,64> par2({std::numeric_limits<double>::min(), std::numeric_limits<double>::max()});
    galgo::Parameter<double,64> par3({std::numeric_limits<double>::min(), std::numeric_limits<double>::max()});
    galgo::Parameter<double,64> par4({std::numeric_limits<double>::min(), std::numeric_limits<double>::max()});
    galgo::Parameter<double,64> par5({std::numeric_limits<double>::min(), std::numeric_limits<double>::max()});
    galgo::Parameter<double,64> par6({std::numeric_limits<double>::min(), std::numeric_limits<double>::max()});
    galgo::Parameter<double,64> par7({std::numeric_limits<double>::min(), std::numeric_limits<double>::max()});
    galgo::Parameter<double,64> par8({std::numeric_limits<double>::min(), std::numeric_limits<double>::max()});

    // initiliazing genetic algorithm
    galgo::GeneticAlgorithm<double> ga(Dispatcher::objective<double>,2,500,true,par1,par2,par3,par4,par5,par6,par7,par8);

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
            binRepresentation >>= 3;
        }
        currentState->stateAction = static_cast<StateDescriptor::stateActionType>((binRepresentation & MASK_STATE_ACTION) % 3);
        out << "State action ID is : " << (binRepresentation & MASK_STATE_ACTION)% 3 << endl;
        theTestMachine->push_back(*currentState);
        out << "---------------------------------------" << endl;
    }

    std::vector<std::vector<StateDescriptor>> *theMachines = new std::vector<std::vector<StateDescriptor>>();
    std::vector<int> *scores = new std::vector<int>(1, 0);
    MegaMachineManager *manager = new MegaMachineManager(*theMachines, scores);
    manager->runMachines();
    return {static_cast<double>(scores->at(0))};
}
