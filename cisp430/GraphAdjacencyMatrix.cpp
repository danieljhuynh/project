// Daniel Huynh
// Graph adjacency matrix
#include <iostream>  // for cout
#include <string>    // for string
#include <string.h>  // for strstr
using namespace std;

// global
int DefaultListSize = 10;

class Graph {
private:
  void operator =(const Graph&) {} // Protect assignment
  Graph(const Graph&) {} // Protect copy constructor
public:
  Graph() {} // Default constructor
  virtual ~Graph() {} // Base destructor
  // Store an edge from "v1" to "v2" with weight "wgt"
  virtual void setEdge(int v1, int v2, int wgt) =0;
};

// Implementation for the adjacency matrix representation
class GraphMatrix : public Graph {
private:
  int numVertex, numEdge; // Store number of vertices, edges
  int **matrix; // Pointer to adjacency matrix
  int *mark; // Pointer to mark array
public:
  GraphMatrix(int numVert) { // Make graph w/ numVert vertices
    int i;
    numVertex = numVert;
    numEdge = 0;
    matrix = (int**) new int*[numVertex]; // Make matrix
    for (i=0; i<numVertex; i++) {
      matrix[i] = new int[numVertex];
    }
  }
  ~GraphMatrix() { // Destructor
    delete [] mark; // Return dynamically allocated memory
    for (int i=0; i<numVertex; i++) {
      delete [] matrix[i];
    }
    delete [] matrix;
  }

  // Set edge (v1, v2) to "wgt"
  void setEdge(int v1, int v2, int wgt) {
    if (matrix[v1][v2] == 0) {
      numEdge++; // Increment edge count
    }
    matrix[v1][v2] = wgt;
  }
  
  // Prints the Adjacency matrix
  void printGraph() {
    for (int i = 0; i < numVertex; i++) {
      for (int j =0; j < numVertex; j++) {
        cout << matrix[i][j] << " ";
      }
      cout << endl;
    }
  }
  // Finds the indegree 0 vertex
  void findNewVertexOfIndegreeZero() {
    int arr[numVertex] = {0};
    for (int i = 0; i < numVertex; i++) {
      for (int j =0; j < numVertex; j++) {
        arr[j] = arr[j] || matrix[i][j]; // bitwise OR
      }
    }
    for (int j = 0; j < numVertex; j++) {
      if (arr[j] == 0) {
        cout << "Vertex " << j+1 << " has a indegree 0" << endl;
      }
    }
  }
};

int main() {
  GraphMatrix newgraph(7);
  newgraph.setEdge(0,1,1);
  newgraph.setEdge(0,2,1);
  newgraph.setEdge(0,3,1);
  newgraph.setEdge(1,3,1);
  newgraph.setEdge(1,4,1);
  newgraph.setEdge(2,5,1);
  newgraph.setEdge(3,2,1);
  newgraph.setEdge(3,5,1);
  newgraph.setEdge(3,6,1);
  newgraph.setEdge(4,3,1);
  newgraph.setEdge(4,6,1);
  newgraph.setEdge(6,5,1);
  
  cout << "Adjacency matrix" << endl;
  newgraph.printGraph();
  newgraph.findNewVertexOfIndegreeZero();

  return 0;
}