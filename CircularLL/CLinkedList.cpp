#include"CLinkedList.hpp"


template<class T>
CircularLinkedList<T>::CircularLinkedList(initializer_list<T> values){ //done
    for (const T& val : values) 
        insertAtTail(val);
}

template<class T>
CircularLinkedList<T>::CircularLinkedList(const CircularLinkedList<T>& other){  // done
    Node<T>* current = other.head; 
    if(!current) return ;
    
    do { 
        this->insertAtTail(current->data); 
        current = current->next; 
    } while (current != other.head); 
    
}

template<class T>
CircularLinkedList<T>::~CircularLinkedList(){ // done
    this->clear();
}

template<class T>
CircularLinkedList<T>& CircularLinkedList<T>::operator=(initializer_list<T> values){ // done  
    this->clear();
    for (const T &val : values) 
        this->insertAtTail(val);
    return *this;
}

template<class T>
CircularLinkedList<T>& CircularLinkedList<T>::operator=(const CircularLinkedList<T>& other){ // done
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
void CircularLinkedList<T>::insertAtTail(T val){ // done
    Node<T> *newNode = new Node<T>(val);

    if(!head){
        head=tail=newNode;
        newNode->next = newNode;  
    }
    else{
        tail->next=newNode;
        tail=newNode;
        tail->next = head; 
    }
    length++;
}

template<class T>
void CircularLinkedList<T>::insertAtHead(T val){ // done
    Node<T> *newNode = new Node<T>(val);

    if(!head){
        head=tail=newNode;
        newNode->next = newNode;  
    }
    else{
        newNode->next=head;
        head = newNode;
        tail->next = head;
    }
    length++;
}


template<class T>
Node<T>* CircularLinkedList<T>::get_nth_node(int n) const{ // done
    if(n<0 || n>=length) throw out_of_range("Index out of range");
    Node<T> *node = head;
    while(n--) node=node->next; 
    return node;
}

template<class T>
T& CircularLinkedList<T>::operator[](int index) const{ // done
    if(index<0 || index>=length) throw out_of_range("Index out of range");
    Node<T> *node = head;
    while(index--) node=node->next; 
    return node->data;
}



template <class T>
void CircularLinkedList<T>::removeAtTail(){ // done
    if(this->head == nullptr)   // length==0
        throw std::runtime_error("Cannot pop from an empty list");
        
    if(this->head==this->tail){ // length == 1
        delete this->tail;
        this->head=this->tail=nullptr;
        length=0;
        return;
    }
    
    // get before last node 
    Node<T> *beforelastNode = this->get_nth_node(this->length-2);
    
    delete this->tail ;
    this->tail = beforelastNode;
    beforelastNode->next = head ;
    
    this->length--;

}

template <class T>
void CircularLinkedList<T>::removeAtHead(){ // done
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
    delete temp;
    
    this->length--;

}

template<class T>
void CircularLinkedList<T>::print() const{ //  done
    
    if(!this->head) return ;
    Node<T>* current = this->head; 
    
    do { 
        cout << current->data << ' ' ; 
        current = current->next; 
        
    } while (current != head); 
        
    cout << '\n';
}

template<class T>
int CircularLinkedList<T>::size() const{ // done
    return this->length;
}

template<class T>
void CircularLinkedList<T>::clear(){ // done
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
bool CircularLinkedList<T>::empty() const{ // done
    return !head; // length==0
}

template<class T>
void CircularLinkedList<T>::erase(int index) { // o(n)
    if(index==0){ this->removeAtHead(); return ;} // o(1)
    if(index==length-1){this->removeAtTail(); return ;} // o(n)
    
    // o(n)

    Node<T> *prev = get_nth_node(index-1); // throw index out of range if so
    Node<T> *toBeDeleted = prev->next ;

    prev->next = toBeDeleted->next;

    delete toBeDeleted;
    length--;
}



template<class T>
void CircularLinkedList<T>::insert_at(T val, int index ) { // done
    if(index==0){ this->insertAtHead(val); return ;} // o(1)
    if(index==length){this->insertAtTail(val); return ;} // o(1)
    
    // o(n)

    Node<T> *prev = get_nth_node(index-1); // throw index out of range if so
    Node<T> *toBeShifted = prev->next ;
    
    // Node<T> *newNode(val);
    Node<T> *newNode = new Node<T>(val);

    prev->next = newNode;
    newNode->next = toBeShifted;
    length++;
}



template<class T>
void CircularLinkedList<T>::swap(int idx1, int idx2) { 
    if(idx1<0 || idx1>=length) throw out_of_range("Index out of range");
    if(idx2<0 || idx2>=length) throw out_of_range("Index out of range");
    
    if(idx1==idx2) return ;
    if(idx1>idx2) std::swap(idx1,idx2);

    Node<T> *node1prev = nullptr, *node1 = head; 
    Node<T> *node2prev = nullptr, *node2 = head;

    for (int i = 0 ; ; i++){
        if (i < idx1){
            node1prev = node1;
            node1 = node1->next;
        }
        if (i < idx2){
            node2prev = node2;
            node2 = node2->next;
        }
        else break;
    }
    
    if (node1==head){ head = node2;}
    else node1prev->next = node2; 
    node2prev->next = node1;

    // if consecutive node 1 = node2prev
    if(node2==tail) tail = node1;
    
    std::swap(node1->next , node2->next );
    tail->next = head ;
}


template<class T>
bool CircularLinkedList<T>::isExist(T val) { 

    if(!this->head) return false ;
    Node<T>* node = this->head; 
    do { 
        if(node->data==val) return true;
        node = node->next;
    } while (node != head); 
        
    return false ;
}

template<class T>
bool CircularLinkedList<T>::isItemAtEqual(T val, int idx) { 
    return this->operator[](idx) == val;
}

template<class T>
T CircularLinkedList<T>::retrieveAt(int idx) { 
    return this->operator[](idx);
}

template<class T>
void CircularLinkedList<T>::replaceAt(T val, int idx) { 
    this->operator[](idx) = val;
    return;
}
