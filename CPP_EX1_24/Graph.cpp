#include "Graph.hpp"
#include <stdexcept>
#include <iostream>
#include <limits>

using namespace std;

namespace ariel {
    Graph::Graph():isDirected(false){} 

    void Graph::loadGraph(vector<vector<int>>& matrix) {
        if (matrix.empty()){
            throw invalid_argument("Invalid graph: The graph is not a square matrix.");
        }
        for(size_t i = 0; i < matrix.size(); i++){
            if (matrix.size() != matrix[i].size()) {
            throw invalid_argument("Invalid graph: The graph is not a square matrix.");
            }
        }
        matrixGraph = matrix;
        classifyGraph();
    }

    bool Graph::getIsDirected(){
        return isDirected; 
    }

    void Graph::classifyGraph() {
        isDirected = false;
        numOfEdges = 0;
        for (size_t i = 0; i < matrixGraph.size(); ++i) {
            for (size_t j = 0; j < matrixGraph.size(); ++j) {
                if (matrixGraph[i][j] != matrixGraph[j][i]) {
                    isDirected = true;
                }
            }
        }
        for (size_t i = 0; i < matrixGraph.size(); ++i) {
            for (size_t j = 0; j < matrixGraph.size(); ++j) {
                if (matrixGraph[i][j] != 0) {
                    if (isDirected) {
                        numOfEdges++;
                    } else {
                        if (i < j) {
                            numOfEdges++;
                            numOfEdges++;
                        }
                    }
                }
            }
        }
    }

    void Graph::printGraph(){
        cout << "Graph with " << matrixGraph.size() << " vertices and " << numOfEdges << " edges";
        cout << (isDirected ? " (Directed)." : " (Undirected).") << endl;
    }
    vector<vector<int>>& Graph::getMatrixGraph(){
        return matrixGraph;
    }
}
