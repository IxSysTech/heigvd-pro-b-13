#ifndef DISPATCHER_H
#define DISPATCHER_H

#include <QObject>
#include <vector>
#include <QTimer>
#include <fstream>
#include "StateMachines/utils.h"
#include "StateMachines/megamachinemanager.h"

///
/// \brief The gaParameters struct, permits to pass the parameters to the GA elegantly
///        This struct is fully dependant on the GA used but this is parameters we ask to the user on parameterwindow.ui
///
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
    int tntsize;
};

// This class is used to emit signals from the GA, in fact the GA is a lib implemented and a bit modified for the project.
// And this affects the functionment because it's not develpped with the QT Framework, so we need a light QObject just to be able to send signals.
class Emitter : public QObject {
    Q_OBJECT
signals:
    ///
    /// \brief incrementProgress announce the GUI to increment the progress bar of a certain percentage
    ///
    void incrementProgress(double);
    ///
    /// \brief stateInfo announce the GUI the current state of the GA execution
    ///
    void stateInfo(unsigned int, double, double);
};

class Dispatcher : public QObject
{
    Q_OBJECT
public:
    ///
    /// \brief Dispatcher create a Dispatcher who will create a machine and use it to analyze given sequences
    /// \param sequencesFile the filepath of sequences
    /// \param debugMachines boolean containing info wether we need to debug or not
    /// \param machineFile filepath to the machine JSON to be parsed and get a machine
    /// \param parent Parent QObject
    ///
    explicit Dispatcher(const QString& sequencesFile, bool debugMachines, const QString& logFileLocation, QObject *parent = nullptr);

    ///
    /// \brief run Run the dispatcher with the GA
    ///
    void run(unsigned int stateNb, unsigned int maxAlert, const gaParameters& gaParam);
    ///
    /// \brief runOneMachine Run the dispatcher as a Machine analyzer
    ///
    void runOneMachine();
    ///
    /// \brief parseJsonMachine
    /// \param jsonMap
    /// \return
    ///
    static std::vector<StateDescriptor>* parseJsonMachine(const QVariantMap& jsonMap);
    ///
    /// \brief parseJson
    /// \param filepath
    /// \return
    ///
    static QVariantMap parseJson(const QString& filepath);

    ~Dispatcher();
signals:
    void finished();
    // these signals are relays for signals of the GA
    void incrementProgress(double);
    void sendState(unsigned int, double, double);
    void sendAnalysis(unsigned int, unsigned int);

private:
    template <typename T>
    ///
    /// \brief objective Objective function needed by the GA, used to calculate fitness.
    ///                  This method create a machine for the given parameters and get the score of the machine as the fitness.
    /// \param x The vector of params by the GA to be tested and calculate the fitness
    /// \return vector of fitnesses
    ///
    static std::vector<T> objective(const std::vector<T>& x);

    template<typename T>
    ///
    /// \brief getMachine method to retrieve machine from GA parameters
    /// \param machine vector of float/double from the GA
    /// \return the machine in form of a vector of StateDescriptor (see utils.h)
    ///
    static std::vector<StateDescriptor> *getMachine(const std::vector<T>& machine);
    ///
    /// \brief split brief implementation of a string split
    /// \param s string to split
    /// \param delimiter the delimiter to use
    /// \return tokens vector
    ///
    static std::vector<std::string> split(const std::string& s, char delimiter);

    // All sequences we have
    std::multimap<int, std::string> *sequences;

    ///
    /// \brief initSequences read file and add the sequences and their IDs to sequences
    /// \param sequencesFile sequencesFile containing the sequences and their expected result ID
    ///
    void initSequences(const QString& sequencesFile);

    QString logFileLocation;

    static unsigned int maxAlert;
    // Info on debugging stateMachines (useful on log of StateMachines)
    static bool debugMachines;

    // Sequences being analyzed at a time T
    static std::multimap<std::string, bool> *currentSequences;

    ///
    /// \brief convert float -> uint32_t useful when getting binary representation of a float
    /// \return uint32_t
    ///
    static uint32_t convert(float);

    ///
    /// \brief convert double -> uint64_t useful when getting binary representation of a float
    /// \return uint64_t
    ///
    static uint64_t convert(double);

public slots:
    ///
    /// \brief relay incrementProgress
    ///
    void relay(double);
    ///
    /// \brief relayState stateInfo
    ///
    void relayState(unsigned int, double, double);
};

#endif // DISPATCHER_H
