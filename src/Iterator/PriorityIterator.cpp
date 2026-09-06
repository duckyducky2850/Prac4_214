#include "PriorityIterator.h"

PriorityIterator::PriorityIterator(IncidentComponent* root, int minSeverity) {
    // TODO: collect leaves via root->collectLeaves(...), filter by
    // minSeverity, sort descending by severity into `snapshot`.
    (void)root;
    (void)minSeverity;
}

bool PriorityIterator::hasNext() const { return position < snapshot.size(); }

IncidentComponent* PriorityIterator::next() {
    // TODO: return snapshot[position++];
    return nullptr;
}

void PriorityIterator::first() { position = 0; }
