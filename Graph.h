#ifndef GRAPHLIBRARY_GRAPH_H
#define GRAPHLIBRARY_GRAPH_H
#include "Nodebook.h"
#include "List.h"
#include "StringOp.h"
#include "stack"
#include "queue"

class Graph{
private:
    List<Nodebook*> books;
    void dfsAlgorithm(stack<Nodebook*> *toVisit, bool visited[], Nodebook *currentNode, string *output);
    void bfsAlgorithm(queue<Nodebook*> *toVisit, bool visited[], Nodebook *currentNode, string *output);
public:
    //Constructor and destructor of the class
    Graph();
    ~Graph();

    //getter
    List<Nodebook*> getBooks();

    //Usefull operations
    bool belongs(string toVerify);
    Nodebook *getNodebook(string name);

    //Operations with nodes
    void addEdge(Book *book);
    void relate(string principal, string secondary, int cost);
    void relate(string principal, string secondary);
    void deleteNode(string name);

    //Graph algorithms
    string dfs(string principalNode);
    string bfs(string principalNode);
    string prim(string principalNode);
    string dijkstraShortestPath(string principalNode, string destinationNode);


    friend std::ostream& operator<<(std::ostream& os,  Graph& graph);
};

Graph::Graph() : books() {}

Graph::~Graph() {
    // Destructor implementation
    // Assuming List<Nodebook*> handles memory deallocation for Nodebook objects
}

List<Nodebook*> Graph::getBooks() {
    return books;
}

Nodebook *Graph::getNodebook(string name){
    StringOp op;
    for(int i=0; i<books.size();i++){
        if(op.equalsNotSensible(name, books.at(i)->getBook()->getTitle()))
            return books.at(i);
    }
    return NULL;
}

bool Graph::belongs(std::string toVerify) {
    StringOp op;
    for (int i = 0; i < books.size(); ++i) {
        if(op.equalsNotSensible(toVerify,books.at(i)->getBook()->getTitle()));
        return true;
    }
    return false;
}

void Graph::addEdge(Book* book) {
    // Implementation of addEdge() function
    Nodebook *toAdd = new Nodebook(book);
    books.append(toAdd);
}

void Graph::relate(string principal, string secondary, int cost) {
    // Implementation of relate() function with cost parameter
    if(belongs(principal) && belongs(secondary)){
        Nodebook *principalNode = getNodebook(principal);
        Nodebook *secondaryNode = getNodebook(secondary);
        principalNode->appendToVertexList(principalNode,secondaryNode,cost);
    } else {
        throw domain_error("Not_Such_element");
    }
}

void Graph::relate(string principal, string secondary) {
    // Implementation of relate() function without cost parameter
    if(belongs(principal) && belongs(secondary)){
        Nodebook *principalNode = getNodebook(principal);
        Nodebook *secondaryNode = getNodebook(secondary);
        principalNode->appendToVertexList(principalNode,secondaryNode);
    } else {
        throw domain_error("Not_Such_Element");
    }
}

void Graph::deleteNode(string name) {
    // Implementation of deleteNode() function
}

string Graph::dfs(string principalNode) {
    string dfsPath;
    bool visited[books.size()];
    for (int i = 0; i < books.size(); ++i) visited[i] = false;
    Nodebook *startNode = getNodebook(principalNode);
    stack<Nodebook*> *toVisit = new stack<Nodebook*>;

    if(startNode!=NULL) dfsAlgorithm(toVisit, visited, startNode,   &dfsPath);

    return dfsPath;
}

void Graph::dfsAlgorithm(stack<Nodebook *> *toVisit, bool *visited, Nodebook *currentNode, string *output) {
    if(!visited[books.positionOf(currentNode)]) {
        visited[books.positionOf(currentNode)] = true;
        output->append("-----" + currentNode->getBook()->getTitle());
    }

    for(int i=0;i < currentNode->getList().size();i++){
        Nodebook *adjacent = currentNode->getList().at(i)->getTo();
        if(!(visited[books.positionOf(adjacent)])){
            toVisit->push(currentNode->getList().at(i)->getTo());
        }
    }

    if(toVisit->empty()){
        return;
    } else {
        Nodebook *aboutToVisit = toVisit->top();
        toVisit->pop();
        dfsAlgorithm(toVisit,visited,aboutToVisit,output);
    }
}

string Graph::bfs(string principalNode) {
    // Implementation of breadth-first search algorithm
    // Return result as a string
    string bfsPath;
    bool visited[books.size()];
    for (int i = 0; i < books.size(); ++i) visited[i] = false;
    Nodebook *startNode = getNodebook(principalNode);
    queue<Nodebook*> *toVisit = new queue<Nodebook*>;
    if(startNode!=NULL){
        bfsAlgorithm(toVisit,visited,startNode,&bfsPath);
    }
    return bfsPath;
}

