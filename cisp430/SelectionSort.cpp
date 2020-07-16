/*
Title: SelectionSort (Source code based on Prof Ross' code)
Author: Daniel Huynh
Date: 1/26/2020
Change List:
  Fixed compiling error: void main to int main
  Added for loop open/close braces
  Added print statements
  Whitespace cleanup
  Since array is global, passing the argument into functions isn't needed
  Copied print_array function from BubbleSort.cpp
*/

#include <stdio.h>
#define SIZE 9

int A[SIZE] = {24,13,26,1,2,27,38,15,10};

void print_array();
void ssort(void);
void swap(int i, int j);

int main() {
	print_array();
	ssort();
  return 0;
}

void ssort() {
  int i, j;
  int m;

  i = SIZE - 1;
  while(i >= 0) {
    // find biggest unsorted element
    j = 0;
    m = 0;
    while(j <= i) {
       if(A[j] > A[m]) 
          m = j;
       j++;
    }
    // put biggest at end
    swap(i, m);
    print_array();
    i--;
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
24 	13 	26 	1 	2 	27 	10 	15 	38 	
24 	13 	26 	1 	2 	15 	10 	27 	38 	
24 	13 	10 	1 	2 	15 	26 	27 	38 	
15 	13 	10 	1 	2 	24 	26 	27 	38 	
2 	13 	10 	1 	15 	24 	26 	27 	38 	
2 	1 	10 	13 	15 	24 	26 	27 	38 	
2 	1 	10 	13 	15 	24 	26 	27 	38 	
1 	2 	10 	13 	15 	24 	26 	27 	38 	
1 	2 	10 	13 	15 	24 	26 	27 	38 	
*/