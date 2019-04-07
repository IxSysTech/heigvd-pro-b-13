#include "megamachine.h"

MegaMachine::MegaMachine(QObject *parent) : QObject(parent)
{
    QTextStream errs(stderr, QIODevice::WriteOnly);
    QTextStream out(stdout, QIODevice::WriteOnly);

    /*for(int i = 0; i < 4; ++i) {
        states.push_back(new QState());
    }

    for(QState* state : states) {
        state->addTransition(this, SIGNAL(A()), states.at(1));
    }

    for(QState* state : states)
        machine.addState(state);

    machine.setInitialState(states.at(0));*/
    QState *s1 = new QState();
    QState *s2 = new QState();
    QState *s3 = new QState();

    s1->addTransition(this, SIGNAL(A()), s2);
    s2->addTransition(this, SIGNAL(T()), s3);
    s3->addTransition(this, SIGNAL(C()), s1);

    machine.addState(s1);
    machine.addState(s2);
    machine.addState(s3);
    machine.setInitialState(s1);

    machine.start();
}

void MegaMachine::readA(){
    machine.isRunning();
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

