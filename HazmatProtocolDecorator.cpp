#include "HazmatProtocolDecorator.h"

HazmatProtocolDecorator::HazmatProtocolDecorator(IncidentComponent* component)
    : IncidentComponentDecorator(component) {}

int HazmatProtocolDecorator::getSeverityScore() const {
    // TODO: return wrapped->getSeverityScore() + <hazmat bump>;
    return wrapped->getSeverityScore();
}

int HazmatProtocolDecorator::getEstimatedEffort() const {
    // TODO: return wrapped->getEstimatedEffort() + <decontamination time>;
    return wrapped->getEstimatedEffort();
}

void HazmatProtocolDecorator::report() const {
    wrapped->report();
    // TODO: print the extra hazmat line
}
