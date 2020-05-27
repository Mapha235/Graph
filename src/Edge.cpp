#include "Edge.hpp"

Edge::Edge(const Vertex& src, const Vertex& dst)
{
    this->src = src;
    this->dst = dst;
}

Edge::Edge(unsigned int id1, unsigned int id2){
    src = Vertex(id1);
    dst = Vertex(id2);
}

Edge::~Edge()
{
}

Vertex Edge::getDst()
{
    return dst;
}

Vertex Edge::getSrc()
{
    return src;
}

std::ostream& operator<<(std::ostream& out, Edge& e)
{
    out << "(" << e.getSrc().getID() 
        << "," << e.getDst().getID() << ")";
    return out;
}