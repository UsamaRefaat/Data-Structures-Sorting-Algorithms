#include<iostream>
#include"SLinkedList.hpp"
#include"SLinkedList.cpp"
 
using namespace std;

#define RESET   "\033[0m"
#define RED     "\033[31m" 

int main () {
 
    SinglyLinkedList list = {2,3,5,6,7};
    
    cout << RED << "\nTesting insertion + Replace + Print\n" << RESET;
    list.insert_at(4,2); // 2 3 4 5 6 7
    
    list.insertAtHead(1); //   1 2 3 4 5 6 7
    list.insertAtHead(0); // 0 1 2 3 4 5 6 7

    list.insertAtTail(8); // 0 1 2 3 4 5 6 7 8
    list.insertAtTail(9); // 0 1 2 3 4 5 6 7 8 9

    list.replaceAt(999,9); // 0 1 2 3 4 5 6 7 8 999

    cout << "Expected output : 0 1 2 3 4 5 6 7 8 999\n";
    cout << "Actual output :   ";
    list.print(); 



    cout << RED << "\nTesting removal + retrieve + size\n" << RESET;
    // list = 0 1 2 3 4 5 6 7 8 999
    
    list.removeAt(9);    // 0 1 2 3 4 5 6 7 8
    list.removeAt(3);    // 0 1 2 4 5 6 7 8
    list.removeAtHead(); //   1 2 4 5 6 7 8
    list.removeAtTail(); //   1 2 4 5 6 7
    
    cout << "Expected output : 1 2 4 5 6 7\n";
    cout << "Actual output :   ";
    for(int i=0 ; i<list.size() ; i++)
        cout << list.retrieveAt(i) << ' ';
    cout << '\n';




    // list = 1 2 4 5 6 7
    cout << RED << "\nlist = " ; 
    for(int i=0 ; i<list.size() ; i++)
        cout << list.retrieveAt(i) << ' ';
    cout << RESET << '\n';
    cout << "Is the item with index 0 = 1? " << (list.isItemAtEqual(1,0)? "YES" : "NO") << '\n';
    cout << "Is the item with index 1 = 5? " << (list.isItemAtEqual(1,5)? "YES" : "NO") << '\n';
    cout << "Does the value 100 exist in the list? " << (list.isExist(100)? "YES" : "NO") << '\n';
    cout << "Does the value 7 exist in the list? " << (list.isExist(7)? "YES" : "NO") << '\n';



    
    // list = 1 2 4 5 6 7
    cout << RED << "\nTesting swap\n" << RESET;
    list.swap(0,5) ; // 7 2 4 5 6 1
    list.swap(4,5); //  7 2 4 5 1 6
    list.swap(2,3); //  7 2 5 4 1 6
    cout << "Expected output : 7 2 5 4 1 6\n";
    cout << "Actual output :   ";
    list.print(); 



    // clear list 
    cout << RED << "\nTesting Clear + Empty + Size\n" << RESET;
    list.clear();
    cout << "IS the list empty? " << (list.empty()? "YES" : "NO") << '\n';
    cout << "What is the size of the list? " << list.size() << '\n';
    cout << "List = " ;  list.print();


    return 0 ;
}



