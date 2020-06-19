#include "Graph.hpp"

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
    for (int i = 0; i < v_count; i++) {
        vertices.push_back(Vertex(i + 1));
        std::vector<int> zeros(v_count, 0);
        adj_matrix.push_back(zeros);
    }

    for (auto it : e) {
        edges.push_back(Edge(getVertex(it.first), getVertex(it.second)));
        adj_matrix.at(it.first - 1).at(it.second - 1) = 1;
        adj_matrix.at(it.second - 1).at(it.first - 1) = 1;
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

Graph::Graph(std::vector<std::vector<int>> adj)
{
    if (adj.size() > 0 && adj.size() == adj[0].size()) {
        adj_matrix = adj;
        /*The following loop only reads the lower triangle of the matrix.
         i loops through the rows, j loops through the columns.*/
        for (int i = 0; i < adj.size(); ++i) {
            vertices.push_back(Vertex(i + 1));
            for (int j = i; j < adj.at(i).size(); ++j) {
                if (adj.at(i).at(j) != 0)
                    edges.push_back(Edge(i + 1, j + 1, adj.at(i).at(j)));
            }
        }
    }
    std::sort(edges.begin(), edges.end(), sortByDst);
}

Graph::~Graph()
{
}

void Graph::removeDup()
{
    vertices.erase(std::unique(vertices.begin(), vertices.end()), vertices.end());
}

// std::vector<Vertex> Graph::getNeighbors(int id)
// {
//     try {
//         getVertex(id);
//         std::vector<Vertex> neighbors;
//         for (auto it : edges) {
//             if (it.getSrc().getID() == id) {
//                 neighbors.push_back(it.getDst());
//             } else if (it.getDst().getID() == id) {
//                 neighbors.push_back(it.getSrc());
//             }
//         }
//         std::sort(neighbors.begin(), neighbors.end(), sortByLabelDes);
//         return neighbors;
//     } catch (const std::exception& e) {
//         std::cerr << e.what() << '\n';
//     }
// }

std::vector<Vertex> Graph::getNeighbors(int id)
{
    // adj_matrix is already sorted
    try {
        getVertex(id);
        std::vector<Vertex> neighbors;
        for (int i = 0; i < adj_matrix.size(); ++i) {
            if (adj_matrix.at(id - 1).at(i) != 0)
                neighbors.push_back(getVertex(i + 1));
        }
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

Edge Graph::getEdge(unsigned int src_id, unsigned int dst_id)
{
    // std::find(edges.begin(), edges.end(), );
    return edges[0];
}

std::vector<Edge> Graph::getEdges()
{
    return edges;
}

void Graph::setEdges(std::vector<Edge> e)
{
    edges = e;
}

void Graph::setWeight(int src_id, int dst_id, int weight)
{
    adj_matrix[src_id - 1][dst_id - 1] = weight;
    adj_matrix[dst_id - 1][src_id - 1] = weight;
}

int Graph::getWeight(int src_id, int dst_id)
{
    return adj_matrix.at(src_id - 1).at(dst_id - 1);
}

Vertex Graph::getVertex(unsigned int id)
{
    // id greater than vertices.size() because id's start from 1
    if (id > vertices.size() || id <= 0) {
        std::string msg = "Requested Vertex with id [";
        msg.append(std::to_string(id));
        msg.append("] does not exist in this Graph. Invoked from this.getVertex().");
        throw std::out_of_range(msg);
    }
    return vertices.at(id - 1);
}

void Graph::addEdge(Edge& v)
{
    int rows = adj_matrix.size();
    int cols = rows;

    int src_id = v.getSrc().getID();
    int dst_id = v.getDst().getID();
    int max = (src_id < dst_id) ? dst_id : src_id;

    if (rows < max) {
        for (auto it = adj_matrix.begin(); it != adj_matrix.end(); ++it)
            it->push_back(0);
        adj_matrix.push_back(std::vector<int>(max - adj_matrix.size(), 0));
        vertices.push_back(Vertex(vertices.size()));
    }
    adj_matrix[src_id - 1][dst_id - 1] = v.value;
    edges.push_back(Edge(src_id, dst_id, v.value));
}

void Graph::removeEdge(const int& src_id, const int& dst_id)
{
}

Graph& Graph::operator=(const Graph& other)
{
    this->adj_matrix = other.adj_matrix;
    this->vertices = other.vertices;
    this->edges = other.edges;
}

std::istream& operator>>(std::istream& in, Graph& graph)
{
    std::vector<std::vector<int>> file_adj;
}
