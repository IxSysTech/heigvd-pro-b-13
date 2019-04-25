#ifndef MEGAMACHINE_H
#define MEGAMACHINE_H
#include <QThread>
#include <QStateMachine>
#include <QIODevice>
#include <QTextStream>
#include <iostream>
#include <vector>
#include <set>
#include <QEventLoop>
#include "utils.h"

class MegaMachine : public QObject
{
    Q_OBJECT
public:
    ///
    /// \brief MegaMachine - Machine to analyze sequences with the emitter from MegamMachineManager
    /// \param nbStates - Number of states for the construction of the machine
    /// \param maxAlerts - When a counter (Yes or No) atteign maxAlerts it stop and announce it to MegaMachineManager
    /// \param id - The ID of the constructed machine
    /// \param parent - parent QObject
    ///
    explicit MegaMachine(int nbStates, int maxAlerts, int id, QObject *parent = nullptr);
    explicit MegaMachine(std::vector<StateDescriptor> states, int maxAlerts, int id, QObject *parent = nullptr);
public slots:
    void yes();
    void no();
    void debugSlot();
    void readA();
    void readC();
    void readG();
    void readT();
    void readX();
    void finishedSequence();
    void reset();
    void machineEnd();
signals:
    void A();
    void C();
    void G();
    void T();
    void X();
    ///
    /// \brief stopMachine - signal permitting to go to finalState of the machine
    ///
    void stopMachine();
    ///
    /// \brief resetMachine - signal to reset machine (go to initial state if on finalState)
    ///
    void resetMachine();
    ///
    /// \brief stopped - Signal announcing the machine has stop
    /// \param stoppedMachine - id of the stopped machine
    /// \param ctrYes - state of the counter of Yes when stopped
    /// \param ctrNo - state of the counter of No when stopped
    ///
    void stopped(int stoppedMachine, int ctrYes, int ctrNo);
private:
    void buildStateMachine(int nbStates);
    ///
    /// \brief buildStateMachine - build a state machine withe the given parameters
    /// \param states - construct machine of the size of vector and the states with the StateDescriptor
    ///
    void buildStateMachine(std::vector<StateDescriptor> states);
    // Counters storing Yes, No of the machine
    int ctrYes, ctrNo;
    // Id of the machine and maxAlerts for the machine
    const int maxAlerts, id;
    // Storing the states of the constructed machine
    std::vector<QState*> states;
    // The actual State Machine
    QStateMachine machine;
};

#endif // MEGAMACHINE_H
