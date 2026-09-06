#ifndef INCIDENTCOMPONENTDECORATOR_H
#define INCIDENTCOMPONENTDECORATOR_H
#include "IncidentComponent.h"

// IncidentComponentDecorator (GoF Decorator: base Decorator). Implements
// the SAME interface as the thing it wraps, so a decorated task/group can
// be used anywhere an IncidentComponent is expected — including added into
// a ResponseGroup, or traversed by an iterator, with no special casing.
class IncidentComponentDecorator : public IncidentComponent {
protected:
    IncidentComponent* wrapped; // OWNED — deleted in this class's destructor

public:
    explicit IncidentComponentDecorator(IncidentComponent* component);
    ~IncidentComponentDecorator() override;

    // Default behaviour: forward everything to the wrapped component.
    // Concrete decorators override the specific behaviour they add to.
    int getSeverityScore() const override;
    int getEstimatedEffort() const override;
    std::string getName() const override;
    void report() const override;
    void add(IncidentComponent* component) override;
    void remove(IncidentComponent* component) override;
    Iterator* createIterator(IteratorType type) override;
    void collectAll(std::vector<IncidentComponent*>& out) override;
    void collectLeaves(std::vector<IncidentComponent*>& out) override;
};
#endif
