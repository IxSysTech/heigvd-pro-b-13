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
    explicit MegaMachine(int nbStates, QObject *parent = nullptr);

public slots:
    void runS1();
    void runS2();
    void runS3();
    void debugSlot();
    void readA();
    void readC();
    void readG();
    void readT();

signals:
    void run();
    void A();
    void C();
    void G();
    void T();
private:
    void buildStateMachine(int nbStates);
    QStateMachine machine;
    std::vector<QState*> states;
};

#endif // MEGAMACHINE_H
