#include "ResponseGroup.h"

ResponseGroup::ResponseGroup(std::string name) : name(std::move(name)) {}

ResponseGroup::~ResponseGroup() {
    // TODO: delete every child (recursive teardown of the whole subtree).
}

void ResponseGroup::add(IncidentComponent* component) {
    children.push_back(component);
}

void ResponseGroup::remove(IncidentComponent* /*component*/) {
    // TODO: erase the matching pointer WITHOUT deleting it — this is what
    // makes "move a task to a different squad" safe.
}

int ResponseGroup::getSeverityScore() const {
    // TODO: return the max severity among children
    return 0;
}

int ResponseGroup::getEstimatedEffort() const {
    // TODO: return the sum of children's effort
    return 0;
}

std::string ResponseGroup::getName() const { return name; }

void ResponseGroup::report() const {
    // TODO: print a one-line summary of THIS group only (not children —
    // that's the Iterator's job).
}

Iterator* ResponseGroup::createIterator(IteratorType /*type*/) {
    // TODO: return new FullSweepIterator(this) or new PriorityIterator(this, 0)
    return nullptr;
}

void ResponseGroup::collectAll(std::vector<IncidentComponent*>& out) {
    out.push_back(this);
    // TODO: recurse into each child via child->collectAll(out)
}

void ResponseGroup::collectLeaves(std::vector<IncidentComponent*>& out) {
    // TODO: recurse into each child via child->collectLeaves(out)
    // (a group does NOT add itself here — only leaves do)
    (void)out;
}
