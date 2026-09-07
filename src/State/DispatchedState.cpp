#include "DispatchedState.h"
#include "EnRouteState.h"
#include "ResponseTask.h"

DispatchedState* DispatchedState::instance() {
    static DispatchedState instance;
    return &instance;
}
void DispatchedState::startTravel(ResponseTask* task) {
    task->setState(EnRouteState::instance());
}