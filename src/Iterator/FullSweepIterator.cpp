#include "FullSweepIterator.h"

FullSweepIterator::FullSweepIterator(IncidentComponent* root) {
    root->collectAll(snapshot); // snapshot taken NOW, not re-checked later
}

bool FullSweepIterator::hasNext() const { return position < snapshot.size(); }

IncidentComponent* FullSweepIterator::next() { return snapshot[position++]; }

void FullSweepIterator::first() { position = 0; }
