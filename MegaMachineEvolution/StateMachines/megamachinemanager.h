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
    /// \brief MegaMachineManager
    /// \param sequences
    /// \param machinesGiven
    /// \param scoresToGive
    /// \param maxAlerts
    /// \param parent
    ///
    explicit MegaMachineManager(std::multimap<std::string, bool> *sequences, std::vector<std::vector<StateDescriptor>> machinesGiven, std::vector<int> *scoresToGive,unsigned int maxAlerts, bool hasDebug, QObject *parent = nullptr);

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
