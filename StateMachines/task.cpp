#include "task.h"

void Task::run()
{
    QTextStream out(stdout, QIODevice::WriteOnly);

    MegaMachine megamachine;

    out << megamachine.machine.isRunning() << endl;
    out << endl;

    QString sequence = "ACGTAGCTTTCAAAGCTAGCATGGCA";
    emitterACGT emitter(sequence);

    QObject::connect(&emitter,SIGNAL(readA()),
                     &megamachine, SLOT(readA()));
    QObject::connect(&emitter,SIGNAL(readC()),
                     &megamachine, SLOT(readC()));
    QObject::connect(&emitter,SIGNAL(readG()),
                     &megamachine, SLOT(readG()));
    QObject::connect(&emitter,SIGNAL(readT()),
                     &megamachine, SLOT(readT()));

    emitter.beginAnalysis();

    emit finished();
}
