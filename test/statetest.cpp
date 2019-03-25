#include "statetest.h"

StateTest::StateTest(int nbMachines,int nbStates, QObject* senderObj, handler* theHandler, QObject *parent) : QObject(parent)
{
    this->testMachine = QVector<QStateMachine*>(nbMachines, new QStateMachine());
    this->nucleicAnounce = senderObj;
    QVector<QState*> *tempStates = new QVector<QState*>();
    int nbMachine = 0;
    for(QStateMachine* currentMachine : this->testMachine){
        for(int currentState = 0; currentState < nbStates; ++currentState){
            tempStates->append(new QState());
        }
        int currentStates = 0;
        for(QState *i : *tempStates){
            qsrand(qrand());
            i->addTransition(this->nucleicAnounce, SIGNAL(readA()), tempStates->at(qrand() % nbStates));
            i->addTransition(this->nucleicAnounce, SIGNAL(readC()), tempStates->at(qrand() % nbStates));
            i->addTransition(this->nucleicAnounce, SIGNAL(readG()), tempStates->at(qrand() % nbStates));
            i->addTransition(this->nucleicAnounce, SIGNAL(readT()), tempStates->at(qrand() % nbStates));
            i->assignProperty(currentMachine, "state", currentStates);
            ++currentStates;
        }

        int counterState = 0;

        for(QState *i : *tempStates){
            QObject::connect(i, SIGNAL(entered()), (QObject*)theHandler, SLOT(getStates(counterState)));
            counterState++;
            currentMachine->addState(i);
        }

        currentMachine->setInitialState(tempStates->at(0));
        delete tempStates;
        ++nbMachine;
    }
}

void StateTest::runMachines(){
    for(QStateMachine* i : this->testMachine){
        i->start();
    }
}
