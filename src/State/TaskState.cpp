#include "TaskState.h"

void TaskState::startTravel(ResponseTask* task) { invalidTransition(task, "startTravel"); }
void TaskState::arriveOnScene(ResponseTask* task) { invalidTransition(task, "arriveOnScene"); }
void TaskState::resolve(ResponseTask* task) { invalidTransition(task, "resolve"); }
void TaskState::escalate(ResponseTask* task) { invalidTransition(task, "escalate"); }

void TaskState::invalidTransition(ResponseTask* /*task*/, const std::string& /*attempted*/) const {
    // TODO: print "[INVALID TRANSITION] <task name> cannot <attempted>()
    // while in state <getName()>" — needs ResponseTask.h include for getName().
}
