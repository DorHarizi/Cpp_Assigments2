#include "Graph.hpp"
#include <stdexcept>
#include <iostream>
#include <limits>

using namespace std;

namespace ariel {
    Graph::Graph():numOfEdges(0), isDirected(false){}

    int Graph::getNumOfEdges(){
        return this->numOfEdges;
    } 

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

    Graph Graph::operator+(const Graph& other){
    if (matrixGraph.size() != other.matrixGraph.size() || matrixGraph[0].size() != other.matrixGraph[0].size()) {
        throw invalid_argument("Cannot add graphs of different sizes");
    }

    Graph resultGraph;
    for (size_t i = 0; i < matrixGraph.size(); ++i) {
        vector<int> row;
        for (size_t j = 0; j < matrixGraph[i].size(); ++j) {
            row.push_back(matrixGraph[i][j] + other.matrixGraph[i][j]);
        }
        resultGraph.getMatrixGraph().push_back(row);
    }

    return resultGraph;
    }

    Graph Graph::operator+=(const Graph& other){
        if (matrixGraph.size() != other.matrixGraph.size() || matrixGraph[0].size() != other.matrixGraph[0].size()) {
            throw invalid_argument("Cannot add graphs of different sizes");
        }

        Graph resultGraph(*this);
        for (size_t i = 0; i < matrixGraph.size(); ++i) {
            for (size_t j = 0; j < matrixGraph[i].size(); ++j) {
                resultGraph.getMatrixGraph()[i][j] += other.matrixGraph[i][j];
            }
        }
        return resultGraph;
    }

    // Unary plus operator
    Graph Graph::operator+()const{
        return *this;
    }

    Graph Graph::operator-(const Graph& other) {
        if (matrixGraph.size() != other.matrixGraph.size() || matrixGraph[0].size() != other.matrixGraph[0].size()) {
            throw invalid_argument("Cannot subtract graphs of different sizes");
        }
        Graph resultGraph;
        for (size_t i = 0; i < matrixGraph.size(); ++i) {
            vector<int> row;
            for (size_t j = 0; j < matrixGraph[i].size(); ++j) {
                row.push_back(matrixGraph[i][j] - other.matrixGraph[i][j]);
            }
            resultGraph.getMatrixGraph().push_back(row);
        }
        return resultGraph;
    }

    // Unary minus operator
    Graph Graph::operator-() const {
        Graph resultGraph(*this);
        for (size_t i = 0; i < matrixGraph.size(); ++i) {
            for (size_t j = 0; j < matrixGraph[i].size(); ++j) {
                resultGraph.getMatrixGraph()[i][j] = -resultGraph.getMatrixGraph()[i][j];
            }
        }
        return resultGraph;
    }

    // Pre-increment operator
    Graph& Graph::operator++() {
        // Increment all elements by 1
        for (size_t i = 0; i < matrixGraph.size(); ++i) {
            for (size_t j = 0; j < matrixGraph[i].size(); ++j) {
                ++matrixGraph[i][j];
            }
        }
        return *this;
    }

    // Pre-decrement operator
    Graph& Graph::operator--() {
        // Decrement all elements by 1
        for (size_t i = 0; i < matrixGraph.size(); ++i) {
            for (size_t j = 0; j < matrixGraph[i].size(); ++j) {
                --matrixGraph[i][j];
            }
        }
        return *this;
    }

    Graph Graph::operator*(int scalar) {
        Graph resultGraph(*this);
        for (size_t i = 0; i < matrixGraph.size(); ++i) {
            for (size_t j = 0; j < matrixGraph[i].size(); ++j) {
                resultGraph.getMatrixGraph()[i][j] *= scalar;
            }
        }
        return resultGraph;
    }

    Graph Graph::operator*(const Graph& other) {
        if (matrixGraph[0].size() != other.matrixGraph.size()) {
            throw invalid_argument("The number of columns in the first matrix must be equal to the number of rows in the second matrix.");
        }

        Graph resultGraph;
        for (size_t i = 0; i < matrixGraph.size(); ++i) {
            vector<int> row;
            for (size_t j = 0; j < other.matrixGraph[0].size(); ++j) {
                int sum = 0;
                for (size_t k = 0; k < matrixGraph[i].size(); ++k) {
                    sum += matrixGraph[i][k] * other.matrixGraph[k][j];
                }
                row.push_back(sum);
            }
            resultGraph.getMatrixGraph().push_back(row);
        }
        return resultGraph;
    }

    bool Graph::operator==(const Graph& other) const {
        if (matrixGraph.size() != other.matrixGraph.size() || matrixGraph[0].size() != other.matrixGraph[0].size()) {
            return false;
        }
        for (size_t i = 0; i < matrixGraph.size(); ++i) {
            for (size_t j = 0; j < matrixGraph[i].size(); ++j) {
                if (matrixGraph[i][j] != other.matrixGraph[i][j]) {
                    return false;
                }
            }
        }
        return true;
    }

    bool Graph::operator!=(const Graph& other) const {
        return !(*this == other);
    }

    bool Graph::operator<(Graph& other){
        // printf("%d > %d", this->getNumOfEdges(), other.getNumOfEdges());
        bool res = this->getNumOfEdges() < other.getNumOfEdges();
        return res;
    }

    bool Graph::operator<= (Graph& other){
        bool res = this->getNumOfEdges() <= other.getNumOfEdges();
        return res;
    }

    bool Graph::operator>(Graph& other){
        // printf("%d > %d", this->getNumOfEdges(), other.getNumOfEdges());
        bool res = this->getNumOfEdges() > other.getNumOfEdges();
        return res;
    }

    bool Graph::operator>=(Graph& other){
        bool res = this->getNumOfEdges() >= other.getNumOfEdges();
        return res;
    }

    Graph& Graph::operator*=(int scalar) {
        for (size_t i = 0; i < matrixGraph.size(); ++i) {
            for (size_t j = 0; j < matrixGraph[i].size(); ++j) {
                matrixGraph[i][j] *= scalar;
            }
        }
        return *this;
    }

    Graph& Graph::operator/=(int scalar) {
        // Divide all elements by scalar (assuming scalar != 0)
        if (scalar == 0) {
            throw invalid_argument("Division by zero");
        }
        for (size_t i = 0; i < matrixGraph.size(); ++i) {
            for (size_t j = 0; j < matrixGraph[i].size(); ++j) {
                matrixGraph[i][j] /= scalar;
            }
        }
        return *this;
    }

    ostream& operator<<(ostream& os, Graph& graph) {
        vector<vector<int>> matrix = graph.getMatrixGraph();
        for (size_t i = 0; i < matrix.size(); ++i) {
            const vector<int>& row = matrix[i];
            for (size_t j = 0; j < row.size(); ++j) {
                int weight = row[j];
                os << weight << " ";
            }
            os << endl;
        }
        return os;
    }
}
