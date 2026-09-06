#ifndef DISPATCHEDSTATE_H
#define DISPATCHEDSTATE_H
#include "TaskState.h"


class DispatchedState : public TaskState {
public:
    static DispatchedState* instance();
    void startTravel(ResponseTask* task) override;
    std::string getName() const override { return "Dispatched"; }
};
#endif