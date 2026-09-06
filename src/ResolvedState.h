#ifndef RESOLVEDSTATE_H
#define RESOLVEDSTATE_H
#include "TaskState.h"

class ResolvedState : public TaskState {
public:
    static ResolvedState* instance();
    std::string getName() const override { return "Resolved"; }
    // No overrides — every transition out of Resolved is invalid (terminal state).
};
#endif
