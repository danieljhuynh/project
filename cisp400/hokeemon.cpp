// hokeemon
// Daniel Huynh, CISP 400
// 11/18/19

#include <iostream>  // for cout
#include <string>    // for string
#include <cctype>    // for tolower/toupper and isdigit
#include <ctime>     // for time
#include <cstdlib>   // for rand
#include <iomanip>   // for output format
#include <fstream>   // for output file
#include <sstream>   // for ostringstream
#include <vector>    // for vector
#include <iterator>  // for iterator
#include <cstddef>   // for size_t
#include <cassert>   // for assert
#include <memory>

// uncomment to disable assert()
// #define NDEBUG

// Use (void) to silent unused warnings.
#define assertm(exp, msg) assert(((void)msg, exp))

// Specification X - Bonus: Use enum for easy code readability
enum moodStatus { mad = 0, frustrated = 1, ok = 2, happy = 3 };

// Specification A2 - Copy Constructor/Assignment Operator isn't needed because it won't be used how I coded my program

using namespace std;

// Specification C2 - Virtual Class Creature
class Creature { // Abstract base class
  protected:
    static const int MAXMOOD = 4;
    // Specification A1 - Critter Name
    string name;
    int moodarray[MAXMOOD];
    int hunger;
    int boredom;
    const string moodLookUpArray[MAXMOOD] = { "Mad", "Frustrated", "Ok", "Happy" };
  public:
    Creature(const string &_name, const int& _hunger, const int& _boredom) : name(_name), hunger(_hunger), boredom(_boredom) {}
    Creature(const string &_name) { name = _name; } // same as : name(_name)
    virtual ~Creature() {};
    // Specification C1 - PassTime()
    void GetMood();
    inline void PassTime() { hunger++; boredom++;}
    inline bool IsDead() { return ((hunger > 10) || (boredom > 20)) ? true : false; }
    inline void PrintMood();
    //pure virtual functions
    virtual int GetHunger()  const = 0; // This is const because this method doesn't change anything
    virtual int GetBoredom() const = 0; // This is const because this method doesn't change anything
    virtual string GetName() const = 0; // This is const because this method doesn't change anything
    virtual void Listen()   = 0;
    virtual void Play()     = 0;
    virtual void Feed()     = 0;
    friend ostream & operator << (ostream &out, const Creature &_creature);
};

// Specification X - Bonus: Overload Operator <<
ostream & operator << (ostream &out, const Creature &_creature) {
  out << "Name: " << _creature.name <<  " Hunger: " << _creature.hunger <<  " Boredom: " << _creature.boredom;
  return out;
}

// Specification B2 - Moods
// Specification X - Bonus: Keep a total count of all moods
void Creature::GetMood() {
  bool debug = 0;
  if (boredom >= 15 && boredom <= 19) {
    if(debug) {cout << "I'm feeling mad\n";}
    moodarray[mad]++;
  } else if (boredom >= 10 && boredom <= 14) {
    if(debug) {cout << "I'm feeling frustrated\n";}
    moodarray[frustrated]++;
  } else if (boredom >= 5 && boredom <= 9) {
    if(debug) {cout << "I'm feeling ok\n";}
    moodarray[ok]++;
  } else if (boredom >= 0 && boredom <= 4) {
    if(debug) {cout << "I'm feeling happy\n";}
    moodarray[happy]++;
  } else {
    cout << "Not a valid mood";
  }
  PassTime();
}

void Creature::PrintMood() {
  for (int i = 0; i < MAXMOOD; i++) {
    cout << moodLookUpArray[i] << " Count: " << moodarray[i] << endl;
  }
}

// Specification C3 - Child Class
class fatmon : public Creature {
  protected:
    float weight;
  public:
    fatmon(const string&, float);
    virtual int GetHunger()  const override { return hunger; }
    virtual int GetBoredom() const override { return boredom; }
    virtual string GetName() const override { return name; }
    virtual void Listen() override;
    virtual void Play() override;
    virtual void Feed() override;
    friend ostream & operator << (ostream &out, const fatmon &_fatmon);
};

// constructor
fatmon::fatmon(const string& _name, float _weight) : Creature(_name) {
  hunger = rand() % 6;  // generates a number between 0 to 5
  boredom = rand() % 6; // generates a number between 0 to 5
  weight = _weight;
}

// Specification X - Bonus: Overload Operator <<
ostream & operator << (ostream &out, const fatmon &_fatmon) {
  out << "Name: " << _fatmon.name <<  " Hunger: " << _fatmon.hunger <<  " Boredom: " << _fatmon.boredom;
  return out;
}

