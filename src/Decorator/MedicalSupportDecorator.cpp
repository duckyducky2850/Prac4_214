#include "MedicalSupportDecorator.h"

MedicalSupportDecorator::MedicalSupportDecorator(IncidentComponent* component)
    : IncidentComponentDecorator(component) {}

int MedicalSupportDecorator::getEstimatedEffort() const {
    // TODO: return wrapped->getEstimatedEffort() + <triage overhead>;
    return wrapped->getEstimatedEffort();
}

void MedicalSupportDecorator::report() const {
    wrapped->report();
    // TODO: print the extra medical support line
}
