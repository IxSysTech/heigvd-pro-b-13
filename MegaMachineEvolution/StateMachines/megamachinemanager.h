#ifndef MEGAMACHINEMANAGER_H
#define MEGAMACHINEMANAGER_H

#include <QObject>
#include <QVector>
#include "emitteracgt.h"
#include "megamachine.h"

class MegaMachineManager : public QObject
{
    Q_OBJECT
public:
    ///
    /// \brief MegaMachineManager Manager for the MegaMachine, in fact this serve to analyze sequences and can manage more machines than one for optimisation.
    ///                           This manager permit to create MegaMachines and serve sequences to them.
    /// \param sequences multimap of the sequences to analyze, this will create an emitterACGT for it
    /// \param machinesGiven The machines that the manager need to create to analyze the sequences
    /// \param scoresToGive The vector of scores that we will use to store the score of each machine (in order)
    /// \param maxAlerts The maxAlerts for ctrYes, ctrNo (see MegaMachine)
    /// \param parent Parent QObject
    ///
    explicit MegaMachineManager(std::multimap<std::string, bool> *sequences, std::vector<std::vector<StateDescriptor>> machinesGiven, std::vector<int> *scoresToGive,unsigned int maxAlerts, bool hasDebug, QObject *parent = nullptr);
    ~MegaMachineManager();
signals:
    ///
    /// \brief finished - announce finished treatment, exit the event loop
    ///
    void finished();
public slots:
    ///
    /// \brief runMachines - Create an emitter and connect it to each machine created.
    ///
    void runMachines();
    ///
    /// \brief stop - Slot of a machine when announcing a finished treatment
    /// \param stoppedMachine - Id of the machine stopped
    /// \param ctrYes - State of the counter of Yes when stopped
    /// \param ctrNo - State of the counter of No when stopped
    ///
    void stop(int stoppedMachine, int ctrYes, int ctrNo);
    ///
    /// \brief nextSequence - Slot when the emitter announce a next sequence to reset all the machines (stopped before)
    ///
    void nextSequence();
private:
    ///
    /// \brief machines - Storing machines created
    ///
    QVector<MegaMachine*> machines;
    ///
    /// \brief theEmitter - Emitter for the sequences to treat
    ///
    emitterACGT *theEmitter;
    ///
    /// \brief scores - Storing the scores of each machine, calculated from the states of the counter when stopped
    ///
    std::vector<int> *scores;

    std::multimap<std::string, bool> *sequences;

    bool hasDebug;

    QTextStream debug;
};

#endif // MEGAMACHINEMANAGER_H
