/*
Title: BubbleSort (Source code based on Prof Ross' code)
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
void swap(int, int);
void bsort();

int main() {
	print_array();
	bsort();
  return 0;
}

void bsort() {
  int i, j;
  for(i = 0; i < SIZE; i++) {
    for(j = SIZE - 1; j > 0; j--) {
      if(A[j] < A[j - 1]) {
        swap(j, j - 1);
        print_array();
      }
    }
  }
}

void swap(int i, int j) {
  int temp;
  temp = A[i];
  A[i] = A[j];
  A[j] = temp;
}

void print_array() {
	for(int i=0; i<SIZE; i++)
		printf("%d \t", A[i]);
	printf("\n");
}

/*
24 	13 	26 	1 	2 	27 	38 	15 	10 	
24 	13 	26 	1 	2 	27 	38 	10 	15 	
24 	13 	26 	1 	2 	27 	10 	38 	15 	
24 	13 	26 	1 	2 	10 	27 	38 	15 	
24 	13 	1 	26 	2 	10 	27 	38 	15 	
24 	1 	13 	26 	2 	10 	27 	38 	15 	
1 	24 	13 	26 	2 	10 	27 	38 	15 	
1 	24 	13 	26 	2 	10 	27 	15 	38 	
1 	24 	13 	26 	2 	10 	15 	27 	38 	
1 	24 	13 	2 	26 	10 	15 	27 	38 	
1 	24 	2 	13 	26 	10 	15 	27 	38 	
1 	2 	24 	13 	26 	10 	15 	27 	38 	
1 	2 	24 	13 	10 	26 	15 	27 	38 	
1 	2 	24 	10 	13 	26 	15 	27 	38 	
1 	2 	10 	24 	13 	26 	15 	27 	38 	
1 	2 	10 	24 	13 	15 	26 	27 	38 	
1 	2 	10 	13 	24 	15 	26 	27 	38 	
1 	2 	10 	13 	15 	24 	26 	27 	38 	
*/