#include "ResponseTask.h"
// TODO: #include the concrete state headers once implemented, e.g.
// #include "DispatchedState.h"

ResponseTask::ResponseTask(std::string name, int severity, int effort)
    : name(std::move(name)), severity(severity), effort(effort),
      state(nullptr) {
    // TODO: initialise state to DispatchedState::instance()
}

int ResponseTask::getSeverityScore() const { return severity; }
int ResponseTask::getEstimatedEffort() const { return effort; }
std::string ResponseTask::getName() const { return name; }

void ResponseTask::report() const {
    // TODO: print name/severity/effort/current state name
}

Iterator* ResponseTask::createIterator(IteratorType /*type*/) {
    // TODO: return new FullSweepIterator(this) or new PriorityIterator(this, 0)
    return nullptr;
}

void ResponseTask::collectAll(std::vector<IncidentComponent*>& out) {
    out.push_back(this);
}

void ResponseTask::collectLeaves(std::vector<IncidentComponent*>& out) {
    out.push_back(this);
}

void ResponseTask::setState(TaskState* newState) { state = newState; }
TaskState* ResponseTask::getState() const { return state; }

void ResponseTask::startTravel() { /* TODO: state->startTravel(this); */ }
void ResponseTask::arriveOnScene() { /* TODO: state->arriveOnScene(this); */ }
void ResponseTask::resolve() { /* TODO: state->resolve(this); */ }
void ResponseTask::escalate() { /* TODO: state->escalate(this); */ }
