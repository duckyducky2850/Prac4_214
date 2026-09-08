#ifndef FULLSWEEPITERATOR_H
#define FULLSWEEPITERATOR_H


#include "Iterator.h"
#include "IncidentComponent.h"
#include <vector>

// FullSweepIterator (GoF ConcreteIterator): visits every component in the
// subtree — both groups and tasks — in pre-order. Used for full incident
// reports.
//
// TRAVERSAL-MODIFICATION POLICY: this iterator takes a SNAPSHOT of the
// structure at construction time (via collectAll). If the tree is changed
// afterwards (a task moved, added, or removed), this iterator keeps
// walking the structure as it existed when it was created. This is the
// safer, easier-to-reason-about policy: a report in progress won't produce
// inconsistent or dangling results just because command reassigned a task
// mid-sweep. If you want to see the change, create a NEW iterator.
class FullSweepIterator : public Iterator {
private:
    std::vector<IncidentComponent*> snapshot;
    size_t position = 0;

public:
    explicit FullSweepIterator(IncidentComponent* root);
    bool hasNext() const override;
    IncidentComponent* next() override;
    void first() override;
};


#endif