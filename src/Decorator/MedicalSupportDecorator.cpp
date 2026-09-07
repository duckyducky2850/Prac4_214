#include "MedicalSupportDecorator.h"
#include <iostream>

MedicalSupportDecorator::MedicalSupportDecorator(IncidentComponent* component)
    : IncidentComponentDecorator(component) {}

int MedicalSupportDecorator::getEstimatedEffort() const {
    return wrapped->getEstimatedEffort() + 15;
}
void MedicalSupportDecorator::report() const {
    wrapped->report();
    std::cout << "    + Medical support attached (triage required)\n";
}