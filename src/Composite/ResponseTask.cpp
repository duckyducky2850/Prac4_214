#include "ResponseTask.h"
#include "ResolvedState.h"
#include "ResolvedState.h"
#include "EscalatedState.h"
#include "EnRouteState.h"
#include "DispatchedState.h"
#include "FullSweepIterator.h"
#include "PriorityIterator.h"
#include <iostream>

ResponseTask::ResponseTask(std::string name, int severity, int effort)
    : name(std::move(name)), severity(severity), effort(effort),
      state(DispatchedState::instance()) {}

int ResponseTask::getSeverityScore() const { return severity; }
int ResponseTask::getEstimatedEffort() const { return effort; }
std::string ResponseTask::getName() const { return name; }

void ResponseTask::report() const {
    std::cout << "  [Task] " << name << " (severity " << severity
              << ", effort " << effort << " min, state: " << state->getName() << ")\n";
}

Iterator* ResponseTask::createIterator(IteratorType type) {
    // A leaf can still be asked to traverse "everything below it" — that's
    // just itself. Reusing the same concrete iterator classes here (rather
    // than a special leaf-only class) keeps the traversal logic in one
    // place; collectAll/collectLeaves on a leaf simply add itself.
    if (type == IteratorType::FULL_SWEEP) return new FullSweepIterator(this);
    return new PriorityIterator(this, /*minSeverity=*/0);
}

void ResponseTask::collectAll(std::vector<IncidentComponent*>& out) { out.push_back(this); }
void ResponseTask::collectLeaves(std::vector<IncidentComponent*>& out) { out.push_back(this); }

void ResponseTask::setState(TaskState* newState) { state = newState; }
TaskState* ResponseTask::getState() const { return state; }

void ResponseTask::startTravel() { state->startTravel(this); }
void ResponseTask::arriveOnScene() { state->arriveOnScene(this); }
void ResponseTask::resolve() { state->resolve(this); }
void ResponseTask::escalate() { state->escalate(this); }
