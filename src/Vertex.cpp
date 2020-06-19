#include "Vertex.hpp"

Vertex::Vertex() {}

Vertex::Vertex(unsigned int id)
{
    this->id = id;
    this->value = 0;
}

Vertex::Vertex(unsigned int id, int value) 
{
    this->id = id;
    this->value = value;
}

Vertex::~Vertex()
{
}

int Vertex::getID()
{
    return id;
}

int Vertex::getValue()
{
    return value;
}

void Vertex::setValue(int v)
{
    value = v;
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

bool Vertex::operator<(const Vertex& other)
{
    return this->id < other.id;
}

std::ostream& operator<<(std::ostream& out, Vertex& e)
{
    out << e.getID();
    return out;
}