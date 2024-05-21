// ooriamelaku@gmail.com
// 208734889
#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <climits>
#include <sstream>
#include <algorithm>
#include "Graph.hpp" 
#include "Algorithms.hpp"

using namespace std;

// of isConnected
void ariel::Algorithms::dfs(const vector<vector<int>>& graph, size_t vertex, vector<bool>& visited) {
    visited[vertex] = true;

    for (size_t i = 0; i < graph[vertex].size(); ++i) {
        if (graph[vertex][i] != 0 && !visited[i]) { // Consider any non-zero value as an edge
            dfs(graph, i, visited);
        }
    }
}

string ariel::Algorithms::isConnected(ariel::Graph graph) {
    const vector<vector<int>>& adjacencyMatrix = graph.getMatrix();
    size_t numVertices = graph.size();

    for (size_t startVertex = 0; startVertex < numVertices; ++startVertex) {
        vector<bool> visited(numVertices, false);

        dfs(adjacencyMatrix, startVertex, visited);

        // Check if all vertices are visited
        for (bool isVisited : visited) {
            if (!isVisited) {
                return "-1";
            }
        }
    }

    return "1";
}

string ariel::Algorithms::printShortestPath(int start, int end, const pair<int, vector<int>>& shortestPath) {
    if (shortestPath.first == -1) {
        return "-1";
    } else if (shortestPath.first == numeric_limits<int>::max()) {
        return "-1";
    }

    ostringstream oss;
    for (size_t i = 0; i < shortestPath.second.size(); ++i) {
        oss << shortestPath.second[i];
        if (i != shortestPath.second.size() - 1) {
            oss << " -> ";
        }
    }
    return oss.str();
}

string ariel::Algorithms::shortestPath(ariel::Graph& graph, size_t start, size_t end) {
    vector<vector<int>> adjacencyMatrix = graph.getMatrix();
    size_t numVertices = size_t(adjacencyMatrix.size());
    bool isWeighted = false;
    // Check if the graph is weighted
    for (size_t i = 0; i < numVertices; ++i) {
        for (size_t j = 0; j < numVertices; ++j) {
            if (adjacencyMatrix[i][j] != 0 && adjacencyMatrix[i][j] != 1) {
                isWeighted = true;
                break;
            }
        }
        if (isWeighted) break;
    }

    if (isWeighted) {
        // If weighted, use Bellman-Ford
        vector<size_t> distance((size_t)numVertices, (size_t) numeric_limits<int>::max()); // To store the distance of each node
        vector<int> parent(numVertices, -1); // To store the parent of each node in the shortest path
        distance[start] = 0;
        // Relax edges
        for (size_t i = 0; i < numVertices - 1; ++i) {
            //Run on all the vertices in the graph
            for (size_t u = 0; u < numVertices; ++u) {
                //Run on all the neighbers of the current vertice
                for (size_t v = 0; v < numVertices; ++v) {
                    if (adjacencyMatrix[u][v] != 0 && distance[u] != numeric_limits<int>::max() &&
                        distance[u] + (size_t)adjacencyMatrix[u][v] < distance[v]) 
                        {
                        distance[v] = distance[u] + (size_t)adjacencyMatrix[u][v];
                        parent[v] = u;
                    }
                }
            }
        }

        // Check for a negative-weight cycle by checking ->.. 
        // ..-> if its possible to relax again(after numVertices -1 times)
        for (size_t u = 0; u < numVertices; ++u) {
            for (size_t v = 0; v < numVertices; ++v) {
                if (adjacencyMatrix[u][v] != 0 && distance[u] != numeric_limits<int>::max() &&
                    distance[u] + (size_t)adjacencyMatrix[u][v] < distance[v]) {
                    return "ERROR - Negative cycle found";
                }
            }
        }

        // Reconstruct shortest path
        vector<int> path;
        size_t current = end;
        // if current = -1 it means it has no father so its finish 
        while (current != -1) {
            path.push_back(current);
            current = (size_t)parent[current];
        }
        reverse(path.begin(), path.end());

        return printShortestPath(start, end, {distance[end], path});
    } 
    else {
        // If the graph unweighted, use BFS
        vector<bool> visited(numVertices, false);
        vector<int> parent(numVertices, -1); // To store the parent of each node in the shortest path
        queue<int> q;
        q.push(start);
        visited[start] = true;

        while (!q.empty()) {
            int currentNode = q.front();
            q.pop();

            if (currentNode == end) {
                vector<int> path;
                size_t current = end;
                while (current != -1) {
                    path.push_back(current);
                    current = (size_t)parent[current];
                }
                reverse(path.begin(), path.end());
                return printShortestPath(start, end, {path.size() - 1, path});
            }

            for (size_t neighbor = 0; neighbor < numVertices; ++neighbor) {
                // if there is an edge between the current and the neighber and the beighber hasn't visited 
                if ((size_t)adjacencyMatrix[(size_t)currentNode][neighbor] == 1 && !visited[neighbor]) {
                    // put it into the queie
                    q.push(neighbor);
                    visited[neighbor] = true;
                    parent[neighbor] = currentNode; // Set parent of neighbor
                }
            }
        }
        // there is no path
        return printShortestPath(start, end, {-1, {}});
    }
}

