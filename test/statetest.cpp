#include "statetest.h"

StateTest::StateTest(int nbMachines,int nbStates, QObject* senderObj, QObject *parent) : QObject(parent)
{
    this->testMachine = QVector<QStateMachine*>(nbMachines, new QStateMachine());
    this->nucleicAnounce = senderObj;
    QVector<QState*> *tempStates;
    for(QStateMachine* currentMachine : this->testMachine){
        for(int currentState = 0; currentState < nbStates; ++currentState){
            tempStates->append(new QState());
        }
        for(QState *i : *tempStates){
            qsrand(qrand());
            i->addTransition(this->nucleicAnounce, SIGNAL(readA()), tempStates->at(qrand() % nbStates));
            i->addTransition(this->nucleicAnounce, SIGNAL(readC()), tempStates->at(qrand() % nbStates));
            i->addTransition(this->nucleicAnounce, SIGNAL(readG()), tempStates->at(qrand() % nbStates));
            i->addTransition(this->nucleicAnounce, SIGNAL(readT()), tempStates->at(qrand() % nbStates));
        }
        int counterState = 0;
        for(QState *i : *tempStates){
            QObject::connect(i, SIGNAL(entered()), this, SLOT(getStates(counterState)));
            counterState++;
            currentMachine->addState(i);
        }
        currentMachine->setInitialState(tempStates->at(0));
        delete tempStates;
    }
}

void StateTest::runMachines(){
    for(QStateMachine* i : this->testMachine){
        i->start();
    }
}

void StateTest::getStates(int state){
    std::cout << "The state " << state << " was entered" << std::endl;
}
