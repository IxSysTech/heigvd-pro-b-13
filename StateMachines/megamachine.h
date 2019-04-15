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
    explicit MegaMachine(int nbStates, int maxAlerts, QObject *parent = nullptr);

public slots:
    void yes();
    void no();
    void debugSlot();
    void readA();
    void readC();
    void readG();
    void readT();
    void readX();
    void stop();

signals:
    void run();
    void A();
    void C();
    void G();
    void T();
    void X();
    void stopped();
private:
    void buildStateMachine(int nbStates);
    int ctrYes, ctrNo;
    const int maxAlerts;

    std::vector<QState*> states;
public:
    QStateMachine machine;
};

#endif // MEGAMACHINE_H
