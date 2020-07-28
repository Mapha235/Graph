#include "Graph.hpp"

#include <chrono>
#include <deque>
#include <fstream>
#include <iostream>
#include <tuple>

#define INFTY ((unsigned)~0)

struct table_row {
};

using namespace std;

unsigned int factorial(unsigned int n)
{
    if (n > 1)
        return n * factorial(n - 1);
    else
        return 1;
}

unsigned int maxEdgeCount(int v_count)
{
    // return factorial(v_count) / (2 * factorial(v_count - 2));
    int sum(0);
    for (int i = 0; i < v_count; i++)
        sum += i;
    return sum;
    // return ((v_count + 1) * v_count) / 2 - v_count;
}

void printEdges(Graph& graph)
{
    for (auto& it : graph.getEdges())
        std::cout << it << std::endl;
}

/*The program will throw a bad_alloc exception whenever v_count > 12
  indicating that there is not enough memory available.*/
Graph completeGraph(int v_count)
{
    std::vector<std::vector<int>> adj(v_count, std::vector<int>(v_count, 1));
    for (int i = 0; i < v_count; ++i) {
        adj[i][i] = 0;
    }

    return Graph(adj);
}

Graph circleGraph(int v_count)
{
    std::vector<std::pair<int, int>> edges;
    for (int i = 1; i <= v_count; i++) {
        edges.push_back(std::make_pair(i, (((i + 1) % v_count == 0) ? (i + 1) : (i + 1) % v_count)));
    }
    return Graph(v_count, edges);
}

Graph starGraph(int v_count)
{
    std::vector<std::pair<int, int>> edges;
    for (int i = 1; i < v_count; ++i) {
        edges.push_back(std::make_pair(1, i + 1));
    }
    return Graph(v_count, edges);
}

/*@param e_count number of edges.*/
Graph pathGraph(int e_count)
{
    std::vector<std::pair<int, int>> edges;
    for (int i = 1; i <= e_count; i++)
        edges.push_back(std::make_pair(i, i + 1));
    return Graph(e_count + 1, edges);
}

Graph gridGraph(int rows, int cols)
{
    int v_count = rows * cols;
    std::vector<std::pair<int, int>> edges;

    for (int i = 0; i < v_count - 1; ++i) {
    }
    return Graph({});
}

std::vector<int> breadth_first_search(Graph& g, int start_id = 1)
{
    std::cout << "BFS:" << std::endl;

    std::vector<int> search_sequence;
    std::deque<int> queue;
    queue.push_back(start_id);

    std::vector<bool> visited;
    for (int i = 0; i < g.getVertices().size(); i++) {
        visited.push_back(false);
    }
    visited[start_id - 1] = true;

    try {
        while (!queue.empty()) {

            for (auto& it : queue) {
                std::cout << it << ',';
            }
            std::cout << "\n";

            for (auto it : g.getNeighbors(queue.front())) {
                if (!visited[it.getID() - 1]) {
                    queue.push_back(it.getID());
                    visited[it.getID() - 1] = true;
                }
            }
            search_sequence.push_back(queue.front());
            queue.pop_front();
        }
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
    }
    return search_sequence;
}

std::vector<int> depth_first_search(Graph& g, int start_id = 1)
{
    std::cout << "DFS:" << std::endl;

    std::vector<int> search_sequence_v;
    std::vector<int> stack;
    std::vector<bool> visited;

    for (int i = 0; i < g.getVertices().size(); i++) {
        visited.push_back(false);
    }

    stack.push_back(start_id);

    try {
        while (!stack.empty()) {
            auto v = stack.back();
            search_sequence_v.push_back(v);

            for (auto& it : stack) {
                std::cout << it << ',';
            }
            std::cout << "\n";

            stack.pop_back();

            if (!visited[v - 1]) {
                visited[v - 1] = true;

                for (auto it : g.getNeighbors(v)) {
                    if (!visited[it.getID() - 1]) {
                        stack.push_back(it.getID());
                    }
                }
            }
        }
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
    }
    return search_sequence_v;
}

