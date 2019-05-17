#ifndef DISPATCHER_H
#define DISPATCHER_H

#include <QObject>
#include <vector>
#include <QTimer>
#include <fstream>
#include "StateMachines/utils.h"
#include "StateMachines/megamachinemanager.h"

union converter {
    float value;
    uint32_t converted;
};

struct gaParameters {
    int mutMode;
    int crossMode;
    int selectMode;
    float crossOverRate;
    float mutationRate;
    float selectivePressureRate;
    int popsize;
    int genNb;
    int elitpop;
    float tolRate;
};

class Emitter : public QObject {
    Q_OBJECT
signals:
    void incrementProgress(double);
};

class Dispatcher : public QObject
{
    Q_OBJECT
public:
    explicit Dispatcher(unsigned int stateNb, unsigned int maxAlert, const gaParameters& gaParam, QObject *parent = nullptr);
    void run();
    template <typename T>
    static std::vector<T> objective(const std::vector<T>& x);
signals:
    void finished();
    void incrementProgress(double);
private:
    static std::vector<std::string> split(const std::string& s, char delimiter);
    static std::multimap<std::string, bool> *sequences;
    static void initSequences();

    const unsigned int stateNb;
    gaParameters gaParam;
    static unsigned int maxAlert;
public slots:
    void relay(double);
};

#endif // DISPATCHER_H
