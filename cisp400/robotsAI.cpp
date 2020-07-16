// Genetic Algorithm Robots
// Daniel Huynh, CISP 400
// 12/5/19

#include <iostream>  // for cout
#include <string>    // for string
#include <cctype>    // for tolower/toupper and isdigit
#include <ctime>     // for time
#include <cstdlib>   // for rand
#include <sstream>   // for ostringstream
#include <vector>    // for vector
#include <iterator>  // for iterator
#include <map>       // for multimap
#include <algorithm> // for sort

enum gridLegend { empty = 0, wall = 1, battery = 2, robot = 9 };
enum robotLegend { robotRowLocation = 0, robotColumnLocation = 1 };
enum directionLegend { randomm = 0, north = 1, east = 2, south = 3, west = 4 };

// Set debug to enable print messages 
bool debug = 0;
bool randomPick = 1;

using namespace std;

class Game {
  private:
    static const int ROWS = 10;
    static const int COLUMN = 10;
    static const int WALLS = 2;
    static const int MAXGENES = 16;
    int batteryCount = 40;
    int grid[ROWS+WALLS][COLUMN+WALLS];
    int robotEnergy = 5;
    int robotXYLocation[2];
    int defaultGenes;
  public:
    Game(); // Constructor
    Game(const multimap<unsigned char, int> &, const multimap<unsigned char, int> &, bool, bool); // Constructor for the children
    Game(const multimap<unsigned char, int> &); // Constructor for my ideal case robot
    void InitGenes();
    void Mutation();
    void InitHalfGenes(const multimap<unsigned char, int> &, multimap<unsigned char, int>::const_iterator, multimap<unsigned char, int>::const_iterator);
    unsigned char MergeBits(unsigned char, unsigned char, unsigned char, unsigned char);
    unsigned char RobotSensor();
    void RobotMove(int);
    void SetupMap();
    void Play();
    void PrintGenes();
    int GeneLookup(unsigned char);
    multimap<unsigned char, int> genes;
    int turns = 0;
    friend ostream & operator << (ostream &, const Game &);
};

// Sorts the vector of Game by turns
struct sortTurns {
  inline bool operator() (const Game& game1, const Game& game2) {
    return (game1.turns > game2.turns);
  }
};

// Constructor for parents
Game::Game() {
  SetupMap();
  // Setup the 16 random genes
  for (int i = 0; i < MAXGENES; i++) {
    InitGenes();  
  }
}

// Constructor for a child from parents
Game::Game(const multimap<unsigned char, int> &parent1, const multimap<unsigned char, int> &parent2, bool same, bool top) {
  SetupMap();
  // Setup the const iterator to be used to determine the midpoint of the multimap    
  multimap<unsigned char, int>::const_iterator mid = parent1.begin();
  // Moves the itr to parent1.size()/2
  advance(mid, parent1.size()/2);
  // Uses top/bottom 8 genes from both parents
  if (same) { 
    // Uses the top 8 genes from both parents
    if (top) {   
      InitHalfGenes(parent1, parent1.begin(), mid);
      // Setup the const iterator to be used to determine the midpoint of the multimap
      mid = parent2.begin();
      // Moves the itr to parent2.size()/2
      advance(mid, parent2.size()/2);
      InitHalfGenes(parent2, parent2.begin(), mid);
    // Uses the bottom 8 genes from both parents
    } else {
      InitHalfGenes(parent1, mid, parent1.end());
      // Setup the const iterator to be used to determine the midpoint of the multimap
      mid = parent2.begin();
      // Moves the itr to parent2.size()/2
      advance(mid, parent2.size()/2);
      InitHalfGenes(parent2, mid, parent2.end());
    }    
  // Uses top 8 genes from one parent, and bottom 8 genes from the other parent
  } else {   
    InitHalfGenes(parent1, parent1.begin(), mid);
    // Setup the const iterator to be used to determine the midpoint of the multimap
    mid = parent2.begin();
    // Moves the itr to parent2.size()/2
    advance(mid, parent2.size()/2);
    InitHalfGenes(parent2, mid, parent2.end());
  }
  Mutation();
}

void Game::Mutation() {
  // For mutation
  multimap<unsigned char, int>::const_iterator lastGenes = genes.end(); // Getting the out of bound end of multimap index
  --lastGenes;            // Getting the last index of the multimap
  genes.erase(lastGenes); // Deleting the last element
  InitGenes();            // Adding a random mutation gene
  if (debug) cout << "Gene size: " << genes.size();
}

// Sets the initial genes for the parents
void Game::InitGenes() {
  unsigned char northBits = rand() % 3; // random 0-2
  unsigned char eastBits  = rand() % 3;  // random 0-2
  unsigned char southBits = rand() % 3; // random 0-2
  unsigned char westBits  = rand() % 3;  // random 0-2
  unsigned char input     = MergeBits(northBits, eastBits, southBits, westBits);
  int output              = rand() % 5;    // random 0-4
  // Insert the input as the key, and the output as the value
  genes.insert(pair<unsigned char, int>(input, output));
}

