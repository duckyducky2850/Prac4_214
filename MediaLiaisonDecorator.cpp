#include "MediaLiaisonDecorator.h"

MediaLiaisonDecorator::MediaLiaisonDecorator(IncidentComponent* component)
    : IncidentComponentDecorator(component) {}

int MediaLiaisonDecorator::getEstimatedEffort() const {
    // TODO: return wrapped->getEstimatedEffort() + <comms overhead>;
    return wrapped->getEstimatedEffort();
}

void MediaLiaisonDecorator::report() const {
    wrapped->report();
    // TODO: print the extra media liaison line
}
