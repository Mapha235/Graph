#pragma once
#include "Vertex.hpp"
#include <iostream>

class Edge {
public:
    Edge(const Vertex& src, const Vertex& dst);
    Edge(unsigned int src_id, unsigned int dst_id, int value);
    virtual ~Edge();
    Vertex getSrc();
    Vertex getDst();
    friend std::ostream& operator<<(std::ostream& out, Edge& e);

    int value;
private:
    Vertex src;
    Vertex dst;
};