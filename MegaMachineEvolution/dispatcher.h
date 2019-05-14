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


class Dispatcher : public QObject
{
    Q_OBJECT
public:
    explicit Dispatcher(int crossMode, int selectMode, int mutMode, double crossOverRate, double mutationRate, double selectivePressureRate, double toleranceRate, unsigned int stateNb, unsigned int popsize, unsigned int maxAlert, unsigned int genNb,  QObject *parent = nullptr);
    void run();
    template <typename T>
    static std::vector<T> objective(const std::vector<T>& x);
signals:
    void finished();
private:
    static std::vector<std::string> split(const std::string& s, char delimiter);
    static std::multimap<std::string, bool> *sequences;
    static void initSequences();

    double crossOverRate, mutationRate, selectivePressureRate, toleranceRate;
    unsigned int stateNb, popsize, genNb;
    int crossMode, selectMode, mutMode;
};

#endif // DISPATCHER_H
