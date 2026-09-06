#include "DispatchedState.h"
// TODO: #include "EnRouteState.h" and "ResponseTask.h" once implemented

DispatchedState* DispatchedState::instance() {
    static DispatchedState instance;
    return &instance;
}

void DispatchedState::startTravel(ResponseTask* /*task*/) {
    // TODO: task->setState(EnRouteState::instance());
}
