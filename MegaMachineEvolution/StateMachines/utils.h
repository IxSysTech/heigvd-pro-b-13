#ifndef UTILS_H
#define UTILS_H
#include <vector>

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
    };

    std::vector<Transition> transitions;
};
#endif // UTILS_H
