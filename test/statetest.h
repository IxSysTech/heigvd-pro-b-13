#ifndef STATETEST_H
#define STATETEST_H

#include <QObject>
#include <QStateMachine>
#include <QVector>
#include <qglobal.h>
#include <iostream>
#include "emitteracgt.h"

class StateTest : public QObject
{
    Q_OBJECT
public:
    explicit StateTest(int nbMachines, int nbStates, QObject* senderObj,  QObject *parent = nullptr);
    void runMachines();
signals:
public slots:
    void getStates(int state);
private:
    QVector<QStateMachine*> testMachine;
    QObject* nucleicAnounce;
};

#endif // STATETEST_H
