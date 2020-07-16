// dungeonGame.cpp
// Daniel Huynh, CISP 360
// 07/30/19

#include <iostream>  // for cout
#include <string>    // for string
#include <cctype>    // for toupper
#include <algorithm> // for remove
#include <vector>    // for vector

using namespace std;

// Function Prototype

class Room {
  private:
    string  roomID,
            roomName,
            roomDescription;
    bool    isRoomOccupied,
            hasVisited,
            hasTreasure,
            hasTrap;

  public:
    Room();
    ~Room();
    static bool foundSword;
    static int monsterScore;
    char checkRoom(char);
    bool isRoomValid();
    void setRoom(string, string, string, bool, bool, bool, bool);
    void goRoom();
    void print();
    void printLook();
    void printBlueText(string);
    void printInstruction();

};

bool Room::foundSword = false;
int Room::monsterScore = 0;

Room::Room() { // constructor
  roomID = "Room#";
  roomName = "Empty Name";
  roomDescription = "Empty Description";
  isRoomOccupied = false;
  hasVisited = false;
}

Room::~Room() { // destructor
  roomID = "";
  roomName = "";
  roomDescription = "";
  isRoomOccupied = false;
  hasVisited = false;
  hasTreasure = false;
  hasTrap = false;
}

// Specification C4 – Abbreviated Room Description
void Room::print() {
  cout << "\n-------------------------------------------";
  if(hasVisited) {
    cout << "\nRoom ID: " << roomID
         << "\nRoom Name: " << roomName << endl;
  } else {
    //hasVisited = true;
    cout << "\nRoom ID: " << roomID
         << "\nRoom Name: " << roomName
         << "\nRoom Description: " << roomDescription << endl;
  }
  cout << "-------------------------------------------" << endl;
}

void Room::printLook() {
  cout << "\n-------------------------------------------";
  cout << "\n Room ID: " << roomID 
       << "\n Room Name: " << roomName 
       << "\n Room Description: " << roomDescription << endl;
  cout << "-------------------------------------------" << endl;
}
  
void Room::printInstruction() {
  cout << "\nDirectional moves are: (N)orth, (S)outh, (E)ast, and (W)est\n";
  cout << "You'll notice that some directional movement aren't available because the map is limited to\n";
  cout << "    ________________________\n";
  cout << "   |       |       |       |\n";
  cout << "   |   1   |   2   |   3   |\n";
  cout << "   |_______|_______|_______|\n";
  cout << "   |       |       |       |\n";
  cout << "   |   4   |   5   |   6   |\n";
  cout << "   |_______|_______|_______|\n";
}

void Room::setRoom(string id, string name, string description, bool occupied, bool visited, bool treasure, bool trap) {
  roomID = id;
  roomName = name;
  roomDescription = description;
  isRoomOccupied = occupied;
  hasVisited = visited;
  hasTreasure = treasure;
  hasTrap = trap;
}
 
bool Room::isRoomValid() {
  if(roomID != "Room#") {
    print();
    return true;
  } else
    cout << roomID << " is not a valid room\n";
  return false;
}

char Room::checkRoom(char exitCode) {
  if (isRoomValid()) {
    if (hasTreasure && !hasVisited) { // If the room contains a treasure
      // Specification A1 - Add combat
      printBlueText("Equipped Bronze Sword!");
      foundSword = true; 
    } else if (hasTrap) {
      cout << "I can't enter, this room has a trap\n";
      exitCode = '\0';
    } else if (isRoomOccupied) {
      cout << "This room is occupied by a Monster!\n";
      if (foundSword) {
        cout << "Luckily I have equipped the sword, Insta-kill!\n";
        cout << "Monster destroyed!\n";
        isRoomOccupied=false;
        monsterScore++;
      } else {
        cout << "I shouldn't enter this room without a weapon or that monster will eat me alive!\n";
        exitCode = '\0';
      }
    }
    if (roomID == "Room 6") {
      cout << "\nCongratulations you've saved the princess!\n";
      exitCode = 'F'; // Winner!
    }
    hasVisited = true;
    // uses input exitCode
  } else {
    exitCode = '\0';
  }
  return exitCode;
}

void Room::printBlueText(string word) {
  cout << "\033[1;34m" + word + "\033[0m\n";
}

