#ifndef MEGAMACHINE_H
#define MEGAMACHINE_H
#include <QThread>
#include <QStateMachine>
#include <QIODevice>
#include <QTextStream>
#include <iostream>
#include <vector>
#include <QEventLoop>

class MegaMachine : public QObject
{
    Q_OBJECT
public:
    explicit MegaMachine(int nbStates, int maxAlerts, int id, QObject *parent = nullptr);

public slots:
    void yes();
    void no();
    void debugSlot();
    void readA();
    void readC();
    void readG();
    void readT();
    void readX();
    // void stop();
    void finishedSequence();
    void reset();
    void nothing();

signals:
    void A();
    void C();
    void G();
    void T();
    void X();
    void stopMachine();
    void resetMachine();
    void stopped(int stoppedMachine, int ctrYes, int ctrNo);
private:
    void buildStateMachine(int nbStates);
    int ctrYes, ctrNo;
    const int maxAlerts, id;
    std::vector<QState*> states;
    QStateMachine machine;
};

#endif // MEGAMACHINE_H
