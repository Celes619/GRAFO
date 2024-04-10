#ifndef NODEBOOK_H
#define NODEBOOK_H
#include "List.h"
#include "Vertex.h"
#include "Book.h"

class Nodebook{
private:
    Book* book;
    List<Vertex*> list;

public:
    Nodebook();
    Nodebook(Book *book);
    ~Nodebook();

    //Getters and setters
    Book* getBook();
    List<Vertex*> getList();

    void setBook(Book *book);
    List<Vertex*> setList();

    //Operations of a node
    void appendToVertexList(Nodebook *from, Nodebook *to);
    void appendToVertexList(Nodebook *from, Nodebook *to, int cost);

    //Overcharge
    friend std::ostream& operator<<(std::ostream& os,  Nodebook& nodebook);


};

Nodebook::Nodebook() : book(nullptr), list() {}

Nodebook::Nodebook(Book *book){
    this->book = book;
}

Nodebook::~Nodebook() {
    delete book; // Deallocate memory for book object
}

Book* Nodebook::getBook() {
    return book;
}

List<Vertex*> Nodebook::getList() {
    return list;
}

void Nodebook::setBook(Book *book) {
    this->book = book;
}

List<Vertex*> Nodebook::setList() {
    return list;
}


void Nodebook::appendToVertexList(Nodebook *from, Nodebook *to) {
    Vertex *toAdd = new Vertex(from,to);
    list.append(toAdd);
}

void Nodebook::appendToVertexList(Nodebook *from, Nodebook *to, int cost) {
    Vertex *toAdd = new Vertex(from, to, cost);
    list.append(toAdd);
}

std::ostream& operator<<(std::ostream& os,  Nodebook& nodebook) {
    os << "-" <<  nodebook.getBook()->getTitle()<<"\n";
    for (int i = 0; i < nodebook.getList().size(); ++i) {
        os << "\t-" << nodebook.getList().at(i)->getTo()->getBook()->getTitle() << " ---- "
        << nodebook.getList().at(i)->getCost() << "\n";

    }
    return os;
}

#endif