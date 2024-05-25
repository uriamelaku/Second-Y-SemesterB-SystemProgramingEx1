# Graphs and Algorithms
This project is a simple design of a graph data structure in C++, along with basic graph algorithms. The project supports both undirected and directed graphs.

Features
Creation of a graph object and specification of whether it is directed or not.
Loading a graph from a two-dimensional adjacency matrix.
The adjacency matrix must be square (number of rows equals number of columns).
For undirected graphs, the adjacency matrix must be symmetric.
Graph Class
Graph.cpp
Class Functions:
loadGraph: Loads a graph from an adjacency matrix.
printGraph: Prints the number of vertices and edges in the graph.
size: Returns the number of vertices in the graph.
getMatrix: Returns the adjacency matrix of the graph as a two-dimensional vector.
isDirected: Returns whether the graph is directed.
Algorithms.cpp
Contains implementations of various functions for graphs.

Functions:
isConnected: Checks if the graph is connected.

Implementation:
The function uses Depth-First Search (DFS) starting from a given node.
The DFS function marks nodes as visited during the search.
The isConnected function performs DFS from each node in the graph and checks if all neighbors are visited. If not all are visited, the graph is not connected.
shortestPath: Finds the shortest path between two vertices based on the type of the graph:

Bellman-Ford for weighted graphs.
BFS for unweighted graphs.
The function uses PrintShortestPath to print the shortest path.
isBipartite: Checks if a given graph is bipartite. A bipartite graph is a graph that can be divided into two disjoint sets such that no edge connects two vertices in the same set.

The function receives the adjacency matrix of the graph.
Initializes a color vector with the value -1 to indicate that vertices are not yet colored.
Uses two vectors, A and B, to store the vertices of each set.
Uses Breadth-First Search (BFS):
For each vertex, if it is not colored, color it with color 0 and start BFS from that vertex.
During BFS, color the neighboring vertices with the opposite color. If an edge is found where both vertices are the same color, the function returns -1, indicating that the graph is not bipartite.
isContainsCycle: Checks if the graph contains a cycle and returns the cycle if it exists.

DFS – Helper function: Performs depth-first search in the graph. If a cycle is found, the function returns the path of the cycle in textual format.
isContainsCycle calls the DFS function on each node in the graph to check if a cycle exists.
Algorithm:
The function defines a color array to check the state of each node (unvisited, visiting, visited). Additionally, it defines a parent array to track the nodes during the search.
Then, it performs depth-first search for each unvisited node.
If a cycle is found during the search, the function returns the cycle in textual format.
negativeCycle: Implements the Bellman-Ford algorithm to find a negative cycle in a directed weighted graph.

The algorithm performs relaxation on all edges in the graph V times, where V is the number of vertices.
During each iteration, if a shorter path is found, the algorithm updates the distance and parent of the current vertex.
At the end of the iterations, if relaxation still occurs, it indicates the presence of a negative cycle.
If relaxation occurs in the last iteration, the algorithm finds the vertex involved in the negative cycle by tracing back through the parent array.
The algorithm constructs the path of the negative cycle and returns it as a string.
Additional Files
demo: Contains main demonstrating the use of the functions.
tests: Contains tests checking edge cases for all functions.
Makefile:
To run the program and demo file, type in the terminal: make run
To run and check the tests, type: make test
Installation and Running Instructions
Clone the repository.
Compile the code using make.
Run the demo with make run.
Test the functions with make test.
