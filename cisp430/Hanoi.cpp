/*
Title: Hanoi (Source code based on Prof Ross' code)
Author: Daniel Huynh
Date: 2/13/2020

Fixed compiling errors
*/

#include <iostream>
using namespace std;

void Hanoi(int N, int Start, int Goal, int Spare) {
  if (N == 1)
    // move the disk to the goal peg
    cout << "Move disk from peg " << Start << " to peg " << Goal << endl;
  else {
    // move the disks above the target disk to the spare peg
    Hanoi(N - 1, Start, Spare, Goal);
    // move the "target" disk to the goal peg
    cout << "Move disk from peg " << Start << " to peg " << Goal << endl;
    // move the disks from the spare peg to the goal peg
    Hanoi(N - 1, Spare, Goal, Start);
  }
}

int main() {
  // start the solution here
  Hanoi(3, 1, 3, 2);
  return 0;
}
