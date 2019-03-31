#include "megamachine.h"

MegaMachine::MegaMachine(QString *filename, QObject *parent) : QObject(parent)
{
    this->machine = QScxmlStateMachine::fromFile(*filename);
    this->machine->init();
    std::cout << this->machine->isRunning() << std::endl;
    this->machine->start();
    std::cout << this->machine->isRunning() << std::endl;
}
