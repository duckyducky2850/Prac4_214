#ifndef ESCALATEDSTATE_H
#define ESCALATEDSTATE_H
#include "TaskState.h"

class EscalatedState : public TaskState {
public:
    static EscalatedState* instance();
    void resolve(ResponseTask* task) override;
    std::string getName() const override { return "Escalated"; }
};
#endif