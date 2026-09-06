#include "IncidentComponent.h"
#include <stdexcept>

// Default behaviour for leaves and decorators: adding/removing a child
// makes no sense unless you're a ResponseGroup, so we fail loudly rather
// than silently doing nothing.
void IncidentComponent::add(IncidentComponent* /*component*/) {
    throw std::logic_error("add() is not supported on this component");
}

void IncidentComponent::remove(IncidentComponent* /*component*/) {
    throw std::logic_error("remove() is not supported on this component");
}
