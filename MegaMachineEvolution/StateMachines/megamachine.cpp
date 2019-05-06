#include "megamachine.h"

void MegaMachine::buildStateMachine(std::vector<StateDescriptor> statesDescriptions) {
    QTextStream out(stdout);
    for(size_t i = 0; i < statesDescriptions.size(); ++i){
        states.push_back(new QState(&machine));
    }

    int stateNumber = 0;
    QState *finalState = new QState(&machine);

    for(StateDescriptor state : statesDescriptions){
        for(StateDescriptor::Transition currentTransition : state.transitions){
            switch(currentTransition.signal){
                case StateDescriptor::Transition::A:
                    states.at(stateNumber)->addTransition(
                                this,
                                SIGNAL(A()),
                                states.at(currentTransition.destinationState)
                              );
                    break;

                case StateDescriptor::Transition::C:
                    states.at(stateNumber)->addTransition(
                                this,
                                SIGNAL(C()),
                                states.at(currentTransition.destinationState)
                              );
                    break;

                case StateDescriptor::Transition::G:
                    states.at(stateNumber)->addTransition(
                                this,
                                SIGNAL(G()),
                                states.at(currentTransition.destinationState)
                              );
                    break;

                case StateDescriptor::Transition::T:
                    states.at(stateNumber)->addTransition(
                                this,
                                SIGNAL(T()),
                                states.at(currentTransition.destinationState)
                              );
                    break;

                case StateDescriptor::Transition::X:
                    states.at(stateNumber)->addTransition(
                                this,
                                SIGNAL(X()),
                                states.at(currentTransition.destinationState)
                              );
                    break;
            }
        }
        // For each state we set the finish of the machine
        states.at(stateNumber)->addTransition(this, SIGNAL(stopMachine()), finalState);

        switch(state.stateAction){
            case StateDescriptor::NO:
                connect(states.at(stateNumber), &QState::entered, this, &MegaMachine::no);
                break;
            case StateDescriptor::YES:
                connect(states.at(stateNumber), &QState::entered, this, &MegaMachine::yes);
                break;
            case StateDescriptor::NOTHING:
                break;
        }
        stateNumber++;
    }
    // This allow a proper reset of the machine
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

    // If nothing was detected
    connect(finalState, &QState::entered, this, &MegaMachine::machineEnd);

    // For conveniance
    machine.setInitialState(states.at(0));

    // connect(&machine, &QStateMachine::stopped, this, &MegaMachine::stop);
    machine.start();
}

void MegaMachine::buildStateMachine(int nbStates)
{
    QTextStream out(stdout);
    for(int i = 0; i < nbStates; ++i){
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
    connect(finalState, &QState::entered, this, &MegaMachine::machineEnd);
    machine.setInitialState(states.at(0));

    // connect(&machine, &QStateMachine::stopped, this, &MegaMachine::stop);
    machine.start();
}

MegaMachine::MegaMachine(int nbStates, int maxAlerts, int id, QObject *parent) : QObject(parent), ctrYes(0), ctrNo(0), maxAlerts(maxAlerts), id(id)
{
    buildStateMachine(nbStates);
}

MegaMachine::MegaMachine(std::vector<StateDescriptor> statesDescriptions, int maxAlerts, int id, QObject *parent) : QObject(parent), ctrYes(0), ctrNo(0), maxAlerts(maxAlerts), id(id)
{
    buildStateMachine(statesDescriptions);
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

void MegaMachine::machineEnd(){
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
    QTextStream out(stdout);
    this->ctrNo = this->ctrYes = 0;
    out << "Machine is running : " << this->machine.isRunning() << endl;
    emit resetMachine();
}