void Graph::bfsAlgorithm(queue<Nodebook *> *toVisit, bool *visited, Nodebook *currentNode, string *output) {
    // Implementation of breadth-first search algorithm
    // Return result as a string
    if(!visited[books.positionOf(currentNode)]) {
        visited[books.positionOf(currentNode)] = true;
        output->append("-----" + currentNode->getBook()->getTitle());
    }
    for(int i=0;i < currentNode->getList().size();i++){
        Nodebook *adjacent = currentNode->getList().at(i)->getTo();
        if(!(visited[books.positionOf(adjacent)])){
            toVisit->push(currentNode->getList().at(i)->getTo());
        }
    }

    if(toVisit->empty()){
        return;
    } else {
        Nodebook *aboutToVisit = toVisit->front();
        toVisit->pop();
        bfsAlgorithm(toVisit,visited,aboutToVisit,output);
    }
}

string Graph::prim(string principalNode) {
    // Implementation of Prim's algorithm
    // Return result as a string
    return "";
}

bool isFinished(bool visitedList[], int size){
    for(int i=0; i<size; i++){
        if(!visitedList[i]){
            return false;
        }
    }
    return true;
}

string Graph::dijkstraShortestPath(std::string principalNode, std::string destinationNode) {
    //Basic information for the dijkstra algorithm
    struct dijkstraTable{
        Nodebook *node;
        int shortestDistance;
        Nodebook *previousNode;
    }; List<dijkstraTable*> table;

    bool visited[books.size()];
    for(int i=0; i< books.size(); i++){
        visited[i] = false;
        dijkstraTable *row = new dijkstraTable;
        row->node = books.at(i);
        row->shortestDistance = INT_MAX;
        row->previousNode = NULL;
        table.append(row);
    }


    //Transfrom from string to Nodebook
    Nodebook *startNode = getNodebook(principalNode);
    Nodebook *finalNode = getNodebook(destinationNode);

    //Assign the first value as a distance of 0
    table.at(books.positionOf(startNode))->shortestDistance = 0;

    if(startNode != NULL && finalNode != NULL){
        //Dijkstra Algorithm
        Nodebook *currentNode = startNode;
        while (!isFinished(visited, books.size())){
            dijkstraTable *currentRow = table.at(books.positionOf(currentNode));
            //For the current node, calculate the distance to all unvisited neighbours
            for(int i=0; i<currentNode->getList().size();i++){
                //Get the row of the neighbour node
                Nodebook *neighbourNode = currentNode->getList().at(i)->getTo();
                dijkstraTable *neighbourRow = table.at(books.positionOf(neighbourNode));

                //Calculate distance for this neighbour, and update if its necessary
                //If it's not visited AND we have a new shortest distance
                if(!visited[books.positionOf(neighbourNode)]&&
                   currentRow->shortestDistance+currentNode->getList().at(i)->getCost()<neighbourRow->shortestDistance){
                    neighbourRow->shortestDistance = currentRow->shortestDistance+currentNode->getList().at(i)->getCost();
                    neighbourRow->previousNode = currentNode;
                }
            }
            //Mark current node as visited
            visited[books.positionOf(currentNode)] = true;
            //Choose new current node from unvisited nodes with minimal distance
            bool foundFirstElement = false;
            dijkstraTable *minimumRow;
            for(int i=0;i<table.size();i++){
                if(!foundFirstElement){
                    if(!visited[books.positionOf(table.at(i)->node)]){
                        minimumRow = table.at(i);
                        foundFirstElement = true;
                    }
                } else {
                    if(!visited[books.positionOf(table.at(i)->node)]&&(table.at(i)->shortestDistance)<minimumRow->shortestDistance){
                        minimumRow = table.at(i);
                    }
                }
            }
            currentNode = minimumRow->node;
        }

        //Interpretation of the table
        Nodebook *iterator = finalNode;
        string toReturn;
        while (iterator != startNode){
            toReturn.append(table.at(books.positionOf(iterator))->node->getBook()->getTitle()+">-");
            iterator = table.at(books.positionOf(iterator))->previousNode;
        }
        toReturn.append(iterator->getBook()->getTitle());
        StringOp helper;
        return helper.reverse(toReturn);
    } else {
        return ".\n";
    }


}

std::ostream& operator<<(std::ostream& os, Graph& graph) {
    for(int i=0;i < graph.getBooks().size(); i++){
        os<< "-" << graph.getBooks().at(i)->getBook()->getTitle()<<"\n";
        for(int j=0;j<graph.getBooks().at(i)->getList().size(); j++){
            os<< "    |--" << graph.getBooks().at(i)->getList().at(j)->getCost();
            os << "--" << graph.getBooks().at(i)->getList().at(j)->getTo()->getBook()->getTitle()<<"\n";
        }
    }
    return os;
}



#endif //GRAPHLIBRARY_GRAPH_H