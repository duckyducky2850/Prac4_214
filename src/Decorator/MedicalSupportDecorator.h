#ifndef MEDICALSUPPORTDECORATOR_H
#define MEDICALSUPPORTDECORATOR_H


#include "IncidentComponentDecorator.h"
#include <iostream>

// --- MedicalSupportDecorator -------------------------------------------
class MedicalSupportDecorator : public IncidentComponentDecorator {
public:
    explicit MedicalSupportDecorator(IncidentComponent* component);
    int getEstimatedEffort() const override; // triage overhead added
    void report() const override;
};
#endif