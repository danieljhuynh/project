// bb.cpp
// Daniel Huynh, CISP 400
// 10/30/19

#include <iostream>  // for cout
#include <string>    // for string
#include <cctype>    // for tolower/toupper and isdigit
#include <ctime>     // for time
#include <cstdlib>   // for rand
#include <iomanip>   // for output format
#include <fstream>   // for output file
#include <sstream>   // for ostringstream

using namespace std;

// Specification A3 - Date Class in Program Greeting
class date {
  private:
    string timeOut;
  public:
    date();
    const string ReturnDate();
    friend ostream & operator << (ostream &out, const date &dt);
};

date::date() {
  timeOut = ReturnDate();
}

// From Googling to return the date and time
const string date::ReturnDate() {
  time_t rawtime;
  time (&rawtime);
  return ctime (&rawtime);
}

ostream & operator << (ostream &out, const date &dt) {
  out << dt.timeOut;
  return out;
}

// Specification C1 - OOP
class ship {
  private:
    static const int MAXSHIPS = 5;
    static const int YMAX = 10;
    static const int XMAX = 10;
    bool IsShotValid;
    int numOfShots;
    int availableShots = MAXSHIPS;
    int shipCount = MAXSHIPS;
    static const string shipList[MAXSHIPS];
    static const string shipCharList[MAXSHIPS];
    static const int shipSizeList[MAXSHIPS];
    // Specification Bonus: Using dynamic array to hold unsunken ships to reduce looping to determine available shots
    string * const availableShip = new string[shipCount]; //const pointer, non-const data 
    string grid[YMAX][XMAX]; // holds the shot fired // 0 - no shot fired, 1 shot fired
    const string filename = "log.txt";
  public:
    ship();
    inline int GetShipCount() { return shipCount; }; // use of inline makes code run faster because it doesn't need to jump to function address
    void SetShotLocation(int, bool);
    void Shoot(bool);
    void ShowMap();
    void ShowSecretMap(bool);
    void DeclareShips();
    void AutoDeclareShips();
    void WriteToFile(bool, int, int);
    bool PlaceShips(int, int, char, bool);
    bool isValidShipPlacement(int, int, int, char, bool);
    bool IsValidLocation(int, int, bool);
    bool IsValidShot(int, int, bool);
    inline bool IsWinner() { return (shipCount == 0); }
    bool IsNum(string);   
};

const string ship::shipList[MAXSHIPS] = { "carrier", "battleship", "cruiser", "submarine", "destroyer" };
const int ship::shipSizeList[MAXSHIPS] = { 5, 4, 3, 3, 2 };
const string ship::shipCharList[MAXSHIPS] = { "CR", "BS", "CU", "SM", "DR" };

// constructor to setup the map
ship::ship() { 
  // setup the grid
  for (int y = 0; y < YMAX; y++) {
    for (int x = 0; x < XMAX; x++) {
      grid[y][x] = to_string(y*10 + x); // converts integer y=7 and x=8, to 78 string
    }
  }
  // setup the available ships
  for (int i = 0; i < MAXSHIPS; i++) { 
    availableShip[i] = shipCharList[i];
  }
}

// Specification B2 - Log file to Disk
void ship::WriteToFile(bool player, int ylocation, int xlocation) {
  ofstream file;
  date timeNow;
  file.open(filename, ios::app); // open for appending
  if (player) { // player1
    file << timeNow;
    file << "\tPlayer: " << player << ", Shot Location: " << (ylocation*10 + xlocation) << endl;
  } else { // player2
    file << "\t\t\t\t\t\t" << timeNow;
    file << "\t\t\t\t\t\t\tPlayer: AI, Shot Location: " << (ylocation*10 + xlocation) << endl;
  }
  file.close();
}

// return true if ship hasn't been shot
bool ship::IsNum(string text) {
	for(size_t i = 0; i < (text.length() - 1); i++) {
		if (!isdigit(text[i])) {
      return false;
    }
  }
  return true;
}

// Shows the player's map
void ship::ShowMap() {
  cout << "\nThis is your map and where AI has fired\n";
  
  for (int y = 0; y < YMAX; y++) {
    cout << "| ";
    for (int x = 0; x < XMAX; x++) {
      cout << setw(2) << setfill('0') << grid[y][x] << " ";
    }
    //cout << setfill(' ') << "|" << endl; // revert setfill
    cout << "|" << endl;
  }
  cout << "_________________________________\n";
}

