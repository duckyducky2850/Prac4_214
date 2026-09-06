#ifndef TASKSTATE_H
#define TASKSTATE_H
#include <string>

class ResponseTask;

// TaskState (GoF State): defines the lifecycle behaviour of a ResponseTask.
// Each transition method has a sensible default (report an invalid
// transition) — concrete states only override the transitions that are
// actually valid from that state.
class TaskState {
public:
    virtual ~TaskState() = default;

    virtual void startTravel(ResponseTask* task);
    virtual void arriveOnScene(ResponseTask* task);
    virtual void resolve(ResponseTask* task);
    virtual void escalate(ResponseTask* task);

    virtual std::string getName() const = 0;

protected:
    // Shared helper: prints a clear message instead of silently doing
    // nothing, so invalid transitions are visible during the demo/testing.
    void invalidTransition(ResponseTask* task, const std::string& attempted) const;
};

#endif
