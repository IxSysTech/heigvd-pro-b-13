#ifndef UTILS_H
#define UTILS_H
#include <vector>

///
/// \brief The StateDescriptor struct - defines a structure for describing States in a megamachine
///        permit to communicate to magamachinemanager and megamachine to create a FSM.
///        This create the first state as initial and create a "final" state to stop the machine.
///
struct StateDescriptor {
    enum {
        NO,
        YES,
        NOTHING
    } stateAction;

    struct Transition {
        typedef enum {
            A, C, G, T, X
        } signalType;
        signalType signal;
        int destinationState;
    };

    std::vector<Transition> transitions;
};
#endif // UTILS_H
