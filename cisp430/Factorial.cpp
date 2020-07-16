/*
Title: Factorial (Source code based on Prof Ross' code)
Author: Daniel Huynh
Date: 2/13/2020
*/

#include <iostream>
using namespace std;

int fac(int n) {
  if(n==0)
    return 1;
  else
    return n * fac(n-1);
}

int main() {
  cout << fac(3) << endl;
  return 0;
}
