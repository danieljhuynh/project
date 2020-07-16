/*
Title: Fibonacci (Source code based on Prof Ross' code)
Author: Daniel Huynh
Date: 2/13/2020
*/

#include <iostream>
using namespace std;

int fib(int n) {
  if(n==0)
    return 0;
  if(n==1)
    return 1;
  else
    return fib(n-1) + fib(n-2);
}

int main() {
  cout << fib(6) << endl;
  return 0;
}