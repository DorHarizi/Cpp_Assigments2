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
            int getNumOfEdges();

            Graph operator+(const Graph& other);
            Graph operator+() const;
            Graph operator+=(const Graph& other);
            Graph operator-() const;
            Graph operator-(const Graph& other);
            Graph& operator--();
            Graph& operator++();
            Graph operator*(int scalar);
            Graph& operator*=(int scalar);
            Graph& operator/=(int scalar);
            Graph operator*(const Graph& other);
            bool operator==(const Graph& other) const;
            bool operator!=(const Graph& other) const;
            bool operator<(Graph& other);
            bool operator<=(Graph& other);
            bool operator>(Graph& other);
            bool operator>=(Graph& other);
            friend ostream& operator<<(ostream& os, Graph& graph);
        };
}