// Specification C3 - Secret Option
void ship::ShowSecretMap(bool secret) {
  int secretShotLocation[MAXSHIPS*5]; // Max ship * max size of a ship
  int secretShotIndex = 0;
  cout << "\nThis is AI's map and where you fired\n";
  for (int y = 0; y < YMAX; y++) {
    cout << "| ";
    for (int x = 0; x < XMAX; x++) {
      if (secret) { // shows the secret
        cout << setw(2) << setfill('0') << grid[y][x] << " ";
        // Specification Bonus: Provides a secret list of locations for easier shooting
        if (grid[y][x] != "XX" && grid[y][x] != "OO" && !IsNum(grid[y][x])) { // If ship exist
          secretShotLocation[secretShotIndex] = (y*10+x);
          secretShotIndex++;
        }
      } else { // shows regular map
        if ((grid[y][x] == "XX") || (grid[y][x] == "OO")) { // shows only where you shot
          cout << setw(2) << setfill('0') << grid[y][x] << " ";
        } else {
          cout << "   ";
        }
      }
    }
    cout << "|" << endl;
  }
  cout << "_________________________________\n";
  if (secret) {
    cout << "You may want to shoot these coordinates: "; 
    for (int i = 0; i < secretShotIndex; i++) {
      cout << secretShotLocation[i] << " ";
    }
    cout << endl;
  }
}

// Ask ship, location, and direction
void ship::DeclareShips() {
  char direction;
  int location;
  bool debug = 1;
  for (int i = 0; i < MAXSHIPS; i++) {
    do {
      cout << "Where do you want to place your " << shipList[i]
           << " of size " << shipSizeList[i] << endl;
      cout << "| 00 01 02 03 04 05 06 07 08 09 |\n"                                                                                                                                                                                                                  
              "| 10 11 12 13 14 15 16 17 18 19 |\n"                                                                                                                                                                                                                  
              "| 20 21 22 23 24 25 26 27 28 29 |\n"                                                                                                                                                                                                                  
              "| 30 31 32 33 34 35 36 37 38 39 |\n"                                                                                                                                                                                                                  
              "| 40 41 42 43 44 45 46 47 48 49 |\n"                                                                                                                                                                                                                  
              "| 50 51 52 53 54 55 56 57 58 59 |\n"                                                                                                                                                                                                                  
              "| 60 61 62 63 64 65 66 67 68 69 |\n"                                                                                                                                                                                                                  
              "| 70 71 72 73 74 75 76 77 78 79 |\n"                                                                                                                                                                                                                  
              "| 80 81 82 83 84 85 86 87 88 89 |\n"                                                                                                                                                                                                                  
              "| 90 91 92 93 94 95 96 97 98 99 |\n"
              "_________________________________\n";    
      cout << "Valid options are between 00 and 99: ";
      cin >> location;
      cout << "\nWhat direction, (D)own or (R)ight: ";
      cin >> direction;
      direction = tolower(direction);
    } while(!PlaceShips(i, location, direction, debug));
  }
}

// Specification B3 - Random Start
void ship::AutoDeclareShips() {
  char direction;
  int location;
  int flip;
  bool debug = 0;
  for (int i = 0; i < MAXSHIPS; i++) {
    do {
      location = rand() % 100; // generates a number between 00 to 99
      flip = rand( ) % 2;      // generates 0 or 1
      if (flip) {
        direction = 'd';
      } else {
        direction = 'r';
      }    
    } while(!PlaceShips(i, location, direction, debug));
  }
}

// Place ship onto map if valid
bool ship::PlaceShips(int shipIndex, int location, char direction, bool debug) {
  int ylocation = location / 10;
  int xlocation = location % 10;
  bool isValid = isValidShipPlacement(shipIndex, ylocation, xlocation, direction, debug);
  if (isValid) {
    for (int i = 0; i < shipSizeList[shipIndex]; i++) {
      if (direction == 'd') {
        grid[ylocation + i][xlocation] = shipCharList[shipIndex];
      } else if (direction == 'r') {
        grid[ylocation][xlocation + i] = shipCharList[shipIndex];
      }
    }
  }
  if (!isValid) { 
    if (debug) cout << "Not a valid location, please try again\n"; 
  } else {
    if (debug) { ShowMap(); }
  }
  return isValid;
}

