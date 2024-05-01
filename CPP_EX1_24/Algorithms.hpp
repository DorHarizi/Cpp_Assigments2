#pragma once

#include "Graph.hpp"
#include <vector> 

namespace ariel {
    class Algorithms {
    public:
        static bool isConnected(Graph& g);
        static string shortestPath(Graph& g, size_t src, size_t dest);
        static bool isContainsCycle(Graph& g);
        static string isBipartite(Graph& g);
        static void DFS(size_t start, std::vector<bool>& visited, vector<vector<int>>& matrixGraph);
        static size_t minDistance(std::vector<int>& srcPathDest, vector<bool>& visited);
        static bool dfs(size_t v,vector<bool>& visited, vector<bool>& recStack, vector<vector<int>>& matrixGraph, int parent , bool isDirected);
    };
}
