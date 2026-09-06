#include "ResolvedState.h"

ResolvedState* ResolvedState::instance() {
    static ResolvedState instance;
    return &instance;
}
