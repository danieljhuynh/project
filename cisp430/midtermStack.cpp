// Daniel Huynh
// Stack
#include <iostream>  // for cout
#include <string>    // for string
#include <string.h>  // for strstr
#include <assert.h>  // for assert

using namespace std;

// global
int DefaultListSize = 10;

template <typename Elem> class Stack {
private:
  void operator =(const Stack&) {} // Protect assignment
  Stack(const Stack&) {} // Protect copy constructor
public:
  Stack() {} // Default constructor
  virtual ~Stack() {} // Base destructor
  // Reinitialize the stack. The user is responsible for
  // reclaiming the storage used by the stack elements.
  virtual void clear() = 0;
  // Push an element onto the top of the stack.
  virtual void push(const Elem&) = 0;
  // Remove and return the element at the top of the stack.
  virtual Elem pop() = 0;
  // Return a copy of the top element.
  virtual const Elem& topValue() const = 0;
  // Return the number of elements in the stack.
  virtual int length() const = 0;
};

// Array-based stack implementation
template <typename Elem> class AStack: public Stack<Elem> {
private:
  int maxSize; // Maximum size of stack
  int top; // Index for top element
  Elem *listArray; // Array holding stack elements
public:
  AStack(int size = DefaultListSize) // Constructor
    { maxSize = size; top = 0; listArray = new Elem[size]; }
  ~AStack() { delete [] listArray; } // Destructor
  void clear() { top = 0; } // Reinitialize
  void push(const Elem& it) { // Put "it" on stack
    assert(top != maxSize && "Stack is full");
    listArray[top++] = it;
  }
  Elem pop() { // Pop top element
    assert(top != 0 && "Stack is empty");
    return listArray[--top];
  }
  const Elem& topValue() const { // Return top element
    assert(top != 0 && "Stack is empty");
    return listArray[top-1];
  }
  int length() const { return top; } // Return length
  
  void pushAll() { // Push all elements
    Elem element;
    for(int i = 0; i < DefaultListSize; i++) {
      cout << "Enter a value: ";
      cin >> element;
      push(element);
    }
  }
  
  void popAll() { // Pop all elments
    if (length() != 0) {
      cout << pop() << " ";
      popAll();
    }
  }
};

int main() {
  int type;
  cout << "Input the number of elements: ";
  cin >> DefaultListSize;
  cout << "Size is: " << DefaultListSize << endl;
  cout << "Please choose a type (1) int, (2) char, or (3) string): ";
  cin >> type;
  
  if (type == 1) {
    AStack<int> arrayStack(DefaultListSize);
    arrayStack.pushAll();
    arrayStack.popAll();
  } else if (type == 2) {
    AStack<char> arrayStack(DefaultListSize);
    arrayStack.pushAll();
    arrayStack.popAll();
  } else if (type == 3) {
    AStack<string> arrayStack(DefaultListSize);
    arrayStack.pushAll();
    arrayStack.popAll();
  }
  cout << endl;
  return 0;
}
