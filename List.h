#ifndef LIST_H
#define LIST_H

#include <iostream>

template <class T> class List;
template <class T>
class ListEntry{
    T thisEntry;
    ListEntry* nextEntry;
    ListEntry* prevEntry;
    ListEntry(T& entry);
    friend class List<T>;
};

template <class T>
//Construct a linked-list entry
ListEntry<T>::ListEntry(T &entry) {
    thisEntry = entry;
    nextEntry = NULL;
    prevEntry = NULL;
}

template <class T>
//Linked List
class List{
private:
    //Pointers
    ListEntry<T>* root;
    ListEntry<T>* lastNode;
    ListEntry<T>* iterator;

    //Additional Functions and Information
    int head;

public:
    //Constructor and destructor of the class
    List();
    ~List();

    //Methods to insert at different positions of the list
    void insertAt(int position, T& toInsert);
    void insertAtBeggining(T& toInsert);
    void append(T& toInsert);

    //Methods to remove elements from the list
    void deleteFirst();
    void deleteLast();
    void deleteAt(int pos);

    //Methods to get information about the list
    int size();
    bool isEmpty();
    int positionOf(T& entry);

    //Methods to get elements of the list
    T at(int pos);
    T firstEntry();
    T lastEntry();
    T nextEntry(int pos);
    T prevEntry(int pos);

    template <typename U>
    friend std::ostream& operator<<(std::ostream& os, const List<U>& list);
};

template <class T>
//Construct the list
List<T>::List() {
    root = lastNode = iterator = NULL;
    head = 0;
}

template <class T>
//Destroys the list
List<T>::~List(){

}

template <class T>
//Insert entry in certain position
void List<T>::insertAt(int position, T &toInsert) {
    //Verifies if we have a correct position
    if(position < 0 || position >= head)
        return;
    if(!position) {
        insertAtBeggining(toInsert);
    } else if(position == head-1){
        append(toInsert);
    } else {
        ListEntry<T>* newEntry = new ListEntry<T>(toInsert);
        at(position); //Moves iterator to the wished position

        //Insert to new position
        newEntry->nextEntry=iterator;
        newEntry->prevEntry=iterator->prevEntry;
        iterator->prevEntry->nextEntry=newEntry;
        iterator->prevEntry=newEntry;
        head++;
    }
}

template <class T>
//Insert at the beggining of the list
void List<T>::insertAtBeggining(T &toInsert) {
    if(!head)root=iterator=lastNode=NULL;

    iterator = root;

    ListEntry<T>* newEntry = new ListEntry<T>(toInsert);

    //Insert newEntry to the beggining of the list
    if(root==NULL){
        root=lastNode=newEntry;
        root->nextEntry = root->prevEntry = NULL;
    } else {
        newEntry->nextEntry = root;
        newEntry->prevEntry = NULL;
        root->prevEntry=newEntry;
        root = newEntry;
    }
    head++;
}

template <class T>
//Insert at the end of the list
void List<T>::append(T &toInsert) {
    if(!head){
        insertAtBeggining(toInsert);
    } else {
        ListEntry<T>* newEntry = new ListEntry<T>(toInsert);
        newEntry->nextEntry=NULL;
        newEntry->prevEntry=lastNode;

        lastNode->nextEntry=newEntry;
        lastNode = newEntry;
        head++;
    }
}

template <class T>
//Remove first element of the list
void List<T>::deleteFirst() {
    if(head==0) return;

    ListEntry<T> *temporal = root;
    //Update if there's only one entry on list
    if(head==1){
        iterator = root =lastNode = NULL;
        head--;
    } else {
        root = root->nextEntry;
        root->prevEntry = NULL;
        delete temporal;
        head--;
    }
}

template <class T>
//Delete Last element of the list
void List<T>::deleteLast() {
    if(isEmpty()) return;

    ListEntry<T> *temporal = lastNode;

    if(head==1){
        iterator=lastNode=root=NULL;
        head--;
    } else {
        lastNode=lastNode->prevEntry;
        delete temporal;
        lastNode->nextEntry = NULL;
        head--;
    }

}

template <class T>
//Delete at x position of the list
void List<T>::deleteAt(int pos) {
    if(pos<0 || pos>=head) return;

    if(!pos){
        deleteFirst();
    } else if(pos == head-1){
        deleteLast();
    } else {
        at(pos);
        ListEntry<T> *temporal = iterator;
        iterator->prevEntry->nextEntry=iterator->nextEntry;
        iterator->nextEntry->prevEntry = iterator->prevEntry;
        delete temporal;
        head--;
    }
}

template <class T>
//Return the size of the list
int List<T>::size() {return head;}

template <class T>
//Return if the list is empty or not
bool List<T>::isEmpty() {return head==0;}

template<class T>
//Return the position of given element
int List<T>::positionOf(T &entry) {
    iterator=root;
    int i=0;
    while (iterator){
        if(entry==iterator->thisEntry){
            return i;
        } else {
            i++;
            iterator = iterator->nextEntry;
        }
    }
    return -1;
}

template <class T>
//Return data of the given position
T List<T>::at(int pos) {
    if(pos<0 || pos>=head) return NULL;

    iterator=root;
    while(pos!=0){
        iterator = iterator->nextEntry;
        pos--;
    }
    return (iterator->thisEntry);
}

template <class T>
//Return the first element
T List<T>::firstEntry() {
    if(!isEmpty()){
        return root->thisEntry;
    }
    return NULL;
}

template <class T>
//Return the last entry
T List<T>::lastEntry() {
    if(!isEmpty()){
        return lastNode->thisEntry;
    }
}

template <class T>
//Return the next Entry of a position
T List<T>::nextEntry(int pos) {
    if(pos<0||pos>=head-1) return NULL;

    at(pos);
    return iterator->nextEntry->thisEntry;
}

template<class T>
//return the previous entry of a position
T List<T>::prevEntry(int pos) {
    if(pos<1||pos>=head)  NULL;

    at(pos);
    return iterator->prevEntry->thisEntry;
}



template<class T>
std::ostream& operator<<(std::ostream& os, const List<T>& list) {
    if(list.head==0){
        os << "";
        return os;
    }

    list.iterator = list.root;
    while (list.iterator!=NULL){
        os << list.iterator->thisEntry << " ";
    }
    return os;
}





#endif