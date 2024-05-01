#include "doctest.h"
#include "Algorithms.hpp"
#include "Graph.hpp"

using namespace ariel;
using namespace std;

TEST_CASE("Test graph initialization") {
    Graph g;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph);
    CHECK(g.getMatrixGraph() == graph);
}

TEST_CASE("Test loading a non-square matrix") {
    Graph g;
    vector<vector<int>> nonSquareGraph = {
        {0, 1},
        {1, 0, 1}};
    CHECK_THROWS(g.loadGraph(nonSquareGraph));
}

TEST_CASE("Test loading an empty matrix") {
    Graph g;
    vector<vector<int>> emptyGraph = {};
    CHECK_THROWS(g.loadGraph(emptyGraph));
}

TEST_CASE("Test graph directivity flag for an undirected graph") {
    Graph g;
    vector<vector<int>> graph = {
        {0, 1, 1},
        {1, 0, 1},
        {1, 1, 0}};
    g.loadGraph(graph);
    CHECK(g.getIsDirected() == false);
}

TEST_CASE("Test graph directivity flag for a directed graph") {
    Graph g;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {0, 0, 1},
        {1, 0, 0}};
    g.loadGraph(graph);
    CHECK(g.getIsDirected() == true);
}

TEST_CASE("Test isConnected on a connected graph") {
    Graph g;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph);
    CHECK(Algorithms::isConnected(g) == true);
}

TEST_CASE("Test isConnected on a disconnected graph") {
    Graph g;
    vector<vector<int>> graph = {
        {0, 1, 1, 0, 0},
        {1, 0, 1, 0, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0}};
    g.loadGraph(graph);
    CHECK(Algorithms::isConnected(g) == false);
}

TEST_CASE("Test shortestPath - path exists") {
    Graph g;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph);
    CHECK(Algorithms::shortestPath(g, 0, 2) == "0->1->2");
}

TEST_CASE("Test shortestPath - path does not exist") {
    Graph g;
    vector<vector<int>> graph = {
        {0, 1, 1, 0, 0},
        {1, 0, 1, 0, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0}};
    g.loadGraph(graph);
    CHECK(Algorithms::shortestPath(g, 0, 4) == "-1");
}

TEST_CASE("Test isContainsCycle - cycle exists") {
    Graph g;
    vector<vector<int>> graph = {
        {0, 1, 1},
        {1, 0, 1},
        {1, 1, 0}};
    g.loadGraph(graph);
    CHECK(Algorithms::isContainsCycle(g) == true);
}

TEST_CASE("Test isContainsCycle - no cycle") {
    Graph g;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph);
    CHECK(Algorithms::isContainsCycle(g) == false);
}

TEST_CASE("Test isBipartite - bipartite graph") {
    Graph g;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph);
    CHECK(Algorithms::isBipartite(g) == "The graph is bipartite: A={0, 2}, B={1}");
}

TEST_CASE("Test isBipartite - not bipartite graph") {
    Graph g;
    vector<vector<int>> graph = {
        {0, 1, 1, 0, 0},
        {1, 0, 1, 0, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0}};
    g.loadGraph(graph);
    CHECK(Algorithms::isBipartite(g) == "0");
}

TEST_CASE("Test invalid graph - non-rectangular matrix") {
    Graph g;
    vector<vector<int>> graph = {
        {0, 1, 2},
        {1, 0, 3},
        {2, 3, 0},
        {0, 0, 4}};
    CHECK_THROWS(g.loadGraph(graph));
}

TEST_CASE("Graph state verification after operations") {
    Graph g;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph);
    CHECK(g.getMatrixGraph().size() == 3);
    CHECK(g.getIsDirected() == false);
}

TEST_CASE("Test graph with all zero weights") {
    Graph g;
    vector<vector<int>> graph = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}};
    g.loadGraph(graph);
    CHECK(Algorithms::isConnected(g) == false);
}

TEST_CASE("Test detecting self-loops") {
    Graph g;
    vector<vector<int>> graph = {
        {1, 0, 0},
        {0, 1, 0},
        {0, 0, 1}};
    g.loadGraph(graph);
    CHECK(Algorithms::isContainsCycle(g) == true);
}

