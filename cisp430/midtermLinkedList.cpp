// Daniel Huynh
// Linked List
#include <iostream>  // for cout
#include <string>    // for string
#include <assert.h>  // for assert

using namespace std;

// global
int DefaultListSize = 5;

template <typename Elem> class List { // List ADT
private:
  void operator =(const List&) {} // Protect assignment
  List(const List&) {} // Protect copy constructor
public:
  List() {} // Default constructor
  virtual ~List() {} // Base destructor
  // Reinitialize the list. The client is responsible for
  // reclaiming the storage used by the list elements.
  virtual void clear() = 0;
  // Insert an element at the front of the right partition.
  // Return true if the insert was successful, false otherwise.
  virtual bool insert(const Elem&) = 0;
  // Append an element at the end of the right partition.
  // Return true if the append was successful, false otherwise.
  virtual bool append(const Elem&) = 0;
  // Remove and return the first element of right partition.
  virtual Elem remove() = 0;
  // Place fence at list start, making left partition empty.
  virtual void movetoStart() = 0;
  // Place fence at list end, making right partition empty.
  virtual void movetoEnd() = 0;
  // Move fence one step left; no change if at beginning.
  virtual void prev() = 0;
  // Move fence one step right; no change if already at end.
  virtual void next() = 0;
  // Return length of left or right partition, respectively.
  virtual int leftLength() const = 0;
  virtual int rightLength() const = 0;
  // Set fence so that left partition has "pos" elements.
  virtual void movetoPos(int pos) = 0;
  // Return the first element of the right partition.
  virtual const Elem& getValue() const = 0;
};

// Singly linked list node
template <typename Elem> class Link {
public:
  Elem element; // Value for this node
  Link *next; // Pointer to next node in list
  // Constructors
  Link(const Elem& elemval, Link* nextval = NULL)
  { element = elemval; next = nextval; }
  Link(Link* nextval =NULL) { next = nextval; }
};

// Linked list implementation
template <typename Elem> class LinkedList: public List<Elem> {
private:
  Link<Elem>* head; // Pointer to list header
  Link<Elem>* tail; // Pointer to last Elem in list
  Link<Elem>* fence; // Last element on left side
  int leftcnt; // Size of left partition
  int rightcnt; // Size of right partition
  
  void init() { // Intialization helper method
    fence = tail = head = new Link<Elem>;
    leftcnt = rightcnt = 0;
  }
  void removeall() { // Return link nodes to free store
    while(head != NULL) {
    fence = head;
    head = head->next;
    delete fence;
    }
  }
  
public:
  LinkedList(int size=DefaultListSize) { init(); } // Constructor
  ~LinkedList() { removeall(); } // Destructor
  void print() const; // Print list contents
  void clear() { removeall(); init(); } // Clear list
  // Insert "it" at front of right partition
  bool insert(const Elem& it) {
    fence->next = new Link<Elem>(it, fence->next);
    if (tail == fence) tail = fence->next; // New tail
    rightcnt++;
    return true;
  }
  bool append(const Elem& it) { // Append "it" to list
    tail = tail->next = new Link<Elem>(it, NULL);
    rightcnt++;
    return true;
  }
  void movetoStart() // Place fence at list start
  { fence = head; rightcnt += leftcnt; leftcnt = 0; }
  void movetoEnd() // Place fence at list end
  { fence = tail; leftcnt += rightcnt; rightcnt = 0; }
  
  // Remove and return first Elem in right partition
  Elem remove() {
    assert(rightLength() > 0 && "Nothing to remove");
    Elem it = fence->next->element; // Remember value
    Link<Elem>* ltemp = fence->next; // Remember link node
    fence->next = ltemp->next; // Remove from list
    if (tail == ltemp) tail = fence; // Reset tail
    delete ltemp; // Reclaim space
    rightcnt--; // Decrement the count
    return it;
  }
  // Move fence one step left; no change if left is empty
  void prev() {
    if (fence == head) return; // No previous Elem
    Link<Elem>* temp = head;
    // March down list until we find the previous element
    while (temp->next!=fence) temp=temp->next;
    fence = temp;
    leftcnt--; rightcnt++; // Set the counts
  }
  // Move fence one step right; no change if right is empty
  void next() {
    if (fence != tail)
    { fence = fence->next; rightcnt--; leftcnt++; }
  }
  int leftLength() const { return leftcnt; }
  int rightLength() const { return rightcnt; }
  // Set the size of left partition to "pos"
  void movetoPos(int pos) {
    assert ((pos>=0)&&(pos<=rightcnt+leftcnt) && "Position out of range");
    rightcnt = rightcnt + leftcnt - pos; // Set counts
    leftcnt = pos;
    fence = head;
    for(int i=0; i<pos; i++) fence = fence->next;
  }
  const Elem& getValue() const { // Return current Elem
    assert(rightLength() > 0 && "Nothing to get");
    return fence->next->element;
  }
};

int printAll(LinkedList<int> *llist, int DefaultListSize) {
  int total = 0;
  llist->movetoPos(0);
  for (int i = 0; i < DefaultListSize; i++) {
    total += llist->getValue();
    llist->next();
  }
  return total;
}

int main() {
  int isFalse = 0;
  int total = 0;
  cout << "Input the number of elements: ";
  cin >> DefaultListSize;
  LinkedList<int> llist(DefaultListSize);
  for(int i =0; i < DefaultListSize; i++) {
    cout << "Enter a number to insert to the list: ";
    cin >> isFalse;
    llist.append(isFalse);
  }
  cout << "Done inserting values\n";
  total = printAll(&llist, DefaultListSize);
  cout << "Total value is: " << total << endl;
  return 0;
}