#include "EscalatedState.h"
#include "ResolvedState.h"
#include "ResponseTask.h"

EscalatedState* EscalatedState::instance() {
    static EscalatedState instance;
    return &instance;
}
void EscalatedState::resolve(ResponseTask* task) {
    task->setState(ResolvedState::instance());
}