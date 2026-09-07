#include "EnRouteState.h"
#include "OnSceneState.h"
#include "EscalatedState.h"
#include "ResponseTask.h"

EnRouteState* EnRouteState::instance() {
    static EnRouteState instance;
    return &instance;
}
void EnRouteState::arriveOnScene(ResponseTask* task) {
    task->setState(OnSceneState::instance());
}
void EnRouteState::escalate(ResponseTask* task) {
    task->setState(EscalatedState::instance());
}