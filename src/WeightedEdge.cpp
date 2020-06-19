#include "WeightedEdge.hpp"

WeightedEdge::WeightedEdge(const Vertex& src, const Vertex& dst)
    : Edge { src, dst }
{
}

WeightedEdge::WeightedEdge(unsigned int src_id, unsigned int dst_id, int w)
    : Edge { src_id, dst_id, w }
    , weight(w)
{
}

WeightedEdge::WeightedEdge(unsigned int src_id, unsigned int dst_id)
    : Edge { src_id, dst_id, 0 }, weight(0)
{
}

WeightedEdge::~WeightedEdge()
{
}