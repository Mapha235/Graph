#include "DirectedEdge.hpp"

DirectedEdge::DirectedEdge(const Vertex& src, const Vertex& dst) : Edge(src,dst) {

}

DirectedEdge::~DirectedEdge() {

}
bool DirectedEdge::operator==(DirectedEdge &other){
    // if(this->getSrc() == other.getDst() && this->getDst() == other.getDst())
    //     return true;
    // else
    //     return false;
    
}