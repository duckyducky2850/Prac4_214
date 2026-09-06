#include "OnSceneState.h"
// TODO: #include "ResolvedState.h", "EscalatedState.h", "ResponseTask.h"

OnSceneState* OnSceneState::instance() {
    static OnSceneState instance;
    return &instance;
}

void OnSceneState::resolve(ResponseTask* /*task*/) {
    // TODO: task->setState(ResolvedState::instance());
}

void OnSceneState::escalate(ResponseTask* /*task*/) {
    // TODO: task->setState(EscalatedState::instance());
}