void Game::InitHalfGenes(const multimap<unsigned char, int> &parent, multimap<unsigned char, int>::const_iterator begin, multimap<unsigned char, int>::const_iterator end) {
  for (auto itr = begin; itr !=end; ++itr) {
    // Insert the input as the key, and the output as the value
    genes.insert(pair<unsigned char, int>((*itr).first, (*itr).second));
  }
}

// Merges the direction into a single unsigned char
unsigned char Game::MergeBits(unsigned char northBits, unsigned char eastBits, unsigned char southBits, unsigned char westBits) {
  unsigned char bits = 0;
  bits |= westBits;
  bits |= southBits << 2;
  bits |= eastBits << 4;
  bits |= northBits << 6;
  return bits;
}

// Setup the map (wall + battery) and starting location for a robot
void Game::SetupMap() {
  defaultGenes = (rand() % 15); // Random 0 to 15 
  bool isValid;
  int rowLocation;
  int columnLocation;
  // Setup the wall
  for (int i = 0; i < ROWS + WALLS; i++) {
    grid[i][0] = wall;  // Left-size walls
    grid[i][11] = wall; // Right-size walls
  }
  for (int j = 0; j < COLUMN + WALLS; j++) {
    grid[0][j] = wall;  // Top-side walls
    grid[11][j] = wall; // Bottom-side walls
  }
  
  // Initialize the 10 x 10 map to be 0
  for (int i = 1; i < ROWS + 1; i++) {
    for (int j = 1; j < COLUMN + 1; j++) {
      grid[i][j] = empty;
    }
  }
 
  // Setup the randomized the battery placement
  while (batteryCount != 0) {
    rowLocation = (rand() % 11) + 1; // generates a number between 1 to 10
    columnLocation = (rand() % 11) + 1; // generates a number between 1 to 10
    if (grid[rowLocation][columnLocation] == empty) { // Currently empty and can place a new battery
      grid[rowLocation][columnLocation] = battery;
      batteryCount--;
    }
  }
  
  // Starting robot location
  do {
    rowLocation = (rand() % 11) + 1; // generates a number between 1 to 10
    columnLocation = (rand() % 11) + 1; // generates a number between 1 to 10
    if (grid[rowLocation][columnLocation] == empty) {
      grid[rowLocation][columnLocation] = robot;
      robotXYLocation[robotRowLocation] = rowLocation;
      robotXYLocation[robotColumnLocation] = columnLocation;
      isValid = true;
    } else {
      isValid = false;
    }
  } while (!isValid);
}

void Game::Play() {
  int direction;
  //if (debug) PrintGenes();
  while (robotEnergy > 0) {
    unsigned char sensorValue = RobotSensor();
    direction = GeneLookup(sensorValue);
    RobotMove(direction);
  }
}

int Game::GeneLookup(unsigned char sensorValue) {
  multimap<unsigned char, int>::iterator itr;
  itr = genes.find(sensorValue); // Tries to find which gene matches the robot sensor input
  if (debug) PrintGenes();
  if (itr == genes.end()) { // If it can't find one, then it'll use the first element in the gene
    itr = genes.begin();
    advance(itr, defaultGenes);
  }
  return itr->second;
}

void Game::PrintGenes() {
  cout << "Printing robot genes" << endl;
  for (multimap<unsigned char, int>::iterator itr = genes.begin(); itr != genes.end(); ++itr) {
    cout << hex << (int)(*itr).first << " : " << dec << (*itr).second << endl;
  }
}

unsigned char Game::RobotSensor() {
  int xlocation = robotXYLocation[robotRowLocation];
  int ylocation = robotXYLocation[robotColumnLocation];
  unsigned char northSensor = grid[xlocation+1][ylocation];
  unsigned char eastSensor  = grid[xlocation][ylocation+1];
  unsigned char southSensor = grid[xlocation-1][ylocation];
  unsigned char westSensor  = grid[xlocation][ylocation-1];
  return MergeBits(northSensor, eastSensor, southSensor, westSensor);
}

