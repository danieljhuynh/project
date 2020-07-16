// Daniel Huynh
// stackQueue.cpp
#include <iostream>  // for cout
#include <string>    // for string
#include <string.h>  // for strstr
#include <assert.h>  // for assert

using namespace std;

// global
int DefaultListSize = 5;

// Abstract DEqueue class
template <typename Elem> class DEqueue {
private:
  void operator =(const DEqueue&) {} // Protect assignment
  DEqueue(const DEqueue&) {} // Protect copy constructor
public:
  DEqueue() {} // Default
  virtual ~DEqueue() {} // Base destructor
  // Reinitialize the DEqueue. The user is responsible for
  // reclaiming the storage used by the DEqueue elements.
  virtual void clear() = 0;
  // Place an element at the rear of the DEqueue.
  virtual void pushRear(const Elem&) = 0;
  // Place an element at the front of the DEqueue.
  virtual void pushFront(const Elem&) = 0;
  // Remove and return element at the front of the DEqueue.
  virtual Elem popFront() = 0;
  // Remove and return element at the rear of the DEqueue.
  virtual Elem popRear() = 0;
  // Return a copy of the front element.
  virtual const Elem& frontValue() const = 0;
  // Return a copy of the rear element.
  virtual const Elem& rearValue() const = 0;
  // Return the number of elements in the DEqueue.
  virtual int length() const = 0;
};

// Array-based DEqueue implementation
template <typename Elem> class ADEQueue: public DEqueue<Elem> {
private:
  int maxSize; // Maximum size of queue
  int front; // Index of front element
  int rear; // Index of rear element
  Elem *listArray; // Array holding queue elements
public:
  ADEQueue(int size = DefaultListSize) { // Constructor
    // Make list array one position larger for empty slot
    maxSize = size+1;
    rear = 0; front = 1;
    listArray = new Elem[maxSize];
  }
  ~ADEQueue() { delete [] listArray; listArray = NULL; } // Destructor
  void clear() { rear = 0; front = 1; } // Reinitialize
  void pushRear(const Elem& it) { // Put "it" in queue
    assert(((rear+2) % maxSize) != front && "Queue is full");
    rear = (rear+1) % maxSize; // Circular increment
    listArray[rear] = it;
  }
  void pushFront(const Elem& it) { // Put "it" in queue
    assert(((rear+2) % maxSize) != front && "Queue is full");
    front = (maxSize + front - 1) % maxSize; // Circular increment
    listArray[front] = it;
  }
  Elem popFront() { // Pop front element out
    assert(length() != 0 && "Queue is empty");
    Elem it = listArray[front];
    front = (maxSize + front+1) % maxSize; // Circular increment
    return it;
  }
  Elem popRear() { // Pop rear element out
    assert(length() != 0 && "Queue is empty");
    Elem it = listArray[rear];
    rear = (maxSize + rear-1) % maxSize; // Circular increment
    return it;
  }
  const Elem& frontValue() const { // Get front value
    assert(length() != 0 && "Queue is empty");
    return listArray[front];
  }
  const Elem& rearValue() const { // Get rear value
    assert(length() != 0 && "Queue is empty");
    return listArray[rear];
  }
  virtual int length() const {// Return length
    return ((rear+maxSize) - front + 1) % maxSize; 
  }
  void printAll() {
    assert(length() != 0 && "Queue is empty");
    cout << "Front Index: " << front << " Rear Index: " << rear << " Max Index: " << maxSize << endl;
    cout << "Print from front to rear" << endl;
    for(int i = front; i != (rear+1); i++) {
      if (i >= maxSize) {
        i = (i - maxSize);
      }
      cout << "Index: " << i << " Value: " << listArray[i] << endl;
    }
  }
};


template <typename Elem> class Stack {
private:
  void operator =(const Stack&) {} // Protect assignment
  Stack(const Stack&) {} // Protect copy constructor
public:
  Stack() {} // Default constructor
  virtual ~Stack() {} // Base destructor
  virtual void push(const Elem&) = 0;
  virtual Elem pop() = 0;

};

// Array-based stack implementation
template <typename Elem> class AStack: public Stack<Elem> {
private:
  ADEQueue<int> arrayQueue;
  int maxSize = 0;
  int length = 0;
public:
  AStack(int size = DefaultListSize) { // Constructor
    ADEQueue<int> arrayQueue(size); 
    maxSize = size;
  }
  ~AStack() {} // Destructor
  void push(const Elem& it) { // Put "it" on stack
    assert(length < maxSize && "Stack is full");
    arrayQueue.pushRear(it);
    length++;
  }
  Elem pop() { // Pop top element
    assert(length > 0 && "Stack underflow");
    auto value = arrayQueue.popRear();
    length--;
    return value;
  }
};

int main() {
  bool cont = true;
  int choice;
  int value;
  cout << "Input the number of elements: ";
  cin >> DefaultListSize;
  AStack<int> arrayStack(DefaultListSize);

  while(cont) {
    cout << "Do you want to 1) push, 2) pop, 3) exit: ";
    cin >> choice;
    switch(choice) {
      case 1: 
        cout << "\tWhat value do you want to push: ";
        cin >> value;
        arrayStack.push(value);
        break;
      case 2:
        cout << "Popping ";
        value = arrayStack.pop();
        cout << value << endl;
        break;
      case 3:
        cout << "Exiting" << endl;
        cont = false;
        break;
    }
  }
  cout << endl;
  return 0;
}