#ifndef ONSCENESTATE_H
#define ONSCENESTATE_H
#include "TaskState.h"

class OnSceneState : public TaskState {
public:
    static OnSceneState* instance();
    void resolve(ResponseTask* task) override;
    void escalate(ResponseTask* task) override;
    std::string getName() const override { return "OnScene"; }
};
#endif
