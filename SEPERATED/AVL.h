#ifndef AVL_H
#define AVL_H

#include <string>
#include <iostream>
using namespace std ;

template <class T, class Compare>
class AVLTree {
private:
    // node
    class Node {
    public:
        T data;
        Node* left{}, *right{};
        int height{};

        Node(T item) : data(item){}
        int get_child_height(Node *node){
            return node? node->height : -1 ;
        }
        void update_height(){
            this->height = 1 + max(get_child_height(this->left),get_child_height(this->right));
        }
        int get_balance_factor(){
            return get_child_height(this->left)-get_child_height(this->right);
        }
    };
    
    Node* root{};
    Compare compare;

    Node* leftRotate(Node* p) {
        Node *q = p->right;
        p->right = q->left ;
        q->left = p ;
        p->update_height();
        q->update_height();
        return q;
    }

    Node* rightRotate(Node* q) {
        Node *p = q->left;
        q->left = p->right ;
        p->right = q ;
        p->update_height();
        q->update_height();
        return p;
    }

    Node* balance(Node *node){ // Balance + return root
        if(node->get_balance_factor()==2){ // Left
            if(node->left->get_balance_factor() == -1) // Left Right 
                node->left = leftRotate(node->left);
            node = rightRotate(node);
        }
        else if(node->get_balance_factor() == -2) { // Right
            if(node->right->get_balance_factor() == 1) //  Right Left 
                node->right = rightRotate(node->right);
            node = leftRotate(node);
        }
        return node ;
    }

    Node* insert(Node* node, T item) {
        if (!node) return new Node(item);
        if ( compare(item, node->data)  )
            node->left = insert(node->left, item);
        else 
            node->right = insert(node->right, item);
    
        node->update_height();
        return balance(node); // returns rooooot
    }

    Node * minNode(Node* node){ 
        Node* current = node; 
        while (current->left ) 
            current = current->left; 
        return current; 
    } 

    Node* deleteNode(Node* node, T x) {  
        if (!node) return nullptr;  
        if ( compare(x, node->data) )  node->left = deleteNode(node->left, x); 
        else if( compare(node->data,x) )  node->right = deleteNode(node->right, x);  
        // found
        else{ 
            if( !node->left && !node->right ) { // 0 child
                delete node;
                return nullptr;
            }
            else if(!node->left != !node->right){ // 1 child
                Node* temp = root->left ? root->left : root->right ;
                delete node;
                return temp;
            } 
            else{ // 2 child
                Node* temp = minNode(node->right); 
                node->data = temp->data; 
                node->right = deleteNode(node->right, temp->data); 
            } 
        } 
        if(node){
            node->update_height();
            node = balance(node);
        }
        return node; 
    } 
    
    
    void clear(Node * root){
        if(!root) return ;
        clear(root->left);
        clear(root->right);
        delete root ; 
    }


    // traverse
    void preOrder(Node *rNode) const{
        if (!rNode) return;
        rNode->data.print();
        preOrder(rNode->left);
        preOrder(rNode->right);
    }

    void inOrder(Node *rNode) const{
        if (!rNode) return; 
        inOrder(rNode->left);
        rNode->data.print();
        inOrder(rNode->right);
    }
    void descendingTraverse(Node *rNode) const{
        if (!rNode) return;
        descendingTraverse(rNode->right);
        rNode->data.print();
        descendingTraverse(rNode->left);
    }

    bool search(Node *rNode, const T &key){
        if (!rNode) return false;
        if (compare(key, rNode->data)) return search(rNode->left, key);
        if (compare(rNode->data, key)) return search(rNode->right, key);
        return true; 
    }



public:
    AVLTree() : compare(Compare()) {};
    ~AVLTree(){this->clear();}

    void insert(T item) {
        root = insert(root, item);
    }

    void clear(){this->clear(root);}
    void printInOrder(){inOrder(this->root);}
    void printPreOrder(){preOrder(this->root);}
    void printDesc(){descendingTraverse(this->root);}
    bool isExists(const T &key){return search(root, key);}
    void deleteNode(T x) {this->deleteNode(root,x);} 
    
    
};

#endif