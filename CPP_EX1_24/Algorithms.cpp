#include "Algorithms.hpp"
#include "Graph.hpp"
#include <vector>
#include <limits>
#include <queue>
#include <string>
#include <iostream>
#include <algorithm> 

using namespace std;

namespace ariel {
    
    void Algorithms::DFS(size_t start, vector<bool>& visited, vector<vector<int>>& matrixGraph){
        visited[start] = true;
        for(size_t i = 0; i < visited.size(); i++){
            if(matrixGraph[start][i] > 0 && !visited[i]){
                DFS(i, visited, matrixGraph);
            }
        }
    }

    bool Algorithms::isConnected(Graph& g) {
        vector<vector<int>> matrixGraph = g.getMatrixGraph();
        if(matrixGraph.size() == 1) return true;
        vector<bool> visited(matrixGraph.size(), false);
        DFS(0, visited, matrixGraph);
        for(bool vertexVisit: visited){
            if(!vertexVisit) return false; 
        }
        return true;
    }

    size_t Algorithms::minDistance(vector<int>& srcPathDest, vector<bool>& visited) {
    size_t min_index = numeric_limits<size_t>::max();
    int min = numeric_limits<int>::max();
    for (size_t v = 0; v < srcPathDest.size(); v++)
        if (!visited[v] && srcPathDest[v] <= min) {
            min = srcPathDest[v];
            min_index = v;
        }
    return min_index;
    }

    string Algorithms::shortestPath(Graph& g, size_t src, size_t dest) {
        vector<vector<int>> matrixGraph = g.getMatrixGraph();
        vector<bool> visited(matrixGraph.size(), false);
        vector<int> srcPathDest(matrixGraph.size(), numeric_limits<int>::max());
        vector<int> predecessor(matrixGraph.size(), -1);
        srcPathDest[src] = 0; 
        for (size_t count = 0; count < matrixGraph.size() - 1; count++) {
            size_t u = minDistance(srcPathDest, visited);
            if (u == -1) break; // No more reachable vertices
            visited[u] = true;
            for (size_t v = 0; v < matrixGraph.size(); v++) {
                if (!visited[v] && matrixGraph[u][v] && srcPathDest[u] != numeric_limits<int>::max() &&
                    srcPathDest[u] + matrixGraph[u][v] < srcPathDest[v]) {
                    srcPathDest[v] = srcPathDest[u] + matrixGraph[u][v];
                    predecessor[v] = u; // Track the path
                }
            }
        }
        vector<size_t> path;
        size_t at = dest;
        while (at != numeric_limits<size_t>::max() && predecessor[at] != -1) {
            path.push_back(at);
            at = static_cast<size_t>(predecessor[at]);
        }
        if (at == src) { // Check if we've traced back to the source
            path.push_back(src);
        } else {
            return "-1";
        }
        reverse(path.begin(), path.end());
        // Build the string for the path src -> dest
        string result;
        for (size_t i = 0; i < path.size(); ++i) {
            result += to_string(path[i]); 
            if (i < path.size() - 1) {
                result += "->";
            }
        }
        return result;
    }

    bool Algorithms::dfs(size_t v,vector<bool>& visited, vector<bool>& recStack, vector<vector<int>>& matrixGraph, int parent = -1, bool isDirected = false) {
    visited[v] = true;
    recStack[v] = true;
    for (size_t i = 0; i < matrixGraph[v].size(); i++) {
        if (matrixGraph[v][i] != 0) {  // There's an edge from v to i
            if (!visited[i]) {  
                if (dfs(i, visited, recStack, matrixGraph, v, isDirected)) {
                    return true;  // If cycle is found
                }
            } else if (isDirected && recStack[i]) {
                return true;  // If it's a directed graph and i is in recStack, cycle found
            } else if (!isDirected && i != parent) {
                return true;  // If it's an undirected graph and i is not the parent, cycle found
            }
        }
    }
    recStack[v] = false; 
    return false;  // No cycle found starting from v
    }

    bool Algorithms::isContainsCycle(Graph& g) {
        vector<vector<int>>& matrixGraph = g.getMatrixGraph();
        vector<bool> visited(matrixGraph.size(), false);
        vector<bool> recStack(matrixGraph.size(), false);
        bool isDirected = g.getIsDirected();
        for (size_t i = 0; i < matrixGraph.size(); i++) {
            if (!visited[i]) {
                if (dfs(i, visited, recStack, matrixGraph, -1, isDirected)) {
                    return true;
                }
            }
        }
    return false;
    }

    string Algorithms::isBipartite(Graph& g) {
        vector<vector<int>>& matrixGraph = g.getMatrixGraph();
        vector<int> color(matrixGraph.size(), -1);  
        vector<int> setA, setB;
        
        for (size_t start = 0; start < matrixGraph.size(); ++start) {
            if (color[start] == -1) {
                queue<int> q;
                q.push(start);
                color[start] = 0; 
                setA.push_back(start);

                while (!q.empty()) {
                    size_t u = static_cast<size_t>(q.front());
                    q.pop();

                    for (size_t v = 0; v < matrixGraph[u].size(); ++v) {
                        if (matrixGraph[u][v] > 0) {  // Check if there is a weight, indicating an edge
                            if (color[v] == -1) {
                                color[v] = 1 - color[u];  
                                q.push(v);
                                if (color[v] == 0) {
                                    setA.push_back(v);
                                } else {
                                    setB.push_back(v);
                                }
                            } else if (color[v] == color[u]) {
                                return "0";  // Not bipartite if two adjacent vertices have the same color
                            }
                        }
                    }
                }
            }
        }
        string output = "The graph is bipartite: A={";
        for (size_t i = 0; i < setA.size(); ++i) {
            output += to_string(setA[i]);
            output += (i < setA.size() - 1) ? ", " : "}, B={";
        }
        for (size_t i = 0; i < setB.size(); ++i) {
            output += to_string(setB[i]);
            output += (i < setB.size() - 1) ? ", " : "}";
        }
        return output;
    }
}

