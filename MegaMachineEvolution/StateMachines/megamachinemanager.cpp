#include "megamachinemanager.h"

MegaMachineManager::MegaMachineManager(std::multimap<std::string, bool> *sequences, std::vector<std::vector<StateDescriptor>> machinesGiven, std::vector<int> *scoresToGive, QObject *parent) : QObject(parent)
{
    this->sequences = sequences;
    int nbMachines = machinesGiven.size();
    for(int i = 0; i < nbMachines; ++i) {
        machines.push_back(new MegaMachine(machinesGiven.at(i), 2, i, this));
    }
    scores = scoresToGive;
}

void MegaMachineManager::runMachines() {    
    theEmitter = new emitterACGT(this->sequences);
    connect(theEmitter, SIGNAL(nextSequence()), this, SLOT(nextSequence()));
    //Test
    for(MegaMachine *machine : machines) {
        //TODO: faire ces connects pour chaque machine
        connect(theEmitter, SIGNAL(readA()),machine,SLOT(readA()));
        connect(theEmitter, SIGNAL(readC()),machine,SLOT(readC()));
        connect(theEmitter, SIGNAL(readG()),machine,SLOT(readG()));
        connect(theEmitter, SIGNAL(readT()),machine,SLOT(readT()));
        connect(theEmitter, SIGNAL(readX()),machine,SLOT(readX()));

        connect(theEmitter, SIGNAL(finishedSequence()), machine, SLOT(finishedSequence()));

        connect(machine, SIGNAL(stopped(int,int,int)), this, SLOT(stop(int,int,int)));
    }
    QTextStream out(stdout);
    theEmitter->beginAnalysis();
    int count = 0;
    for(int i : *scores) {
        out << "Score : " << i << " for machine : " << count++ << endl;
    }
    emit finished();
}

void MegaMachineManager::stop(int stoppedMachine, int ctrYes, int ctrNo){
    QTextStream out(stdout);
    out << "One of my machine has stop, we should disconnect events for the machine : " << stoppedMachine << endl;
    /*disconnect(theEmitter, SIGNAL(readA()),machines.at(stoppedMachine),SLOT(readA()));
    disconnect(theEmitter, SIGNAL(readC()),machines.at(stoppedMachine),SLOT(readC()));
    disconnect(theEmitter, SIGNAL(readG()),machines.at(stoppedMachine),SLOT(readG()));
    disconnect(theEmitter, SIGNAL(readT()),machines.at(stoppedMachine),SLOT(readT()));
    disconnect(theEmitter, SIGNAL(readX()),machines.at(stoppedMachine),SLOT(readX()));
    disconnect(theEmitter, SIGNAL(finished()), machines.at(stoppedMachine), SLOT(stop()));*/

    // TODO: demander commant gérer les cas où le maxAlert n'est pas atteint (mais que ctrYes et ctrNo sont incrémentées)
    // Pour le moment : on admet que c'est comme si rien détecter (0)

    if(ctrYes != ctrNo)
        if((ctrYes > ctrNo ? true : false) == theEmitter->getCurrentResult())
            ++(*scores)[stoppedMachine];
}

void MegaMachineManager::nextSequence() {
    QTextStream out(stdout);
    out << "Resetting the machines for next sequence ..." << endl;
    out.flush();
    for(MegaMachine *machine : machines) {
        machine->reset();
    }
}
