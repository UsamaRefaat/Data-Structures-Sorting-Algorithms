#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <deque>
#include <set>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <iterator>
#include <cmath>
#include <fstream>

using namespace std;

#define ll long long
#define bn endl
#define fast ios::sync_with_stdio(false), cout.tie(0), cin.tie(0);

class item
{
public:
    string itemName;
    string category;
    int price;

    item(string name, string cat, int p) : itemName(name), category(cat), price(p) {}

    struct LessThanName
    {
        bool operator()(const item &a, const item &b) const
        {
            return a.itemName < b.itemName;
        }
    };

    struct LessThanPrice
    {
        bool operator()(const item &a, const item &b) const
        {
            return a.price < b.price;
        }
    };

    void print() const
    {
        cout << "Name: " << itemName << ", Category: " << category << ", Price: " << price << bn;
    }
};

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

class heap
{
    // AbdulRahman , MoAli code;
};

void readItems(istream &input,
               binarySearchTree<item, item::LessThanName> &bstByName,
               binarySearchTree<item, item::LessThanPrice> &bstByPrice)
{
    int numItems;
    input >> numItems;
    input.ignore();
    for (int i = 0; i < numItems; ++i)
    {
        string name, category;
        int price;
        getline(input, name);
        getline(input, category);
        input >> price;
        input.ignore();
        item newItem(name, category, price);
        bstByName.insert(newItem);
        bstByPrice.insert(newItem);
    }
}

void readItems(istream &input,
               AVLTree<item, item::LessThanName> &AVLByName,
               AVLTree<item, item::LessThanPrice> &AVLByPrice)
{
    int numItems;
    input >> numItems;
    input.ignore();
    for (int i = 0; i < numItems; ++i){
        string name, category;
        int price;
        getline(input, name);
        getline(input, category);
        input >> price;
        input.ignore();
        item newItem(name, category, price);
        AVLByName.insert(newItem);
        AVLByPrice.insert(newItem);
    }
}

void displayMainMenu()
{
    cout << "Welcome to the Tree Data Structures Program" << endl;
    cout << "Choose which non-linear structure to use:" << endl;
    cout << "1. Binary Search Trees (BST)" << endl;
    cout << "2. Heaps" << endl;
    cout << "3. AVL Trees" << endl;
    cout << "4. Exit" << endl;
    cout << "Enter your choice: ";
}

