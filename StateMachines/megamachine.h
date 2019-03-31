#ifndef MEGAMACHINE_H
#define MEGAMACHINE_H
#include <QScxmlStateMachine>
#include <QIODevice>
#include <QTextStream>
#include <iostream>

class MegaMachine : public QObject
{
    Q_OBJECT
public:
    explicit MegaMachine(const QString *filename, QObject *parent = nullptr);
    QScxmlStateMachine *machine;
public slots:
    void readA();
    void readC();
    void readG();
    void readT();
};

#endif // MEGAMACHINE_H
