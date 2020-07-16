// Daniel Huynh
// Graph adjacency list
#include <iostream>  // for cout
#include <string>    // for string
#include <string.h>  // for strstr
#include <assert.h>  // for assert

using namespace std;

// global
int DefaultListSize = 6;

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

// Edge implementation for adjacency list
class Edge {
  public:
  int vertex, weight;
  Edge() { vertex = -1; weight = -1; }
  Edge(int v, int w) { vertex = v; weight = w; }
};

class Graph {
private:
  void operator =(const Graph&) {} // Protect assignment
  Graph(const Graph&) {} // Protect copy constructor
public:
  Graph() {} // Default constructor
  virtual ~Graph() {} // Base destructor
  // Return the number of vertices in the graph
  virtual int n() =0;
  // Return the current number of edges in the graph
  virtual int e() =0;
  // Store an edge from "v1" to "v2" with weight "wgt"
  virtual void setEdge(int v1, int v2, int wgt) =0;
  virtual int getnumVertex() const =0;
  // Delete the edge going from "v1" to "v2"
  virtual void delEdge(int v1, int v2) =0;
  // Return weight of the edge from "v1" to "v2".
  // Return 0 if no such edge exists.
  virtual int weight(int v1, int v2) =0;
  // Get the mark value for vertex "v"
  virtual int getMark(int v) =0;
  // Set the mark value for vertex "v" to be "val"
  virtual void setMark(int v, int val) =0;
  // Return the index of the first neighbor for vertex "v"
  virtual int first(int v) =0;
  // Return the index of the next neighbor (after "v2") for vertex "v1"
  virtual int next(int v1, int v2) =0;
};

class Graphl : public Graph {
private:
  int numVertex, numEdge; // Number of vertices, edges
  List<Edge>** vertex; // List headers
  int *mark; // Pointer to mark array
public:
  Graphl(int numVert) { // Graph has "numVert" vertices
    int i;
    numVertex = numVert;
    numEdge = 0;
    mark = new int[numVert]; // Initialize mark array
    for (i=0; i<numVertex; i++) mark[i] = 0; // daniel USED TO BE UNVISITED
    // Create and initialize adjacency lists
    vertex = (List<Edge>**) new List<Edge>*[numVertex];
    for (i=0; i<numVertex; i++)
      //vertex[i] = new LinkedList<Edge>();
      vertex[i] = new LinkedList<Edge>();
  }
  ~Graphl() { // Destructor
    delete [] mark; // Return dynamically allocated memory
    for (int i=0; i<numVertex; i++)
      delete vertex[i];
    delete [] vertex;
  }

  int n() { return numVertex; } // Number of vertices
  int e() { return numEdge; } // Number of edges

  int getnumVertex() const {
    return numVertex;
  }

  // Set edge (v1, v2) to "wgt"
  void setEdge(int v1, int v2, int wgt) {
    assert(wgt>0 && "Illegal weight value");
    Edge it(v2, wgt);
    Edge curr;
    if (vertex[v1]->rightLength() > 0)
      curr = vertex[v1]->getValue();
    else curr.vertex = numVertex;
    // If not already at "v2", we must search from the start
    if (curr.vertex != v2)
    for (vertex[v1]->movetoStart(); vertex[v1]->rightLength() > 0; vertex[v1]->next()) {
      curr = vertex[v1]->getValue();
      if (curr.vertex >= v2)
        break;
    }
    if (curr.vertex == v2) // Edge (v1, v2) already exists
      curr = vertex[v1]->remove(); // Clear out existing one
    else numEdge++; // Otherwise, add a new edge
    vertex[v1]->insert(it);
  }

  int getMark(int v) { return mark[v]; }
  void setMark(int v, int val) { mark[v] = val; }

  void delEdge(int v1, int v2) { // Delete edge (v1, v2)
    Edge curr;
    curr = vertex[v1]->getValue();
    if (curr.vertex != v2) // If not already at "v2",

    for (vertex[v1]->movetoStart(); vertex[v1]->rightLength() > 0; vertex[v1]->next()) {
      curr = vertex[v1]->getValue();
      if (curr.vertex >= v2) break;
    }
    // If not at v2 now, then there is no edge (v1, v2)
    if (curr.vertex == v2) {
    curr = vertex[v1]->remove();
    numEdge--;
    }
  }