binarySearchTree<item, item::LessThanName> bstByName;
binarySearchTree<item, item::LessThanPrice> bstByPrice;
void BSTMenu(binarySearchTree<item, item::LessThanName> &bstByName, binarySearchTree<item, item::LessThanPrice> &bstByPrice)
{
    
    ifstream inputFile("input.txt");

    if (!inputFile.is_open())
    {
        cout << "Error opening file!" << endl;
        return ;
    }

    readItems(inputFile, bstByName, bstByPrice);

    inputFile.close();
    int choice;
    do
    {
        cout << "\nBinary Search Trees (BST) Mini-Menu" << endl;
        cout << "1. Add item data" << endl;
        cout << "2. Remove item data" << endl;
        cout << "3. Display the item data normally" << endl;
        cout << "4. Display all the items sorted by their name ascending" << endl;
        cout << "5. Display all the items sorted by their name descending" << endl;
        cout << "6. Display all the items sorted by their prices ascending" << endl;
        cout << "7. Display all the items sorted by their prices descending" << endl;
        cout << "8. Back to Main Menu" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        string itemName, category;
        int price;
        switch (choice)
        {
        case 1:
            cout << "Enter item name: ";
            cin.ignore();
            getline(cin, itemName);
            cout << "Enter category: ";
            getline(cin, category);
            cout << "Enter price: ";
            cin >> price;
            bstByName.insert(item(itemName, category, price));
            bstByPrice.insert(item(itemName, category, price));
            break;
        case 2:
            cout << "Enter item name: ";
            cin.ignore();
            getline(cin, itemName);
            cout << "Enter category: ";
            getline(cin, category);
            cout << "Enter price: ";
            cin >> price;
            if (bstByName.search(item(itemName, category, price)) && bstByPrice.search(item(itemName, category, price)))
            {
                bstByName.Delete(item(itemName, category, price));
                bstByPrice.Delete(item(itemName, category, price));
            }
            else
            {
                cout << "Wrong input data !!" << endl;
            }

            break;
        case 3:
            bstByName.preOrder(bstByName.root); 
            break;
        case 4:
            bstByName.inOrder(bstByName.root); // name ascending
            break;
        case 5:
            bstByName.descendingTraverse(bstByName.root); // name desc
            break;
        case 6:
            bstByPrice.inOrder(bstByPrice.root); // price asc
            break;
        case 7:
            bstByPrice.descendingTraverse(bstByPrice.root); // price desc
            break;
        case 8:
            return;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (true);
}

void HeapMenu()
{
    // Abdulrahman , MoAli
}


AVLTree<item, item::LessThanName> AVLByName;
AVLTree<item, item::LessThanPrice> AVLByPrice;
void AVLTreeMenu(AVLTree<item, item::LessThanName> &AVLByName, AVLTree<item, item::LessThanPrice> &AVLByPrice)
{
    ifstream inputFile("input.txt");

    if (!inputFile.is_open())
    {
        cout << "Error opening file!" << endl;
        return ;
    }

    readItems(inputFile, AVLByName, AVLByPrice);

    inputFile.close();
    int choice;
    do
    {
        cout << "\nAVLTree Mini-Menu" << endl;
        cout << "1. Add item data" << endl;
        cout << "2. Remove item data" << endl;
        cout << "3. Display the item data normally" << endl;
        cout << "4. Display all the items sorted by their name ascending" << endl;
        cout << "5. Display all the items sorted by their name descending" << endl;
        cout << "6. Display all the items sorted by their prices ascending" << endl;
        cout << "7. Display all the items sorted by their prices descending" << endl;
        cout << "8. Back to Main Menu" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        string itemName, category;
        int price;
        switch (choice)
        {
        case 1:
            cout << "Enter item name: ";
            cin.ignore();
            getline(cin, itemName);
            cout << "Enter category: ";
            getline(cin, category);
            cout << "Enter price: ";
            cin >> price;
            AVLByName.insert(item(itemName, category, price));
            AVLByPrice.insert(item(itemName, category, price));
            break;
        case 2:
            cout << "Enter item name: ";
            cin.ignore();
            getline(cin, itemName);
            cout << "Enter category: ";
            getline(cin, category);
            cout << "Enter price: ";
            cin >> price;
            if (AVLByName.isExists(item(itemName, category, price)) && AVLByPrice.isExists(item(itemName, category, price)))
            {
                AVLByName.deleteNode(item(itemName, category, price));
                AVLByPrice.deleteNode(item(itemName, category, price));
            }
            else
            {
                cout << "Wrong input data !!" << endl;
            }

            break;
        case 3:
            AVLByName.printPreOrder(); 
            break;
        case 4:
            AVLByName.printInOrder(); // name ascending
            break;
        case 5:
            AVLByName.printDesc(); // name desc
            break;
        case 6:
            AVLByPrice.printInOrder(); // price asc
            break;
        case 7:
            AVLByPrice.printDesc(); // price desc
            break;
        case 8:
            return;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (true);
}

int main()
{
    int choice;
    bool exitProgram = false;

    while (!exitProgram)
    {
        displayMainMenu();
        cin >> choice;

        switch (choice)
        {
        case 1: // Binary Search Trees (BST)
            BSTMenu(bstByName, bstByPrice);
            break;
        case 2: // Heaps
            HeapMenu();
            break;
        case 3: // AVL Trees
            AVLTreeMenu(AVLByName, AVLByPrice);
            break;
        case 4:
            exitProgram = true;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
            break;
        }
    }

    cout << "Exiting program..." << endl;

    return 0;
}
