#include"SLinkedList.hpp"


template<class T>
SinglyLinkedList<T>::SinglyLinkedList(initializer_list<T> values){ //done
    for (const T& val : values) 
        insertAtTail(val); 
}

template<class T>
SinglyLinkedList<T>::SinglyLinkedList(const SinglyLinkedList<T>& other){  // done
    for(const T &data : other)
        insertAtTail(data);
    
}

template<class T>
SinglyLinkedList<T>::~SinglyLinkedList(){ // done
    this->clear();
}

template<class T>
SinglyLinkedList<T>& SinglyLinkedList<T>::operator=(initializer_list<T> values){ // done
    
    this->clear();
    for (const T &val : values) 
        this->insertAtTail(val);
    return *this;
}

template<class T>
SinglyLinkedList<T>& SinglyLinkedList<T>::operator=(const SinglyLinkedList<T>& other){ // done
    if (this == &other) // self-assignment guard
        return *this;
    
    this->clear();
    for(const T &data : other)
        insertAtTail(data);
    
    return *this;
}

template<class T>
void SinglyLinkedList<T>::insertAtTail(T val){ // done
    Node<T> *newNode = new Node<T>(val);

    if(!head){head=tail=newNode;}
    else{
        tail->next=newNode;
        tail=newNode;
    }
    length++;
}

template<class T>
void SinglyLinkedList<T>::insertAtHead(T val){ // done
    Node<T> *newNode = new Node<T>(val);

    if(!head){head=tail=newNode;}
    else{
        newNode->next=head;
        head = newNode;
    }
    length++;
}


template<class T>
Node<T>* SinglyLinkedList<T>::get_nth_node(int n) const{ // done
    if(n<0 || n>=length) throw out_of_range("Index out of range");
    Node<T> *node = head;
    while(n--) node=node->next; 
    return node;
}

template<class T>
T& SinglyLinkedList<T>::operator[](int index) const{ // done
    if(index<0 || index>=length) throw out_of_range("Index out of range");
    Node<T> *node = head;
    while(index--) node=node->next; 
    return node->data;
}



template <class T>
void SinglyLinkedList<T>::removeAtTail(){ // done
    if(this->head== nullptr)   // length==0
        throw std::runtime_error("Cannot pop from an empty list");
        
    if(this->head==this->tail){ // length == 1
        delete this->tail;
        this->head=this->tail=nullptr;
        return;
    }
    
    // get before last node 
    Node<T> *beforelastNode = this->get_nth_node(this->length-2);
    
    delete this->tail ;
    this->tail = beforelastNode;
    beforelastNode->next = nullptr ;
    
    this->length--;

}

template <class T>
void SinglyLinkedList<T>::removeAtHead(){ // done
    if(this->head== nullptr)   // length==0
        throw std::runtime_error("Cannot pop from an empty list");
        

    if(this->head==this->tail){ // length == 1
        delete this->head;
        this->head=this->tail=nullptr;
        return;
    }
        
    Node<T> *temp = head;
    head = head->next;
    delete temp;
    
    this->length--;

}

template<class T>
void SinglyLinkedList<T>::print() const{ //  done
    
    if(!head) return ;
    
    for(Node<T> *node = this->head ; node ; node = node->next )
        cout << node->data << ' ';
        
    cout << '\n';
}

template<class T>
int SinglyLinkedList<T>::size() const{ // done
    return this->length;
}

template<class T>
void SinglyLinkedList<T>::clear(){ // done
    Node<T> *temp = head;
    while(head){
        head = head->next;
        delete temp;
        temp = head;
    }
    this->head = this-> tail = nullptr ;
    length=0;
}

template<class T>
bool SinglyLinkedList<T>::empty() const{ // done
    return !head; // length==0
}

template<class T>
void SinglyLinkedList<T>::removeAt(int idx) { // o(n)
    if(idx==0){ this->removeAtHead(); return ;} // o(1)
    if(idx==length-1){this->removeAtTail(); return ;} // o(n)
    
    // o(n)

    Node<T> *prev = get_nth_node(idx-1); // throw index out of range if so
    Node<T> *toBeDeleted = prev->next ;

    prev->next = toBeDeleted->next;

    delete toBeDeleted;
    length--;
}

template<class T>
void SinglyLinkedList<T>::erase_next_node(Node<T> *prev) { // o(1)
    if(prev==nullptr){ this->removeAtHead(); return ;} // o(1)
    if(prev==tail) throw out_of_range("Index out of range");
    
    Node<T> *toBeDeleted = prev->next ;

    if(toBeDeleted == tail) {
        delete this->tail;
        this->tail = prev;
        prev->next = nullptr;
    } 
    else {
        prev->next = toBeDeleted->next;
        delete toBeDeleted;
    }

    this->length--;
}

