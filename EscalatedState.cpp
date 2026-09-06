#include "EscalatedState.h"
// TODO: #include "ResolvedState.h", "ResponseTask.h"

EscalatedState* EscalatedState::instance() {
    static EscalatedState instance;
    return &instance;
}

void EscalatedState::resolve(ResponseTask* /*task*/) {
    // TODO: task->setState(ResolvedState::instance());
}
