// ooriamelaku@gmail.com
// 208734889
#include "doctest.h"
#include "Algorithms.hpp"
#include "Graph.hpp"

using namespace std;

//1
TEST_CASE("Test isConnected")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    CHECK(ariel::Algorithms::isConnected(g) == "1");

    vector<vector<int>> graph2 = {
        {0, 1, 1, 0, 0},
        {1, 0, 1, 0, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0}};
    g.loadGraph(graph2);
    CHECK(ariel::Algorithms::isConnected(g) == "-1"); 
}
//2
TEST_CASE("Test shortestPath")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::shortestPath(g, 0, 2) == "0 -> 1 -> 2");


    vector<vector<int>> graph2 = {
        {0, 1, 1, 0, 0},
        {1, 0, 1, 0, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0}};
    g.loadGraph(graph2);
    CHECK(ariel::Algorithms::shortestPath(g, 0, 4) == "-1");
}
//3
TEST_CASE("Test isContainsCycle")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::isContainsCycle(g) == "-1");

    vector<vector<int>> graph2 = {
        {0, 1, 1, 0}, 
        {1, 0, 1, 0}, 
        {1, 1, 0, 0}, 
        {0, 0, 0, 0}};
    g.loadGraph(graph2);
    CHECK(ariel::Algorithms::isContainsCycle(g) == "2 -> 3 -> 1");
}
//4

