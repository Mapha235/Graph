#include "Graph.hpp"

// Graph::Graph(unsigned int v, std::vector<Edge> e)
// {
//     for(int i = 0; i < v; ++i)
//         vertices.insert(Vertex(i));
//     edges = e;
// }

bool sortByLabelDes(Vertex v1, Vertex v2)
{
    return v1.getID() < v2.getID();
}

bool sortByDst(Edge e1, Edge e2)
{
    return e1.getDst().getID() <= e2.getDst().getID();
}

Graph::Graph(std::vector<Vertex> v, std::vector<Edge> e)
{
    vertices = v;
    std::sort(vertices.begin(), vertices.end(), sortByLabelDes);
    edges = e;
    std::sort(edges.begin(), edges.end(), sortByDst);
    removeDup();
}

Graph::Graph(int v_count, std::vector<std::pair<int, int>> e)
{
    for (int i = 0; i < v_count; i++)
        vertices.push_back(Vertex(i + 1));
    for (auto it : e) {
        edges.push_back(Edge(getVertex(it.first), getVertex(it.second)));
    }
    std::sort(edges.begin(), edges.end(), sortByDst);
}

Graph::Graph(int v_count, std::vector<Edge> e)
{
    for (int i = 0; i < v_count; i++)
        vertices.push_back(Vertex(i + 1));
    edges = e;
    std::sort(edges.begin(), edges.end(), sortByDst);
}

Graph::~Graph()
{
}

void Graph::removeDup()
{
    vertices.erase(std::unique(vertices.begin(), vertices.end()), vertices.end());
}

std::vector<Vertex> Graph::getNeighbors(int id)
{
    try {
        getVertex(id);
        std::vector<Vertex> neighbors;
        for (auto it : edges) {
            if (it.getSrc().getID() == id) {
                neighbors.push_back(it.getDst());
            } else if (it.getDst().getID() == id) {
                neighbors.push_back(it.getSrc());
            }
        }
        std::sort(neighbors.begin(), neighbors.end(), sortByLabelDes);
        return neighbors;
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
    }
}

bool Graph::hasLoop()
{
    for (auto it : edges) {
        if (it.getSrc() == it.getDst())
            return true;
    }
    return false;
}

std::vector<Vertex> Graph::getVertices()
{
    return vertices;
}

Edge Graph::getEdge(unsigned int src_id, unsigned int dst_id){
    // std::find(edges.begin(), edges.end(), );
    return edges[0];
}

std::vector<Edge> Graph::getEdges()
{
    return edges;
}

void Graph::setEdges(std::vector<Edge> e){
    edges = e;
}

Vertex Graph::getVertex(unsigned int id)
{
    // id greater than vertices.size() because id's start from 1
    if (id > vertices.size() || id <= 0) {
        std::string msg = "Requested Vertex with id [";
        msg.append(std::to_string(id));
        msg.append("] does not exist in this Graph.");
        throw std::out_of_range(msg);
    }
    return vertices.at(id - 1);
}

void Graph::add(const std::pair<int, int>& v)
{
}

void Graph::remove(const std::pair<int, int>& v)
{
}

Graph& Graph::operator+=(const Edge& e)
{
}

Graph& Graph::operator=(const Graph& other)
{
    this->vertices = other.vertices;
    this->edges = other.edges;
}
