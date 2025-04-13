# [Graphs - Activity 2](https://github.com/d-khan/dslabs/blob/8214da88d1009266cf3a6d4fc51cf19eac19160a/graphs/Activity2.md)

## Task 1

> Explain with the help of an example "Why Dijkstra's algorithm fails on
> negative weights".

Dijkstra's algorithm fails on graphs with negative-weight edges because it
relies on a fundamental assumption: once a vertex is visited (marked as
"settled"), its shortest path from the source cannot be improved further. With
negative weights, this assumption no longer holds.

**Example**:

```txt
A ----- B
|   2   |
|       |
|1      |-2
|   3   |
C ----- D
```

Vertex,Edge,Weight A,B,2 A,C,1 B,D,-2 C,D,3

Finding the shortest path from A to D using Dijkstra's algorithm:

1. Start at A (distance = 0)
2. Visit neighbors of A:
   - Update B: dist[B] = 2
   - Update C: dist[C] = 1
3. Extract minimum (C with distance 1)
4. Visit neighbors of C:
   - Update D: dist[D] = 1 + 3 = 4
5. Extract minimum (B with distance 2)
6. Visit neighbors of B:
   - Update D: dist[D] = 2 + (-2) = 0
7. Extract minimum (D with distance 0)
8. Algorithm terminates, shortest path to D is 0 via A->B->D

**The Problem:** If we had processed B before C (which is valid in Dijkstra's),
we would have settled D with distance 0. Then when examining C, we would not
revisit D because it's already settled. This why Dijkstra's algorithm can
produce incorrect results with negative weights - it prematurely finalizes
vertices.

**The core issue:** Negative weights can create situations where a longer
initial path becomes shorter later due to negative edges, but Dijkstra's greedy
approach doesn't reconsider vertices it has already finalized. This violates the
algorithm's primary assumption that settled vertices have their final shortest
distances.
