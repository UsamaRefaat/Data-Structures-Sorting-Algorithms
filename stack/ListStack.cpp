
#include <iostream>
using namespace std;

template<class elementType>
class ListStack {
    template<class T>
    struct Node {
        T data;
        Node* next;
        Node(T data) : data(data), next(nullptr) {}
    };

    Node<elementType>* head;
    int elementCount;

public:
    ListStack() : head(nullptr), elementCount(0) {}

    void push(elementType value) {
        Node<elementType>* item = new Node<elementType>(value);
        item->next = head;
        head = item;
        elementCount++;
    }

    bool isEmpty() {
        return head == nullptr;
    }

    elementType pop() {
        if (!isEmpty()) {
            elementCount--;
            Node<elementType>* temp = head;
            head = head->next;
            elementType t = temp->data;
            delete temp;
            return t;
        } else {
            return -1;
        }
    }

    elementType top() {
        if (!isEmpty()) {
            return head->data;
        } else {
				return -1;
        }
    }

    void print() {
        Node<elementType>* temp = head;
        while (temp != nullptr) {
            cout << temp->data << ' ';
            temp = temp->next;
        }
        cout << endl;
    }

    void clear() {
        while (!isEmpty()) {
            Node<elementType>* temp = head;
            head = head->next;
            delete temp;
        }
        elementCount = 0;
    }
		
		int stackSize() {return elementCount;}

    ~ListStack() {
        clear();
    }
};

int main() {
    ListStack<int> stack;
    stack.push(1);
    stack.push(2);
    stack.push(3);
    stack.print();  // Output: 3 2 1

    stack.pop();
    stack.print();  // Output: 2 1

    cout << "Top element: " << stack.top() << endl;  // Output: Top element: 2
		cout << "The stack size is " << stack.stackSize() << endl;
    stack.clear();
    stack.print();  // Output: (empty line)

    return 0;
}


