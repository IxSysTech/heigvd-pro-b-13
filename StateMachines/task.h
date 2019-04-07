#ifndef TASK_H
#define TASK_H

#include <QObject>
#include "megamachine.h"
#include "emitteracgt.h"

class Task : public QObject
{
    Q_OBJECT
public:
    explicit Task(QObject *parent = 0);

signals:
    void readA();
    void readC();
    void readG();
    void readT();
    void finished();

public slots:
    void run();
private:
    MegaMachine *machine;
};

#endif // TASK_H
