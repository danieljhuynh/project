// Daniel Huynh
// characterHash

#include <iostream>
#include <string>
using namespace std;

int characterHash(string key, int size) {
  int total = 0;
  for(string::iterator it = key.begin(); it != key.end(); ++it) {
    total = total + *it;
  }
  return total % size;
}

int main() {
  string key;
  int size;
  cout << "Enter string: ";
  cin >> key;
  cout << "Enter table size: ";
  cin >> size;
  cout << "Sum of ASCII values: " << characterHash(key, size) << endl;
}
