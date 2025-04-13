# [Graphs Activity 1](https://github.com/d-khan/dslabs/blob/8214da88d1009266cf3a6d4fc51cf19eac19160a/graphs/Activity1.md)

## Task 1

> Create a theoretical graph using a pen and paper OR electronically.

```txt
  A -- B
 /|    |
C |    |
 \|    |
  D    E
```

Undirected graph with 5 vertices, 6 edges:

| Vertices | Edges |
| -------- | ----- |
| A        | B,C,D |
| B        | A,E   |
| C        | A,D   |
| D        | A,C   |
| E        | B     |

## Task 2

> Implement the graph created in step 1 and apply breadth and depth-first search
> algorithms using C++.

See: [Code](./graphs.cpp)

## Task 3

> Compare both search algorithms in the context of Big O notations.

Both BFS and DFS have the same time complexity in most implementations:

- **Time Complexity**: O(V + E) where V is the number of vertices and E is the
  number of edges

  - Each vertex is visited once: O(V)
  - Each edge is considered once: O(E)

- **Space Complexity**:
  - BFS: O(V) - In worst case, all vertices might be in the queue
  - DFS: O(V) - In worst case, all vertices might be in the stack (or recursion
    call stack)

**Key differences in practical terms**:

- BFS finds the shortest path in unweighted graphs
- DFS is typically simpler to implement recursively
- BFS explores level by level (breadth-wise), while DFS explores as far as
  possible (depth-wise)
- Memory usage can differ depending on the graph structure:
  - For wide graphs, BFS may use more memory than DFS
  - For deep graphs, DFS may use more memory than BFS (due to recursion stack
    depth)
