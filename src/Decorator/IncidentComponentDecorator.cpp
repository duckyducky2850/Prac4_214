#include "IncidentComponentDecorator.h"

IncidentComponentDecorator::IncidentComponentDecorator(IncidentComponent* component)
    : wrapped(component) {}

IncidentComponentDecorator::~IncidentComponentDecorator() {
    delete wrapped; // this decorator owns whatever it wraps
}

int IncidentComponentDecorator::getSeverityScore() const { return wrapped->getSeverityScore(); }
int IncidentComponentDecorator::getEstimatedEffort() const { return wrapped->getEstimatedEffort(); }
std::string IncidentComponentDecorator::getName() const { return wrapped->getName(); }
void IncidentComponentDecorator::report() const { wrapped->report(); }
void IncidentComponentDecorator::add(IncidentComponent* component) { wrapped->add(component); }
void IncidentComponentDecorator::remove(IncidentComponent* component) { wrapped->remove(component); }
Iterator* IncidentComponentDecorator::createIterator(IteratorType type) { return wrapped->createIterator(type); }

void IncidentComponentDecorator::collectAll(std::vector<IncidentComponent*>& out) {
    // Report ourselves (the decorated component), not the raw wrapped
    // pointer - makes it visible that this is a decorated component in the traversal.
    out.push_back(this);
}
void IncidentComponentDecorator::collectLeaves(std::vector<IncidentComponent*>& out) {
    out.push_back(this);
}