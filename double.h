#ifndef DOUBLY_H
#define DOUBLY_H
#include <iostream>
#include "list.h"

// TODO: Implement all methods
template <typename T>
class DoubleList : public List<T> {
private:
    Node<T>* head;
    Node<T>* tail;
    int nodes;
public:
    DoubleList() : List<T>() {
        head = nullptr;
        tail = nullptr;
    }

    ~DoubleList(){
        for (auto it = head; it->next != nullptr; it = it->next){
            delete it;
        }
        delete head;
        delete tail;
    }

    typedef ListIterator<T> Iterator;

    Iterator begin(){
        return Iterator(this, this->head);
    }

    Iterator end(){
        return Iterator(this, nullptr);
    }

    T front(){
        return head->data;
        //throw ("sin definir");
    }

    T back(){
        return tail->data;
        //throw ("sin definir");
    }

    bool is_empty(){
        if(head == nullptr && tail == nullptr)
            return true;
        else
            return false;
        //throw ("sin definir");
    }

    void push_front(T data){
        Node<T>* nuevo = new Node<T>;
        nuevo->data = data;
        if(is_empty()){
            head = nuevo;
            tail = nuevo;
        }
        else {
            nuevo->next = head;
            head->prev = nuevo;
            head = nuevo;
            //throw ("sin definir");
        }
    }

    void push_back(T data){
        auto nuevo = new Node<T>(data);
        if(is_empty()){
            head = nuevo;
            tail = nuevo;
        }
        else{
            nuevo->next = nullptr;
            nuevo->prev = tail;
            tail->next = nuevo;
            tail = nuevo;
        }
        //throw ("sin definir");
    }

    T pop_front(){
        if(is_empty()){
            return head->data;
        }
        else{
            T val = head->data;
            head = head->next;
            delete head->prev;
            head -> prev = nullptr;
            return val;
        }
        //throw ("sin definir");
    }

    T pop_back(){
        if(is_empty()){
            return head->data;
        }
        else {
            T val = tail->data;
            tail = tail->prev;
            delete tail->next;
            tail->next = nullptr;
            return val;
        }
        //throw ("sin definir");
    }

    T insert(T data, int pos){
        auto nuevo = new Node<T>(data);
        int size = this->size();
        if(is_empty()){
            head = nuevo;
            tail = nuevo;
        }
        else if(pos == 0){
            nuevo->next = head;
            head->prev = nuevo;
            head = nuevo;
        }
        else if(pos == size){
            nuevo->next = nullptr;
            nuevo->prev = tail;
            tail->next = nuevo;
            tail = nuevo;
        }
        else if(pos>0 && pos<size){
            auto temp = head;
            for(int i = 0; i < pos - 1; i++)
                temp = temp->next;
            nuevo->next = temp->next;
            nuevo->prev = temp;
            temp->next->prev = nuevo;
            temp->next = nuevo;
        }
        //else
        //throw exception ("posicion no valida");
        return nuevo->data;
    }

    void remove(int pos){
        int size = this->size();
        if(is_empty()){
            return;
        }
        else if(pos == 0){
            head = head -> next;
            delete head->prev;
            head -> prev = nullptr;
        }
        else if(pos == size){
            tail = tail->prev;
            delete tail->next;
            tail->next = nullptr;
        }
        else if(pos>0 && pos<size){
            auto temp = head;
            for (int i = 0; i < pos; ++i){
                temp = temp->next;
            }
            temp->next->prev = temp->prev;
            temp->prev->next = temp->next;
            delete temp;
        }
        //else
        //throw exception ("posicion no valida");
    }

    T& operator[](int pos){
        auto temp = head;
        int size = this->size();
        if(is_empty()){
            return head->data;
        }
        else if(pos == 0){
            return head->data;
        }
        else if(pos == size){
            return tail->data;
        }
        else if(pos>0 && pos<size){
            for (int i = 0; i < pos; ++i) {
                temp = temp->next;
            }
            return temp->data;
        }
        //else
        //throw exception ("posicion no valida");
    }

    int size(){
        int cont = 0;
        for (auto it = head; it != nullptr; it = it->next){
            cont++;
        }
        return cont;
        //throw ("sin definir");
    }

    void clear(){
        if(is_empty()){
            return;
        }
        else{
            for(auto it = head; it->next != nullptr; it = it->next){
                delete it;
            }
        }
        head = tail = nullptr;
        //throw ("sin definir");
    }

    void sort(){//insert sort
        if (is_empty() || size()==1){
            return;
        }
        else{
            Node<T>* front = head;
            Node<T>* back = nullptr;
            while (front != nullptr)
            {
                back = front->next;
                while (back != nullptr && back->prev != nullptr && back->data < back->prev->data){
                    T value = back->data;
                    back->data = back->prev->data;
                    back->prev->data = value;
                    back = back->prev;
                }
                front = front->next;
            }
        }
        //throw ("sin definir");
    }

    bool is_sorted(){
        int cont = 0;
        for (auto it = head; it->next != nullptr; it = it->next){
            if(it->data < it->next->data)
                cont++;
        }
        return cont == size()-1;
        //throw ("sin definir");
    }

    void reverse(){
        auto it = head;
        Node<T>* temp = nullptr;

        while (it != nullptr) {
            temp = it->prev;
            it->prev = it->next;
            it->next = temp;
            it = it->prev;
        }
        if(temp != nullptr)
            head = temp->prev;
        //throw ("sin definir");
    }

    string name(){
        return "DoubleList";
    }
//    void display(){
//        for (auto it = head; it != nullptr; it = it->next){
//            cout << it->data << " ";
//        }
//        cout << endl;
//    }

};
#endif