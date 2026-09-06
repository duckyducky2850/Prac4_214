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
    // TODO: push `this` (so the decoration is visible to the caller), then
    // decide how to handle `wrapped` being a group — see header note.
    out.push_back(this);
}

void IncidentComponentDecorator::collectLeaves(std::vector<IncidentComponent*>& out) {
    // TODO: same consideration as collectAll — see header note.
    out.push_back(this);
}
