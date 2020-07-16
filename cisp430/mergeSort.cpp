// Daniel Huynh
// Merge Sort
#include <iostream>  // for cout

using namespace std;

void mergeSort(int*, int, int);
void merge(int*, int, int, int);

void mergeSort(int *arr, int left, int right) { 
  if (left < right) {
    int mid = left+(right-left)/2; 

    mergeSort(arr, left, mid); 
    mergeSort(arr, mid+1, right); 
    merge(arr, left, right, mid); 
  } 
} 

void merge(int *arr, int left, int right, int mid) { 
  int midLeft = mid - left + 1; 
  int midRight =  right - mid; 

  int leftArr[midLeft];
  int rightArr[midRight]; 

  // Copying left/right array to temp array
  for (int i = 0; i < midLeft; i++) {
    leftArr[i] = arr[left + i]; 
  }
  for (int j = 0; j < midRight; j++) {
    rightArr[j] = arr[mid + 1+ j]; 
  }
  
  int i = 0; 
  int j = 0; 
  int k = left;
  while (i < midLeft && j < midRight) { 
    if (leftArr[i] <= rightArr[j]) { 
      arr[k] = leftArr[i]; 
      i++; 
    } else { 
      arr[k] = rightArr[j]; 
      j++; 
    } 
    k++; 
  } 
  
  // copying array back
  while (i < midLeft) { 
    arr[k] = leftArr[i]; 
    i++; 
    k++; 
  } 
  while (j < midRight) { 
    arr[k] = rightArr[j]; 
    j++; 
    k++; 
  } 
}

int main() { 
  const int SIZE = 10;
  int arr[SIZE] = { 20, 34, 1, 40, -1, 100, 15, 28, 65, 50 };

  cout << "Original unsorted array" << endl;
  for(int i=0; i < SIZE; i++) {
    cout << arr[i] << " ";
  }
  cout << endl;
  
  mergeSort(arr, 0, SIZE - 1); 
  
  cout << "Sorted array" << endl;
  for(int i=0; i < SIZE; i++) {
    cout << arr[i] << " ";
  }
  cout << endl;
  return 0; 
}