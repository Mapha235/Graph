#pragma once
#include "Graph.hpp"

class DirectedGraph : public Graph{

public:
    DirectedGraph(std::vector<std::vector<int>> adj);
    ~DirectedGraph();
};