// Checks to make sure all location are valid for ship to be placed
bool ship::isValidShipPlacement(int shipIndex, int ylocation, int xlocation, char direction, bool debug) { 
  bool isValid = true;
  for (int i = 0; i < shipSizeList[shipIndex]; i++) {
    if (direction == 'd') {
      isValid = (isValid && IsValidLocation(ylocation + i, xlocation, debug));
    } else if (direction == 'r') {
      isValid = (isValid && IsValidLocation(ylocation, xlocation + i, debug));
    }
  }
  return isValid;
}

// Specification B1 - Validate Input
// Specification A1 - Adv Input Validation
bool ship::IsValidLocation(int ylocation, int xlocation, bool debug) {
  bool isValid = true;
  if ((ylocation > 9) || (ylocation < 0)) {
    if (debug) {cout << "ylocation is out of bounds\n";}
    isValid = false;
  } else if ((xlocation > 9) || (xlocation < 0)) {
    if (debug) {cout << "xlocation is out of bounds\n";}
    isValid = false;
  } else if (IsNum(grid[ylocation][xlocation])) {
    isValid = true;
  } else {
    if (debug) {cout << ylocation << xlocation << " has been occupied already\n";}
    isValid = false;
  }
  return isValid;
}

// Specification C2 - Prohibit AI wasted shots
bool ship::IsValidShot(int ylocation, int xlocation, bool debug) {
  bool isValid = true;
  if ((ylocation > 9) || (ylocation < 0)) {
    if (debug) {cout << "ylocation is out of bounds\n";}
    isValid = false;
  } else if ((xlocation > 9) || (xlocation < 0)) {
    if (debug) {cout << "xlocation is out of bounds\n";}
    isValid = false;
  } else if (grid[ylocation][xlocation] == "XX") {
    if (debug) {cout << "You already shot here and got a target\n";}
    isValid = false;
  } else if (grid[ylocation][xlocation] == "OO") {
    if (debug) {cout << "You already shot here and missed\n";}
    isValid = false;
  } else {
    if (debug) {
      if (IsNum(grid[ylocation][xlocation])) {
        cout << "Your shot missed\n";
      } else {
        cout << "You shot: " << grid[ylocation][xlocation] << endl;
      }
    }
    isValid = true;
  }
  return isValid;
}

void ship::Shoot(bool debug) {
  int location;
  int ylocation;
  int xlocation;
  int indexOfShip = -1;
  bool shipExist = false;
  if (debug) { // Player's turn
    ShowSecretMap(false);
    do {
      cout << "Provide location: ";
      cin >> location;
      ylocation = location / 10;
      xlocation = location % 10;
    } while (!IsValidShot(ylocation, xlocation, debug));
  } else { //AI's turn
    do {
      ylocation = rand() % 10; // generates a number between 0 to 9
      xlocation = rand() % 10; // generates a number between 0 to 9
    } while (!IsValidShot(ylocation, xlocation, debug));
  }
  WriteToFile(debug, ylocation, xlocation); // Logs the battle
  if (IsNum(grid[ylocation][xlocation])) { // this is a miss
    grid[ylocation][xlocation] = "OO"; // Sets the shot for a miss
    return;
  } 
  for (int i = 0; i < MAXSHIPS; i++) {
    if (grid[ylocation][xlocation] == availableShip[i]) {
      indexOfShip = i;
      break; // once it found the index, no need to keep searching
    }
  }
  if (indexOfShip == -1) {
    cout << "Something went wrong";
    return;
  }
  grid[ylocation][xlocation] = "XX"; // Sets the shot
  for (int y = 0; y < YMAX; y++) { // Checks to see if entire ship exist after the shot
    for (int x = 0; x < XMAX; x++) {
      if (grid[y][x] == availableShip[indexOfShip]) {
        shipExist = true; // ship still exist
      }
    }
  }
  
  if (!shipExist) { // Ship is sunk
    cout << "GOOD JOB, YOU SUNK " << availableShip[indexOfShip] << "!!!!!\n";
    shipCount = shipCount - 1; // Enemy's ship count
    availableShip[indexOfShip] = " ";
  }
}