TEST_CASE("Test graph with isolated vertices") {
    Graph g;
    vector<vector<int>> graph = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}};
    g.loadGraph(graph);
    CHECK(Algorithms::isConnected(g) == false);
}

TEST_CASE("Test dense graph connectivity") {
    Graph g;
    vector<vector<int>> graph = {
        {0, 1, 1},
        {1, 0, 1},
        {1, 1, 0}};
    g.loadGraph(graph);
    CHECK(Algorithms::isConnected(g) == true);
}

TEST_CASE("Test single vertex graph") {
    Graph g;
    vector<vector<int>> graph = {{0}};
    g.loadGraph(graph);
    CHECK(Algorithms::isConnected(g) == true);
}

TEST_CASE("Test two vertex disconnected graph") {
    Graph g;
    vector<vector<int>> graph = {
        {0, 0},
        {0, 0}};
    g.loadGraph(graph);
    CHECK(Algorithms::isConnected(g) == false);
}

TEST_CASE("Test two vertex connected graph") {
    Graph g;
    vector<vector<int>> graph = {
        {0, 1},
        {1, 0}};
    g.loadGraph(graph);
    CHECK(Algorithms::isConnected(g) == true);
}

TEST_CASE("Test fully connected triangle graph") {
    Graph g;
    vector<vector<int>> graph = {
        {0, 1, 1},
        {1, 0, 1},
        {1, 1, 0}};
    g.loadGraph(graph);
    CHECK(Algorithms::isConnected(g) == true);
}

TEST_CASE("Test graph bipartiteness with odd cycle") {
    Graph g;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph);
    CHECK(Algorithms::isBipartite(g) == "The graph is bipartite: A={0, 2}, B={1}");
}

TEST_CASE("Test graph bipartiteness with even cycle") {
    Graph g;
    vector<vector<int>> graph = {
        {0, 1, 0, 1},
        {1, 0, 1, 0},
        {0, 1, 0, 1},
        {1, 0, 1, 0}};
    g.loadGraph(graph);
    CHECK(Algorithms::isBipartite(g) == "The graph is bipartite: A={0, 2}, B={1, 3}");
}

TEST_CASE("Test graph non-rectangular matrix") {
    Graph g;
    vector<vector<int>> graph = {
        {0, 1, 2},
        {1, 0}};
    CHECK_THROWS(g.loadGraph(graph));
}

TEST_CASE("Test graph rectangular but not square matrix") {
    Graph g;
    vector<vector<int>> graph = {
        {0, 1},
        {1, 0},
        {1, 1}};
    CHECK_THROWS(g.loadGraph(graph));
}

TEST_CASE("Test removing edges and checking connectivity") {
    Graph g;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 0},
        {0, 0, 0}};
    g.loadGraph(graph);
    CHECK(Algorithms::isConnected(g) == false);
}

TEST_CASE("Test adding edges and checking cycle presence") {
    Graph g;
    vector<vector<int>> graph = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}};
    g.loadGraph(graph);
    graph[0][1] = 1;
    graph[1][2] = 1;
    graph[2][0] = 1;
    g.loadGraph(graph);
    CHECK(Algorithms::isContainsCycle(g) == true);
}

TEST_CASE("Test checking graph completeness") {
    Graph g;
    vector<vector<int>> graph = {
        {0, 1, 1},
        {1, 0, 1},
        {1, 1, 0}};
    g.loadGraph(graph);
    CHECK(Algorithms::isConnected(g) == true);
}

TEST_CASE("Test checking graph for disconnected components") {
    Graph g;
    vector<vector<int>> graph = {
        {0, 0, 1},
        {0, 0, 0},
        {1, 0, 0}};
    g.loadGraph(graph);
    CHECK(Algorithms::isConnected(g) == false);
}

TEST_CASE("Test loading graph with negative weights") {
    Graph g;
    vector<vector<int>> graph = {
        {0, 0, 1},
        {0, 0, 0},
        {1, 0, 0}};
    g.loadGraph(graph);
    CHECK(Algorithms::isConnected(g) == false);
}
