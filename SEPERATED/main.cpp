#include<iostream>
#include<initializer_list>
#include<vector>
#include<deque>
#include <fstream>
#include"AVL.h"
#include"BST.h"
#include"items.h"

using namespace std ;

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
            // HeapMenu();
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