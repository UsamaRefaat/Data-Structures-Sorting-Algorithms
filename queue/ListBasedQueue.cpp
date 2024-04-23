#include <iostream>
using namespace std;

template<class elementType>
class ListQueue {
    template<class T>
    struct Node {
        T data;
        Node* next;
        Node(T data) : data(data), next(nullptr) {}
    };

    Node<elementType>* head;
    Node<elementType>* tail;
    int elementCount;

public:
    ListQueue() : head(nullptr), tail(nullptr), elementCount(0) {}

    void enqueue(elementType data) {
        elementCount++;
        Node<elementType>* item = new Node<elementType>(data);
        if (!head) {
            head = tail = item;
        } else {
            tail->next = item;
            tail = item;
        }
    }

    bool isEmpty() {
        return head == nullptr;
    }

    elementType dequeue() {
        if (!isEmpty()) {
            elementCount--;
            Node<elementType>* temp = head;
            elementType d = temp->data;
            head = head->next;
            delete temp;
            return d;
        } else {
            return -1;
        }
    }

    elementType first() {
        if (!isEmpty()) {
            return head->data;
        } else {
            throw logic_error("Queue is empty");
        }
    }

    void print() {
        for (Node<elementType>* i = head; i; i = i->next) {
            cout << i->data << ' ';
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

    int queueSize() {
        return elementCount;
    }

    ~ListQueue() {
        clear();
    }
};

int main() {
    ListQueue<int> queue;
    
    // Example usage of functions
    queue.enqueue(1);
    queue.enqueue(2);
    queue.enqueue(3);

    cout << "Queue size: " << queue.queueSize() << endl;  // Output: Queue size: 3

    queue.print();  // Output: 1 2 3

    queue.dequeue();

    cout << "First element after dequeue: " << queue.first() << endl;  // Output: First element after dequeue: 2

    queue.print();  // Output: 2 3

    cout << "Is queue empty? " << (queue.isEmpty() ? "Yes" : "No") << endl;  // Output: Is queue empty? No

    queue.clear();
    cout << "Queue size after clear: " << queue.queueSize() << endl;  // Output: Queue size after clear: 0

    cout << "Is queue empty after clear? " << (queue.isEmpty() ? "Yes" : "No") << endl;  // Output: Is queue empty after clear? Yes

    return 0;
}
