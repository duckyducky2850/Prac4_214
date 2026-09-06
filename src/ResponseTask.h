#ifndef RESPONSETASK_H
#define RESPONSETASK_H

#include "IncidentComponent.h"

class TaskState;

// ResponseTask (GoF Composite: Leaf). A single unit of work with no
// children. Also the object whose lifecycle is managed by the State
// pattern (see TaskState / ConcreteStates).
class ResponseTask : public IncidentComponent {
private:
    std::string name;
    int severity;      // 1 (low) .. 10 (critical)
    int effort;         // base effort in minutes
    TaskState* state;   // NON-owning: states are singletons, never deleted here

public:
    ResponseTask(std::string name, int severity, int effort);
    ~ResponseTask() override = default;

    // IncidentComponent interface
    int getSeverityScore() const override;
    int getEstimatedEffort() const override;
    std::string getName() const override;
    void report() const override;
    Iterator* createIterator(IteratorType type) override;
    void collectAll(std::vector<IncidentComponent*>& out) override;
    void collectLeaves(std::vector<IncidentComponent*>& out) override;

    // State-pattern plumbing
    void setState(TaskState* newState);
    TaskState* getState() const;

    // Lifecycle actions — each delegates to the current state.
    void startTravel();
    void arriveOnScene();
    void resolve();
    void escalate();
};
#endif