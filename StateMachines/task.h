#ifndef TASK_H
#define TASK_H

#include <QObject>
#include "emitteracgt.h"
#include "megamachinemanager.h"

class Task : public QObject
{
    Q_OBJECT
public:
    explicit Task(QObject *parent = 0);

signals:
    void finished();

public slots:
    void run();
private:
    MegaMachineManager *manager;
    MegaMachine *machine;
};

#endif // TASK_H
