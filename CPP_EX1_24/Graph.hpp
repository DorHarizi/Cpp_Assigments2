#pragma once

#include <vector>
#include <iostream>
using namespace std;

namespace ariel {
    class Graph {
        private:
            vector<vector<int>> matrixGraph;
            int numOfEdges;
            bool isDirected;  // True if the graph is directed, false if undirected

        public:
            Graph();
            void loadGraph(vector<vector<int>>& matrix);
            void printGraph();
            void classifyGraph();
            bool getIsDirected(); 
            vector<vector<int>>& getMatrixGraph();
        };
}