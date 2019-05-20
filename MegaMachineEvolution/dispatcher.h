#ifndef DISPATCHER_H
#define DISPATCHER_H

#include <QObject>
#include <vector>
#include <QTimer>
#include <fstream>
#include "StateMachines/utils.h"
#include "StateMachines/megamachinemanager.h"

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
    void stateInfo(unsigned int, double, double);
};

class Dispatcher : public QObject
{
    Q_OBJECT
public:
    explicit Dispatcher(unsigned int stateNb, unsigned int maxAlert, const gaParameters& gaParam, const QString& filePath, bool debugMachines, QObject *parent = nullptr);
    void run();
    template <typename T>
    static std::vector<T> objective(const std::vector<T>& x);
    ~Dispatcher();
signals:
    void finished();
    void incrementProgress(double);
    void sendState(unsigned int, double, double);
    void sendAnalysis(unsigned int, unsigned int);


private:
    template<typename T>
    static std::vector<StateDescriptor> *getMachine(const std::vector<T>& machine);
    static std::vector<std::string> split(const std::string& s, char delimiter);

    std::multimap<int, std::string> *sequences;
    void initSequences(const QString& filePath);

    const unsigned int stateNb;
    gaParameters gaParam;

    static unsigned int maxAlert;
    static bool debugMachines;

    static std::multimap<std::string, bool> *currentSequences;

    static uint32_t convert(float);
    static uint64_t convert(double);

public slots:
    void relay(double);
    void relayState(unsigned int, double, double);
};

#endif // DISPATCHER_H
