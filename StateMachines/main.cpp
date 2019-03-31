#include <QCoreApplication>
#include "megamachine.h"
#include "emitteracgt.h"

int main(int argc, char *argv[])
{
    //QCoreApplication a(argc, argv);

        QString filename = "../StateMachines/machine.scxml";
        MegaMachine megamachine(&filename);

        QString sequence = "A";
        emitterACGT emitter(sequence);

        QObject::connect(&emitter,SIGNAL(readA()),
                         &megamachine, SLOT(readA()));

        emitter.beginAnalysis();
        return 0;

    //return a.exec();
}
