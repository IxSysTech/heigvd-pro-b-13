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
    void A();
    void C();
    void G();
    void T();
    void finished();

private:
    void buildStateMachine();
    QStateMachine machine;

public slots:
    void run();
    void runS1();
    void runS2();
    void runS3();
    void debugSlot();
};

#endif // TASK_H
