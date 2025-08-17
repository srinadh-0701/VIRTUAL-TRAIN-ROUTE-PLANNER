# Virtual Train Route Planner (Doubly + Circular Linked List)

**Data Structures:** Doubly linked list for forward/back navigation; optional **circular** mode for loop routes.

## Features
- Add stations (append or at position).
- Show entire route.
- Set current station and move **Next/Prev**.
- Toggle **circular mode** (when ON, next from tail wraps to head).
- Remove station by name; clear route.

## Build & Run
```bash
g++ -std=c++17 -O2 -o TrainPlanner main.cpp
./TrainPlanner
```
