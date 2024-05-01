<div dir="rtl" lang="he">

# Graph & Algorithms

This project implements a series of graph algorithms using an adjacency matrix-based representation of graphs.

## Overview

The project comprises two main components: `Graph.cpp` and `Algorithms.cpp`, supplemented by a demonstration file `Demo.cpp`. Comprehensive unit tests are provided in the `Task2_Test` directory.

### `Graph.cpp`

This file contains the implementation of the `Graph` class, which represents a graph using an adjacency matrix. Key functionalities include:

#### Operator Overloads

- `operator+`: Adds two graphs by adding their corresponding matrix elements. The operation is only valid if both graphs are of the same size. Throws an error otherwise.
- `operator+=`: Adds another graph to the current graph, updating the current graph's adjacency matrix.
- `operator+`: Unary plus, returns a copy of the graph.
- `operator-`: Subtracts the adjacency matrix of another graph from this one. The operation is only valid if both graphs are of the same size.
- `operator-`: Unary minus, negates the adjacency matrix of the graph, turning all positive weights into negative and vice versa.
- `opertator-=`: Subtracts another graph from this graph and updates the current graph's adjacency matrix.
- `operator++`: Prefix increment, increments all weights in the graph by 1.
- `operator--`: Prefix decrement, decrements all weights in the graph by 1.
- `operator*`: Multiplies each element of the graph's adjacency matrix by a scalar value.
- `operator*=`: Multiplies each element of the graph's adjacency matrix by a scalar value and updates the graph.
- `operator*`: Multiplies two graphs using matrix multiplication rules. The operation is only valid if the number of columns in the first graph equals the number of rows in the second graph.
- `operator/=`: Divides each element of the graph's adjacency matrix by a scalar value. Throws an error if dividing by zero.
- `operator==`: Checks if two graphs are equal by comparing their sizes and all corresponding elements in their adjacency matrices.
- `operator!=`: Checks if two graphs are not equal.
- `operator<`: Compares two graphs based on the sum of their adjacency matrix values, determining if the first is less than the second.
- `operator<=`: Compares two graphs to determine if the first is less than or equal to the second.
- `operator>`: Compares two graphs to determine if the first is greater than the second.
- `operator>=`: Compares two graphs to determine if the first is greater than or equal to the second.

### `Algorithms.cpp`

This file implements various graph algorithms including:

- `isConnected`: Checks if the graph is connected.
- `shortestPath`: Computes the shortest path between two vertices.
- `isContainsCycle`: Determines if the graph contains a cycle.
- `isBipartite`: Checks if the graph is bipartite.
- Additional methods supporting graph manipulation and analysis.

### `Demo.cpp`

Provides examples demonstrating the usage of the implemented graph algorithms to showcase their functionalities in practical scenarios.

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
