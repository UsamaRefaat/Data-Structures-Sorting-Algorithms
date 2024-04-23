#include"DLinkedList.hpp"


template<class T>
DoublyLinkedList<T>::DoublyLinkedList(initializer_list<T> values){ //done
    for (const T& val : values) 
        insertAtTail(val);
}

template<class T>
DoublyLinkedList<T>::DoublyLinkedList(const DoublyLinkedList<T>& other){  // done
    for(const T &data : other)
        insertAtTail(data);
    
}

template<class T>
DoublyLinkedList<T>::~DoublyLinkedList(){ // done
    this->clear();
}

template<class T>
DoublyLinkedList<T>& DoublyLinkedList<T>::operator=(initializer_list<T> values){ // done
    
    this->clear();
    for (const T &val : values) 
        this->insertAtTail(val);
    return *this;
}

template<class T>
DoublyLinkedList<T>& DoublyLinkedList<T>::operator=(const DoublyLinkedList<T>& other){ // done
    if (this == &other) // self-assignment guard
        return *this;
    
    this->clear();
    for(const T &data : other)
        insertAtTail(data);
    
    return *this;
}

template<class T>
void DoublyLinkedList<T>::link(Node<T>* first, Node<T>*second) {
    if (first)
        first->next = second;
    if (second)
        second->prev = first;
}


template<class T>
void DoublyLinkedList<T>::insertAtTail(T val){ // done
    Node<T> *newNode = new Node<T>(val);

    if(!head){head=tail=newNode;}
    else{
        link(tail,newNode);
        tail=newNode;
    }
    length++;
}

template<class T>
void DoublyLinkedList<T>::insertAtHead(T val){ // done
    Node<T> *newNode = new Node<T>(val);

    if(!head){head=tail=newNode;}
    else{
        link(newNode,head);
        head = newNode;
    }
    length++;
}


