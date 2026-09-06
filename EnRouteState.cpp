#include "EnRouteState.h"
// TODO: #include "OnSceneState.h", "EscalatedState.h", "ResponseTask.h"

EnRouteState* EnRouteState::instance() {
    static EnRouteState instance;
    return &instance;
}

void EnRouteState::arriveOnScene(ResponseTask* /*task*/) {
    // TODO: task->setState(OnSceneState::instance());
}

void EnRouteState::escalate(ResponseTask* /*task*/) {
    // TODO: task->setState(EscalatedState::instance());
}
