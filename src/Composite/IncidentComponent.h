#ifndef INCIDENTCOMPONENT_H
#define INCIDENTCOMPONENT_H
#include <string>
#include <vector>
#include "Iterator.h"

enum class IteratorType { FULL_SWEEP, PRIORITY };

// IncidentComponent (GoF Composite): the shared abstraction implemented by
// both the leaf (ResponseTask), the composite (ResponseGroup), and any
// decorator. Client code should only ever talk to this interface —
// it never needs to know whether it holds a single task or an entire team.
class IncidentComponent {
public:
    virtual ~IncidentComponent() = default;

    // Core behaviour every component must provide.
    virtual int getSeverityScore() const = 0;
    virtual int getEstimatedEffort() const = 0;
    virtual std::string getName() const = 0;
    virtual void report() const = 0;

    // Composite-only operations. Default behaviour is "not supported" —
    // ResponseGroup overrides these; ResponseTask (a leaf) does not.
    virtual void add(IncidentComponent* component);
    virtual void remove(IncidentComponent* component);

    // Iterator factory (GoF Iterator): hands back a traversal object
    // without exposing the internal container used to store children.
    virtual Iterator* createIterator(IteratorType type) = 0;

    // Internal traversal hooks used ONLY by the Iterator concrete classes.
    // These are what let FullSweepIterator/PriorityIterator walk the tree
    // via polymorphism instead of the client (or the iterator) needing to
    // downcast or reach into a group's private container.
    virtual void collectAll(std::vector<IncidentComponent*>& out) = 0;
    virtual void collectLeaves(std::vector<IncidentComponent*>& out) = 0;
};
#endif
