// ticTacToe.cpp
// Daniel Huynh, CISP 360
// 07/23/19

#include <iostream> // for cout
#include <cctype>   // for tolower
#include <cstdlib>  // for rand

using namespace std;

// Specification C5 - No Globals

// Function Prototype
int whoFirst();
void fillBox(const int, char **);
bool isValidMove(const int, char **, int);
int movePlayer(const int, char **, char);
int moveAI(const int, char **);
void displayBox(const int, char **, char, int *);
bool isWinner(const int, char **, char);
bool isTie(const int, char **);
void printBox();
void playTime();
void explainGame();
void playGame();

int main() {
  int choice;
  srand(time(0)); // to randomize the seed
  
  // Program Greeting
  cout << "Welcome to the Tic Tac Toe Game\n";
  cout << "--------------------------------\n";

  // Specification A1 - Main Game Loop
  // Specification B1 - Start Menu
  do {
    cout << "(1) Explain Game || "
            "(2) Play || "
            "(3) Quit: ";
    cin >> choice;
    switch (choice) {
      case 1: // Explaining the game
        explainGame();
        choice = 3; 
        break;
      case 2: // Playing the game
        playGame();
        choice = 3;
        break;
      case 3: // Quiting game
        cout << "Thanks for playing" << endl;
        break;
      // Specification B2 - Valid Menu Choices
      default:
        cout << "\nThat's not a valid option\n";
        choice = 1;
    }   
  } while (choice != 3);
}

// Specification C1 - Random Start
int whoFirst() {
  int first;
  first = rand() % 2;
  return first;
}

// Initialize the array with empty values
void fillBox(const int rowSize, char box[][3]) {
  for (int row = 0; row < rowSize; row++) {
    for (int column = 0; column < rowSize; column++)
      box[row][column]= '\0';
  }
}

// Specification B4 – Valid Move
bool isValidMove(const int rowSize, char box[][3], int inputLocation) {
  bool validMove;
  int row, column;
  
  row = (inputLocation - 1) / rowSize;
  column = (inputLocation - 1) % rowSize;
  if (box[row][column] ==  '\0') // Verify that box is empty
    validMove = true;
  else // Box has already been occupied 
    validMove = false;
  return validMove;
}

// Determining player's move
int movePlayer(const int rowSize, char box[][3], char humanAI) {
  int inputLocation;
  bool isValid=false;
  
  do {
    cout << "Where would you like to place " << humanAI << " : ";
    cin >> inputLocation;
    if (inputLocation > 0 && inputLocation < 10) { // Verify input is between 1-9
      if (isValidMove(rowSize, box, inputLocation))
        isValid=true;
      else {
        cout << "Sorry that spot has been taken\n";
        isValid=false;
      }
    } else
      cout << "Please use numbers between 1-9\n";
  } while (!isValid);
  return inputLocation;
}

// Specification C3 - AI
// AI current will go in the order from 1-9
int moveAI(const int rowSize, char box[][3]) {
  int location;
  for (int row = 0; row < rowSize; row++) {
    for (int column = 0; column < rowSize; column++) {
      if (box[row][column] ==  '\0') { // Empty
        location = (((row*rowSize)+1)+column); // Converting row and column back to box number
        return location;
      }
    } 
  }
  return 0;
}

// Specification B3 - Pretty Display
// Specification C2 - Simple Display
void displayBox(const int rowSize, char box[][3], char humanAI, int recordMoveHuman[], int recordIndexHuman, int recordMoveAI[], int recordIndexAI) {
  int inputLocation;  // Used to display the number of empty space inside the grid
  int row, 
      column;
      
  // Specification A4 - Play by Play
  if (humanAI == 'X') { // Player's turn
    inputLocation=movePlayer(rowSize, box, humanAI);
    cout << "Human location: " << inputLocation;
    recordMoveHuman[recordIndexHuman] = inputLocation;
  } else { // AI's turn
    inputLocation=moveAI(rowSize, box);
    cout << "AI location: " << inputLocation;
    recordMoveAI[recordIndexAI] = inputLocation;
  }
  if (inputLocation == 0)
    cout << "Error" << endl;
  else {
    row = (inputLocation - 1) / rowSize;
    column = (inputLocation - 1) % rowSize;
    box[row][column] = humanAI;    
    
    // prints the current box
    cout << "\n----------------\n"; // Display top of grid
    for (int row = 0; row < rowSize; row++) {
      cout << "|  ";
      for (int column = 0; column < rowSize; column++) {
        if (box[row][column] !=  '\0') // Print value in 2D-array
          cout << box[row][column] << " |  ";
        else { // Print empty cell
          cout << "  |  ";
        }
      }
      cout << "\n----------------\n"; // Display inbetween grid
    }
  }
}

