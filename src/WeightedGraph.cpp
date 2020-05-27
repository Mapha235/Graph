#include "WeightedGraph.hpp"

WeightedGraph::WeightedGraph(int v_count, std::vector<std::pair<Edge, int>> e_w)
    : Graph(v_count, std::vector<Edge>())
{
}

WeightedGraph::WeightedGraph(Graph g, std::vector<std::pair<Edge, int>> weights)
    : Graph(g)
{
}
WeightedGraph::~WeightedGraph() {}

void WeightedGraph::setWeight(unsigned int src_id, unsigned int dst_id, int weight)
{
    if (weight < 0)
        throw std::invalid_argument("Invalid weight number. Must be greater than 0");
    else{
        auto temp = getEdge(src_id, dst_id);
    }
}

void WeightedGraph::removeDup()
{
    Graph::removeDup();
}

std::vector<Vertex> WeightedGraph::getNeighbors(int id)
{
    return Graph::getNeighbors(id);
}

void WeightedGraph::add(const std::pair<int, int>& v)
{
}

void WeightedGraph::remove(const std::pair<int, int>& v)
{
}

std::vector<Edge> WeightedGraph::getEdges()
{
    return Graph::getEdges();
}

void WeightedGraph::setEdges(std::vector<Edge> e)
{
}