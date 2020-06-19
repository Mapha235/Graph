#pragma once
#include <iostream>

class Vertex {

public:
    Vertex();
    explicit Vertex(unsigned int id);
    Vertex(unsigned int id, int value);
    ~Vertex();

    int getID();
    int getValue();
    void setValue(int v);
    /*Overloading this operator is required for the removeDup() 
    method in the Graph class as this compares the ID of both operands 
    used in std::unique instead of the operands address. */
    bool operator==(const Vertex &other);
    bool operator!=(const Vertex &other);
    bool operator<(const Vertex &other);
    friend std::ostream& operator<<(std::ostream& out, Vertex& e);
private:
    //unique ID
    unsigned int id;
    //evaluation value for upcoming algorithms
    int value;
};