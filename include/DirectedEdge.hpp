#pragma once
#include "Edge.hpp"

class DirectedEdge : public Edge {
public:
    DirectedEdge(const Vertex& src, const Vertex& dst);
    ~DirectedEdge();

    bool operator==(DirectedEdge &other);

private:
    
};