// Daniel Huynh
// Queue
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
  
  void pushAll() {
    int element;
    for(int i = 0; i < DefaultListSize; i++) {
      cout << "Enter a value: ";
      cin >> element;
      pushRear(element);
    }
  }
  
  void printAll() {
    assert(length() != 0 && "Queue is empty");
    cout << "Front Index: " << front << " Rear Index: " << rear << " Max Index: " << maxSize << endl;
    for(int i = front; i != (rear+1); i++) {
      if (i >= maxSize) {
        i = (i - maxSize);
      }
      cout << "Index: " << i << " Value: " << listArray[i] << endl;
    }
  }
  
  void getOddEvenCount() {
    int odd, even;
    odd = even = 0;
    assert(length() != 0 && "Queue is empty");
    for(int i = front; i != (rear+1); i++) {
      if (i >= maxSize) {
        i = (i - maxSize);
      }
      if (listArray[i] % 2 == 0) {
        even++;
      } else {
        odd++;
      }
    }
    cout << "Total odd: " << odd << endl;
    cout << "Total even: " << even << endl;
  }
};

int main() {
  cout << "Input the number of elements: ";
  cin >> DefaultListSize;
  cout << "Size is: " << DefaultListSize << endl;
  ADEQueue<int> arrayQueue(DefaultListSize);
  arrayQueue.pushAll();
  arrayQueue.printAll();
  arrayQueue.getOddEvenCount();
  return 0;
}