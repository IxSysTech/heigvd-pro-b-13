#ifndef STATETEST_H
#define STATETEST_H

#include <QObject>
#include <QStateMachine>
#include <QVector>
#include <qglobal.h>
#include <string>
#include <iostream>
#include "emitteracgt.h"
#include "handler.h"
#include <QScxmlStateMachine>

class StateTest : public QObject
{
    Q_OBJECT
public:
    explicit StateTest(int nbMachines, int nbStates, QObject* senderObj, handler* theHandler, QObject *parent = nullptr);
    void runMachines();
private:
    QVector<QStateMachine*> testMachine;
    QObject* nucleicAnounce;
};

#endif // STATETEST_H
