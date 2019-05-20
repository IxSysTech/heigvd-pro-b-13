#include "megamachinemanager.h"

MegaMachineManager::MegaMachineManager(std::multimap<std::string, bool> *sequences, std::vector<std::vector<StateDescriptor>> machinesGiven, std::vector<int> *scoresToGive,unsigned int maxAlerts,bool hasDebug,  QObject *parent) : debug(stdout), hasDebug(hasDebug), QObject(parent)
{
    this->sequences = sequences;
    int nbMachines = machinesGiven.size();
    for(int i = 0; i < nbMachines; ++i) {
        machines.push_back(new MegaMachine(machinesGiven.at(i), maxAlerts, i, hasDebug, this));
    }
    scores = scoresToGive;
}

void MegaMachineManager::runMachines() {    
    theEmitter = new emitterACGT(this->sequences);
    connect(theEmitter, SIGNAL(nextSequence()), this, SLOT(nextSequence()));

    for(MegaMachine *machine : machines) {
        connect(theEmitter, SIGNAL(readA()),machine,SLOT(readA()));
        connect(theEmitter, SIGNAL(readC()),machine,SLOT(readC()));
        connect(theEmitter, SIGNAL(readG()),machine,SLOT(readG()));
        connect(theEmitter, SIGNAL(readT()),machine,SLOT(readT()));
        connect(theEmitter, SIGNAL(readX()),machine,SLOT(readX()));

        connect(theEmitter, SIGNAL(finishedSequence()), machine, SLOT(finishedSequence()));

        connect(machine, SIGNAL(stopped(int,int,int)), this, SLOT(stop(int,int,int)));
    }

    theEmitter->beginAnalysis();
    int count = 0;

    if(hasDebug)
        for(int i : *scores)
            debug << "Score : " << i << " for machine : " << count++ << endl;

    emit finished();
}

void MegaMachineManager::stop(int stoppedMachine, int ctrYes, int ctrNo){
    if(hasDebug)
        debug << "The machine : " << stoppedMachine << "has stop" << endl;

    if(ctrYes != ctrNo)
            if((ctrYes > ctrNo ? true : false) == theEmitter->getCurrentResult())
                ++(*scores)[stoppedMachine];
}

void MegaMachineManager::nextSequence() {
    if(hasDebug)
        debug << "Resetting the machines for next sequence ..." << endl;

    for(MegaMachine *machine : machines) {
        machine->reset();
    }
}
