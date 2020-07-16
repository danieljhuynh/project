/*
Title: Bob (Source code based on Prof Ross' code)
Author: Daniel Huynh
Date: 2/13/2020
*/

#include <iostream>
using namespace std;

int y; // global

void p(int x) {
  x = y - 1;
  y += x;
  cout << x << " " << y << endl;
  if (x<3) p(x);
  cout << x << " " << y << endl;
}

int  main() {
  int x;
  x = 0; y = 2; p(x); 
  cout << x << " " << y << endl;
  return 0;
}