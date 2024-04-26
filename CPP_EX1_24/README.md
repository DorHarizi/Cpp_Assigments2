<div dir="rtl" lang="he">
  
# Graph Algorithms

This project implements a set of graph algorithms using a representation based on an adjacency matrix.

## Overview

The project consists of two main components: `Graph.cpp` and `Algorithms.cpp`, along with a demonstration file `Demo.cpp`. Additionally, comprehensive unit tests are provided in the `Task2_Test` directory.

### `Graph.cpp`

This file contains the implementation of the `Graph` class, representing a graph using an adjacency matrix. The class includes methods such as `loadGraph` for loading a graph from an adjacency matrix, and `printGraph` for printing the graph's representation.

### `Algorithms.cpp`

This file contains implementations of various graph algorithms:

- `isConnected(Graph& g)`: Checks if a graph is connected.
- `shortestPath(Graph& g, size_t src, size_t dest)`: Finds the shortest path between two vertices in a graph.
- `isContainsCycle(Graph& g)`: Checks if a graph contains a cycle.
- `isBipartite(Graph& g)`: Determines if a graph is bipartite.
- `negativeCycle(Graph& g)`: Finds a negative cycle in a graph.

### `Demo.cpp`

This file contains demonstration examples showcasing the usage of the implemented graph algorithms.

## Usage

To compile and run the demo program:

<div dir='ltr'>
    make demo && ./demo
</div>

To compile and run the test program:

<div dir='ltr'>
    make test && ./test
    make valgrind
    make tidy
</div>

</div>