/*  @param  w_g weighted graph
    @param  start_id     start Vertex
    @param  dst_id       destination Vertex,
                        dst_id == 0 means no destination specified
    @return shortest_path
*/
std::vector<int> dijkstra(Graph& w_g, int start_id = 1, int dst_id = 0)
{
    std::cout << "Dijkstra:" << std::endl;
    std::vector<std::vector<int>> table;
    std::vector<int> path;
    std::vector<bool> visited;

    std::vector<Vertex> vertices = w_g.getVertices();

    int infinity = std::numeric_limits<int>::max();

    for (auto& it : vertices) {
        it.setValue(infinity);
        visited.push_back(false);
    }

    // std::vector<Vertex>::iterator current = vertices.begin() + (start_id - 1);
    // current->setValue(0);
    vertices.at(start_id - 1).setValue(0);

    while (!vertices.empty()) {
        auto min = min_element(vertices.begin(), vertices.end(),
            [](Vertex lhs, Vertex rhs) { return lhs.getValue() < rhs.getValue(); });
        auto current = *min;
        std::cout << "ID: " << current.getID() << std::endl;
        std::cout << "Value: " << current.getValue() << std::endl;
        vertices.erase(min);
        visited[current.getID() - 1] = true;
        for (auto y : w_g.getNeighbors(current.getID())) {
            if (current.getValue() + w_g.getWeight(current.getID(), y.getID()) < y.getValue() && visited[y.getID() - 1]) {
                vertices.at(0).setValue(current.getValue() + w_g.getWeight(current.getID(), y.getID()));
            }
        }
    }
    // vertices.erase(std::remove(vertices.begin(), vertices.end(), w_g.getVertex(start_id)), vertices.end());

    return path;
}

bool hasCircle(Graph& g, int start_id = 1)
{
    std::vector<int> parent;
    std::deque<int> queue;
    queue.push_back(start_id);

    std::vector<bool> visited;
    for (int i = 0; i < g.getVertices().size(); i++) {
        visited.push_back(false);
        parent.push_back(0);
    }
    visited[start_id - 1] = true;

    //modified bfs
    while (!queue.empty()) {
        for (auto it : g.getNeighbors(queue.front())) {
            if (visited[it.getID() - 1] && parent[queue.front() - 1] != it.getID()) {
                return true;
            } else if (!visited[it.getID() - 1]) {
                queue.push_back(it.getID());
                visited[it.getID() - 1] = true;
                parent[it.getID() - 1] = queue.front();
            }
        }
        queue.pop_front();
    }
    return false;
}

/*  @param w_g Input graph
    @return corresponding minimum spanning tree
*/
Graph kruskal(Graph& w_g)
{
    std::cout << "Kruskal:" << std::endl;
    std::vector<Vertex> r_node;
    std::deque<Edge> edges;
    std::vector<bool> visited;
    std::vector<std::vector<int>> adj;

    for (int i = 0; i < w_g.getVertices().size(); ++i) {
        std::vector<int> zeros(w_g.getVertices().size(), 0);
        adj.push_back(zeros);
        visited.push_back(false);
    }

    Graph min_span_tree(adj);

    for (auto edge : w_g.getEdges()) {
        edges.push_back(edge);
    }

    /*  Sort the edges by weight.
        In case of a tie, sort the edges by their Source and Destination ID's*/
    std::sort(edges.begin(), edges.end(), [](Edge& lhs, Edge& rhs) {
        return lhs.value < rhs.value || (lhs.value == rhs.value && lhs.getSrc().getID() < rhs.getSrc().getID()) || (lhs.value == rhs.value && lhs.getSrc().getID() == rhs.getSrc().getID() && lhs.getDst().getID() < rhs.getDst().getID());
    });

    std::cout << "Step\tCurrent\t\tWeight\t\tValid?" << std::endl;

    std::string valid = "yes";
    int step = 1;

    while (!edges.empty()) {
        auto edge = edges.begin();
        int src_id = edge->getSrc().getID();
        int dst_id = edge->getDst().getID();

        min_span_tree.setWeight(src_id, dst_id, edge->value);
        int min_id = edge->getSrc().getID() < edge->getDst().getID() ? edge->getSrc().getID() : edge->getDst().getID();
        if (hasCircle(min_span_tree, min_id)) {
            min_span_tree.setWeight(src_id, dst_id, 0);
            valid = "no";
        } else
            min_span_tree.addEdge(*edge);

        std::cout << step << ".\t" << *edge << "\t\t" << edge->value << "\t\t" << valid << std::endl;
        valid = "yes";
        edges.pop_front();
        // cout << "Edges" << endl;
        // printEdges(min_span_tree);
        step++;
    }

    // std::cout << "Minimum Spanning Tree edges: " << std::endl;
    // printEdges(min_span_tree);
    cout << "Edge-size: " << min_span_tree.getEdges().size() << std::endl;
    return min_span_tree;
}

std::vector<Edge> xyRouting(Graph mesh, Vertex src, Vertex dst)
{
    return {};
}


void ford_fulkerson(Graph& g){

}

Graph read_graph_from_file(std::string path)
{

    return Graph({});
}

std::vector<int> permutations(Graph g)
{
}

void tsp_mst_dfs(Graph g)
{
    Graph min_span_tree = kruskal(g);
    auto search_sequence = depth_first_search(min_span_tree);

}

