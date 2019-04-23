#ifndef MEGAMACHINEMANAGER_H
#define MEGAMACHINEMANAGER_H

#include <QObject>
#include <QVector>
#include "emitteracgt.h"
#include "megamachine.h"

class MegaMachineManager : public QObject
{
    Q_OBJECT
public:
    explicit MegaMachineManager(QObject *parent = nullptr);

signals:
    void finished();
public slots:
    void runMachines();
    void stop(int stoppedMachine, int ctrYes, int ctrNo);
    void nextSequence();
private:
    QVector<MegaMachine*> machines;
    emitterACGT *theEmitter;
    QVector<int> scores;
};

#endif // MEGAMACHINEMANAGER_H
