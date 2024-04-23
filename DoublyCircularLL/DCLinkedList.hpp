#ifndef DoublyCircular_LINKED_LIST_HPP
#define DoublyCircular_LINKED_LIST_HPP

#include<iostream>
#include <initializer_list>
#include <map>
using namespace std;


template<class T>
struct Node{
    T data ;
    Node * next{};
    Node * prev{};
    Node(T val):data(val){}
};

template<class T>
class DoublyCircularLinkedList{
private :
    Node<T> *head{};
    Node<T> *tail{};
    int length{};
    Node<T>* get_nth_node(int n) const;  // o(n)
    void link(Node<T>* first, Node<T>*second) ;


public :
    DoublyCircularLinkedList(){}
    DoublyCircularLinkedList(initializer_list<T> values);
    DoublyCircularLinkedList(const DoublyCircularLinkedList<T>& other);
    ~DoublyCircularLinkedList();
    DoublyCircularLinkedList<T>& operator=(initializer_list<T> values);
    DoublyCircularLinkedList<T>& operator=(const DoublyCircularLinkedList<T>& other);
    
    void insertAtTail(T val); // o(1)
    void insertAtHead(T val); // o(1)
    void removeAtTail(); // o(n)
    void removeAtHead(); // o(1)
    
    void removeAt(int index); // o(n)
    void insert_at(T val, int index); // o(n)
    
    void clear(); //o(n)
    
    int size() const; // o(1)
    bool empty() const; // o(1)
    
    T& operator[](int index) const; // o(n)
    
    void print() const; // o(n)

    void swap(int idx1, int idx2);
    
    T retrieveAt (int index);
    void replaceAt (T val, int index);
    bool isExist (T val) ;
    bool isItemAtEqual (T val, int index) ;
    
    T& front(){if(length==0) throw out_of_range("Index out of range");  return this->head->data;} // o(1)
    T& back(){ if(length==0) throw out_of_range("Index out of range");  return this->tail->data;} // o(1)
    
};

#endif
