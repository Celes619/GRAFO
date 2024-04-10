#ifndef BOOK_H
#define BOOK_H
#include <iostream>
using namespace std;

class Book{
private:
    string author;
    string title;
    string date;
    string description;

public:
    // Constructors
    Book(string title, string description, string date);
    Book(string title, string description, int day, int month, int year);
    Book(string title, string description, string day, string month, string year);

    // Getters
    string getAuthor();
    string getTitle();
    string getDescription();
    string getDate();
    string getYear();
    // Setters
    void setAuthor(string author);
    void setTitle(string title);
    void setDescription(string description);
    void setDate( string date);
    void setDate(int day, int month, int year);

    // toString method
    friend std::ostream& operator<<(std::ostream& os, const Book& c);
};


// Constructors
Book::Book(string title, string description, string date) {
    this->title = title;
    this->description = description;
    this->date = date;
    author = "Garcia Marquez";
}

Book::Book(string title, string description, int day, int month, int year) {
    this->title = title;
    this->description = description;
    this->date = std::to_string(day) + "/" + std::to_string(month) + "/" + std::to_string(year);
    author = "Garcia Marquez";
}

Book::Book(string title, string description, string day, string month, string year) {
    this->title = title;
    this->description = description;
    this->date = day + "/" + month + "/" + year;
    author = "Garcia Marquez";
}



// Getters
string Book::getAuthor() {
    return author;
}

string Book::getTitle() {
    return title;
}

string Book::getDescription() {
    return description;
}

string Book::getDate() {
    return date;
}

string Book::getYear() {
    string year;
    size_t pos = date.find("/");
    year = date.substr(pos+1, date.size());
    pos = year.find("/");
    year = year.substr(pos+1,year.size());
    return year;
}

// Setters
void Book::setAuthor(string author) {
    this->author = author;
}

void Book::setTitle(string title) {
    this->title = title;
}

void Book::setDescription(string description) {
    this->description = description;
}

void Book::setDate(string date) {
    this->date = date;
}

void Book::setDate(int day, int month, int year) {
    this->date = std::to_string(day) + "/" + std::to_string(month) + "/" + std::to_string(year);
}

// Overloaded operator<< function
std::ostream& operator<<(std::ostream& os, const Book& book) {
    os << "Title: " << book.title << "\nAuthor: " << book.author << "\nDescription: " << book.description << "\nDate: " << book.date;
    return os;
}


#endif