#include"DCLinkedList.hpp"



template<class T>
DoublyCircularLinkedList<T>::DoublyCircularLinkedList(initializer_list<T> values){ //done
    for (const T& val : values) 
        insertAtTail(val);
}

template<class T>
DoublyCircularLinkedList<T>::DoublyCircularLinkedList(const DoublyCircularLinkedList<T>& other){  // done
    Node<T>* current = other.head; 
    if(!current) return ;
    
    do { 
        this->insertAtTail(current->data); 
        current = current->next; 
    } while (current != other.head); 
    
}

template<class T>
DoublyCircularLinkedList<T>::~DoublyCircularLinkedList(){ // done
    this->clear();
}

template<class T>
DoublyCircularLinkedList<T>& DoublyCircularLinkedList<T>::operator=(initializer_list<T> values){ // done  
    this->clear();
    for (const T &val : values) 
        this->insertAtTail(val);
    return *this;
}

template<class T>
DoublyCircularLinkedList<T>& DoublyCircularLinkedList<T>::operator=(const DoublyCircularLinkedList<T>& other){ // done
    if (this == &other) // self-assignment guard
        return *this;
    
    this->clear();

    Node<T>* current = other.head; 
    if(!current) return *this;
    
    do { 
        this->insertAtTail(current->data); 
        current = current->next; 
    } while (current != other.head); 
    
    return *this;
}

template<class T>
void DoublyCircularLinkedList<T>::link(Node<T>* first, Node<T>*second) {
    if (first)
        first->next = second;
    if (second)
        second->prev = first;
}



template<class T>
void DoublyCircularLinkedList<T>::insertAtTail(T val){ // done
    Node<T> *newNode = new Node<T>(val);

    if(!head){
        head=tail=newNode;
    }
    else{
        link(tail,newNode);
        tail=newNode;
    }
    tail->next = head;
    head->prev = tail ;
    length++;
}

template<class T>
void DoublyCircularLinkedList<T>::insertAtHead(T val){ // done
    Node<T> *newNode = new Node<T>(val);

    if(!head){
        head=tail=newNode;

    }
    else{
        link(newNode,head);
        head = newNode;
    }
    tail->next = head;
    head->prev = tail ;
    length++;
}


template<class T>
Node<T>* DoublyCircularLinkedList<T>::get_nth_node(int n) const{ // done
    if(n<0 || n>=length) throw out_of_range("Index out of range");
    Node<T> *node;
    if(n<=length/2){    
        node = head;
        while(n--) node=node->next; 
    }

    else{
        node = tail;
        n = length - n - 1;
        while(n--) node=node->prev;
    }
    return node;
}

template<class T>
T& DoublyCircularLinkedList<T>::operator[](int index) const{ // done
    if(index<0 || index>=length) throw out_of_range("Index out of range");
    Node<T> *node;
    if(index<=length/2){ // loop from the begin
        node = head;
        while(index--) node=node->next; 
    }
    else{ // loop from back
        node = tail;
        index = length - index - 1;
        while(index--) node=node->prev;
    }
    
    return node->data;
}



template <class T>
void DoublyCircularLinkedList<T>::removeAtTail(){ // done
    if(this->head == nullptr)   // length==0
        throw std::runtime_error("Cannot pop from an empty list");
        
    if(this->head==this->tail){ // length == 1
        delete this->tail;
        this->head=this->tail=nullptr;
        length=0;
        return;
    }
    
    // get before last node 
    Node<T> *beforelastNode = this->tail->prev;
    
    delete this->tail ;
    this->tail = beforelastNode;
    tail->next = head ;
    head->prev = tail ;

    this->length--;

}

template <class T>
void DoublyCircularLinkedList<T>::removeAtHead(){ // done
    if(this->head== nullptr)   // length==0
        throw std::runtime_error("Cannot pop from an empty list");
        

    if(this->head==this->tail){ // length == 1
        delete this->head;
        this->head=this->tail=nullptr;
        this->length=0;
        return;
    }
        
    Node<T> *temp = head;
    head = head->next;
    tail->next = head;
    head->prev = tail ;
    delete temp;
    
    this->length--;

}

template<class T>
void DoublyCircularLinkedList<T>::print() const{ //  done
    
    if(!this->head) return ;
    Node<T>* current = this->head; 
    
    do { 
        cout << current->data << ' ' ; 
        current = current->next; 
        
    } while (current != head); 
        
    cout << '\n';
}

template<class T>
int DoublyCircularLinkedList<T>::size() const{ // done
    return this->length;
}

template<class T>
void DoublyCircularLinkedList<T>::clear(){ // done
    if(!head) return ;     
    Node<T> *temp = head;
    tail->next = nullptr;
    while(head){
        head = head->next;
        delete temp;
        temp = head;
    }
    this->head = this-> tail = nullptr ;
    length=0;
}

template<class T>
bool DoublyCircularLinkedList<T>::empty() const{ // done
    return !head; // length==0
}

template<class T>
void DoublyCircularLinkedList<T>::removeAt(int index) { // o(n)
    if(index==0){ this->removeAtHead(); return ;} // o(1)
    if(index==length-1){this->removeAtTail(); return ;} // o(n)
    
    // o(n)

    Node<T> *prev = get_nth_node(index-1); // throw index out of range if so
    Node<T> *toBeDeleted = prev->next ;

    link(prev,toBeDeleted->next);
    delete toBeDeleted;
    
    length--;
}



template<class T>
void DoublyCircularLinkedList<T>::insert_at(T val, int index ) { // done
    if(index==0){ this->insertAtHead(val); return ;} // o(1)
    if(index==length){this->insertAtTail(val); return ;} // o(1)
    
    // o(n)

    Node<T> *prev = get_nth_node(index-1); // throw index out of range if so
    Node<T> *toBeShifted = prev->next ;
    
    // Node<T> *newNode(val);
    Node<T> *newNode = new Node<T>(val);
    link(prev,newNode);
    link(newNode,toBeShifted);

    length++;
}



template<class T>
void DoublyCircularLinkedList<T>::swap(int idx1, int idx2) { 
    if(idx1<0 || idx1>=length) throw out_of_range("Index out of range");
    if(idx2<0 || idx2>=length) throw out_of_range("Index out of range");
    
    if(idx1==idx2) return ;
    if(idx1>idx2 ) std::swap(idx1,idx2);
    
    Node<T> *node1 = get_nth_node(idx1), *node2 = get_nth_node(idx2);
    Node<T> *prev = node1->prev; 
    Node<T> *next = node1->next; 


    if(idx1+1!=idx2) link( node2->prev ,node1);
    link(node1, (idx1==0 && idx2==this->length-1)? node2 : node2->next); 
    link(prev,node2);
    link(node2, (next==node2? node1 : next));        
    
    if(node1==head) head = node2;              
    if(node2==tail) tail = node1;
    tail->next = head ;
    head->prev = tail ;
}


template<class T>
bool DoublyCircularLinkedList<T>::isExist(T val) { 

    if(!this->head) return false ;
    Node<T>* node = this->head; 
    do { 
        if(node->data==val) return true;
        node = node->next;
    } while (node != head); 
        
    return false ;
}

template<class T>
bool DoublyCircularLinkedList<T>::isItemAtEqual(T val, int idx) { 
    return this->operator[](idx) == val;
}

template<class T>
T DoublyCircularLinkedList<T>::retrieveAt(int idx) { 
    return this->operator[](idx);
}

template<class T>
void DoublyCircularLinkedList<T>::replaceAt(T val, int idx) { 
    this->operator[](idx) = val;
    return;
}
