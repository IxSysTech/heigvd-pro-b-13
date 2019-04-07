#include "megamachine.h"

void MegaMachine::buildStateMachine(int nbStates)
{
    for(int i = 0; i < nbStates; ++i){
        states.push_back(new QState(&machine));
    }
    srand(time(NULL));
    for(QState *state : states){
        state->addTransition(this, SIGNAL(A()), states.at(rand() % nbStates));
        state->addTransition(this, SIGNAL(C()), states.at(rand() % nbStates));
        state->addTransition(this, SIGNAL(G()), states.at(rand() % nbStates));
        state->addTransition(this, SIGNAL(T()), states.at(rand() % nbStates));
    }

    connect(states.at(0), &QState::entered, this, &MegaMachine::runS1);
    connect(states.at(1), &QState::entered, this, &MegaMachine::runS2);
    connect(states.at(2), &QState::entered, this, &MegaMachine::runS3);

    machine.setInitialState(states.at(0));

    machine.start();
}

MegaMachine::MegaMachine(int nbStates, QObject *parent) : QObject(parent)
{
    buildStateMachine(nbStates);
}

void MegaMachine::runS1()
{
    std::cout << "entered state S1" << std::endl;
}

void MegaMachine::runS2()
{
    std::cout << "entered state S2" << std::endl;
}

void MegaMachine::runS3()
{
    std::cout << "entered state S3" << std::endl;
}

void MegaMachine::debugSlot()
{
    std::cout << "debug slot was triggered!" << std::endl;
}

void MegaMachine::readA(){
    emit A();
}
void MegaMachine::readC(){
    emit C();
}
void MegaMachine::readG(){
    emit G();
}
void MegaMachine::readT(){
    emit T();
}

