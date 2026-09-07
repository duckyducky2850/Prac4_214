#include "TaskState.h"
#include "ResponseTask.h"
#include <iostream>

void TaskState::startTravel(ResponseTask* task) { invalidTransition(task, "startTravel"); }
void TaskState::arriveOnScene(ResponseTask* task) { invalidTransition(task, "arriveOnScene"); }
void TaskState::resolve(ResponseTask* task) { invalidTransition(task, "resolve"); }
void TaskState::escalate(ResponseTask* task) { invalidTransition(task, "escalate"); }

void TaskState::invalidTransition(ResponseTask* task, const std::string& attempted) const {
    std::cout << "[INVALID TRANSITION] \"" << task->getName() << "\" cannot "
              << attempted << "() while in state " << getName() << "\n";
}