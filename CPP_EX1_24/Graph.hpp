#pragma once

#include <vector>
#include <iostream>
using namespace std;

namespace ariel {
    class Graph {
        private:
            vector<vector<int>> matrixGraph;
            int numOfEdges;
            bool isDirected; 

        public:
            Graph();
            void loadGraph(vector<vector<int>>& matrix);
            void printGraph();
            void classifyGraph();
            bool getIsDirected(); 
            vector<vector<int>>& getMatrixGraph();
        };
}