#include "OnSceneState.h"
#include "ResolvedState.h"
#include "EscalatedState.h"
#include "ResponseTask.h"

OnSceneState* OnSceneState::instance() {
    static OnSceneState instance;
    return &instance;
}
void OnSceneState::resolve(ResponseTask* task) {
    task->setState(ResolvedState::instance());
}
void OnSceneState::escalate(ResponseTask* task) {
    task->setState(EscalatedState::instance());
}