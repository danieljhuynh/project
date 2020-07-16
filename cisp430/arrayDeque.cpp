// Daniel Huynh
#include <iostream>  // for cout
#include <string>    // for string
#include <string.h>  // for strstr
#include <assert.h>  // for assert

using namespace std;

// global
int DefaultListSize = 5;
enum choice { CLEAR = 0, PUSHFRONT = 1, POPFRONT = 2, PUSHREAR = 3, POPREAR = 4, GETFRONT = 5, GETREAR = 6, GETSIZE = 7, PRINTALL = 8, QUIT = 9 };

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

int main() {
  ADEQueue<int> arrayQueue;
  bool quit = false;
  
  do {
    int instruction;
    choice instr;
    
    int element;
    cout << "Which instruction would you like to do?\n"
            "\t(0) Clear (1) PushFront (2) PopFront (3) PushRear (4) PopRear\n"
            "\t(5) GetFront (6) GetRear (7) GetSize (8) PrintAll (9) Quit: ";
    cin >> instruction;
    instr = static_cast<choice>(instruction);

    switch(instr) {
      case CLEAR:
        cout << "Cleared the queue\n";
        arrayQueue.clear();
        break;
      case PUSHFRONT:
        cout << "What number do you want to push to the front? ";
        cin >> element;  
        arrayQueue.pushFront(element);
        break;
      case POPFRONT:
        cout << "Popping from front: " << arrayQueue.popFront() << endl;
        break;
      case PUSHREAR:
        cout << "What number do you want to push to the rear? ";
        cin >> element;  
        arrayQueue.pushRear(element);
        break;
      case POPREAR:
        cout << "Popping from rear: " << arrayQueue.popRear() << endl;
        break;
      case GETFRONT:
        cout << "Front Value: " << arrayQueue.frontValue() << endl;
        break;
      case GETREAR:
        cout << "Rear Value: " << arrayQueue.rearValue() << endl;
        break;
      case GETSIZE:
        cout << "Size: " << arrayQueue.length() << endl;
        break;
      case PRINTALL:
        arrayQueue.printAll();
        cout << endl;
        break;
      case QUIT:
      default:
        quit = true;
        break;
    }
    if(quit) { cout << "Bye!" << endl; }
  } while(!quit);
  
  return 0;
}