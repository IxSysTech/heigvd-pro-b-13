#include "task.h"
#include <QTextStream>

Task::Task(QObject * parent) : QObject(parent)
{
    machine = new MegaMachine(this);
}

void Task::run()
{
       QTextStream qin(stdin);
       QTextStream out(stdout);

       emitterACGT *theEmitter = new emitterACGT("ACGTGCA");

       connect(theEmitter, SIGNAL(readA()),machine,SLOT(readA()));
       connect(theEmitter, SIGNAL(readC()),machine,SLOT(readC()));
       connect(theEmitter, SIGNAL(readG()),machine,SLOT(readG()));
       connect(theEmitter, SIGNAL(readT()),machine,SLOT(readT()));

       theEmitter->beginAnalysis();

       emit finished();
}