std::string ariel::Algorithms::isBipartite(ariel::Graph& graph) {
    vector<vector<int>> adjacencyMatrix = graph.getMatrix();
    size_t numVertices = graph.size();
    vector<int> color(numVertices, -1); // Initialize color array with -1. -1 means no color
    vector<int> A, B; // Vectors to store the vertices of each set

    for (size_t i = 0; i < numVertices; ++i) {
        if (color[i] == -1) { // If vertex hasn't been colored yet
            color[i] = 0; // Color the vertex with color 0
            A.push_back(i); // Add the vertex to set A
            queue<int> q;
            q.push(i); // Push the vertex into the queue

            while (!q.empty()) {
                // u equals to the first elemnt in the queue
                size_t u = (size_t)q.front();
                q.pop();

                // loop on all the neighbers of the current vertice
                for (size_t v = 0; v < numVertices; ++v) {
                    if (adjacencyMatrix[(size_t)u][v] && color[v] == -1) { // If there's an edge and vertex hasn't colored
                        color[v] = 1 - color[u]; // Color vertex with opposite color of its parent
                        if (color[v] == 0) {
                            A.push_back(v);
                        } else {
                            B.push_back(v);
                        }
                        q.push(v); // Push vertex into the queue
                    } 
                    else if (adjacencyMatrix[u][v] && color[u] == color[v]) { // If there's an edge and vertices have same color
                        return "-1";
                    }
                }
            }
        }
    }

    // Convert the sets to strings
    ostringstream oss;
    oss << "The graph is bipartite: A={";
    for (size_t i = 0; i < A.size(); ++i) {
        oss << A[i];
        if (i != A.size() - 1) {
            oss << ", ";
        }
    }
    oss << "}, B={";
    for (size_t i = 0; i < B.size(); ++i) {
        oss << B[i];
        if (i != B.size() - 1) {
            oss << ", ";
        }
    }
    oss << "}";
    return oss.str();
}

string ariel::Algorithms::dfs(const std::vector<vector<int>>& graph, size_t node, int parentNode, vector<int>& color, vector<int>& parent) {
    color[node] = 1; // Color the vertex with color 1
    parent[node] = parentNode; // Set parent of the node

    for (size_t i = 0; i < graph[node].size(); ++i) {
        if (graph[node][i] != 0) { // If there's an edge
            if (color[i] == 0) { // If vertex hasn't been colored
                string cycle = dfs(graph, i, node, color, parent);
                if (!cycle.empty()) {
                    return cycle;
                }
            } 
            else if (i != parentNode) { // If there's an edge and vertices have same color and it's not the parent
                // Store the vertices of the cycle in a vector
                vector<int> cycle;
                cycle.push_back(i);
                for (size_t j = node; j != i; j = (size_t)parent[j]) {
                    cycle.push_back(j);
                }
                // Create a string of the cycle in reverse order
                ostringstream oss;
                for (auto it = cycle.rbegin(); it != cycle.rend(); ++it) {
                    oss << *it + 1;
                    if (it + 1 != cycle.rend()) {
                        oss << " -> ";
                    }
                }
                return oss.str();
            }
        }
    }

    return "-1";
}

string ariel::Algorithms::isContainsCycle(ariel::Graph& graph) {
    vector<vector<int>> adjacencyMatrix = graph.getMatrix();
    size_t numVertices = (size_t)graph.size();
    vector<int> color(numVertices, 0); // Initialize color array with 0
    vector<int> parent(numVertices, -1); // Initialize parent array with -1

    // loop on every vertice
    for (size_t i = 0; i < numVertices; ++i) {
        if (color[i] == 0) { // If vertex hasn't been colored yet
            string cycle = dfs(adjacencyMatrix, i, -1, color, parent);
            if (cycle != "-1") {
                return cycle ;
            }
        }
    }
    return "-1";
}

std::string ariel::Algorithms::findNegativeCycle(ariel::Graph& graph) {
    const vector<vector<int>>& adjacencyMatrix = graph.getMatrix();
    size_t numVertices = adjacencyMatrix.size();
    vector<int> distance(numVertices, INT_MAX); // Initialize distance array with maximum integer value
    vector<int> predecessor(numVertices, -1); // Initialize predecessor array for path reconstruction
    distance[0] = 0; // Distance from source to source is 0

    int lastRelaxedNode = -1; // To keep track of the last node where relaxation happened

    // Relax all edges
    for (size_t i = 0; i < numVertices; ++i) {
        lastRelaxedNode = -1;
        for (size_t u = 0; u < numVertices; ++u) {
            for (size_t v = 0; v < numVertices; ++v) {
                if (adjacencyMatrix[u][v] != 0 && distance[u] != INT_MAX && distance[u] + adjacencyMatrix[u][v] < distance[v]) {
                    distance[v] = distance[u] + adjacencyMatrix[u][v];
                    predecessor[v] = u;
                    lastRelaxedNode = v;
                }
            }
        }
    }

    // If relaxation happened in the V-th iteration, there is a negative cycle
    if (lastRelaxedNode != -1) {
        // To obtain the actual cycle, we can simply start from the last relaxed node and go backwards for V steps
        size_t cycleNode = (size_t)lastRelaxedNode;
        for (size_t i = 0; i < numVertices; ++i) {
            cycleNode = (size_t)predecessor[cycleNode];
        }

        // Now cycleNode is a node in the cycle, we can reconstruct the cycle path
        vector<int> cyclePath;
        for (size_t v = cycleNode;; v = (size_t)predecessor[v]) {
            cyclePath.push_back(v);
            if (v == cycleNode && cyclePath.size() > 1) {
                break;
            }
        }
        reverse(cyclePath.begin(), cyclePath.end());

        // Convert the cycle path to the desired string format
        ostringstream oss;
        for (size_t i = 0; i < cyclePath.size() - 1; ++i) { // Exclude the last node in the cycle
            oss << cyclePath[i] + 1; // +1 because nodes are 1-indexed in the output
            if (i != cyclePath.size() - 2) { // Adjust this check to exclude the last node in the cycle
                oss << " -> ";
            }
        }
        return oss.str();
    }

    return "-1";
}