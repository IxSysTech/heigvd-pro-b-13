#include "megamachinemanager.h"

MegaMachineManager::MegaMachineManager(QObject *parent) : QObject(parent)
{
    //TODO: Créer les machines en regardant le vector de vector contenat les params des machines.
    // Multithread ici
    machines.push_back(new MegaMachine(10, 1, this));
}

void MegaMachineManager::runMachines() {

    emitterACGT *theEmitter = new emitterACGT("ACGTGCXXXA");

    //Test
    MegaMachine *machine = machines.at(0);

    //TODO: faire ces connects pour chaque machine
    connect(theEmitter, SIGNAL(readA()),machine,SLOT(readA()));
    connect(theEmitter, SIGNAL(readC()),machine,SLOT(readC()));
    connect(theEmitter, SIGNAL(readG()),machine,SLOT(readG()));
    connect(theEmitter, SIGNAL(readT()),machine,SLOT(readT()));
    connect(theEmitter, SIGNAL(readX()),machine,SLOT(readX()));

    connect(machine, SIGNAL(stopped(int)), this, SLOT(stop(int)));
    QTextStream out(stdout);
    //out << machine->machine.isRunning();
    theEmitter->beginAnalysis();
    emit finished();
}

void MegaMachineManager::stop(int stoppedMachine){
    QTextStream out(stdout);
    out << "One of my machine has stop, we should disconnect events for the machine : " << stoppedMachine << endl;
}
