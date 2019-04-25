#include "megamachine.h"

void MegaMachine::buildStateMachine(int nbStates)
{
    QTextStream out(stdout);
    /*for(int i = 0; i < nbStates; ++i){
        states.push_back(new QState(&machine));
    }
    srand(time(NULL));
    int stateNumber = 0;
    size_t transition = 0;
    QState *finalState = new QState(&machine);

    for(QState *state : states){
        out << "From State : " << stateNumber << endl;
        transition = rand() % nbStates;
        state->addTransition(this, SIGNAL(A()), states.at(transition));
        out << "A -> " << transition << endl;
        transition = rand() % nbStates;
        state->addTransition(this, SIGNAL(C()), states.at(transition));
        out << "C -> " << transition << endl;
        transition = rand() % nbStates;
        state->addTransition(this, SIGNAL(G()), states.at(transition));
        out << "G -> " << transition << endl;
        transition = rand() % nbStates;
        state->addTransition(this, SIGNAL(T()), states.at(transition));
        out << "T -> " << transition << endl;
        transition = rand() % nbStates;
        state->addTransition(this, SIGNAL(X()), states.at(transition));
        out << "X -> " << transition << endl;
        out << "-----------------------------------------" << endl;
        state->addTransition(this, SIGNAL(stopMachine()), finalState);

        stateNumber++;
    }
    finalState->addTransition(this, SIGNAL(resetMachine()), states.at(0));

    // Logging
    int i = 0;
    int idMachine = this->id;
    for(QState *state : states){
        connect(state, &QState::entered, [i, idMachine] () {
            QTextStream out(stdout);
            out << "Entered state : " << i << " for machine " << idMachine << endl;
        });
        ++i;
    }

    // connect(states.at(0), &QState::entered, this, &MegaMachine::yes);
    // connect(states.at(1), &QState::entered, this, &MegaMachine::no);
    connect(states.at(2), &QState::entered, this, &MegaMachine::yes);

    // If nothing was detected
    connect(finalState, &QState::entered, this, &MegaMachine::nothing);
    machine.setInitialState(states.at(0));

    // connect(&machine, &QStateMachine::stopped, this, &MegaMachine::stop);
    machine.start();*/

    /**
      Test machine
    **/

    for(int i = 0; i < 5; ++i){
        states.push_back(new QState(&machine));
    }

    QState *finalState = new QState(&machine);

    for(QState* state : states)
        state->addTransition(this, SIGNAL(stopMachine()), finalState);

    states.at(0)->addTransition(this, SIGNAL(A()), states.at(1));

    states.at(1)->addTransition(this, SIGNAL(C()), states.at(2));
    states.at(1)->addTransition(this, SIGNAL(C()), states.at(0));
    states.at(1)->addTransition(this, SIGNAL(G()), states.at(0));
    states.at(1)->addTransition(this, SIGNAL(T()), states.at(0));
    states.at(1)->addTransition(this, SIGNAL(X()), states.at(0));

    states.at(2)->addTransition(this, SIGNAL(G()), states.at(3));
    states.at(2)->addTransition(this, SIGNAL(C()), states.at(0));
    states.at(2)->addTransition(this, SIGNAL(G()), states.at(0));
    states.at(2)->addTransition(this, SIGNAL(T()), states.at(0));
    states.at(2)->addTransition(this, SIGNAL(X()), states.at(0));

    states.at(3)->addTransition(this, SIGNAL(T()), states.at(4));
    states.at(3)->addTransition(this, SIGNAL(C()), states.at(0));
    states.at(3)->addTransition(this, SIGNAL(G()), states.at(0));
    states.at(3)->addTransition(this, SIGNAL(T()), states.at(0));
    states.at(3)->addTransition(this, SIGNAL(X()), states.at(0));

    states.at(4)->addTransition(this, SIGNAL(A()), states.at(1));

    finalState->addTransition(this, SIGNAL(resetMachine()), states.at(0));

    connect(states.at(4), &QState::entered, this, &MegaMachine::yes);

    // If nothing was detected
    connect(finalState, &QState::entered, this, &MegaMachine::nothing);
    machine.setInitialState(states.at(0));

    machine.start();
}

MegaMachine::MegaMachine(int nbStates, int maxAlerts, int id, QObject *parent) : QObject(parent), ctrYes(0), ctrNo(0), maxAlerts(maxAlerts), id(id)
{
    buildStateMachine(nbStates);
}

void MegaMachine::yes(){
    if(++(this->ctrYes) >= maxAlerts)
        emit stopMachine();
        //this->machine.stop();
}

void MegaMachine::no(){
    if(++(this->ctrNo) >= maxAlerts)
        emit stopMachine();
        //this->machine.stop();
}

void MegaMachine::nothing(){
    QTextStream out(stdout);
    out << "A Machine has stop ! Result is : yes -> " << ctrYes << " and no -> " << ctrNo << endl;
    // Emit which machine has stop
    emit stopped(id, ctrYes, ctrNo);
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
void MegaMachine::finishedSequence(){
    emit stopMachine();
}

void MegaMachine::reset(){
    this->ctrNo = this->ctrYes = 0;
    emit resetMachine();
}

/*
void MegaMachine::stop(){
    QTextStream out(stdout);
    out << "A Machine has stop ! Result is : yes -> " << ctrYes << " and no -> " << ctrNo << endl;
    // Emit which machine has stop
    emit stopped(id, ctrYes, ctrNo);
}*/

