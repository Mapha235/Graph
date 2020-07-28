#pragma once
#include "Edge.hpp"
#include "Vertex.hpp"
#include <algorithm>
#include <iostream>
#include <string>
#include <tuple>
#include <utility> //pair
#include <vector>

class Graph {

public:
    Graph(std::vector<Vertex> v, std::vector<Edge> e);
    /*@param v_count number of vertices.
    @param e vector of edges.*/
    Graph(int v_count, std::vector<std::pair<int, int>> e);
    Graph(int v_count, std::vector<Edge> e);
    explicit Graph(std::vector<std::vector<int>> adj);
    virtual ~Graph();
    /*Removes duplicate vertices and edges.*/
    virtual void removeDup();
    virtual std::vector<Vertex> getNeighbors(int id);
    /*Add an edge to the Graph.*/
    virtual void addEdge(Edge& v);
    /*Remove an edge from the Graph.*/
    virtual void removeEdge(const int& src_id, const int& dst_id);
    Edge getEdge(unsigned int src_id, unsigned int dst_id);
    virtual std::vector<Edge> getEdges();
    virtual void setEdges(std::vector<Edge> e);

    /*Needs to be checked in order 
    for the Handshaking Lemma to be valid.
    @return true if the graph has a loop.*/
    bool hasLoop();
    Vertex getVertex(unsigned int id);
    std::vector<Vertex> getVertices();
    void removeVertex(unsigned int id);


    virtual void setWeight(int src_id, int dst_id, int weight);
    int getWeight(int src_id, int dst_id);

    Graph& operator=(const Graph& other);
    friend std::istream& operator>>(std::istream& in, Graph& graph);

protected:
    std::vector<std::vector<int>> adj_matrix;
    std::vector<Vertex> vertices;
    std::vector<Edge> edges;
};