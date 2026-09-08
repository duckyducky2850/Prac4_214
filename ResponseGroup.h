#ifndef RESPONSEGROUP_H
#define RESPONSEGROUP_H
#include "IncidentComponent.h"

// ResponseGroup (GoF Composite: Composite). Used for both the "team" and
// "squad" level of the hierarchy — one concrete class is enough here, so
// we don't introduce ResponseTeam/Squad subclasses unless a real behavioural
// difference between the two levels shows up later.
class ResponseGroup : public IncidentComponent {
private:
    std::string name;
    std::vector<IncidentComponent*> children; // OWNING pointers — see destructor

public:
    explicit ResponseGroup(std::string name);
    ~ResponseGroup() override; // deletes every child — recursive teardown

    void add(IncidentComponent* component) override;
    void remove(IncidentComponent* component) override; // removes WITHOUT deleting (see README on ownership during a move)

    int getSeverityScore() const override; // aggregate: highest severity among children
    int getEstimatedEffort() const override; // aggregate: sum of children's effort
    std::string getName() const override;
    void report() const override;
    Iterator* createIterator(IteratorType type) override;
    void collectAll(std::vector<IncidentComponent*>& out) override;
    void collectLeaves(std::vector<IncidentComponent*>& out) override;

    // Deliberately NO getChildren(): client code (and even the iterators)
    // never obtains the raw container. collectAll/collectLeaves are the
    // only sanctioned way in, and they're called polymorphically.
};
#endif