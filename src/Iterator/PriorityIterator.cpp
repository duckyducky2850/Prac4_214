#include "PriorityIterator.h"
#include <algorithm>

PriorityIterator::PriorityIterator(IncidentComponent* root, int minSeverity) {
    std::vector<IncidentComponent*> leaves;
    root->collectLeaves(leaves);

    for (IncidentComponent* leaf : leaves) {
        if (leaf->getSeverityScore() >= minSeverity) {
            snapshot.push_back(leaf);
        }
    }

    std::sort(snapshot.begin(), snapshot.end(),
              [](const IncidentComponent* a, const IncidentComponent* b) {
                  return a->getSeverityScore() > b->getSeverityScore(); // descending
              });
}

bool PriorityIterator::hasNext() const { return position < snapshot.size(); }

IncidentComponent* PriorityIterator::next() { return snapshot[position++]; }

void PriorityIterator::first() { position = 0; }
