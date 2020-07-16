// Daniel Huynh
// Reverse Stack
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
  virtual void clear() = 0;
  virtual void push(const Elem&) = 0;
  virtual Elem pop() = 0;
  virtual const Elem& topValue() const = 0;
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
};

int main() {
  AStack<char> arrayStack;
  string str;
  cout << "Enter a string: ";
  cin >> str;
  cout << "Input string: " << str << endl;
  
  for (unsigned int i = 0; i < str.size(); i++) {
    arrayStack.push(str[i]);          
  }
  cout << "Output string in reverse order: ";
  for (unsigned int i = 0; i < str.size(); i++) {
    cout << arrayStack.topValue();
    arrayStack.pop();
  }
  cout << endl;
  return 0;
}
