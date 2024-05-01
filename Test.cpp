#include "doctest.h"
#include "Algorithms.hpp"
#include "Graph.hpp"

using namespace std;

TEST_CASE("Test graph addition")
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph);
    ariel::Graph g2;
    vector<vector<int>> weightedGraph = {
        {0, 1, 1},
        {1, 0, 2},
        {1, 2, 0}};
    g2.loadGraph(weightedGraph);
    ariel::Graph g3 = g1 + g2;
    vector<vector<int>> expectedGraph = {
        {0, 2, 1},
        {2, 0, 3},
        {1, 3, 0}};
    // CHECK(g3.printGraph() == "[0, 2, 1]\n[2, 0, 3]\n[1, 3, 0]");
}

TEST_CASE("Test graph multiplication")
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph);
    ariel::Graph g2;
    vector<vector<int>> weightedGraph = {
        {0, 1, 1},
        {1, 0, 2},
        {1, 2, 0}};
    g2.loadGraph(weightedGraph);
    ariel::Graph g4 = g1 * g2;
    vector<vector<int>> expectedGraph = {
        {0, 0, 2},
        {1, 0, 1},
        {1, 0, 0}};
    // CHECK(g4.printGraph() == "[0, 0, 2]\n[1, 0, 1]\n[1, 0, 0]");
}

TEST_CASE("Invalid operations")
{
    ariel::Graph g1;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g1.loadGraph(graph);
    ariel::Graph g2;
    vector<vector<int>> weightedGraph = {
        {0, 1, 1, 1},
        {1, 0, 2, 1},
        {1, 2, 0, 1}};
    CHECK_THROWS(g2.loadGraph(weightedGraph));
    ariel::Graph g5;
    vector<vector<int>> graph2 = {
        {0, 1, 0, 0, 1},
        {1, 0, 1, 0, 0},
        {0, 1, 0, 1, 0},
        {0, 0, 1, 0, 1},
        {1, 0, 0, 1, 0}};
    g5.loadGraph(graph2);
    CHECK_THROWS(g5 * g1);
    CHECK_THROWS(g1 * g2);

    // Addition of two graphs with different dimensions
    ariel::Graph g6;
    vector<vector<int>> graph3 = {
        {0, 1, 0, 0, 1},
        {1, 0, 1, 0, 0},
        {0, 1, 0, 1, 0},
        {0, 0, 1, 0, 1},
        {1, 0, 0, 1, 0}};
    g6.loadGraph(graph3);
    CHECK_THROWS(g1 + g6);
}
TEST_CASE("Test empty graph initialization") {
    ariel::Graph g;
    vector<vector<int>> emptyGraph = {};
    CHECK_THROWS_AS(g.loadGraph(emptyGraph), invalid_argument);
}


TEST_CASE("Test unary plus operator") {
    ariel::Graph g;
    vector<vector<int>> graph = {{1, -1}, {-1, 1}};
    g.loadGraph(graph);
    ariel::Graph gPlus = +g;
    CHECK(gPlus == g);
}

TEST_CASE("Test unary minus operator") {
    ariel::Graph g;
    vector<vector<int>> graph = {{1, -1}, {-1, 1}};
    g.loadGraph(graph);
    ariel::Graph gNeg = -g;
    vector<vector<int>> expectedGraph = {{-1, 1}, {1, -1}};
    CHECK(gNeg.getMatrixGraph() == expectedGraph);
}

TEST_CASE("Test pre-increment operator") {
    ariel::Graph g;
    vector<vector<int>> graph = {{0, 1}, {1, 0}};
    g.loadGraph(graph);
    ++g;
    vector<vector<int>> expectedGraph = {{1, 2}, {2, 1}};
    CHECK(g.getMatrixGraph() == expectedGraph);
}

TEST_CASE("Test pre-decrement operator") {
    ariel::Graph g;
    vector<vector<int>> graph = {{2, 3}, {3, 2}};
    g.loadGraph(graph);
    --g;
    vector<vector<int>> expectedGraph = {{1, 2}, {2, 1}};
    CHECK(g.getMatrixGraph() == expectedGraph);
}

TEST_CASE("Graph scalar multiplication and assignment") {
    ariel::Graph g;
    vector<vector<int>> graph = {{1, 2}, {3, 4}};
    g.loadGraph(graph);
    g *= 2;
    vector<vector<int>> expectedGraph = {{2, 4}, {6, 8}};
    CHECK(g.getMatrixGraph() == expectedGraph);
}

TEST_CASE("Graph scalar division and assignment") {
    ariel::Graph g;
    vector<vector<int>> graph = {{2, 4}, {6, 8}};
    g.loadGraph(graph);
    g /= 2;
    vector<vector<int>> expectedGraph = {{1, 2}, {3, 4}};
    CHECK(g.getMatrixGraph() == expectedGraph);
}

TEST_CASE("Test equality operator") {
    ariel::Graph g1, g2;
    vector<vector<int>> graph = {{1, 0}, {0, 1}};
    g1.loadGraph(graph);
    g2.loadGraph(graph);
    CHECK(g1 == g2);
}

