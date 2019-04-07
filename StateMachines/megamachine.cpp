#include "megamachine.h"

void MegaMachine::buildStateMachine()
{
    QState *s1 = new QState(&machine);
    QState *s2 = new QState(&machine);
    QState *s3 = new QState(&machine);

    s1->addTransition(this, SIGNAL(A()), s2);
    s1->addTransition(this, SIGNAL(C()), s1);
    s1->addTransition(this, SIGNAL(G()), s3);
    s1->addTransition(this, SIGNAL(T()), s2);

    s2->addTransition(this, SIGNAL(A()), s1);
    s2->addTransition(this, SIGNAL(C()), s3);
    s2->addTransition(this, SIGNAL(G()), s2);
    s2->addTransition(this, SIGNAL(T()), s3);

    s3->addTransition(this, SIGNAL(A()), s2);
    s3->addTransition(this, SIGNAL(C()), s3);
    s3->addTransition(this, SIGNAL(G()), s1);
    s3->addTransition(this, SIGNAL(T()), s2);

    connect(s1, &QState::entered, this, &MegaMachine::runS1);
    connect(s2, &QState::entered, this, &MegaMachine::runS2);
    connect(s3, &QState::entered, this, &MegaMachine::runS3);

    machine.setInitialState(s1);

    machine.start();
}

MegaMachine::MegaMachine(QObject *parent) : QObject(parent)
{
    buildStateMachine();
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

