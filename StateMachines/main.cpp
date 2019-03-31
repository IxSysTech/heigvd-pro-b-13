#include <QCoreApplication>
#include "megamachine.h"

int main(int argc, char *argv[])
{
    //QCoreApplication a(argc, argv);
        QTextStream out(stdout, QIODevice::WriteOnly);

        QString filename = "./machine.scxml";
        MegaMachine megamachine(&filename);

        out << "oo";

        return 0;

    //return a.exec();
}
