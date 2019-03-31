#include "megamachine.h"

MegaMachine::MegaMachine(const QString *filename, QObject *parent) : QObject(parent)
{
    QScxmlStateMachine *machine = QScxmlStateMachine::fromFile(*filename);
    if (!machine->parseErrors().isEmpty()) {
        QTextStream errs(stderr, QIODevice::WriteOnly);
        const auto errors = machine->parseErrors();
        for (const QScxmlError &error : errors) {
            errs << error.toString();
        }
    }
}

void MegaMachine::readA(){
    this->machine->submitEvent("readA");
}
void MegaMachine::readC(){
    this->machine->submitEvent("readC");
}
void MegaMachine::readG(){
    this->machine->submitEvent("readG");
}
void MegaMachine::readT(){
    this->machine->submitEvent("readT");
}

