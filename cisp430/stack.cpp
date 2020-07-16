// Stack abtract class
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
};

int main() {
  AStack<char> arrayStack;
  string str;
  string arraypush = "[({";
  string arraypop = "])}";
  cout << "String input : ";
  cin >> str;
  for (unsigned int i = 0; i < str.size(); i++) {             // checking each character of input string
    if(arraypush.find(str[i]) != std::string::npos) {         // check to see if we need to be pushing [, (, or {
      cout << "Pushing " << str[i] << endl;
      arrayStack.push(str[i]);                                // pushing to stack
    } else if(arraypop.find(str[i]) != std::string::npos) {   // check to see if we need to be popping ], ), or }
      cout << "Popping: " << str[i] << endl;
      if(str[i] == ')') {                                     // if the current character is )
        if ((int(arrayStack.topValue())+1) != int(str[i])) {  // if ( not matching )
          cout << "Previous value is " << arrayStack.topValue() <<" however you're trying to pop " << str[i] << endl;
          cout << "No matching closing for ()" << endl;
          break;
        }
      } else {
        if ((int(arrayStack.topValue())+2) != int(str[i])) {  // if [ not matching ] or if { not matching }
          cout << "Previous value is " << arrayStack.topValue() <<" however you're trying to pop " << str[i] << endl;
          cout << "No matching closing for either [] or {}" << endl;
          break;
        }
      }
      arrayStack.pop();                                       // popping from stack
    } else {
      cout << "Error found" << endl;
    }
  }
  if(arrayStack.length() != 0) {                              // if stack is empty
    cout << "False" << endl;
  } else {
    cout << "True" << endl;
  }
  return 0;
}