// Specification A2 - MultiFire Game
void ship::SetShotLocation(int turns, bool debug) {
  if (debug) {
    cout << "Number of shots available to you: " << turns << endl;
  } else {
    cout << "Number of shots available to AI: " << turns << endl;
  }
  while(turns != 0) {
    Shoot(debug);
    turns--;
  } 
}

// Function Prototype
void Header(string);
inline void print(string text);

int main() {
  ship player1;
  ship player2;
  int choice;
  char gameMode;
  bool isValidGameMode = true;
  bool gameOver = false;
  char randomShip;
  date timeNow;
  
  // Program Greeting
  Header("BattleShip");
  cout << "The current date is: " << timeNow << endl;
  
  // Setting up game mode
  do {
    cout << "Do you want to play (N)ormal or (M)ultiFire Game: ";
    cin >> gameMode;
    gameMode = tolower(gameMode);
    switch(gameMode) {
      case 'n':
      case 'm':
        isValidGameMode = true;
        break;
      default:
        cout << "Not a valid entry, enter 'n' or 'm' only\n";
        isValidGameMode = false;
        break; 
    }
  } while(!isValidGameMode);
  
  // Setting up map
  print("\nLet's start by setting up the map");
  srand(time(0));     // to randomize the seed
  
  // Specification Bonus: Allowing player to place random ships as well
  do {
    cout << "Do you want to place random ships too? (Y)es or (N)o: ";
    cin >> randomShip;
    randomShip = tolower(randomShip);
    switch(randomShip) {
      case 'n':
      case 'y':
        isValidGameMode = true;
        break;
      default:
        cout << "Not a valid entry, enter 'y' or 'n' only\n";
        isValidGameMode = false;
        break; 
    }
  } while(!isValidGameMode);

  if (randomShip == 'n') {
    player1.DeclareShips();
  } else {
    player1.AutoDeclareShips();
  }
  player2.AutoDeclareShips();
  
  // Playing the game
  do {  
    cout << "What do you want to do (1) Shoot (2) Show Secret Map (3) Rules: " ;
    cin >> choice;
    switch(choice) {
      case 1: // shoot
        player1.ShowMap(); // Shows your ship map and where AI has fired
        if (gameMode == 'm') { // multi-fire turns
          player2.SetShotLocation(player1.GetShipCount(), true); // Sets player1 shots on player2's map. [turns, true - printing for player]
          if (player2.IsWinner()) { 
            cout << "YOU WIN!\n";
            gameOver = true; 
          } else {
            player1.SetShotLocation(player2.GetShipCount(), false); // Sets player2 shots on player1's map. [turns, false - no print messages]
            if (player1.IsWinner()) { 
              cout << "AI WIN!\n";
              gameOver = true; 
            }
          }
        } else { // normal turns
          player2.SetShotLocation(1, true); // Sets player1 shots on player2's map. [1 turn, true - printing for player]
          if (player2.IsWinner()) { 
            cout << "YOU WIN!\n";
            gameOver = true; 
          } else {
            player1.SetShotLocation(1, false); // Sets player2 shots on player1's map. [1 turn, false - no print messages]
            if (player1.IsWinner()) { 
              cout << "AI WIN!\n";
              gameOver = true; 
            }
          }
        }     
        break;
      case 2: // show AI's map
        player2.ShowSecretMap(true);
        break;
      case 3: // show instructions
        print("OO: Missed shot");
        print("XX: Shot a ship");
        print("CR: Carrier");
        print("BS: Battleship");
        print("CU: Cruiser");
        print("SM: Submarine");
        print("DR: Destroyer");
        break;
      default: // invalid choice
        cout << "Invalid choice\n";
        break;
      }
  } while (!gameOver);
  
  return 0;
}

// Created print statement to remove need of adding newline
inline void print(string text) {
  cout << text << endl;
}

// Template for printing headers
void Header(string output) {
  string separator; // for header separator
  separator.assign(output.length(), '=');

  // Since toupper only works on chars, I need a for loop to iterate through the string
  for (auto& c: output)
    c = toupper(c);
  cout << "\n"      << output << endl;
  cout << separator << endl   << endl;
}