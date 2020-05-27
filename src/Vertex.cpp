#include "Vertex.hpp"

Vertex::Vertex() {}

Vertex::Vertex(unsigned int id)
{
    this->id = id;
}

Vertex::~Vertex()
{
}

int Vertex::getID()
{
    return id;
}

bool Vertex::operator==(const Vertex& other)
{
    // return this == &other;
    return this->id == other.id;
}
bool Vertex::operator!=(const Vertex& other)
{
    return this != &other;
}

std::ostream& operator<<(std::ostream& out, Vertex& e)
{
    out << e.getID();
    return out;
}