std::vector<int> tsp_nearest_neighbor(Graph g, int start_id = 1)
{
    std::vector<int> sequence;
    std::vector<bool> visited(g.getVertices().size(), false);

    // sequence.push_back(start_id);
    visited[start_id - 1] = true;

    while (!sequence.empty()) {
        for (auto y : g.getNeighbors(start_id)) { }
    }
}

void tsp_backtracking(Graph g)
{
    
}

bool sat()
{
}

//TODO
template <typename ReturnType, typename... Args>
void clock(ReturnType*(algorithm)(Args... args))
{

    auto t1 = std::chrono::high_resolution_clock::now();

    // *(algorithm)(args);

    auto t2 = std::chrono::high_resolution_clock::now();
    std::cout << "\n";
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
    double milli = static_cast<double>(duration) / 1000.0;
    double seconds = milli / 1000.0;
    std::cout << "Finished in: " << seconds << "s" << endl;
}

/*  c=99  1
    g=103 5
    k=107 2
    p=112 0
    s=115 3*/
Graph (*specialGraph[])(int) = { pathGraph, circleGraph, completeGraph, starGraph };

int main(int argc, char** argv)
{
    int hash;
    int number;
    Graph g({});

    if (argc == 3) {
        hash = static_cast<int>(argv[1][0]) % 7;
        number = std::stoi(argv[2]);

        g = specialGraph[hash](number);
    } else {
        std::vector<std::vector<int>> dij = {
            //a  b  c  d  e
            { 0, 5, 2, 0, 1, 1 }, //a
            { 5, 0, 0, 2, 0, 0 }, //b
            { 2, 0, 0, 2, 4, 0 }, //c
            { 0, 2, 2, 0, 3, 0 }, //d
            { 1, 0, 4, 3, 0, 1 }, //e
            { 1, 0, 4, 0, 1, 0 }
        };

        g = read_graph_from_file("./data/graph.txt");
        g = Graph(dij);
    }

    pair<int, int> edge1(1, 2);
    pair<int, int> edge2(1, 3);
    pair<int, int> edge3(1, 4);
    pair<int, int> edge4(2, 5);
    pair<int, int> edge5(2, 6);
    pair<int, int> edge6(6, 10);
    pair<int, int> edge7(3, 7);
    pair<int, int> edge8(7, 11);
    pair<int, int> edge9(4, 8);
    pair<int, int> edge10(4, 9);
    pair<int, int> edge11(9, 12);
    pair<int, int> edge12(9, 13);
    auto edges = {
        edge1,
        edge2,
        edge3,
        edge4,
        edge5,
        edge6,
        edge7,
        edge8,
        edge9,
        edge10,
        edge11,
        edge12,
    };

    pair<int, int> edge_1(1, 2);
    pair<int, int> edge_2(1, 5);
    pair<int, int> edge_3(2, 4);
    pair<int, int> edge_4(4, 5);
    pair<int, int> edge_5(5, 3);
    pair<int, int> edge_6(3, 4);
    auto edges2 = {
        edge_1,
        edge_2,
        edge_3,
        edge_4,
        edge_5,
        edge_6
    };

    std::vector<std::vector<int>> k5 = {
        { 0, 1, 1, 0, 0 },
        { 1, 0, 0, 1, 0 },
        { 1, 0, 0, 1, 1 },
        { 0, 1, 1, 0, 1 },
        { 0, 0, 1, 1, 0 }
    };

    Graph example(5, edges2);
    Graph complete = completeGraph(5);
    Graph circle = circleGraph(10);
    Graph tree(13, edges);
    Graph star = starGraph(6);
    Graph path = pathGraph(7);
    // Graph g(dij);
    Graph c(k5);

    // for (auto it : breadth_first_search(g, 1))
    //     std::cout << it << ',';

    // std::cout << "\n\n";

    // for (auto it : breadth_first_search(complete, 1))
    //     std::std::cout << it << ',';

    auto t1 = std::chrono::high_resolution_clock::now();

    // depth_first_search(g);
    tsp_mst_dfs(g);

    auto t2 = std::chrono::high_resolution_clock::now();
    std::cout << "\n";
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
    double milli = static_cast<double>(duration) / 1000.0;
    double seconds = milli / 1000.0;
    std::cout << "Time: " << seconds << " s" << endl;

    // std::cout << "Time in " << static_cast<char>(230) << "s: " << duration << endl;
    // printEdges(complete);
    // printEdges(complete);
    // std::cout << g.getWeight(1, 2) << std::endl;

    // auto neighbors_dij = complete.getNeighbors(1);
    // for (auto it : neighbors_dij) {
    //     std::cout << it << std::endl;
    // }

    // auto dij_edges = g.getEdges();
    // for (auto it : dij_edges)
    //     std::cout << it << " value: " << it.value << std::endl;

    return 0;
}

#endif
