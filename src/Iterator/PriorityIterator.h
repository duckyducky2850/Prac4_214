#ifndef PRIORITYITERATOR_H
#define PRIORITYITERATOR_H
#include "Iterator.h"
#include "IncidentComponent.h"
#include <vector>

// PriorityIterator (GoF ConcreteIterator): visits only LEAF tasks (groups
// are skipped — they aren't actionable items) whose severity is at or
// above a threshold, ordered from most to least severe. Used when a
// dispatcher needs to know what to act on right now.
//
// This is a genuinely different traversal from FullSweepIterator: different
// selection rule (filtered by severity), different order (severity
// descending, not structural pre-order), and different purpose (urgent
// action list vs. complete report). Same snapshot policy as FullSweepIterator.
class PriorityIterator : public Iterator {
private:
    std::vector<IncidentComponent*> snapshot;
    size_t position = 0;

public:
    PriorityIterator(IncidentComponent* root, int minSeverity);
    bool hasNext() const override;
    IncidentComponent* next() override;
    void first() override;
};
#endif