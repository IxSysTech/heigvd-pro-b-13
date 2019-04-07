#ifndef TASK_H
#define TASK_H

#include <QObject>
#include "megamachine.h"
#include "emitteracgt.h"

class Task : public QObject
{
    Q_OBJECT
public:
    explicit Task(QObject *parent = 0) : QObject(parent) {}

public slots:
    void run();

signals:
    void finished();
};

#endif // TASK_H
