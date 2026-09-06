#include "FullSweepIterator.h"

FullSweepIterator::FullSweepIterator(IncidentComponent* root) {
    // TODO: root->collectAll(snapshot);
    (void)root;
}

bool FullSweepIterator::hasNext() const { return position < snapshot.size(); }

IncidentComponent* FullSweepIterator::next() {
    // TODO: return snapshot[position++];
    return nullptr;
}

void FullSweepIterator::first() { position = 0; }
