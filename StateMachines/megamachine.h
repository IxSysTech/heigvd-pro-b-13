#ifndef MEGAMACHINE_H
#define MEGAMACHINE_H
#include <QStateMachine>
#include <QIODevice>
#include <QTextStream>
#include <iostream>
#include <vector>

class MegaMachine : public QObject
{
    Q_OBJECT
public:
    explicit MegaMachine(QObject *parent = nullptr);
    QStateMachine machine;
    std::vector<QState*> states;
public slots:
    void readA();
    void readC();
    void readG();
    void readT();

signals:
    void A();
    void C();
    void G();
    void T();
};

#endif // MEGAMACHINE_H
