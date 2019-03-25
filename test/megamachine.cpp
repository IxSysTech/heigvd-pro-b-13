#include "megamachine.h"

MegaMachine::MegaMachine(QString filenmae, QObject *parent) : QObject(parent)
{
    auto *stateMachine = QScxmlStateMachine::fromFile(filenmae);
    stateMachine->start();
}
