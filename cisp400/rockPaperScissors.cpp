// rockPaperScissors.cpp
// Daniel Huynh, CISP400
// 08/30/2019

#include <iostream>  // for cout
#include <string>    // for string
#include <cstdlib>   // for rand
#include <ctime>     // for srand

using namespace std;

#define MAX_DIFFERENT_SCORES 3
enum score  { tieScore, compScore, humanScore };

// Function Prototype
int checkWinner(int);

int main() {
  int totalHands = 0; // Keeps track of total hands played
  int winner = 0;
	bool cont=true;     // to continue playing
  int humanChoice;
  int array[MAX_DIFFERENT_SCORES] = {0};
  
  // Program Greeting
  cout << "Welcome to a game of Rock, Paper, Scissors!" << endl;
  cout << "------------------------------------------"  << endl << endl;

  srand(time(0));     // to randomize the seed
  do {
    cout << "(0) Rock, (1) Paper, (2) Scissors, (3) Quit: ";
    cin >> humanChoice;
    // Four option menu with input validation
    switch(humanChoice) {
      case 0:
        cout << "You picked Rock" << endl;
        winner = checkWinner(humanChoice);
        array[winner] = array[winner] + 1;
        break;
      case 1:
        cout << "You picked Paper" << endl;
        winner = checkWinner(humanChoice);
        array[winner] = array[winner] + 1;
        break;
      case 2:
        cout << "You picked Scissors" << endl;
        winner = checkWinner(humanChoice);
        array[winner] = array[winner] + 1;
        break;
      case 3:
        cont=false;
        break;
      default:
        cout << "That's not a valid option" << endl;
        break;
    }
  } while(cont);


  for (int i=0; i < MAX_DIFFERENT_SCORES; i++) {
    totalHands = totalHands + array[i];
  }

  cout << "\nYou've scored: "          << array[humanScore] << endl;
  cout << "Computer scored: "          << array[compScore]  << endl;
  cout << "Number of ties: "           << array[tieScore]   << endl;
  cout << "\nNumber of games played: " << totalHands        << endl;

  if (array[humanScore] > array[compScore]) {
    cout << "You've won most hands" << endl;
  } else if (array[compScore] > array[humanScore]) {
    cout << "Computer won most hands" << endl;
  } else {
    cout << "Both you and the computer scored equal amount of points" << endl;
  }

  return 0;
}

int checkWinner(int humanChoice) {
  int compChoice;
  int win;
  // 0 - Rock, 1 - Paper, 2 - Scissors
  compChoice = rand() % 3; // Random digit between 1-3
  // 0 - Tie, 1 - Human, 2 - Computer
  if (compChoice == 0) {
    cout << "Computer picked Rock" << endl;
  } else if (compChoice == 1) {
    cout << "Computer picked Paper" << endl;
  } else {
    cout << "Computer picked Scissors" << endl;
  }
  win = (compChoice - humanChoice + 3) % 3;
  return win;
}