TEST_CASE("Test isBipartite")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::isBipartite(g) == "The graph is bipartite: A={0, 2}, B={1}");

    vector<vector<int>> graph2 = {
        {0, 1, 1, 0, 0},
        {1, 0, 1, 0, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0}};
    g.loadGraph(graph2);
    CHECK(ariel::Algorithms::isBipartite(g) == "-1");

    vector<vector<int>> graph3 = {
        {0, 3, 0, 0, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 4, 0},
        {0, 0, 0, 0, 3},
        {0, 0, 0, 0, 0}};
    g.loadGraph(graph3);
    CHECK(ariel::Algorithms::isBipartite(g) == "The graph is bipartite: A={0, 2, 4}, B={1, 3}");
}
//5
TEST_CASE("Test invalid graph")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 1, 2, 0},
        {1, 0, 3, 0},
        {2, 3, 0, 4},
        {0, 0, 4, 0},
        {0, 0, 0, 5}};
    CHECK_THROWS(g.loadGraph(graph));

    ariel::Graph g3;
    vector<vector<int>> graph3 = {
        {0, 1, 2, 0},
        };
    CHECK_THROWS(g3.loadGraph(graph3));
    
    ariel::Graph g4;
    vector<vector<int>> graph4 = {
        {}
        };
    CHECK_THROWS(g4.loadGraph(graph4));
}
//6
TEST_CASE("Test big Graphs with positive cycles")
{
    ariel::Graph g5;
    vector<vector<int>> graph5 = {
        {0, 6, 0, 0, 0},
      {0, 0, 0, 0, 6},
      {0, 0, 0, 6, 0},
      {0, 0, 0, 0, 0},
      {6, 0, 0, 0, 0}};
    g5.loadGraph(graph5);

    CHECK(ariel::Algorithms::isContainsCycle(g5) == "2 -> 5 -> 1");
    CHECK(ariel::Algorithms::findNegativeCycle(g5) == "-1");
    CHECK(ariel::Algorithms::isBipartite(g5) == "-1");

    ariel::Graph g6;
    vector<vector<int>> graph6 = {
        { 0, 6, 0, 0, 0},
        {0, 0, 9, 0, 0},
        {0, 0, 0, 1, 0},
        {0, 0, 0, 0, 7},
        {6, 0, 0, 0, 0}};

    g6.loadGraph(graph6);
    CHECK(ariel::Algorithms::isContainsCycle(g6) == "2 -> 3 -> 4 -> 5 -> 1");
    CHECK(ariel::Algorithms::shortestPath(g6, 0, 4) == "0 -> 1 -> 2 -> 3 -> 4");
    CHECK(ariel::Algorithms::isBipartite(g6) == "-1");
    CHECK(ariel::Algorithms::findNegativeCycle(g6) == "-1");

}
//7
TEST_CASE("Test big Graphs with negative cycles")
{
    ariel::Graph g7;
    vector<vector<int>> graph7 = {
        {0, -10, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 1},
        {0, 0, 0, 0, 0, 0},
        {0, 1, 0, 0, 0, 0},
        {0, 0, 1, 0, 0, 0},
        {-10, 0, 0, 0, 0, 0}};
    g7.loadGraph(graph7);

    CHECK(ariel::Algorithms::isContainsCycle(g7) == "2 -> 6 -> 1");
    CHECK(ariel::Algorithms::findNegativeCycle(g7) == "1 -> 2 -> 6");

}
//8
TEST_CASE("Test big with positive cycle")
{
    ariel::Graph g7;
    vector<vector<int>> graph7 = {
        {0, -10, 1, 0, 0}, 
    {-10, 0, 1, -10, 0}, 
    {1, 1, 0, 0, 0}, 
    {0, -10, 0, 0, 0}, 
    {0, 0, 0, 0, 0}};
    g7.loadGraph(graph7);

    CHECK(ariel::Algorithms::isContainsCycle(g7) == "2 -> 3 -> 1");

}
//9
TEST_CASE("Test big Graphs that pibartite")
{
    ariel::Graph g8;
    vector<vector<int>> graph8 = {

        {0, 1, 0, 0, 0, 0, 0, 0}, 
        {1, 0, 1, 0, 0, 0, 0, 0}, 
        {0, 1, 0, 1, 0, 0, 0, 0}, 
        {0, 0, 1, 0, 1, 0, 0, 0}, 
        {0, 0, 0, 1, 0, 1, 0, 0}, 
        {0, 0, 0, 0, 1, 0, 1, 0}, 
        {0, 0, 0, 0, 0, 1, 0, 1}, 
        {0, 0, 0, 0, 0, 0, 1, 0}};
            g8.loadGraph(graph8);

    CHECK(ariel::Algorithms::isBipartite(g8) == "The graph is bipartite: A={0, 2, 4, 6}, B={1, 3, 5, 7}");

};
//10
TEST_CASE("Checking a bid graph with one and two edges")
{
    //with 1 edge
    ariel::Graph g9;
    vector<vector<int>> graph9 = {
        {0, 0, 0, 0, 0, 1}, 
        {0, 0, 0, 0, 0, 0}, 
        {0, 0, 0, 0, 0, 0}, 
        {0, 0, 0, 0, 0, 0}, 
        {0, 0, 0, 0, 0, 0}, 
        {1, 0, 0, 0, 0, 0}};
    g9.loadGraph(graph9);

    CHECK(ariel::Algorithms::isContainsCycle(g9) == "-1");
    CHECK(ariel::Algorithms::isConnected(g9) == "-1");
    CHECK(ariel::Algorithms::shortestPath(g9, 0, 4) == "-1");
    CHECK(ariel::Algorithms::isBipartite(g9) == "The graph is bipartite: A={0, 1, 2, 3, 4}, B={5}");
    CHECK(ariel::Algorithms::findNegativeCycle(g9) == "-1");

    // with 2 edges
    ariel::Graph g10;
    vector<vector<int>> graph10 = {
        {0, 0, 0, 0, 0, 1}, 
        {0, 0, 0, 0, 0, 0}, 
        {0, 0, 0, 1, 0, 0}, 
        {0, 0, 1, 0, 0, 0}, 
        {0, 0, 0, 0, 0, 0}, 
        {1, 0, 0, 0, 0, 0}};
    g10.loadGraph(graph10);

    CHECK(ariel::Algorithms::isContainsCycle(g10) == "-1");
    CHECK(ariel::Algorithms::isConnected(g10) == "-1");
    CHECK(ariel::Algorithms::shortestPath(g10, 0, 4) == "-1");
    CHECK(ariel::Algorithms::isBipartite(g10) == "The graph is bipartite: A={0, 1, 2, 4}, B={5, 3}");
    CHECK(ariel::Algorithms::findNegativeCycle(g10) == "-1");

}
//11
TEST_CASE("Testing a graph with a few positive cycles")
{
    ariel::Graph g11;
    vector<vector<int>> graph11 = {
        {0, 0, 0, 0, 1, 1}, 
        {0, 0, 0, 0, 0, 0}, 
        {0, 0, 0, 1, 1, 0}, 
        {0, 0, 1, 0, 1, 0}, 
        {1, 0, 1, 1, 0, 1}, 
        {1, 0, 0, 0, 1, 0}};
    g11.loadGraph(graph11);

    CHECK(ariel::Algorithms::isContainsCycle(g11) == "3 -> 4 -> 5");
    CHECK(ariel::Algorithms::isConnected(g11) == "-1");
    CHECK(ariel::Algorithms::shortestPath(g11, 0, 2) == "0 -> 4 -> 2");
    CHECK(ariel::Algorithms::isBipartite(g11) == "-1");
    CHECK(ariel::Algorithms::findNegativeCycle(g11) == "-1");

}
//12
TEST_CASE("Testing isbipartite again")
{
    ariel::Graph g12;
    vector<vector<int>> graph12 = {
        {0, 0, 0, 0, 1, 1}, 
        {0, 0, 0, 0, 0, 0}, 
        {0, 0, 0, 1, 0, 0}, 
        {0, 0, 1, 0, 0, 0}, 
        {1, 0, 0, 0, 0, 1}, 
        {1, 0, 0, 0, 1, 0}};
    g12.loadGraph(graph12);
    CHECK(ariel::Algorithms::isBipartite(g12) == "-1");

    ariel::Graph g13;
    vector<vector<int>> graph13 = {
        {0, 0, 0, 0, 1, 1}, 
        {0, 0, 0, 0, 0, 0}, 
        {0, 0, 0, 1, 0, 0}, 
        {0, 0, 1, 0, 0, 0}, 
        {1, 0, 0, 0, 0, 0}, 
        {1, 0, 0, 0, 0, 0}};
    g13.loadGraph(graph13);
    CHECK(ariel::Algorithms::isBipartite(g13) == "The graph is bipartite: A={0, 1, 2}, B={4, 5, 3}");
}
//13
TEST_CASE("Testing more directed weighted graphs")
{
    ariel::Graph g14;
    vector<vector<int>> graph14 = {
        {0, 1, 0, 0},
        {0, 0, 2, 0},
        {0, 0, 0, 3},
        {0, 0, 0, 0}
        };
    g14.loadGraph(graph14);

    CHECK(ariel::Algorithms::isContainsCycle(g14) == "-1");
    CHECK(ariel::Algorithms::isConnected(g14) == "-1");
    CHECK(ariel::Algorithms::shortestPath(g14, 0, 2) == "0 -> 1 -> 2");
    CHECK(ariel::Algorithms::isBipartite(g14) == "The graph is bipartite: A={0, 2}, B={1, 3}");
    CHECK(ariel::Algorithms::findNegativeCycle(g14) == "-1");

    ariel::Graph g15;
    vector<vector<int>> graph15 = {
        {0, 3, 0, 0, 0},
        {0, 0, 3, 0, 0},
        {3, 0, 0, 0, 0},
        {0, 0, 0, 0, 3},
        {0, 0, 0, 0, 0}};
    g15.loadGraph(graph15);

    CHECK(ariel::Algorithms::isContainsCycle(g15) == "2 -> 3 -> 1");
    CHECK(ariel::Algorithms::isConnected(g15) == "-1");
    CHECK(ariel::Algorithms::shortestPath(g15, 0, 2) == "0 -> 1 -> 2");
    CHECK(ariel::Algorithms::isBipartite(g15) == "-1");
    CHECK(ariel::Algorithms::findNegativeCycle(g15) == "-1");

}
//14
TEST_CASE("Testing small undirected weighted graphs")
{
    ariel::Graph g16;
    vector<vector<int>> graph16 = {
        {0, 5, 0},
        {5, 0, 0},
        {0, 0, 0}
        };
    g16.loadGraph(graph16);

    CHECK(ariel::Algorithms::isContainsCycle(g16) == "-1");
    CHECK(ariel::Algorithms::isConnected(g16) == "-1");
    CHECK(ariel::Algorithms::shortestPath(g16, 0, 2) == "-1");
    CHECK(ariel::Algorithms::isBipartite(g16) == "The graph is bipartite: A={0, 2}, B={1}");
    CHECK(ariel::Algorithms::findNegativeCycle(g16) == "-1");
}
//15
TEST_CASE("Testing more small undirected weighted graphs")
{
    ariel::Graph g17;
    vector<vector<int>> graph17 = {
        {0, 5},
        {5, 0}};
    g17.loadGraph(graph17);

    CHECK(ariel::Algorithms::isContainsCycle(g17) == "-1");
    CHECK(ariel::Algorithms::isConnected(g17) == "1");
    CHECK(ariel::Algorithms::isBipartite(g17) == "The graph is bipartite: A={0}, B={1}");
    CHECK(ariel::Algorithms::findNegativeCycle(g17) == "-1");
}
//16
TEST_CASE("Testing graph with no edges")
{
    ariel::Graph g18;
    vector<vector<int>> graph18 = {
        {0}
        };
    g18.loadGraph(graph18);

    CHECK(ariel::Algorithms::isContainsCycle(g18) == "-1");
    CHECK(ariel::Algorithms::isConnected(g18) == "1");
    CHECK(ariel::Algorithms::shortestPath(g18, 0, 2) == "-1");
    CHECK(ariel::Algorithms::isBipartite(g18) == "The graph is bipartite: A={0}, B={}");
    CHECK(ariel::Algorithms::findNegativeCycle(g18) == "-1");

    ariel::Graph g19;
    vector<vector<int>> graph19 = {
        {0, 5},
        {5, 0}};
    g19.loadGraph(graph19);

    CHECK(ariel::Algorithms::isContainsCycle(g19) == "-1");
    CHECK(ariel::Algorithms::isConnected(g19) == "1");
    CHECK(ariel::Algorithms::isBipartite(g19) == "The graph is bipartite: A={0}, B={1}");
    CHECK(ariel::Algorithms::findNegativeCycle(g19) == "-1");
}
//17
TEST_CASE("Testing an empty graph")
{
    ariel::Graph g20;
    vector<vector<int>> graph20 = {
        {}
        };

    CHECK_THROWS(g20.loadGraph(graph20));
}
//18
TEST_CASE("Testing more invalid graph")
{
    ariel::Graph g21;
    vector<vector<int>> graph21 = {
        {0,0,0},
        {0,0,0},
        {0,0,0},
        {0,0,0},
        };
    CHECK_THROWS(g21.loadGraph(graph21));


    ariel::Graph g22;
    vector<vector<int>> graph22 = {
        {0, 5},
        {5, 0},
        {5, 0}};
  
    CHECK_THROWS(g22.loadGraph(graph22));
}
//19
TEST_CASE("Testing big graph with no edges")
{
    ariel::Graph g23;
    vector<vector<int>> graph23 = {
        {0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0}
        };
    g23.loadGraph(graph23);
    CHECK(ariel::Algorithms::isContainsCycle(g23) == "-1");
    CHECK(ariel::Algorithms::isConnected(g23) == "-1");
    CHECK(ariel::Algorithms::shortestPath(g23, 0, 2) == "-1");
    CHECK(ariel::Algorithms::isBipartite(g23) == "The graph is bipartite: A={0, 1, 2, 3, 4, 5, 6}, B={}");
    CHECK(ariel::Algorithms::findNegativeCycle(g23) == "-1");
}
//20
TEST_CASE("Checking unconccted undirected graphs")
{
    ariel::Graph g24;
    vector<vector<int>> graph24 = {
        {0, 0, 3, 3},
        {0, 0, 0, 0},
        {3, 0, 0, 3},
        {3, 0, 3, 0},
        };
    g24.loadGraph(graph24);

    CHECK(ariel::Algorithms::isContainsCycle(g24) == "3 -> 4 -> 1");
    CHECK(ariel::Algorithms::isConnected(g24) == "-1");
    CHECK(ariel::Algorithms::shortestPath(g24, 0, 2) == "0 -> 2");
    CHECK(ariel::Algorithms::isBipartite(g24) == "-1");
    CHECK(ariel::Algorithms::findNegativeCycle(g24) == "-1");
}
    




