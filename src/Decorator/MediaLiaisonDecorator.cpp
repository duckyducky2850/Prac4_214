#include "MediaLiaisonDecorator.h"
#include <iostream>

MediaLiaisonDecorator::MediaLiaisonDecorator(IncidentComponent* component)
    : IncidentComponentDecorator(component) {}

int MediaLiaisonDecorator::getEstimatedEffort() const {
    return wrapped->getEstimatedEffort() + 10; // comms overhead
}
void MediaLiaisonDecorator::report() const {
    wrapped->report();
    std::cout << "    + Media liaison assigned (press updates required)\n";
}