#include "ResponseGroup.h"
#include "FullSweepIterator.h"
#include "PriorityIterator.h"
#include <algorithm>
#include <iostream>
#include <numeric>

ResponseGroup::ResponseGroup(std::string name) : name(std::move(name)) {}

ResponseGroup::~ResponseGroup() {
    // Ownership policy: a group owns everything inside it. Destroying a
    // group recursively destroys the whole subtree beneath it, including
    // any nested groups (whose own destructors then run and do the same).
    for (IncidentComponent* child : children) {
        delete child;
    }
}

void ResponseGroup::add(IncidentComponent* component) {
    children.push_back(component);
}

void ResponseGroup::remove(IncidentComponent* component) {
    // NOTE: remove() does NOT delete — it only detaches. This is what makes
    // "move a task to a different squad" safe: remove() from the old
    // group, then add() into the new one. The task is deleted exactly
    // once, by whichever group still owns it when it's torn down.
    children.erase(std::remove(children.begin(), children.end(), component), children.end());
}

int ResponseGroup::getSeverityScore() const {
    int worst = 0;
    for (const IncidentComponent* child : children) {
        worst = std::max(worst, child->getSeverityScore());
    }
    return worst;
}

int ResponseGroup::getEstimatedEffort() const {
    int total = 0;
    for (const IncidentComponent* child : children) {
        total += child->getEstimatedEffort();
    }
    return total;
}

std::string ResponseGroup::getName() const { return name; }

void ResponseGroup::report() const {
    // Describes ONLY this group. Visiting every node in the tree is the
    // Iterator's job (see FullSweepIterator) — report() recursing here too
    // would print every node once per ancestor, duplicating the traversal.
    std::cout << "[Group] " << name << " (worst severity " << getSeverityScore()
              << ", total effort " << getEstimatedEffort() << " min)\n";
}

Iterator* ResponseGroup::createIterator(IteratorType type) {
    if (type == IteratorType::FULL_SWEEP) return new FullSweepIterator(this);
    return new PriorityIterator(this, /*minSeverity=*/0);
}

void ResponseGroup::collectAll(std::vector<IncidentComponent*>& out) {
    out.push_back(this);
    for (IncidentComponent* child : children) {
        child->collectAll(out); // polymorphic recursion — no type checks needed
    }
}

void ResponseGroup::collectLeaves(std::vector<IncidentComponent*>& out) {
    for (IncidentComponent* child : children) {
        child->collectLeaves(out); // groups don't add themselves, only leaves do
    }
}
