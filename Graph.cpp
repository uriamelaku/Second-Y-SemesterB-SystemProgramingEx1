// ooriamelaku@gmail.com
// 208734889
#include "Graph.hpp"

using namespace std;
using namespace ariel;

void Graph::loadGraph(vector<vector<int>> graph) {
    for (const auto& row : graph) {
        if (row.size() != graph.size()) {
            cout << "Invalid graph: The graph is not a square matrix." << endl;
            return;
        }
    }
    this->graph = graph;
}

void Graph::printGraph() {
    int numVertices = graph.size();
    int numEdges = 0;

    // Count the number of edges
    for (size_t i = 0; i < graph.size(); ++i) {
        for (size_t j = i + 1; j < graph[i].size(); ++j) {
            if (graph[i][j] != 0) {
                numEdges++;
            }
            if (graph[j][i] != 0) { 
                numEdges++;
            }
        }
    }
    // For undirected graphs, divide by 2 since each edge is counted twice
    if (!isDirected()) {
        numEdges /= 2;
    }
    cout << "Graph with " << numVertices << " vertices and " << numEdges << " edges." << endl;
}

size_t Graph::size() const {
    return (size_t)graph.size();
}

const vector<vector<int>>& Graph::getMatrix() const {
    return graph;
}

bool Graph::isDirected() {
    for (size_t i = 0; i < graph.size(); ++i) {
        for (size_t j = i + 1; j < graph[i].size(); ++j) {
            // If there's an edge from i to j or from j to i, but not both, the graph is directed
            if ((graph[i][j] != 0 && graph[j][i] == 0) || (graph[i][j] == 0 && graph[j][i] != 0)) {
                return true;
            }
            // If both edges exist but have different weights, the graph is directed
            if (graph[i][j] != graph[j][i]) {
                return true;
            }
        }
    }
    return false;
}
