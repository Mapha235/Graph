#pragma once
#include "Vertex.hpp"
#include <iostream>

class Edge {
public:
    Edge(const Vertex& src, const Vertex& dst);
    Edge(unsigned int id1, unsigned int id2);
    virtual ~Edge();
    Vertex getSrc();
    Vertex getDst();
    friend std::ostream& operator<<(std::ostream& out, Edge& e);

private:
    Vertex src;
    Vertex dst;
};