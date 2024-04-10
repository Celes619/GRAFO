#ifndef VERTEX_H
#define VERTEX_H
#include "Book.h"
#include <iostream>

class Nodebook;

class Vertex{
private:
    Nodebook *from;
    Nodebook *to;
    int cost;

public:
    Vertex();
    Vertex(Nodebook *from, Nodebook *to);
    Vertex(Nodebook *from, Nodebook *to, int cost);

    ~Vertex();

    //Getters and setters
    int getCost();
    Nodebook* getFrom();
    Nodebook* getTo();

    void setCost(int cost);
    void setFrom(Nodebook* book);
    void setTo(Nodebook *book);

    friend std::ostream& operator<<(std::ostream& os,  Vertex& vertex);

};

Vertex::Vertex() : cost(0), from(nullptr), to(nullptr) {}

Vertex::Vertex(Nodebook *from, Nodebook *to) {
    this ->from = from;
    this->to = to;
    this->cost = 0;
}

Vertex::Vertex(Nodebook *from, Nodebook *to, int cost) {
    this->from = from;
    this->to = to;
    this->cost = cost;
}

Vertex::~Vertex() {}

int Vertex::getCost() {
    return cost;
}

Nodebook* Vertex::getFrom() {
    return from;
}

Nodebook* Vertex::getTo() {
    return to;
}

void Vertex::setCost(int cost) {
    this->cost = cost;
}

void Vertex::setFrom(Nodebook* book) {
    from = book;
}

void Vertex::setTo(Nodebook* book) {
    to = book;
}

#include "Nodebook.h"

std::ostream& operator<<(std::ostream& os, Vertex& vertex) {

    os << vertex.from << "---" << vertex.cost << "---" << vertex.to;
    return os;
}



#endif