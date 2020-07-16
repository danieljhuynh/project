// pig.cpp
// Daniel Huynh, CISP 400
// 09/2/19

#include <iostream>  // for cout
#include <string>    // for string
#include <cctype>    // for toupper
#include <ctime>     // for time
#include <cstdlib>   // for rand

using namespace std;

// Holds the game stats
class gameStats {
  private:
    int arraySize;
  public:
    int* whoWon;
    int* turnsPlayed;
    void updateArraySize(int);
    gameStats();
    ~gameStats();
};

gameStats::gameStats() { // constructor
  arraySize = 10;
  whoWon = new int[arraySize];
  turnsPlayed = new int[arraySize];
}

gameStats::~gameStats() { // destructor
  delete [] whoWon;
  delete [] turnsPlayed;
  whoWon = nullptr;
  turnsPlayed = nullptr;
}

// Specification X: Using a dynamic array instead of a large static one or vectors
void gameStats::updateArraySize(int dataSize) {
  if (dataSize >= arraySize) {
    arraySize *= 2; // doubles the array size
    int *temp = new int[arraySize];
    for (int i=0; i < dataSize; i++) {
      temp[i] = turnsPlayed[i];
    }
    delete [] turnsPlayed;
    turnsPlayed = temp;
    temp = new int[arraySize];
    for (int i=0; i < dataSize; i++) {
      temp[i] = whoWon[i];
    }
    delete [] whoWon;
    whoWon = temp;
  }
}

// Holds the grand score
class player {
  private:
    int totalScore;
  public:
    player();
    ~player();
    void hold(int);
    bool checkWinner();
};

player::player() { // constructor
  totalScore = 0;
}

player::~player() { // destructor
  totalScore = 0;
}

// Function Prototype
void ReturnDate();
void Header(string);
int WhoStart();
bool IsGameEnd();

// Specification B1 - Track each turn
void player::hold(int score) {
  totalScore = totalScore + score;
  cout << "\nGrand total score: " << totalScore << endl;
}

// Returns true if there's a winner
bool player::checkWinner() {
  if (totalScore >= 100) {
    return true;
  } else {
    return false;
  }
}

int main() {
  player human;
  player ai;
  gameStats groupStats;
  int resignCount = 0,
      gamesPlayedCount = 0,
      numTurn=0,
      humanTurn,
      humanWon,
      rollNum;
  char option;
  string playerName;
  
  // Program Greeting
  Header("welcome to pig");
  ReturnDate();

  // Specification C2 - Student Name
  cout << "What is your name: ";
  getline(cin, playerName);

  if (WhoStart()) {
    cout << "\nYou go first, " << playerName << "\n\n";
    humanTurn = 1;
  } else { // AI first
    cout << "\nAI goes first\n\n";
    humanTurn = 0;
  }

  // Specification C1 - Time Seed
  srand(time(NULL));
  do {
    if (humanTurn % 2 == 1) { // Human's Turn
      int score = 0;
      Header("Your turn!");
      do {
        cout << "Pick an option "
               "<R>oll, "
               "<H>old, "
               "Re<s>ign, "
               "<Q>uit\n";
        cin >> option;

        // Specification A4 - Upper and Lower Case
        option = tolower(option);

        // Specification C3 - REPLACED
        // Specification B3 - Alpha Menu
        // Specification C4 - Bulletproof Menu
        switch(option) {
          case 'r': // Roll
            rollNum = ((rand() % 6) + 1);
            cout << "You rolled: " << rollNum << endl;
            if (rollNum == 1) {
              score = 0;
              cout << "Sorry you loss all yours points\n";
              option = 'h'; // Loss turn
            } else {
              score = score + rollNum;
              cout << "Your current score is: " << score << endl;
            }
            break;
          case 'h': // Hold
            human.hold(score);
            break;
          // Specification B4 – Resign Option
          case 's': // Resign
            groupStats.updateArraySize(gamesPlayedCount);
            groupStats.turnsPlayed[gamesPlayedCount] = numTurn;
            numTurn = 0;
            resignCount++;
            gamesPlayedCount++;
            human.~player(); // resets scores
            ai.~player();    // resets scores
            break;
          case 'q': // Quit
            human.~player();
            ai.~player();
            break;
          default:
            option = 'r';
            break;
        } 
      } while (option == 'r');
    } else { // Computer Turns
      bool hold = false;
      int score = 0;
      Header("AI's turn!");
      do {
        rollNum = (rand() % 6) + 1;
        cout << "AI rolled: " << rollNum << endl;
        score = score + rollNum;
        if ((rollNum >= 1) && (rollNum <= 3 )) {
          cout << "AI is holding this turn with: " << score << " Points\n";
          ai.hold(score);
          hold = true;
        } else {
          cout << "AI will be rolling this turn\n";
          cout << "Current score: " << score << endl;
        }
      } while (hold == false);
    }
    humanTurn = (humanTurn % 2) + 1; // Switches turns
    numTurn++; // incrementing turns played
    groupStats.turnsPlayed[gamesPlayedCount] = numTurn;

    if (ai.checkWinner() || human.checkWinner()) {
      if (human.checkWinner()) { 
        cout << "You Win!\n";
        humanWon = 1;
      } else {
        cout << "AI Won!\n";
        humanWon = 0;
      }
      groupStats.whoWon[gamesPlayedCount] = humanWon;
      gamesPlayedCount++;
      numTurn = 0;
      if (IsGameEnd()) {
        option = 'q';
      } else {
        human.~player(); // resets scores
        ai.~player();    // resets scores
      }
    }
    
  } while (option != 'q');
  
  // Specification A2 - Group Stats
  for (int i=0; i < gamesPlayedCount; i++) {
    cout << "Game " << i+1 << ": ";
    if (groupStats.whoWon[i] == 1) {
      cout << "You won";
    } else {
      cout << "AI won";
    }
    cout << ", Number of Turns: " << groupStats.turnsPlayed[i] << endl;
  }
  cout << "Resign Count: " << resignCount << endl;
  cout << "Game Over " << playerName << endl;
  
  return 0;
}

// Specification A3 - Current Date
void ReturnDate() {
  time_t now = time(0);
  char* timeVar = ctime(&now);
  cout << "\nThe current date and time is: " << timeVar << endl;
}

// Template for printing headers
void Header(string output) {
  string separator; // for header separator
  separator.assign(output.length(), '=');
  // Since tolower only works on chars, I need a for loop to iterate through the string
  for (auto& c: output) 
    c = toupper(c);
  cout << "\n" << output    << endl;
  cout << separator << endl << endl;
}

// Specification B2 - Randomize Start
int WhoStart() {
  int first;
  first = rand() % 2;
  return first;
}

// Specification A1 - Main Event Loop
bool IsGameEnd() {
  char choice;
  bool isValid;
  bool endGame;

  do {
    cout << "Want to quit playing? 'y' or 'n': ";
    cin >> choice;
    switch(tolower(choice)) {
      case 'y':
        endGame = true; 
        isValid = true;
        break;
      case 'n':
        endGame = false;
        isValid = true;
        break;
      default:
        isValid = false;
        break;
    }
  } while(isValid != true);

  return endGame;
}
