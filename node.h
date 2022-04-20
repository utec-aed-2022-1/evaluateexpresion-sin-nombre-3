#ifndef NODE_H
#define NODE_H
#include <iostream>
template <typename T>
struct Node {
    T data;
    Node<T>* next;
    Node<T>* prev;

    Node(){ 
        //data = 0;
        next = nullptr;
        prev = nullptr;
    }

    Node(T value){
        data = value;
        next = nullptr;
        prev = nullptr;
    }

    void killSelf(){
        delete this;
    }    
};

#endif