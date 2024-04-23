
#include <iostream>
using namespace std;

template <class elementType>
class ArrayStack {
    int size;
    int top;
    elementType *arr;
    int elementCount;

public:
    ArrayStack(int size) : size(size), top(-1), elementCount(0) {
        arr = new elementType[size];
    }

    ~ArrayStack() {
        delete[] arr;
    }

    bool isEmpty() {
        return top == -1;
    }

    bool full() {
        return top == size - 1;
    }

    void push(elementType element) {
        if (full())
            cout << "Stack is full" << endl;
        else {
            elementCount++;
            arr[++top] = element;
        }
    }

    elementType pop() {
        if (!isEmpty()) {
            elementCount--;
            return arr[top--];
        } else {
            return -1;
        }
    }

    elementType Top() {
        if (!isEmpty())
            return arr[top];
        else
            return -1;
    }

    int stackSize() {
        return elementCount;
    }

    void clear() {
        elementCount = 0;
        top = -1;
    }

    void print() {
        if (isEmpty())
            return;

        for (int i = top; i >= 0; i--)
            cout << arr[i] << ' ';
        cout << endl;
    }
};

int main() {
    ArrayStack<int> S(5);
    S.push(1);
    S.push(2);
    S.push(3);
    S.push(4);
    S.push(5);

    cout << "The first element to get removed is: " << S.pop() << endl;

    cout << "Now the top element is: " << S.Top() << endl;

    if (!S.isEmpty())
        cout << "The Stack is not empty yet." << endl;

    cout << "The stack size is now " << S.stackSize() << endl;

    cout << "Now we print the stack: " << endl;
    S.print();

    S.clear();

    return 0;
}