  int weight(int v1, int v2) { // Return weight of (v1, v2)
    Edge curr;
    if (vertex[v1]->rightLength() > 0)
      curr = vertex[v1]->getValue();
    else curr.vertex = numVertex;
    if (curr.vertex != v2) // If not already at "v2",
      for (vertex[v1]->movetoStart(); vertex[v1]->rightLength() > 0; vertex[v1]->next()) {
      curr = vertex[v1]->getValue();
      if (curr.vertex >= v2) break;
    }
    if (curr.vertex == v2)
      return curr.weight;
    else // If not at "v2" now, there is no edge (v1, v2)
      return 0; // Weight is 0 if (v1, v2) does not exist
  }

  int first(int v) { // Return first neighbor of "v"
    vertex[v]->movetoStart();
    if (vertex[v]->rightLength() == 0)
      return numVertex; // No neighbor
    Edge it = vertex[v]->getValue();
    return it.vertex;
  }

  int next(int v1, int v2) { // Get v1’s next neighbor after "v2"
    Edge it;
    // If we’re at "v2" now we can just move forward
    if (vertex[v1]->rightLength() > 0) {
      it = vertex[v1]->getValue();
      if (it.vertex == v2) {
        vertex[v1]->next();
        if (vertex[v1]->rightLength() > 0) {
          it = vertex[v1]->getValue();
          return it.vertex;
        }
      }
    }
    // If here, then we need to search for "v2".
    vertex[v1]->movetoStart();
    while (vertex[v1]->rightLength() > 0) {
      it = vertex[v1]->getValue();
      if (it.vertex > v2) break;
      vertex[v1]->next();
    }
    if (vertex[v1]->rightLength() == 0)
      return numVertex; // No vertex
    else return it.vertex;
  }
};

void PreVisit(Graph* G, int v) {
  cout << "PreVisit Value: " << v << endl;
}

void PostVisit(Graph* G, int v, int *currentPath, int endGoal) {
  //cout << "PostVisit Value: " << v << endl;
  G->setMark(v, 0);
  int size = G->getnumVertex();
  //cout << endl;
  if (v == endGoal) {
    for (int i = 0; i < size; i++) {
      if (currentPath[i] == -1) break;
      cout << currentPath[i] << " ";
    }
    cout << endl;
  }
}

//DFS(G, start, end, graphPath, 0)
void DFS(Graph* G, int v, int endGoal, int *currentPath, int currentDepth) { // Depth first search
  //PreVisit(G, v); // Take appropriate action
  currentPath[currentDepth] = v;
  G->setMark(v, 1); // // daniel why VISITED
  for (int w=G->first(v); w<G->n(); w = G->next(v,w)) {
    if ((G->getMark(w) == 0) && (v != endGoal)) // daniel why UNVISITED
      DFS(G, w, endGoal, currentPath, currentDepth+1);
  }
  PostVisit(G, v, currentPath, endGoal); // Take appropriate action
  currentPath[currentDepth] = -1;
}

void graphTraverse(Graph* G, int start, int end) {
  int v;
  int size = G->getnumVertex();
  int graphPath[size];

  for(int i = 0; i < size; i++) {
    graphPath[i] = -1;
  }

  // Initialize mark bits
  for (v=0; v<G->n(); v++)
    G->setMark(v, 0);  // daniel why UNVISITED

  //for (v=start; v<G->n(); v++) {
    //if (G->getMark(v) == 0) // daniel why UNVISITED
  DFS(G, start, end, graphPath, 0);
  cout << endl;
  //}
}

int main() {
  Graphl newgraph(7);
  newgraph.setEdge(1,2,1);
  newgraph.setEdge(2,4,1);
  newgraph.setEdge(3,1,1);
  newgraph.setEdge(3,2,1);
  newgraph.setEdge(3,5,1);
  newgraph.setEdge(4,6,1);
  newgraph.setEdge(5,2,1);
  newgraph.setEdge(5,4,1);
  newgraph.setEdge(5,6,1);

  cout << "These are all path from point 3 to 6" << endl;
  graphTraverse(&newgraph,3,6);

  return 0;
}
