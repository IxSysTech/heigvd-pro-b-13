#ifndef UTILS_H
#define UTILS_H
#include <vector>

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
