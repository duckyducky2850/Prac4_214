#include "HazmatProtocolDecorator.h"
#include <iostream>

HazmatProtocolDecorator::HazmatProtocolDecorator(IncidentComponent* component)
    : IncidentComponentDecorator(component) {}

int HazmatProtocolDecorator::getSeverityScore() const {
    return wrapped->getSeverityScore() + 2; // hazmat raises how urgent this is
}
int HazmatProtocolDecorator::getEstimatedEffort() const {
    return wrapped->getEstimatedEffort() + 30; // decontamination time
}
void HazmatProtocolDecorator::report() const {
    wrapped->report();
    std::cout << "    + Hazmat protocol active (decontamination required)\n";
}