// Specification A5 - Using Functions
// Specification C4 - Decide Winner
// Returns 1 if there's a winner
bool isWinner(const int rowSize, char box[][3], char humanAI) {
  char element;
  
  // This check is opposite of result because previous loop swaps the position after turn
  if (humanAI == 'X')
    element = 'O';
  else
    element = 'X';
  
  // Won by Horizontal matches
  if      (box[0][0] == element && box[0][1] == element && box[0][2] == element) return true;
  else if (box[1][0] == element && box[1][1] == element && box[1][2] == element) return true;
  else if (box[2][0] == element && box[2][1] == element && box[2][2] == element) return true;
  // Won by Vertical matches
  else if (box[0][0] == element && box[1][0] == element && box[2][0] == element) return true;
  else if (box[0][1] == element && box[1][1] == element && box[2][1] == element) return true;
  else if (box[0][2] == element && box[1][2] == element && box[2][2] == element) return true;
  // Won by Diagonal matches
  else if (box[0][0] == element && box[1][1] == element && box[2][2] == element) return true;
  else if (box[2][0] == element && box[1][1] == element && box[0][2] == element) return true;
  // No wins
  else return false;
}

void printBox() {
  cout << "-------------------\n";
  cout << "|  1  |  2  |  3  |\n";
  cout << "-------------------\n";
  cout << "|  4  |  5  |  6  |\n";
  cout << "-------------------\n";
  cout << "|  7  |  8  |  9  |\n";
  cout << "-------------------\n";
}

// Checks to see if there's any tie game, returns true if it's a tie game
bool isTie(const int rowSize, char box[][3]) {
  for (int row = 0; row < rowSize; row++) {
    for (int column = 0; column < rowSize; column++) {
      if (box[row][column] ==  '\0') // If any empty space then it's not a tie game
        return false;
    }
  }
  return true;       
}

void playTime() {
  // Specification B5 - Array Data Type
  const int RecordSize = 5;   // Because there's up to 5 possible moves for each player
  const int rowSize = 3;
  char box[rowSize][3];    // Stores 'x' or 'o' in a 3x3 grid
  int recordMoveHuman[RecordSize] = {0}; // Stores the movement
  int recordMoveAI[RecordSize] = {0}; // Stores the movement
  int recordIndexHuman = 0;       // Would use a static int inside the displayBox function but when playing another game, the index doesn't reset
  int recordIndexAI = 0;       // Would use a static int inside the displayBox function but when playing another game, the index doesn't reset
  char humanAI;      // X for human and O for AI
  static int scoreHuman = 0; // Static int is used to continue counting score each time function is called
  static int scoreAI = 0;    // Static int is used to continue counting score each time function is called
  
  printBox();
  if (whoFirst()) { // Human first
    cout << "\nYou go first\n\n";
    humanAI = 'X';
  } else { // AI first
    cout << "\nAI goes first\n\n";
    humanAI = 'O';
  }

  fillBox(rowSize, box); // Initialize the array with empty values
  
  // if there's a winner or a tie game then don't enter while loop
  while (!((isWinner(rowSize, box, humanAI)) || isTie(rowSize, box)) )  {
    if (humanAI == 'X') { // Player's turn
      cout << "\nYour turn\n";
      displayBox(rowSize, box, humanAI, recordMoveHuman, recordIndexHuman, recordMoveAI, recordIndexAI);
      humanAI = 'O';
      recordIndexHuman++;
    } else {  // AI's turn
      cout << "\nAI's turn: ";
      displayBox(rowSize, box, humanAI, recordMoveHuman, recordIndexHuman, recordMoveAI, recordIndexAI);
      humanAI = 'X';
      recordIndexAI++;
    }   
  } 
  
  // This check is opposite of result because previous loop swaps the position after turn
  // Specification A3 - Keep Score
  if (isWinner(rowSize, box, humanAI)) { // Check to see if it's a tie or a winner
    if (humanAI == 'X') {
      cout << "AI Won!!!!\n";
      scoreAI++;
    } else {
      cout << "You Win!!!!\n";
      scoreHuman++;
    }
  } else
    cout << "Tie game!\n\n";
  
  cout << "This was the order of the moves for you: ";
  for (int i = 0; i < recordIndexHuman; i++) {
    if (recordMoveHuman[i] != 0)
      cout << recordMoveHuman[i] << " ";
  }
  cout << "\nThis was the order of the moves for AI: ";
  for (int i = 0; i < recordIndexAI; i++) {
    if (recordMoveAI[i] != 0)
      cout << recordMoveAI[i] << " ";
  }
  
  cout << "\nYour score is: " << scoreHuman << endl;
  cout << "AI score is: "   << scoreAI    << endl;
}

void explainGame() {
  cout << "Game instructions:\n"
          "Take turns placing 'X' or 'O'.\n"
          "First to 3 in a row (Horizontal, Vertical, or Diagonal) wins!\n"
          "Input values 1-9 to place your selection in the grid\n";
  printBox();
}

void playGame() {
  char playAgain = 'y';
  do {
    if (tolower(playAgain) == 'y') {
      cout << "Time to play!\n";
      cout << "Recall the number input for each square\n";
      playTime();
    }
    // Specification A2 - Simple Prompt
    cout << "Do you want to play again y/n? ";
    cin >> playAgain;
    switch (tolower(playAgain)) {
      case 'y': 
        cout << "Playing again!" << endl;
        break;
      case 'n':
        cout << "Thanks for playing" << endl;
        break;
      default:
        cout << "That's not a valid option" << endl;
    }
  } while (tolower(playAgain) != 'n');
}
