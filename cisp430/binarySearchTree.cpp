// Daniel Huynh
#include <iostream>  // for cout
#include <string>    // for string
#include <string.h>  // for strcpy
#include <assert.h>  // for assert

using namespace std;

// Binary tree node abstract base class
template <typename Elem> class BinNode {
public:
  virtual ~BinNode() {} // Base destructor
  // Return the node’s value
  virtual Elem& val() = 0;
  
  // Set the node’s value
  virtual void setVal(const Elem&) = 0;
  
  // Return the node’s left child
  virtual BinNode* left() const = 0;
  
  // Set the node’s left child
  virtual void setLeft(BinNode*) = 0;
  
  // Return the node’s right child
  virtual BinNode* right() const = 0;
  
  // Set the node’s right child
  virtual void setRight(BinNode*) = 0;
  
  // Return true if the node is a leaf, false otherwise
  virtual bool isLeaf() = 0;
  
  virtual void visit() = 0;
};

// Simple binary tree node implementation
template <typename Elem> class BNode : public BinNode<Elem> {
private:
  Elem it; // The node’s value
  BNode* lc; // Pointer to left child
  BNode* rc; // Pointer to right child
public:
  // Two constructors -- with and without initial values
  BNode() { lc = rc = NULL; }
  BNode(Elem e, BNode* l = NULL, BNode* r = NULL) { 
    it = e; lc = l; rc = r; 
  }  
  ~BNode() { delete lc; delete rc; rc = lc = NULL;} // Destructor
  // Functions to set and return the value and key
  Elem& val() {
    return it; 
  }
  void setVal(const Elem& e) {
    it = e; 
  }
  // Functions to set and return the children
  inline BNode* left() const { 
    return lc; 
  }
  void setLeft(BinNode<Elem>* b) { 
    lc = (BNode*)b; 
  }
  inline BNode* right() const { 
    return rc; 
  }
  void setRight(BinNode<Elem>* b) { 
    rc = (BNode*)b; 
  }
  // Return true if it is a leaf, false otherwise
  bool isLeaf() { 
    return (lc == NULL) && (rc == NULL); 
  }

  void visit() {
    cout << it << endl;
  }  
};

template <typename Elem> void preorder(BinNode<Elem>* root) {
  if (root == NULL) {
    return; // Empty subtree, do nothing
  }
  root->visit();
  preorder(root->left());
  preorder(root->right());
}

template <typename Elem> void postorder(BinNode<Elem>* root) {
  if (root == NULL) {
    return; // Empty subtree, do nothing
  }
  postorder(root->left());
  postorder(root->right());
  root->visit();
}

template <typename Elem> void inorder(BinNode<Elem>* root) {
  if (root == NULL) {
    return; // Empty subtree, do nothing
  }
  inorder(root->left());
  root->visit();
  inorder(root->right());
}

int main() {
  BNode<char>* nodeRoot  = new BNode<char>;
  BNode<char>* nodeLeft  = new BNode<char>;
  BNode<char>* nodeRight = new BNode<char>;
  BNode<char>* nodeMainRoot;
  
  // sets complete right node of root
  nodeRoot->setVal('C');
  nodeLeft->setVal('F');
  nodeRight->setVal('G');
  nodeRoot->setLeft(nodeLeft);
  nodeRoot->setRight(nodeRight);
  
  // sets the root node
  nodeRight = nodeRoot;
  nodeRoot  = new BNode<char>;
  nodeRoot->setVal('A');
  nodeMainRoot = nodeRoot;
  nodeLeft  = new BNode<char>;
  nodeLeft->setVal('B');
  nodeRoot->setRight(nodeRight);
  nodeRoot->setLeft(nodeLeft);

  // sets complete left node of root
  nodeRoot = nodeLeft;
  nodeLeft = new BNode<char>;
  nodeLeft->setVal('D');
  nodeRight = new BNode<char>;
  nodeRight->setVal('E');
  nodeRoot->setLeft(nodeLeft);
  nodeRoot->setRight(nodeRight);
  
  // print
  cout << "PreOrder: " << endl;
  preorder(nodeMainRoot);
  
  cout << "PostOrder: " << endl;
  postorder(nodeMainRoot);
  
  cout << "InOrder: " << endl;
  inorder(nodeMainRoot);
  
  delete nodeMainRoot;
  nodeMainRoot = NULL;
}