void fatmon::Listen() {
  cout << "My hunger is: " << hunger << " and my boredom is: " << boredom << endl;
  GetMood();
}

void fatmon::Play() {
  cout << "Playing with my Fatmon" << endl;
  boredom = boredom - 4;
  if (boredom < 0) { boredom = 0;}
  cout << "My boredom level has decreased to: " << boredom << endl;
  GetMood();
}

void fatmon::Feed() {
  cout << "Feeding my Fatmon" << endl;
  hunger = hunger - 4;
  if (hunger < 0) { hunger = 0;}
  cout << "My hunger level has decreased to: " << hunger << endl;
  GetMood();
}

// Specification B3 - Second Child Class
class tallmon : public Creature {
  protected:
    float height;
  public:
    tallmon(const string&, float);
    virtual int GetHunger()  const override { return hunger; }
    virtual int GetBoredom() const override { return boredom; }
    virtual string GetName() const override { return name; }
    virtual void Listen() override;
    virtual void Play() override;
    virtual void Feed() override;
    friend ostream & operator << (ostream &out, const tallmon &_tallmon);
};

// constructor
tallmon::tallmon(const string& _name, float _height) : Creature(_name) {
  hunger = rand() % 6;  // generates a number between 0 to 5
  boredom = rand() % 6; // generates a number between 0 to 5
  height = _height;
}

// Specification X - Bonus: Overload Operator <<
ostream & operator << (ostream &out, const tallmon &_tallmon) {
  out << "Name: " << _tallmon.name <<  " Hunger: " << _tallmon.hunger <<  " Boredom: " << _tallmon.boredom;
  return out;
}

void tallmon::Listen() {
  cout << "My hunger is: " << hunger << " and my boredom is: " << boredom << endl;
  GetMood();
}

void tallmon::Play() {
  cout << "Playing with my Tallmon" << endl;
  boredom = boredom - 4;
  if (boredom < 0) { boredom = 0;}
  cout << "My boredom level has decreased to: " << boredom << endl;
  GetMood();
}

void tallmon::Feed() {
  cout << "Feeding my Tallmon" << endl;
  hunger = hunger - 4;
  if (hunger < 0) { hunger = 0;}
  cout << "My hunger level has decreased to: " << hunger << endl;
  GetMood();
}

// Function Prototype
void Header(string);
char CheckValidMenu();

int main() {
  string fatmonName;
  float fatmonWeight;
  string tallmonName;
  char choice;
  float tallmonHeight;
  bool isAlive;

  srand(time(0)); // to randomize the seed
  Header("Let's Play Hokeemon");
  cout << "What would you like to call your Fatmon: ";
  getline(cin, fatmonName);
  cout << "How fat in pounds is " << fatmonName << ": ";
  cin >> fatmonWeight;
  
  // Specification A3 - Code Protection
  if (cin.fail()) { assertm(0, "That's not a number"); }
  
  cout << "What would you like to call your Tallmon: ";
  cin.ignore(256, '\n'); // To ignore the previous newline entered from previous cin
  getline(cin, tallmonName);
  cout << "How tall in inches is " << tallmonName << ": ";
  cin >> tallmonHeight;
  if (cin.fail()) { assertm(0, "That's not a number"); }

  vector<unique_ptr<Creature>> monster;
  monster.push_back(unique_ptr<Creature>(new fatmon(fatmonName, fatmonWeight)));
  monster.push_back(unique_ptr<Creature>(new tallmon(tallmonName, tallmonHeight)));

  // Playing each monster, one at a time
  for(auto& it : monster) {
    cout << "--------------------------------\n";
    cout << it->GetName() << "'s Hunger is: " << it->GetHunger() << " and Boredom is: " << it->GetBoredom() << endl;
    //cout << it << endl;
    do {
    isAlive = !(it->IsDead());
    choice = CheckValidMenu();
    switch(choice) {
      case 'l':
        it->Listen();
        break;
      case 'p':
        it->Play();
        break;
      case 'f':
        it->Feed();
        break;
      case 'q':
        isAlive = false;
        break;
      default:
        break;
    }
    } while(isAlive);
    it->PrintMood();
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

// Specification B1 - Validate Input
char CheckValidMenu() {
  char option;
  bool isValid;
  do {
    cout << "\nWhat would you like to do (L)isten, (P)lay, (F)eed, or (Q)uit: ";
    cin >> option;
    if (cin.fail()) {
      cin.clear(); // Removes the error
      cin.ignore(1000,'\n'); // Removes the error
      isValid = false;
    } else {
      isValid = true;
    }
  } while(!isValid);
  return tolower(option);
}