template<class T>
void SinglyLinkedList<T>::insert_at(T val, int index) { // done
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
void SinglyLinkedList<T>::reverse() { // done
    if(length==0 || length==1)return;
    
    Node<T>* prev = nullptr;
    Node<T>* current = head;
    Node<T>* next = nullptr;

    while (current) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }

    std::swap(head,tail);
}

template<class T>
void SinglyLinkedList<T>::make_unique() { // time : o(nlogn).  space : o(n)
    if(length==0 || length==1)return;
    
    map<T,bool> occurred ;
    Node<T> *prev = nullptr ;
    Node<T> *node = head  ;
    
    while(node){
        if(occurred[node->data]){
            node = node->next; // increment before deletion, dont increment prev
            erase_next_node(prev);
        }
        else{         
            occurred[node->data]=1;
            prev = node ;
            node = node->next;
        }
    }
}

// o(n)
template<class T>
bool SinglyLinkedList<T>::isExist(T val) { 
    Node<T> *node = head;
    while(node){
        if(node->data==val) return true;
        node = node->next;
    }
    return false;
}

template<class T>
bool SinglyLinkedList<T>::isItemAtEqual(T val, int idx) { 
    return this->operator[](idx) == val;
}

template<class T>
T SinglyLinkedList<T>::retrieveAt(int idx) { 
    return this->operator[](idx);
}

template<class T>
void SinglyLinkedList<T>::replaceAt(T val, int idx) { 
    this->operator[](idx) = val;
    return;
}

template<class T>
void SinglyLinkedList<T>::swap(int idx1, int idx2) { 
    if(idx1<0 || idx1>=length) throw out_of_range("Index out of range");
    if(idx2<0 || idx2>=length) throw out_of_range("Index out of range");
    
    if(idx1==idx2) return ;
    if(idx1>idx2) std::swap(idx1,idx2);

    Node<T> *node1prev = nullptr, *node1 = head; 
    Node<T> *node2prev = nullptr, *node2 = head;

    for (int i = 0 ; ; i++){
        if (node1 && i < idx1){
            node1prev = node1;
            node1 = node1->next;
        }
        if (node2 && i < idx2){
            node2prev = node2;
            node2 = node2->next;
        }
        else break;
    }
    
    if (node1==head) head = node2;
    else node1prev->next = node2; 
    node2prev->next = node1;

    // if consecutive node 1 = node2prev
    if(node2==tail) tail = node1;
    std::swap(node1->next , node2->next );

}

//*********************************************************************************************
// iterator
//*********************************************************************************************

template<class T>
bool SinglyLinkedList<T>::Iterator::operator==(const Iterator& other) const{
    return this->current==other.current;    
    // compares if they have the same memory address
}

template<class T>
bool SinglyLinkedList<T>::Iterator::operator==(const ConstIterator& other) const{
    return this->current==other.current;    
    // compares if they have the same memory address
}

template<class T>
bool SinglyLinkedList<T>::Iterator::operator!=(const Iterator& other) const{
    return this->current!=other.current;
   // !(*this==other) leverage the overloaded ==
}

template<class T>
bool SinglyLinkedList<T>::Iterator::operator!=(const ConstIterator& other) const{
    return this->current!=other.current;
   // !(*this==other) leverage the overloaded ==
}

template<class T>
T& SinglyLinkedList<T>::Iterator::operator*() { // done
    return this->current->data;
}

template <class T>
class SinglyLinkedList<T>::Iterator& SinglyLinkedList<T>::Iterator::operator++() { // done
    if( current) this->current = this->current->next;
    return *this;
}
template <class T>
class SinglyLinkedList<T>::Iterator& SinglyLinkedList<T>::Iterator::operator++(int) { // done
    if( current) this->current = this->current->next;
    return *this;
}

//*********************************************************************************************
// const_iterator
//*********************************************************************************************

template<class T>
bool SinglyLinkedList<T>::ConstIterator::operator==(const ConstIterator& other) const{
    return this->current==other.current;    
    // compares if they have the same memory address
}

template<class T>
bool SinglyLinkedList<T>::ConstIterator::operator==(const Iterator& other) const{
    return this->current==other.current;    
    // compares if they have the same memory address
}

template<class T>
bool SinglyLinkedList<T>::ConstIterator::operator!=(const ConstIterator& other) const{
    return this->current!=other.current;
    // !(*this==other) leverage the overloaded ==
}

template<class T>
bool SinglyLinkedList<T>::ConstIterator::operator!=(const Iterator& other) const{
    return this->current!=other.current;
    // !(*this==other) leverage the overloaded ==
}

template<class T>
const T& SinglyLinkedList<T>::ConstIterator::operator*() const { // done
    return this->current->data;
}

template <class T>
class SinglyLinkedList<T>::ConstIterator& SinglyLinkedList<T>::ConstIterator::operator++() { // done
    
    if( current) this->current = this->current->next;
    return *this;
}
template <class T>
class SinglyLinkedList<T>::ConstIterator& SinglyLinkedList<T>::ConstIterator::operator++(int) { // done
    if( current) this->current = this->current->next;
    return *this;
}

