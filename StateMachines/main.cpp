#include <QCoreApplication>
#include "megamachine.h"
#include "emitteracgt.h"

int main(int argc, char *argv[])
{
        // QCoreApplication a(argc, argv);
        QTextStream out(stdout, QIODevice::WriteOnly);

        QString filename = "./machine.scxml";
        MegaMachine megamachine(&filename);

        QStringList test = megamachine.machine->activeStateNames();
        for(QString temp : test){
            out << temp;
        }
        out << megamachine.machine->isRunning() << endl;

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
        return 0;

    //return a.exec();
}
