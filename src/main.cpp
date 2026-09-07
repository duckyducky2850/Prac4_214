#include "ResponseGroup.h"
#include "ResponseTask.h"
#include "HazmatProtocolDecorator.h"
#include "MedicalSupportDecorator.h"
#include "MediaLiaisonDecorator.h"
#include "Iterator.h"
#include "PriorityIterator.h"
#include "TaskState.h"
#include <iostream>

void printSeparator(const std::string& title) {
    std::cout << "\n===== " << title << " =====\n";
}

int main() {
    // ---------------------------------------------------------------
    // Build the hierarchy: Incident -> Team -> Squad -> Task
    // ---------------------------------------------------------------
    ResponseGroup* incident = new ResponseGroup("Building Collapse - Main St");

    ResponseGroup* fireDivision = new ResponseGroup("Fire Division");
    ResponseGroup* engine12 = new ResponseGroup("Engine 12 Crew");
    ResponseTask* searchTask = new ResponseTask("Search Building 3", 8, 40);
    ResponseTask* ventTask = new ResponseTask("Ventilate stairwell", 4, 20);
    engine12->add(searchTask);
    engine12->add(ventTask);
    fireDivision->add(engine12);

    ResponseGroup* medicalDivision = new ResponseGroup("Medical Division");
    ResponseGroup* triageB = new ResponseGroup("Triage Unit B");
    ResponseTask* casualty4 = new ResponseTask("Treat casualty #4", 9, 25);
    ResponseTask* casualty7 = new ResponseTask("Treat casualty #7", 3, 15);
    triageB->add(casualty4);
    triageB->add(casualty7);
    medicalDivision->add(triageB);

    incident->add(fireDivision);
    incident->add(medicalDivision);

    // ---------------------------------------------------------------
    // Scenario 1: full report (Iterator - FULL_SWEEP) + a hazard is
    // discovered mid-response, so we decorate + reassign a task.
    // ---------------------------------------------------------------
    printSeparator("FULL INCIDENT REPORT (before hazmat discovery)");
    Iterator* fullReportBefore = incident->createIterator(IteratorType::FULL_SWEEP);
    for (fullReportBefore->first(); fullReportBefore->hasNext(); ) {
        fullReportBefore->next()->report();
    }
    delete fullReportBefore;

    // A hazmat leak is discovered at the search task -> decorate it.
    // Decorators stack: hazmat AND medical support both apply here.
    engine12->remove(searchTask); // detach WITHOUT deleting (see ResponseGroup::remove)
    IncidentComponent* decoratedSearch =
        new MedicalSupportDecorator(new HazmatProtocolDecorator(searchTask));
    engine12->add(decoratedSearch); // put the (now decorated) task back

    printSeparator("SAME TASK AFTER STACKING DECORATORS");
    decoratedSearch->report();
    std::cout << "  -> effort now " << decoratedSearch->getEstimatedEffort()
              << " min, severity now " << decoratedSearch->getSeverityScore() << "\n";

    // ---------------------------------------------------------------
    // Runtime structural change + traversal policy demonstration:
    // an iterator created BEFORE a move keeps its snapshot; one created
    // AFTER the move sees the new structure. This is the deliberate
    // "snapshot" policy documented in FullSweepIterator.h.
    // ---------------------------------------------------------------
    Iterator* beforeMove = incident->createIterator(IteratorType::FULL_SWEEP);

    // Escalate casualty #4, then move it from Triage B to Engine 12
    // (e.g. it now needs fire-crew extraction support).
    casualty4->startTravel();
    casualty4->arriveOnScene();
    casualty4->escalate();
    triageB->remove(casualty4);
    engine12->add(casualty4);

    Iterator* afterMove = incident->createIterator(IteratorType::FULL_SWEEP);

    printSeparator("ITERATOR CREATED BEFORE THE MOVE (snapshot, old structure)");
    for (beforeMove->first(); beforeMove->hasNext(); ) {
        std::cout << "  - " << beforeMove->next()->getName() << "\n";
    }
    printSeparator("ITERATOR CREATED AFTER THE MOVE (reflects new structure)");
    for (afterMove->first(); afterMove->hasNext(); ) {
        std::cout << "  - " << afterMove->next()->getName() << "\n";
    }
    delete beforeMove;
    delete afterMove;

    // ---------------------------------------------------------------
    // Scenario 2: mass-casualty triage using PriorityIterator, plus
    // state-machine validity checks (one valid path, one invalid attempt).
    // ---------------------------------------------------------------
    printSeparator("PRIORITY TRIAGE (severity >= 5, most urgent first)");
    Iterator* urgent = new PriorityIterator(incident, /*minSeverity=*/5);
    for (urgent->first(); urgent->hasNext(); ) {
        IncidentComponent* item = urgent->next();
        std::cout << "  - " << item->getName() << " (severity " << item->getSeverityScore() << ")\n";
    }
    delete urgent;

    printSeparator("STATE TRANSITIONS ON A FRESH TASK");
    ResponseTask* triageTask = new ResponseTask("Assess trapped worker", 7, 20);
    std::cout << "Initial state: " << triageTask->getState()->getName() << "\n";
    triageTask->arriveOnScene();  // INVALID: hasn't started travel yet
    triageTask->startTravel();
    triageTask->arriveOnScene();
    std::cout << "State is now: " << triageTask->getState()->getName() << "\n";
    triageTask->startTravel();    // INVALID: already past that stage
    triageTask->resolve();
    std::cout << "Final state: " << triageTask->getState()->getName() << "\n";

    incident->add(triageTask); // fold it into the hierarchy for cleanup

    
    // Reassign casualty #7 to Engine 12 as backup support.
    triageB->remove(casualty7); // detach before transferring ownership
    engine12->add(casualty7);
    // ---------------------------------------------------------------
    // Cleanup: destroying the root recursively destroys everything,
    // including decorated tasks (their destructors delete what they wrap).
    // ---------------------------------------------------------------
    delete incident;

    return 0;
}
