#include "Edge.hpp"

Edge::Edge(const Vertex& src, const Vertex& dst)
{
    this->src = src;
    this->dst = dst;
}

Edge::Edge(unsigned int src_id, unsigned int dst_id, int value){
    src = Vertex(src_id);
    dst = Vertex(dst_id);
    this->value = value;
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