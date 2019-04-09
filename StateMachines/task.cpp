#include "task.h"
#include <QTextStream>

Task::Task(QObject * parent) : QObject(parent)
{
    //manager = new MegaMachineManager(this);
    machine = new MegaMachine(3, 1, this);
}

void Task::run()
{
       QTextStream qin(stdin);
       QTextStream out(stdout);

       //manager->runMachines();

       emitterACGT *theEmitter = new emitterACGT("ACGTGCA");

       //Test
       //machines.push_back(new MegaMachine(3, 1 , this));
       //MegaMachine *machine = machines.at(0);

       //TODO: faire ces connects pour chaque machine
       connect(theEmitter, SIGNAL(readA()),machine,SLOT(readA()));
       connect(theEmitter, SIGNAL(readC()),machine,SLOT(readC()));
       connect(theEmitter, SIGNAL(readG()),machine,SLOT(readG()));
       connect(theEmitter, SIGNAL(readT()),machine,SLOT(readT()));

       connect(machine, SIGNAL(stopped()), this, SLOT(stop()));
       //QTextStream out(stdout);
       out << machine->machine.isRunning();
       theEmitter->beginAnalysis();

       emit finished();
}
