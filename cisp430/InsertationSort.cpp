/*
Title: InsertationSort (Source code based on Prof Ross' code)
Author: Daniel Huynh
Date: 1/26/2020
Change List:
  Fixed compiling error: void main to int main
  Added for loop open/close braces
  Added print statements
  Whitespace cleanup
  Since array is global, passing the argument into functions isn't needed
*/

#include <stdio.h>
#define SIZE 9

int A[SIZE] = {24,13,26,1,2,27,38,15,10};

void print_array();
void isort();

int main() {
  print_array();
	isort();
  return 0;
}

void isort() {
  int i, j;
  int temp;

  for(i = 0; i < SIZE; i++) {
    // find insertion spot
    j = i; 
    temp = A[i];
    while(A[j - 1] > temp && j > 0) {
      A[j] = A[j - 1];
      j--;
    }
    A[j] = temp;
    print_array();
  }
}

void print_array() {
	for(int i=0; i<SIZE; i++) 
		printf("%d \t", A[i]);
	printf("\n");
}

/*
24 	13 	26 	1 	2 	27 	38 	15 	10 	
24 	13 	26 	1 	2 	27 	38 	15 	10 	
13 	24 	26 	1 	2 	27 	38 	15 	10 	
13 	24 	26 	1 	2 	27 	38 	15 	10 	
1 	13 	24 	26 	2 	27 	38 	15 	10 	
1 	2 	13 	24 	26 	27 	38 	15 	10 	
1 	2 	13 	24 	26 	27 	38 	15 	10 	
1 	2 	13 	24 	26 	27 	38 	15 	10 	
1 	2 	13 	15 	24 	26 	27 	38 	10 	
1 	2 	10 	13 	15 	24 	26 	27 	38 	
*/