# TaskForge: Emergency Response Coordination System

COS 214 Practical 4 — a hierarchical work-processing system for coordinating
incident response teams, squads, and tasks.

**Team:** *Lethabo Molobi,Lillian Muller ,Francois Venter*



## Domain

An **Incident** (root) contains **ResponseGroup**s used at two levels —
divisions (e.g. Fire Division, Medical Division) and, nested inside them,
crews/squads (e.g. Engine 12 Crew, Triage Unit B) — which in turn contain
individual **ResponseTask**s. This gives a genuine part-whole hierarchy at
least three levels deep below the root: `Incident → Division → Crew → Task`.

Tasks move through a lifecycle (`Dispatched → EnRoute → OnScene →` either
`Resolved` or an `Escalated` branch that still leads to `Resolved`). Tasks
(or groups) can be decorated with optional, stackable responsibilities —
`HazmatProtocol`, `MedicalSupport`, `MediaLiaison` — and the whole tree can
be traversed in two independent, purpose-built ways without exposing its
internal storage to client code.

## Patterns

|Pattern|Participants|
|-|-|
|**Composite**|`IncidentComponent` (Component) · `ResponseTask` (Leaf) · `ResponseGroup` (Composite)|
|**Iterator**|`Iterator` (Iterator) · `FullSweepIterator` / `PriorityIterator` (ConcreteIterator) · `IncidentComponent::createIterator` (factory method)|
|**State**|`TaskState` (State) · `DispatchedState` / `EnRouteState` / `OnSceneState` / `EscalatedState` / `ResolvedState` (ConcreteState) · `ResponseTask` (Context)|
|**Decorator**|`IncidentComponentDecorator` (Decorator) · `HazmatProtocolDecorator` / `MedicalSupportDecorator` / `MediaLiaisonDecorator` (ConcreteDecorator)|

## Traversal-modification policy

Both `FullSweepIterator` and `PriorityIterator` take a **snapshot** of the
structure at the moment they're constructed (via the `collectAll` /
`collectLeaves` traversal hooks). An iterator created *before* a structural
change (a task moved, added, decorated, or removed) keeps walking the
structure exactly as it looked when it was created; it will not see the
change and will not dangle. To observe a change, create a new iterator
afterwards. This is demonstrated directly in `main.cpp` (see the
"before the move" / "after the move" section).

## Ownership policy

* A `ResponseGroup` owns every child added to it and deletes the whole
subtree recursively in its destructor.
* `ResponseGroup::remove()` **detaches without deleting**, which is what
makes moving a task between groups safe — remove from the old parent,
add to the new one, and it is destroyed exactly once, by whichever
group still owns it when the tree is torn down.
* An `IncidentComponentDecorator` owns whatever it wraps and deletes it in
its own destructor, so a decorated component can be added into a group
like any other component and still be torn down correctly.
* `TaskState` concrete states are stateless singletons (function-local
`static`), never heap-allocated and never owned by `ResponseTask` — there
is nothing to leak.

## Build and run

```bash
make clean \&\& make
./taskforge
```

## Build and run (Docker)

```bash
docker build -t taskforge .
docker run -it taskforge
```

To get a shell inside the container instead of running immediately:

```bash
docker run -it taskforge bash
make clean \&\& make
./taskforge
```

## GDB (inside the container)

```bash
docker run -it taskforge bash
gdb ./taskforge
(gdb) break ResponseTask::escalate
(gdb) run
(gdb) next
(gdb) print this->severity
(gdb) continue
```

## Valgrind (inside the container)

```bash
docker run -it taskforge bash
valgrind --leak-check=full --show-leak-kinds=all ./taskforge
```

Expected: `definitely lost: 0 bytes`. *Paste the actual run's summary here
once captured, and include the full log in `docs/valgrind.txt`.*

## Project layout

```
.
├── main.cpp                          # demo scenarios
├── Makefile
├── Dockerfile
├── README.md
├── docs/                             # design PDF, UML diagrams, Valgrind/GDB evidence
├── IncidentComponent.h/.cpp          # Composite: shared interface
├── ResponseTask.h/.cpp               # Composite: leaf + State context
├── ResponseGroup.h/.cpp              # Composite: composite
├── Iterator.h                        # Iterator interface
├── FullSweepIterator.h/.cpp          # Iterator: full traversal
├── PriorityIterator.h/.cpp           # Iterator: severity-filtered traversal
├── TaskState.h/.cpp                  # State interface
├── DispatchedState.h/.cpp            # State: concrete lifecycle state
├── EnRouteState.h/.cpp                # State: concrete lifecycle state
├── OnSceneState.h/.cpp                # State: concrete lifecycle state
├── EscalatedState.h/.cpp              # State: concrete lifecycle state
├── ResolvedState.h/.cpp               # State: concrete lifecycle state
├── IncidentComponentDecorator.h/.cpp # Decorator base
├── HazmatProtocolDecorator.h/.cpp    # Decorator: concrete responsibility
├── MedicalSupportDecorator.h/.cpp    # Decorator: concrete responsibility
└── MediaLiaisonDecorator.h/.cpp      # Decorator: concrete responsibility
```



