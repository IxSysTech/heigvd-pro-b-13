#include "megamachine.h"

MegaMachine::MegaMachine(const QString *filename, QObject *parent) : QObject(parent)
{
    QTextStream errs(stderr, QIODevice::WriteOnly);
    QTextStream out(stdout, QIODevice::WriteOnly);

    this->machine = QScxmlStateMachine::fromFile(*filename);
    if (!machine->parseErrors().isEmpty()) {
        const auto errors = machine->parseErrors();
        for (const QScxmlError &error : errors) {
            errs << error.toString();
        }
    }

    machine->connectToState("Init", [](bool active) {
        QTextStream out(stdout, QIODevice::WriteOnly);
        out << (active ? "entered" : "exited") << "the s1 state";});
    machine->connectToState("s1", [](bool active) {
        QTextStream out(stdout, QIODevice::WriteOnly);
        out << (active ? "s2" : "exited") << "the s1 state";});
    machine->connectToState("s3", [](bool active) {
        QTextStream out(stdout, QIODevice::WriteOnly);
        out << (active ? "entered" : "exited") << "the s1 state";});
    machine->connectToState("s4", [](bool active) {
        QTextStream out(stdout, QIODevice::WriteOnly);
        out << (active ? "entered" : "exited") << "the s1 state";});

    bool initOk = machine->init();
    if (!initOk)
        errs << "Erreur Init" << endl;
    machine->start();
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

