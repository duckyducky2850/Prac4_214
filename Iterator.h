#pragma once

// Forward declaration only — Iterator never needs the full definition,
// which avoids a circular include with IncidentComponent.h.
class IncidentComponent;

// Iterator (GoF): defines a uniform way to step through a collection
// of IncidentComponent* without exposing how that collection is stored.
class Iterator {
public:
    virtual ~Iterator() = default;
    virtual bool hasNext() const = 0;
    virtual IncidentComponent* next() = 0;
    virtual void first() = 0; // reset to the start of the traversal
};
