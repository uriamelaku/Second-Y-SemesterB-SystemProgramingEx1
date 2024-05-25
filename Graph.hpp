// ooriamelaku@gmail.com
// 208734889
#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <iostream>

namespace ariel {

    class Graph {
    private:
        std::vector<std::vector<int>> graph;

    public:
        void loadGraph(std::vector<std::vector<int>> graph);
        void printGraph();
        size_t size() const;
        const std::vector<std::vector<int>>& getMatrix() const;
        bool isDirected();
    };

}

#endif
