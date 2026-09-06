#ifndef ENROUTESTATE_H
#define ENROUTESTATE_H
#include "TaskState.h"

class EnRouteState : public TaskState {
public:
    static EnRouteState* instance();
    void arriveOnScene(ResponseTask* task) override;
    void escalate(ResponseTask* task) override;
    std::string getName() const override { return "EnRoute"; }
};
#endif