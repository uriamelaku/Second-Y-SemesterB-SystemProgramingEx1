// ooriamelaku@gmail.com
// 208734889
#ifndef GRAPH_FUNCTIONS_H
#define GRAPH_FUNCTIONS_H

#include <vector>
#include <iostream>
#include "Graph.hpp"


namespace ariel{

    class Algorithms{
        public:

    // Depth-first search function
    static void dfs(const std::vector<std::vector<int>>& graph, size_t vertex, std::vector<bool>& visited);

    // Function to check if the graph is connected
    static std::string isConnected(ariel::Graph graph);


    static std::string printShortestPath(int start, int end, const std::pair<int, std::vector<int>>& shortestPath);


    // Function to find the shortest path in the graph
    static std::string shortestPath(ariel::Graph& graph, size_t start, size_t end);


    // Function to check if the graph is bipartite
    static std::string isBipartite(ariel::Graph& graph);

    // Function to perform depth-first search for cycle detection
    static std::string dfs(const std::vector<std::vector<int>>& graph, size_t node, int parentNode, std::vector<int>& color, std::vector<int>& parent);

    // Function to check if the graph contains a cycle
    static std::string isContainsCycle(ariel::Graph& graph);

    // Function to check if the graph contains a negative cycle
    static std::string findNegativeCycle(ariel::Graph& graph);

    };
}


#endif 
