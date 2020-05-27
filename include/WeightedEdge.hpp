#pragma once
#include "Edge.hpp"

class WeightedEdge : public Edge{

public:
    WeightedEdge(const Vertex &src, const Vertex &dst);
    WeightedEdge(unsigned int src_id, unsigned int dst_id, int w);
    WeightedEdge(unsigned int src_id, unsigned int dst_id);
    ~WeightedEdge();

    int getWeight();
    void setWeight();


private:
    int weight;
};