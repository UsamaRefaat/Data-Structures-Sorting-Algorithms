#ifndef BST_H
#define BST_H
#include <iostream>
#include <string>
using namespace std ;

template <typename T, typename Compare>
class binarySearchTree
{
public:
    class node
    {
    public:
        T data;
        node *left, *right;
        node(T item) : data(item), left(NULL), right(NULL) {}
    };

    node *root;
    Compare compare;

    binarySearchTree() : root(NULL), compare(Compare()) {}
    ~binarySearchTree() {this->clear(this->root);}

    void clear(node * root){
        if(!root) return ;
        clear(root->left);
        clear(root->right);
        delete root ; 
    }


    bool isNull(node *tRoot) const
    {
        return (tRoot == NULL);
    }

    node *insert(node *rNode, T item)
    {
        if (isNull(rNode))
        {
            rNode = new node(item);
        }
        else if (compare(item, rNode->data))
        {
            rNode->left = insert(rNode->left, item);
        }
        else
        {
            rNode->right = insert(rNode->right, item);
        }
        return rNode;
    }

    void insert(T item)
    {
        root = insert(root, item);
    }

    void preOrder(node *rNode) const
    {
        if (!rNode)
            return;
        rNode->data.print();
        preOrder(rNode->left);
        preOrder(rNode->right);
    }

    void inOrder(node *rNode) const
    {
        if (isNull(rNode))
        {
            return;
        }
        inOrder(rNode->left);
        rNode->data.print();
        inOrder(rNode->right);
    }

    void descendingTraverse(node *rNode) const
    {
        if (isNull(rNode))
        {
            return;
        }
        descendingTraverse(rNode->right);
        rNode->data.print();
        descendingTraverse(rNode->left);
    }

    node *findMin(node *rNode)
    {
        if (isNull(rNode))
        {
            return NULL;
        }
        else if (isNull(rNode->left))
        {
            return rNode;
        }
        else
        {
            return findMin(rNode->left);
        }
    }

    node *findMax(node *rNode)
    {
        if (isNull(rNode))
        {
            return NULL;
        }
        else if (isNull(rNode->right))
        {
            return rNode;
        }
        else
        {
            return findMax(rNode->right);
        }
    }
    bool search(node *rNode, const T &key)
    {
        if (isNull(rNode))
        {
            return false;
        }
        if (compare(key, rNode->data))
        {
            return search(rNode->left, key);
        }
        else if (compare(rNode->data, key))
        {
            return search(rNode->right, key);
        }
        else
        {
            return true;
        }
    }

    bool search(const T &key)
    {
        return search(root, key);
    }
    node *Delete(node *rNode, const T &key)
    {
        if (isNull(rNode))
        {
            return NULL;
        }
        if (compare(key, rNode->data))
        {
            rNode->left = Delete(rNode->left, key);
        }
        else if (compare(rNode->data, key))
        {
            rNode->right = Delete(rNode->right, key);
        }
        else
        {
            if (rNode->left == NULL && rNode->right == NULL) // leaf
            {
                delete rNode;
                rNode = NULL;
            }
            else if (rNode->left != NULL && rNode->right == NULL) // only left child
            {
                node *temp = rNode;
                rNode = rNode->left;
                delete temp;
            }
            else if (rNode->left == NULL && rNode->right != NULL) // only right child
            {
                node *temp = rNode;
                rNode = rNode->right;
                delete temp;
            }
            else // two children, find predecessor
            {
                node *maxLeft = findMax(rNode->left);
                rNode->data = maxLeft->data;
                rNode->left = Delete(rNode->left, maxLeft->data);
            }
        }
        return rNode;
    }

    void Delete(const T &key)
    {
        if (search(key))
        {
            root = Delete(root, key);
        }
        else
        {
            cout << "Item does not exist." << endl;
        }
    }
};




#endif
