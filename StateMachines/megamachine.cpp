#include "megamachine.h"

MegaMachine::MegaMachine(QObject *parent) : QObject(parent)
{
    QTextStream errs(stderr, QIODevice::WriteOnly);
    QTextStream out(stdout, QIODevice::WriteOnly);

    machine = new QStateMachine();

    for(int i = 0; i < 4; ++i) {
        states.push_back(new QState());
    }

    for(QState* state : states) {
        state->addTransition(this, SIGNAL(A()), states.at(1));
        machine->addState(state);
    }

    machine->setInitialState(states.at(0));
    machine->start();
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

