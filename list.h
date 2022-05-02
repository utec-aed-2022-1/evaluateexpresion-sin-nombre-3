#ifndef LIST_H
#define LIST_H

#include "node.h"
#include <string>
using namespace std;

template <class T>
class ListIterator;

// TODO: Implement all methods
template <typename T>
class List {
    Node<T>* head;
    Node<T>* tail;
    int nodes;
    friend class ListIterator<T>;

public:
    List() : head(nullptr), tail(nullptr), nodes(0) {};
    virtual ~List(){
        for (auto it = head; it->next != nullptr; it = it->next){
            delete it;
        }
        delete head;
        delete tail;
    };

    //Contrato
    typedef ListIterator<T> Iterator;
    virtual Iterator begin() = 0;
    virtual Iterator end() = 0;
    virtual T front() = 0;
    virtual T back() = 0;
    virtual void push_front(T) = 0;
    virtual void push_back(T) = 0;
    virtual T pop_front() = 0;
    virtual T pop_back() = 0;
    virtual T insert(T, int) = 0;
    virtual void remove(int) = 0;
    virtual T& operator[](int) = 0;//debe ser declarado en cada clase hija
    virtual bool is_empty() = 0;
    virtual int size() = 0;
    virtual void clear() = 0;
    virtual void sort() = 0;
    virtual bool is_sorted() = 0;
    virtual void reverse() = 0;
    virtual std::string name() = 0;
    //virtual void display() = 0;
};

template <class T>
class ListIterator{
private:
    Node<T>* current;
    List<T>* list;
    friend class List<T>;
public:
    ListIterator(){
        list = nullptr;
        current = nullptr;
    }
    ListIterator(List<T>* _list, Node<T>* _current){
        list = _list;
        current = _current;
    }

    ListIterator& operator++();
    ListIterator& operator--();
    T& operator*();
    bool operator!=(ListIterator other);
};

template <class T>
ListIterator<T>& ListIterator<T>::operator++(){
    current = current->next;
    return *this;
}
template <class T>
ListIterator<T>& ListIterator<T>::operator--(){// No es posible usar solo en forward list
    current = current->prev;
    return *this;
}
template <class T>
T& ListIterator<T>::operator*(){
    return current->data;
}
template <class T>
bool ListIterator<T>::operator!=(ListIterator<T> other){
    return current != other.current;
}

#endif