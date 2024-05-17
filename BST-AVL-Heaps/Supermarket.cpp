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

class aVL
{
    // Omar Saleh code
};

class heap
{
    // AbdulRahman code;
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

void BSTMenu(binarySearchTree<item, item::LessThanName> &bstByName, binarySearchTree<item, item::LessThanPrice> &bstByPrice)
{
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
            bstByName.inOrder(bstByName.root);
            break;
        case 5:
            bstByName.descendingTraverse(bstByName.root);
            break;
        case 6:
            bstByPrice.inOrder(bstByPrice.root);
            break;
        case 7:
            bstByPrice.descendingTraverse(bstByPrice.root);
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
    // Abdulrahman
}

void AVLTreeMenu()
{
    // omarsaleh
}

int main()
{
    binarySearchTree<item, item::LessThanName> bstByName;
    binarySearchTree<item, item::LessThanPrice> bstByPrice;

    ifstream inputFile("input.txt");

    if (!inputFile.is_open())
    {
        cout << "Error opening file!" << endl;
        return 1;
    }

    readItems(inputFile, bstByName, bstByPrice);

    inputFile.close();

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
            AVLTreeMenu();
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
