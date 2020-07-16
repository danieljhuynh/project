/*
Title: 4 Queens (Source code based on Prof Ross' code)
Author: Daniel Huynh
Date: 2/13/2020

Fixed compiling errors
*/

#include <stdio.h>
int sol[5]; // global solution “stack”. ignore cell 0

void printsolution(void) {
  for(int i=1;i<5;i++) {
    printf("%d ,", sol[i]);
  }
  printf("\n");
}

bool cellok(int n){
  int i;

  // check for queens on other rows
  for(i=1;i<n;i++) {
    if(sol[i] == sol[n]) {
      return false;
    }
  }
  // check for queens on diagonals
  for(i=1;i<n;i++) {
    if((sol[i] == (sol[n] - (n - i))) || (sol[i] == (sol[n] + (n - i)))) {
      return false;
    }
  }
  return true;
}

void build(int n) {
  int p = 1;
  // loop while there are more possible moves
  while (p <= 4) {
    // Store this move
    sol[n] = p;
    // Check if cell is okay
    if(cellok(n)) {
      // is this the last column?
      if(n == 4) printsolution();
      else build(n + 1);  // get the next move
    }
    p++;
  }
}

int main() {
  build(1);
  return 0;
}
