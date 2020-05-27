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
    virtual ~Graph();
    /*Removes duplicate vertices and edges.*/
    virtual void removeDup();
    virtual std::vector<Vertex> getNeighbors(int id);
    /*Add an edge to the Graph.*/
    virtual void add(const std::pair<int, int>& v);
    /*Remove an edge from the Graph.*/
    virtual void remove(const std::pair<int, int>& v);

    /*Needs to be checked in order 
    for the Handshaking Lemma to be valid.*/
    bool hasLoop();
    bool hasCircle();
    Vertex getVertex(unsigned int id);
    std::vector<Vertex> getVertices();

    Edge getEdge(unsigned int src_id, unsigned int dst_id);
    virtual std::vector<Edge> getEdges();
    virtual void setEdges(std::vector<Edge> e);

    Graph& operator+=(const Graph& other);
    Graph& operator+=(const Vertex& v);
    Graph& operator+=(const Edge& e);
    Graph& operator=(const Graph& other);

protected:
    std::vector<Vertex> vertices;
    std::vector<Edge> edges;
};