void Game::RobotMove(int direction) {
  robotEnergy--;
  turns++;
  switch(direction) {
    case randomm: // Move Random
      direction = (rand() % 4) + 1; // random 1 - 4
    case north: // Move North
      if (debug) cout << "Robot wants to move North" << endl;
      if (grid[(robotXYLocation[robotRowLocation] - 1)][robotXYLocation[robotColumnLocation]] != wall) { // If robot didn't hit a wall
        if (debug) cout << "Robot moving North" << endl;
        grid[robotXYLocation[robotRowLocation]][(robotXYLocation[robotColumnLocation])] = empty;         // Clear current robot location on the map
        robotXYLocation[robotRowLocation] = robotXYLocation[robotRowLocation] - 1;                       // Update robot X Y location
      }
      break;        
    case east: // Move East
      if (debug) cout << "Robot wants to move East" << endl;
      if (grid[robotXYLocation[robotRowLocation]][(robotXYLocation[robotColumnLocation] + 1)] != wall) { // If robot didn't hit a wall
        if (debug) cout << "Robot moving East" << endl;
        grid[robotXYLocation[robotRowLocation]][(robotXYLocation[robotColumnLocation])] = empty;         // Clear current robot location on the map
        robotXYLocation[robotColumnLocation] = robotXYLocation[robotColumnLocation] + 1;                 // Update robot X Y location
      }
      break;
    case south: // Move South
      if (debug) cout << "Robot wants to move South" << endl;
      if (grid[(robotXYLocation[robotRowLocation] + 1)][robotXYLocation[robotColumnLocation]] != wall) { // If robot didn't hit a wall
        if (debug) cout << "Robot moving South" << endl;
        grid[robotXYLocation[robotRowLocation]][(robotXYLocation[robotColumnLocation])] = empty;         // Clear current robot location on the map
        robotXYLocation[robotRowLocation] = robotXYLocation[robotRowLocation] + 1;                       // Update robot X Y location
      }
      break;
    case west: // Move West
      if (debug) cout << "Robot wants to move West" << endl;
      if (grid[robotXYLocation[robotRowLocation]][(robotXYLocation[robotColumnLocation] - 1)] != wall) { // If robot didn't hit a wall
        if (debug) cout << "Robot moving West" << endl;
        grid[robotXYLocation[robotRowLocation]][(robotXYLocation[robotColumnLocation])] = empty;         // Clear current robot location on the map
        robotXYLocation[robotColumnLocation] = robotXYLocation[robotColumnLocation] - 1;                 // Update robot X Y location
      }
      break;
    default: // Shouldn't ever get to this case
      break;
  }
  // Found a battery
  if (grid[robotXYLocation[robotRowLocation]][robotXYLocation[robotColumnLocation]] == battery) { 
    robotEnergy = robotEnergy + 5;
  }
  // Move robot on the grid
  grid[robotXYLocation[robotRowLocation]][robotXYLocation[robotColumnLocation]] = robot; 
}

ostream & operator << (ostream &out, const Game &game) {
  for (int i = 0; i < game.ROWS + game.WALLS; i++) {
    for (int j = 0; j < game.COLUMN + game.WALLS; j++) {
      out << game.grid[i][j] << " ";
    }
    out << "\n";
  }
  return out;
}

// Function Prototype
void Header(string);

int main() {
  static const int ROBOT_COUNT = 200;
  static const int GENERATION_NUM = 100;
  srand(time(0));     // to randomize the seed
  float avgInitTurns = 0;
  
  // Program Greeting
  Header("Genetic Algorithm Robots");
  
  // Stores each robot into a vector
  vector<Game> games;
  
  // Runs the X robots, X being the "ROBOT_COUNT"
  for (int i = 0; i < ROBOT_COUNT; i++) {
    if (debug) cout << "Starting Robot: " << i << endl;
    Game robot;
    if (debug) cout << "Robot starting location"<< endl;
    if (debug) cout << robot;
    robot.Play();
    games.push_back(robot);
    if (debug) cout << "Max turns for Robot " << i << ": " << robot.turns << endl;
  }
  
  // Sort the vector
  std::sort(games.begin(), games.end(), sortTurns());
  
  // print the sorted vector
  for (auto it = games.begin(); it != games.end(); it++) {
    int x = it->turns;
    avgInitTurns += x;
    if (debug) cout << "Turns: " << x << endl;
  }
  cout << "Avg Turns: " << avgInitTurns/ROBOT_COUNT << endl;
  
  // Iterations of childs
  for (int i = 0; i < GENERATION_NUM; i++) {
    // Creating a temp Vector
    float avgTurns = 0;
    vector<Game> tempGames;
    tempGames = games;
    // Clears the vector of each robots
    games.clear();
    
    // Creates 4 childs each loop
    for (int j = 0; j < ROBOT_COUNT/2; j++) {
      // Creates the genes for child 1, top half from parent1 and bottom half from parent2
      Game child1(tempGames[j*2].genes, tempGames[j*2+1].genes, 0, 0);
      child1.Play();
      // Append the child 1's data to vector
      games.push_back(child1);
      
      // Creates the genes for child 2, top half from parent2 and bottom half from parent1
      Game child2(tempGames[j*2+1].genes, tempGames[j*2].genes, 0, 0);
      child2.Play();
      // Append the child 2's data to vector
      games.push_back(child2);
      
      // Creates the genes for child 3, top half from parent1 and parent2
      Game child3(tempGames[j*2].genes, tempGames[j*2+1].genes, 1, 1);
      child3.Play();
      // Append the child 3's data to vector
      games.push_back(child3);
      
      // Creates the genes for child 4, bottom half from parent1 and parent2
      Game child4(tempGames[j*2].genes, tempGames[j*2+1].genes, 1, 0);
      child4.Play();
      // Append the child 4's data to vector
      games.push_back(child4);
    }
    
    // Sort the vector
    std::sort(games.begin(), games.end(), sortTurns());
    
    // print the sorted vector
    for (auto it = games.begin(); it != games.end(); it++) {
      int x = it->turns;
      avgTurns += x;
      //cout << "Turns: " << x << endl;
    }
    cout << "Avg Turns: " << avgTurns/ROBOT_COUNT << endl;
  }
  return 0;
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