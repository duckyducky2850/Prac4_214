#ifndef HAZMATPROTOCOLDECORATOR_H
#define HAZMATPROTOCOLDECORATOR_H
#include "IncidentComponentDecorator.h"

class HazmatProtocolDecorator : public IncidentComponentDecorator {
public:
    explicit HazmatProtocolDecorator(IncidentComponent* component);
    int getSeverityScore() const override; // hazmat bumps severity up
    int getEstimatedEffort() const override; // decontamination time added
    void report() const override;
};
#endif