template<class T>
Node<T>* DoublyLinkedList<T>::get_nth_node(int n) const{ // done
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
T& DoublyLinkedList<T>::operator[](int index) const{ // done
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
void DoublyLinkedList<T>::removeAtTail(){ // done
    if(this->head== nullptr)   // length==0
        throw std::runtime_error("Cannot pop from an empty list");
        
    if(this->head==this->tail){ // length == 1
        delete this->tail;
        this->head=this->tail=nullptr;
        this->length = 0;
        return;
    }
    
    // get before last node 
    Node<T> *beforelastNode = this->tail->prev;
    
    delete this->tail ;
    this->tail = beforelastNode;
    beforelastNode->next = nullptr ;
    
    this->length--;

}

template <class T>
void DoublyLinkedList<T>::removeAtHead(){ // done
    if(this->head== nullptr)   // length==0
        throw std::runtime_error("Cannot pop from an empty list");
        

    if(this->head==this->tail){ // length == 1
        delete this->head;
        this->head=this->tail=nullptr;
        this->length = 0 ;
        return;
    }
        
    Node<T> *temp = head;
    head = head->next;
    head->prev = nullptr;
    delete temp;
    
    this->length--;

}

template<class T>
void DoublyLinkedList<T>::print() const{ //  done
    
    if(!head) return ;
    
    for(Node<T> *node = this->head ; node ; node = node->next )
        cout << node->data << ' ';
        
    cout << '\n';
}

template<class T>
int DoublyLinkedList<T>::size() const{ // done
    return this->length;
}

template<class T>
void DoublyLinkedList<T>::clear(){ // done
    Node<T> *temp = head;
    while(head){
        head = head->next;
        delete temp;
        temp = head;
    }
    length=0;
}

template<class T>
bool DoublyLinkedList<T>::empty() const{ // done
    return !head; // length==0
}

template<class T>
void DoublyLinkedList<T>::removeAt(int index) { // o(n)
    if(index==0){ this->removeAtHead(); return ;} // o(1)
    if(index==length-1){this->removeAtTail(); return ;} // o(1)
    
    // o(n)

    Node<T> *prev = get_nth_node(index-1); // throw index out of range if so
    Node<T> *toBeDeleted = prev->next ;

    link(prev,toBeDeleted->next);
    delete toBeDeleted;
    
    length--;
}

template<class T>
void DoublyLinkedList<T>::erase(Node<T> *toBeDeleted) { // o(1)
    if(toBeDeleted==head){ this->removeAtHead(); return ;} // o(1)
    if(toBeDeleted==tail){this->removeAtTail(); return ;} // o(1)
    
    // o(1)

    Node<T> *prev = toBeDeleted->prev ;

    link(prev,toBeDeleted->next);
    delete toBeDeleted;
    
    length--;
}



template<class T>
void DoublyLinkedList<T>::insert_at(T val, int index) { // done
    if(index==0){ this->insertAtHead(val); return ;} // o(1)
    if(index==length){this->insertAtTail(val); return ;} // o(1)
    
    // o(n)

    Node<T> *prev = get_nth_node(index-1); // throw index out of range if so
    Node<T> *toBeShifted = prev->next ;
    
    Node<T> *newNode = new Node<T>(val);
    link(prev,newNode);
    link(newNode,toBeShifted);

    length++;
}
  
 
template<class T>
void DoublyLinkedList<T>::reverse() { // done
    if(length==0 || length==1) return;
    
    Node<T>* current = head;

    while (current) {
        std::swap(current->next,current->prev);
        current = current->prev ;
    }

    std::swap(head,tail);
}

template<class T>
void DoublyLinkedList<T>::make_unique() { // time : o(nlogn).  space : o(n)
    if(length==0 || length==1) return;
    
    map<T,bool> occurred ;
    Node<T> *node = head  ;
    
    while(node){
        if(occurred[node->data]){
            Node<T> *temp = node ;
            node = node->next; // increment before deletion, dont increment prev
            erase(temp);
        }
        else{         
            occurred[node->data] = 1;
            node = node->next;
        }
    }
}

// o(n)
template<class T>
void DoublyLinkedList<T>::swap(int idx1, int idx2) { 
    if(idx1<0 || idx1>=length) throw out_of_range("Index out of range");
    if(idx2<0 || idx2>=length) throw out_of_range("Index out of range");
    
    if(idx1==idx2) return ;
    if(idx1>idx2) std::swap(idx1,idx2);

    Node<T> *node1 = get_nth_node(idx1), *node2 = get_nth_node(idx2);
    
    Node<T> *prev = node1->prev;
    Node<T> *next = node1->next;
 

    if(idx1+1!=idx2) link( node2->prev ,node1);
    link(node1, node2->next);

    link(prev,node2);
    link(node2, (next==node2? node1 : next));

    if(node1==head) head = node2;
    if(node2==tail) tail = node1;

}

// o(n)
template<class T>
bool DoublyLinkedList<T>::isExist(T val) { 
    Node<T> *node = head;
    while(node){
        if(node->data==val) return true;
        node = node->next;
    }
    return false;
}

template<class T>
bool DoublyLinkedList<T>::isItemAtEqual(T val, int idx) { 
    return this->operator[](idx) == val;
}

template<class T>
T DoublyLinkedList<T>::retrieveAt(int idx) { 
    return this->operator[](idx);
}

template<class T>
void DoublyLinkedList<T>::replaceAt(T val, int idx) { 
    this->operator[](idx) = val;
    return;
}

//*********************************************************************************************
// iterator
//*********************************************************************************************

template<class T>
bool DoublyLinkedList<T>::Iterator::operator==(const Iterator& other) const{
    return this->current==other.current;    
    // compares if they have the same memory address
}

template<class T>
bool DoublyLinkedList<T>::Iterator::operator==(const ConstIterator& other) const{
    return this->current==other.current;    
    // compares if they have the same memory address
}

template<class T>
bool DoublyLinkedList<T>::Iterator::operator!=(const Iterator& other) const{
    return this->current!=other.current;
   // !(*this==other) leverage the overloaded ==
}

template<class T>
bool DoublyLinkedList<T>::Iterator::operator!=(const ConstIterator& other) const{
    return this->current!=other.current;
   // !(*this==other) leverage the overloaded ==
}

template<class T>
T& DoublyLinkedList<T>::Iterator::operator*() { // done
    return this->current->data;
}

template <class T>
class DoublyLinkedList<T>::Iterator& DoublyLinkedList<T>::Iterator::operator++() { // done
    if(current==list->tail) isEnd = true ;
    if( current) this->current = this->current->next;
    return *this;
}
template <class T>
class DoublyLinkedList<T>::Iterator& DoublyLinkedList<T>::Iterator::operator++(int) { // done
    if(current==list->tail) isEnd = true ;
    if( current) this->current = this->current->next;
    return *this;
}
template <class T>
class DoublyLinkedList<T>::Iterator& DoublyLinkedList<T>::Iterator::operator--() { // done
    if( current) this->current = this->current->prev;
    else if(isEnd) {this->current = list->tail ; this->isEnd = false ;}
    return *this;
}
template <class T>
class DoublyLinkedList<T>::Iterator& DoublyLinkedList<T>::Iterator::operator--(int) { // done
    if( current) this->current = this->current->prev;
    else if(isEnd) {this->current = list->tail ; this->isEnd = false ;}
    return *this;
}


//*********************************************************************************************
// const_iterator
//*********************************************************************************************

template<class T>
bool DoublyLinkedList<T>::ConstIterator::operator==(const ConstIterator& other) const{
    return this->current==other.current;    
    // compares if they have the same memory address
}

template<class T>
bool DoublyLinkedList<T>::ConstIterator::operator==(const Iterator& other) const{
    return this->current==other.current;    
    // compares if they have the same memory address
}

template<class T>
bool DoublyLinkedList<T>::ConstIterator::operator!=(const ConstIterator& other) const{
    return this->current!=other.current;
    // !(*this==other) leverage the overloaded ==
}

template<class T>
bool DoublyLinkedList<T>::ConstIterator::operator!=(const Iterator& other) const{
    return this->current!=other.current;
    // !(*this==other) leverage the overloaded ==
}

template<class T>
const T& DoublyLinkedList<T>::ConstIterator::operator*() const { // done
    return this->current->data;
}

template <class T>
class DoublyLinkedList<T>::ConstIterator& DoublyLinkedList<T>::ConstIterator::operator++() { // done
    if(current==list->tail) isEnd = true ;
    if( current) this->current = this->current->next;
    return *this;
}
template <class T>
class DoublyLinkedList<T>::ConstIterator& DoublyLinkedList<T>::ConstIterator::operator++(int) { // done
    if(current==list->tail) isEnd = true ;
    if( current) this->current = this->current->next;    
    return *this;
}

template <class T>
class DoublyLinkedList<T>::ConstIterator& DoublyLinkedList<T>::ConstIterator::operator--() { // done
    if( current) this->current = this->current->prev;
    else if(isEnd) {this->current = list->tail ; this->isEnd = false ;}
    return *this;
}
template <class T>
class DoublyLinkedList<T>::ConstIterator& DoublyLinkedList<T>::ConstIterator::operator--(int) { // done
    if( current) this->current = this->current->prev;
    else if(isEnd) {this->current = list->tail ; this->isEnd = false ;}
    return *this;
}
