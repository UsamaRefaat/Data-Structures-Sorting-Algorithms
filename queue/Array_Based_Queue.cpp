#include <bits/stdc++.h>

using namespace std;

template <class elementType>
class ArrayBasedQueue {
	int first;
	int size;
	int last;
	elementType *arr; 
	int elementCount;
public:
	
	ArrayBasedQueue(int size) : size(size) {
		first = last = -1;
		arr = new elementType[size];
		elementCount = 0;  
	}	
	
	~ArrayBasedQueue() {
		delete[] arr;
	}

	
	bool full() {
		return (first == 0 && last == size - 1) || (last == first - 1);  
	}

	bool isEmpty() {
		return first == -1;
	}


	void enqueue(elementType element) {
		if (!full()) {
			elementCount++;
			if (last == -1 || last == size - 1) {
				last =0;
				arr[last] = element;
				if (first == -1) first++;
			} else {
				arr[++last] = element;
			}
		} else  cout << "Queue is full" << endl;
	}


	elementType dequeue() {
			if (!isEmpty()) {
		elementCount--;
		int temp = first;
		if (first == last) {first = last - 1;}
		else if (first == size - 1) {first = 0;} else {first++;}

		return arr[temp]; }
			else return -1;
	}
		

    elementType front() {
		return arr[first];
	}	


	int queueSize () {
		return elementCount;
	}

	void print() {
		if (isEmpty()) {cout << "Queue is empty" << endl;}
		else {
				int i;
				cout << "Front: " << arr[first] << endl << "Elements: ";

				for ( i = first; i != last; i = ( i + 1) % size) cout << arr[i];
				cout << arr[i] << endl;
		}
	}

	void clear() {
			elementCount = 0;	
			first = last = -1;

	}
	
};int main () {
ArrayBasedQueue<int> Q(5); 

Q.enqueue(1); Q.enqueue(2); Q.enqueue(3); Q.enqueue(4); Q.enqueue(5); 

cout << "Dequeued Element: " << Q.dequeue() << endl; 

cout << "The front is now: " << Q.front() << endl;

cout << "The size of the Queue is: " << Q.queueSize() << endl;
if (!Q.isEmpty()) 
		cout << "The Queue is not empty now " << endl;
Q.print(); 

Q.clear();

}
