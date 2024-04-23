#ifndef DOUBLY_LINKED_LIST_HPP
#define DOUBLY_LINKED_LIST_HPP

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
    
    void set(Node *Next, Node *Prev){
        this->next = Next;
        this->prev = Prev;
    }
};

template<class T>
class DoublyLinkedList{
private :
    Node<T> *head{};
    Node<T> *tail{};
    int length{};
    Node<T>* get_nth_node(int n) const;  // o(n)
    void link(Node<T>* first, Node<T>*second) ;
    void erase(Node<T> *toBeDeleted); 


public :
    DoublyLinkedList(){}
    DoublyLinkedList(initializer_list<T> values);
    DoublyLinkedList(const DoublyLinkedList<T>& other);
    ~DoublyLinkedList();
    DoublyLinkedList<T>& operator=(initializer_list<T> values);
    DoublyLinkedList<T>& operator=(const DoublyLinkedList<T>& other);
    
    void insertAtTail(T val); // o(1)
    void insertAtHead(T val); // o(1)
    void removeAtTail(); //  o(1)
    void removeAtHead(); // o(1)
    
    void removeAt(int index); // o(n)
    void insert_at(T val, int idx); // o(n)
    void replaceAt(T val, int idx); 

    void clear(); //o(n)
    
    int size() const; // o(1)
    bool empty() const; // o(1)

    void reverse(); // o(n)
    void make_unique(); // o(nlogn)
    
    T& operator[](int index) const; // o(n)
    
    void print() const; // o(n)

    void swap(int idx1, int idx2); // o(n)

    bool isExist(T val); // o(n)

    bool isItemAtEqual (T val, int idx) ; // o(n)
    
    T retrieveAt (int idx) ; // o(n)

    class ConstIterator;
    ConstIterator  cbegin() const { return ConstIterator(this->head, this); }
    ConstIterator cend() const { return ConstIterator(nullptr, this, true); }
    ConstIterator  begin() const { return ConstIterator(this->head, this); }
    ConstIterator end() const { return ConstIterator(nullptr, this, true); }
    
    class Iterator;
    Iterator begin() { return Iterator(this->head, this); }
    Iterator end() { return Iterator(nullptr, this, true); }
    
    T& front(){if(length==0) throw out_of_range("Index out of range");  return this->head->data;} // o(1)
    T& back(){ if(length==0) throw out_of_range("Index out of range");  return this->tail->data;} // o(1)
    
};

template<class T>
class DoublyLinkedList<T>::Iterator {
private:
    Node<T>* current;
    bool isEnd;
    friend class ConstIterator;
    DoublyLinkedList<T> *list ;
    friend class DoublyLinkedList ;
public:
    Iterator(Node<T>* start, DoublyLinkedList<T> *List, bool isend = false) : current(start), list(List), isEnd(isend) {}
    T& operator*();
    Iterator& operator++(); // Pre-increment
    Iterator& operator++(int); // Post-increment 
    Iterator& operator--(); // Pre-decrement
    Iterator& operator--(int); // Post-decrement 
    bool operator==(const Iterator& other) const; 
    bool operator==(const ConstIterator& other) const; 
    bool operator!=(const Iterator& other) const;
    bool operator!=(const ConstIterator& other) const;
};

template<class T>
class DoublyLinkedList<T>::ConstIterator {
private:
    const Node<T>* current;
    bool isEnd;
    friend class Iterator;
    const DoublyLinkedList<T> *list ;
    friend class DoublyLinkedList ;

public:
    ConstIterator(Node<T>* start, const DoublyLinkedList<T> *List, bool isend = false) : current(start), list(List), isEnd(isend) {}
    const T& operator*() const;
    ConstIterator& operator++(); // Pre-increment
    ConstIterator& operator++(int); // Post-increment 
    ConstIterator& operator--(); // Pre-decrement
    ConstIterator& operator--(int); // Post-decrement 
    bool operator==(const ConstIterator& other) const; 
    bool operator==(const Iterator& other) const; 
    bool operator!=(const ConstIterator& other) const;
    bool operator!=(const Iterator& other) const;
};



#endif
