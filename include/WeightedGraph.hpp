#include "Graph.hpp"
#include "WeightedEdge.hpp"

class WeightedGraph : public Graph {
public:
    WeightedGraph(int v_count, std::vector<std::pair<Edge, int>> e_w);
    WeightedGraph(Graph g, std::vector<std::pair<Edge, int>> weights);
    virtual ~WeightedGraph();

    /*@param src_id     ID of the source vertex.
    @param dst_id       ID of the destination vertex
    @param weight       weight of the described edge.*/
    void setWeight(unsigned int src_id, unsigned int dst_id, int weight);

    virtual void removeDup();
    virtual std::vector<Vertex> getNeighbors(int id);
    virtual void add(const std::pair<int, int>& v);
    virtual void remove(const std::pair<int, int>& v);
    virtual std::vector<Edge> getEdges();
    virtual void setEdges(std::vector<Edge> e);

protected:
    std::vector<WeightedEdge> w_edges;
};