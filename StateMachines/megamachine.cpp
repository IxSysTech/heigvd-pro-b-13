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
        state->addTransition(this, SIGNAL(X()), states.at(rand() % nbStates));
    }

    int i = 0;
    for(QState *state : states){
        connect(state, &QState::entered, this, [i] () {
            QTextStream out(stdout);
            out << "Entered state : " << i << endl;
        });
        ++i;
    }

    // connect(states.at(0), &QState::entered, this, &MegaMachine::yes);
    connect(states.at(1), &QState::entered, this, &MegaMachine::no);
    connect(states.at(2), &QState::entered, this, &MegaMachine::yes);
    machine.setInitialState(states.at(0));

    connect(&machine, &QStateMachine::stopped, this, &MegaMachine::stop);
    machine.start();
}

MegaMachine::MegaMachine(int nbStates, int maxAlerts, QObject *parent) : QObject(parent), maxAlerts(maxAlerts)
{
    buildStateMachine(nbStates);
}

void MegaMachine::yes(){
    if(++(this->ctrYes) >= maxAlerts)
        this->machine.stop();
}

void MegaMachine::no(){
    if(++(this->ctrNo) >= maxAlerts)
        this->machine.stop();
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

void MegaMachine::readX(){
    emit X();
}

void MegaMachine::stop(){
    QTextStream out(stdout);
    out << "A Machine has stop !" << endl;
    emit stopped();
}