int main() {
  const int rowSize = 2;
  Room rooms[rowSize][3];
  string playerName;
  char exitCode;
  vector<char> validDirection{};
  bool keepSearching;

  // Player starting location
  int x = 0;
  int y = 0;

  // Program Greeting
  cout << "My Mission: Rescue the Princess!\n";
  cout << "----------------------------------\n\n";
  cout << "Game Settings: (I)nstructions, (Q)uit \n";
  
  // Specification C2 - Player Name
  cout << "What is your player name: ";
  getline(cin, playerName);
  
  // Specification A2 - Use 2D array instead of exitCode to point to roomID. Pros: Increased readability of the code. Cons: Harder to create an unique map, due to out of bounds checking
  //                  id      , name    , description                                         , occupied , visited , treasure, trap
  rooms[0][0].setRoom("Room 1", "Jungle", "Welcome to the gloomy jungle"                      , false    , false   , false   , false); 
  rooms[0][1].setRoom("Room 2", "Cave"  , "Crawled into a dark and smelly cave"               , false    , false   , false   , false);
  rooms[0][2].setRoom("Room 3", "Tunnel", "Found a muddy tunnel"                              , true     , false   , false   , false);
  // Specification B1 - Add trap encounters
  rooms[1][0].setRoom("Room 4", "Ditch" , "Fell a ditch filled with snakes!"                  , false    , false   , false   , true );
  // Specification C1 - Five Rooms
  // Specification A3 - Add treasure
  rooms[1][1].setRoom("Room 5", "Lake"  , "Let's go for a swim in the lake. I found a sword!" , false    , false   , true    , false);
  // Specification B3 - Add more rooms
  // Specification B2 - Add more monsters
  rooms[1][2].setRoom("Room 6", "Castle", "I've arrived at the castle"                        , true     , false   , false   , false);

  rooms[x][y].checkRoom(exitCode);
  
  do {
    // Specification A - Only show valid moves by checking boundary of 2D array
    validDirection = {'N','S','E','W','L','I','Q'};
    if (x == 0) {
      validDirection.erase(std::remove(validDirection.begin(), validDirection.end(), 'N'), validDirection.end());
    }
    if (x == 1) {
      validDirection.erase(std::remove(validDirection.begin(), validDirection.end(), 'S'), validDirection.end());
    }
    if (y == 0) {
      validDirection.erase(std::remove(validDirection.begin(), validDirection.end(), 'W'), validDirection.end());
    }
    if (y == 2) {
      validDirection.erase(std::remove(validDirection.begin(), validDirection.end(), 'E'), validDirection.end());
    }
    do {
      cout << "\nWhat would you like to do, " << playerName << "? (";
      for (char i : validDirection)
        cout << " " << i;
      cout << " ): ";
      cin >> exitCode;
      exitCode = toupper(exitCode);
      if (std::find(validDirection.begin(), validDirection.end(), exitCode) == validDirection.end()) {
        cout << exitCode << " isn't a valid option\n";
        keepSearching = true;
      }
      else
        keepSearching = false;
    } while (keepSearching);

    // Specification C3 - Input Validation
    switch(exitCode) {
      case 'N':
        x--;
        exitCode = rooms[x][y].checkRoom(exitCode);
        if (exitCode == '\0')
          x++;
        break;
      case 'S':
        x++;
        exitCode = rooms[x][y].checkRoom(exitCode);
        if (exitCode == '\0')
          x--;
        break;
      case 'E':
        y++;
        exitCode = rooms[x][y].checkRoom(exitCode);
        if (exitCode == '\0')
          y--;
        break;
      case 'W':
        y--;
        exitCode = rooms[x][y].checkRoom(exitCode);
        if (exitCode == '\0')
          y++;
        break;
      // Specification C5 - Detailed Look
      case 'L':
        rooms[x][y].printLook();
        exitCode = '\0';
        break;
      // Specification A - Added display instruction option
      case 'I':
        rooms[x][y].printInstruction();
        exitCode = '\0';
        break;
      // Specification A - Added a quit option
      case 'Q':
        cout << "Quitting: This game is too hard!\n";
        exitCode = 'F';
        break;
      default:
        exitCode = '\0';
        break;
    }
  } while (exitCode != 'F'); // F for finished
  // Specification A - Record numbers of monsters killed from all Class objects
  cout << "You've killed a total monster count of: " << rooms[x][y].monsterScore << endl;
  cout << "\nGame over " << playerName << endl;
  
  return 0;
}
