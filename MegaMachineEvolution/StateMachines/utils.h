#ifndef UTILS_H
#define UTILS_H
#include <vector>
#include <QJsonObject>
#include <QJsonArray>

///
/// \brief The StateDescriptor struct - defines a structure for describing States in a megamachine
///        permit to communicate to magamachinemanager and megamachine to create a FSM.
///        This create the first state as initial and create a "final" state to stop the machine.
///
struct StateDescriptor {
    typedef enum {
        NOTHING,
        NO,
        YES
    } stateActionType;
    stateActionType stateAction;

    struct Transition {
        typedef enum {
            A, C, G, T, X, Count = 5
        } signalType;
        signalType signal;
        unsigned int destinationState;

        Transition(signalType signal, unsigned int destinationState) : signal(signal), destinationState(destinationState) {}
        ///
        /// \brief toJson method to retrieve a JSON representation of a Transition struct
        /// \return a QJsonObject of Transition
        ///
        QJsonObject toJson() {
            return {
                {"signal", signal},
                {"destinationState", static_cast<int>(destinationState)}
            };
        }
    };

    std::vector<Transition> transitions;

    ///
    /// \brief toJson method to retrieve a JSON representation of a StateDescriptor struct
    /// \return a QJsonObject of StateDescriptor
    ///
    QJsonObject toJson() {
        QJsonArray jsontr;

        for(Transition t : transitions)
            jsontr.push_back(t.toJson());

        return {
            {"stateAction", stateAction},
            {"transitions", jsontr}
        };
    }
};
#endif // UTILS_H
