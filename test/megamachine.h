#ifndef MEGAMACHINE_H
#define MEGAMACHINE_H
#include <QScxmlStateMachine>
#include <iostream>

class MegaMachine : public QObject
{
    Q_OBJECT
public:
    explicit MegaMachine(QString *filename, QObject *parent = nullptr);
    QScxmlStateMachine *machine;

signals:

public slots:
};

#endif // MEGAMACHINE_H