TEST_CASE("Test inequality operator") {
    ariel::Graph g1, g2;
    vector<vector<int>> graph1 = {{1, 0}, {0, 1}};
    vector<vector<int>> graph2 = {{0, 1}, {1, 0}};
    g1.loadGraph(graph1);
    g2.loadGraph(graph2);
    CHECK(g1 != g2);
}

TEST_CASE("Test less than operator") {
    ariel::Graph g1, g2;
    vector<vector<int>> graph1 = {{0, 1}, {1, 0}};
    vector<vector<int>> graph2 = {{0, 0}, {0, 0}};
    g1.loadGraph(graph1);
    g2.loadGraph(graph2);
    bool d = g2 < g1;
    CHECK(d);
}

TEST_CASE("Test greater than operator") {
    ariel::Graph g1, g2;
    vector<vector<int>> graph1 = {{0, 1}, {1, 0}};
    vector<vector<int>> graph2 = {{0, 0}, {0, 0}};
    g1.loadGraph(graph1);
    g2.loadGraph(graph2);
    bool d = g1 > g2;
    CHECK(d);
}

TEST_CASE("Test less than or equal to operator") {
    ariel::Graph g1, g2;
    vector<vector<int>> graph1 = {{1, 0}, {0, 1}};
    vector<vector<int>> graph2 = {{0, 0}, {0, 0}};
    g1.loadGraph(graph1);
    g2.loadGraph(graph2);
    CHECK(g2 <= g1);
    CHECK(g1 <= g1); // Equality implies less than or equal
}

TEST_CASE("Test greater than or equal to operator") {
    ariel::Graph g1, g2;
    vector<vector<int>> graph1 = {{1, 0}, {0, 1}};
    vector<vector<int>> graph2 = {{0, 0}, {0, 0}};
    g1.loadGraph(graph1);
    g2.loadGraph(graph2);
    CHECK(g1 >= g2);
    CHECK(g1 >= g1); // Equality implies greater than or equal
}

TEST_CASE("Test throwing division by zero") {
    ariel::Graph g;
    vector<vector<int>> graph = {{2, 4}, {6, 8}};
    g.loadGraph(graph);
    CHECK_THROWS_AS(g /= 0, invalid_argument);
}

TEST_CASE("Test adding graphs with incompatible sizes") {
    ariel::Graph g1, g2;
    vector<vector<int>> graph1 = {{1}};
    vector<vector<int>> graph2 = {{1, 2}, {3, 4}};
    g1.loadGraph(graph1);
    g2.loadGraph(graph2);
    CHECK_THROWS(g1 + g2);
}

TEST_CASE("Test subtracting graphs with incompatible sizes") {
    ariel::Graph g1, g2;
    vector<vector<int>> graph1 = {{1, 2}, {3, 4}};
    vector<vector<int>> graph2 = {{1}};
    g1.loadGraph(graph1);
    g2.loadGraph(graph2);
    CHECK_THROWS(g1 - g2);
}

TEST_CASE("Check isDirected classification") {
    ariel::Graph g;
    vector<vector<int>> directedGraph = {{0, 1}, {0, 0}};
    g.loadGraph(directedGraph);
    CHECK(g.getIsDirected() == true);
}

TEST_CASE("Check undirected graph classification") {
    ariel::Graph g;
    vector<vector<int>> undirectedGraph = {{0, 1}, {1, 0}};
    g.loadGraph(undirectedGraph);
    CHECK(g.getIsDirected() == false);
}

TEST_CASE("Check graph addition with correct dimensions but different edge counts") {
    ariel::Graph g1, g2;
    vector<vector<int>> graph1 = {{1, 2}, {3, 4}};
    vector<vector<int>> graph2 = {{1, 2}, {3, 4}};
    g1.loadGraph(graph1);
    g2.loadGraph(graph2);
    ariel::Graph g3 = g1 + g2;
    vector<vector<int>> expectedGraph = {{2, 4}, {6, 8}};
    CHECK(g3.getMatrixGraph() == expectedGraph);
}

TEST_CASE("Check graph multiplication with correct dimensions but different edge counts") {
    ariel::Graph g1, g2;
    vector<vector<int>> graph1 = {{1, 2}, {3, 4}};
    vector<vector<int>> graph2 = {{1, 0}, {0, 1}};
    g1.loadGraph(graph1);
    g2.loadGraph(graph2);
    ariel::Graph g3 = g1 * g2;
    vector<vector<int>> expectedGraph = {{1, 2}, {3, 4}};
    CHECK(g3.getMatrixGraph() == expectedGraph);
}

TEST_CASE("Verify number of edges in Graph") {
    ariel::Graph g;
    vector<vector<int>> graph = {{0, 1}, {1, 0}};
    g.loadGraph(graph);
    CHECK(g.getNumOfEdges() == 1);  // Assuming undirected graph
}

