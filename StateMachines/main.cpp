#include <QCoreApplication>
#include "megamachine.h"

int main(int argc, char *argv[])
{
    //QCoreApplication a(argc, argv);

        QString filename = "../StateMachines/machine.scxml";
        MegaMachine megamachine(&filename);

        return 0;

    //return a.exec();
}
