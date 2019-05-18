#include "megamachine.h"

void MegaMachine::buildStateMachine(std::vector<StateDescriptor> statesDescriptions) {
    for(size_t i = 0; i < statesDescriptions.size(); ++i){
        states.push_back(new QState(&machine));
    }

    unsigned int stateNumber = 0;
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

                default:
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
    if(hasDebug) {
        int i = 0;
        int idMachine = this->id;
        for(QState *state : states){
            connect(state, &QState::entered, [i, idMachine] () {
                QTextStream debug(stdout);
                debug << "Entered state : " << i << " for machine " << idMachine << endl;
            });
            ++i;
        }
    }

    // If nothing was detected
    connect(finalState, &QState::entered, this, &MegaMachine::machineEnd);

    // For conveniance
    machine.setInitialState(states.at(0));

    machine.start();
}

MegaMachine::MegaMachine(std::vector<StateDescriptor> statesDescriptions, int maxAlerts, int id, bool hasDebug, QObject *parent) : QObject(parent), ctrYes(0), ctrNo(0), maxAlerts(maxAlerts), id(id), hasDebug(hasDebug), debug(stdout)
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
    if(hasDebug)
        debug << "A Machine has stop ! Result is : yes -> " << ctrYes << " and no -> " << ctrNo << endl;

    // Emit which machine has stop
    emit stopped(id, ctrYes, ctrNo);
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

    if(hasDebug)
        debug << "Machine is running : " << this->machine.isRunning() << endl;

    emit resetMachine();
}

