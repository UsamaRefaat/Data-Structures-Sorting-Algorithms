#ifndef HEAP_H
#define HEAP_H

#include <string>
#include <iostream>
#include <cassert>
using namespace std ;

class Item
{
public:
    string itemName;
    string category;
    int price;

    Item(string name, string cat, int p) : itemName(name), category(cat), price(p) {}
    Item() : itemName(""), category(""), price(0) {}
    struct LessThanName
    {
        bool operator()(const Item &a, const Item &b, bool isMinHeap) const
        {
            return (isMinHeap? a.itemName < b.itemName : a.itemName > b.itemName);
        }
    };

    struct LessThanPrice
    {
        bool operator()(const Item &a, const Item &b,  bool isMinHeap) const
        {
            return (isMinHeap? a.price < b.price : a.price > b.price);
        }
    };
    bool operator==(const Item& other) const {
        return itemName == other.itemName && category == other.category && price == other.price;
    }


    void print() const
    {
        cout << "Name: " << itemName << ", Category: " << category << ", Price: " << price << '\n';
    }
};


template <class T, class Compare>
class Heap {
private:
    T *array;
    int size;
    int capacity;
    bool isMinHeap;
    Compare compare;


    int left(int node) {
        int p = 2 * node + 1;
        return (p >= size) ? -1 : p;
    }
    
    int right(int node) {
        int p = 2 * node + 2;
        return (p >= size) ? -1 : p;
    }
    
    int parent(int node) {
        return (node == 0) ? -1 : (node - 1) / 2;
    }

    void heapify_up(int child_pos) {
        int par_pos = parent(child_pos);
        if (child_pos == 0 || compare( array[par_pos] , array[child_pos], isMinHeap ) )
            return;

        std::swap(array[child_pos], array[par_pos]);
        heapify_up(par_pos);
    }

    void heapify_down(int parent_pos) {
        int child_pos = left(parent_pos);
        int right_child = right(parent_pos);

        if (child_pos == -1)  return;

        if (right_child != -1 &&  compare(array[right_child] , array[child_pos],isMinHeap ) )
            child_pos = right_child;

        if (  compare(array[child_pos],array[parent_pos], isMinHeap)  ) {
            std::swap(array[parent_pos], array[child_pos]);
            heapify_down(child_pos);
        }
    }


public:
    Heap(bool isMinHeap, int capacity = 1000) : compare(Compare()), size(0), capacity(capacity), isMinHeap(isMinHeap) {
        array = new T[capacity] ;
    }
    Heap(const Heap& other) : compare(Compare()), size(other.size), capacity(other.capacity), isMinHeap(other.isMinHeap) {
        array = new T[capacity];
        std::copy(other.array, other.array + size, array);
    }

    ~Heap() {
        delete[] array;
    }

    void push(T key) {
        assert(size + 1 <= capacity);
        array[size++] = key;
        heapify_up(size - 1);
    }

    void pop() {
        assert(!isempty());
        array[0] = array[--size];
        heapify_down(0);
    }

    T top() {
        assert(!isempty());
        return array[0];
    }

    bool isempty() {return !size;}

    void print(){
        for(int i=0;i<size;i++) array[i].print(); 
        cout << '\n';
    }

    void print_sorted(){
        Heap temp = *this;
        while(!temp.isempty()){
            temp.top().print();
            temp.pop();
        }
        cout << '\n';
    }
    bool deleteElement( T element) {
        for (int i = 0; i < size; i++) {
            if (array[i] == element) {
                array[i] = array[--size];
                heapify_down(i);
                return true ;
            }
        }
        return false ;
    }

};

#endif
