#ifndef MEDIALIASIONDECORATOR_H
#define MEDIALIASIONDECORATOR_H

#include "IncidentComponentDecorator.h"

class MediaLiaisonDecorator : public IncidentComponentDecorator {
public:
    explicit MediaLiaisonDecorator(IncidentComponent* component);
    int getEstimatedEffort() const override; // comms overhead added
    void report() const override;
};
#endif