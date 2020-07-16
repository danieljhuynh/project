// InvInq.cpp
// Daniel Huynh, CISP 400
// 9/19/19

#include <iostream>  // for cout
#include <string>    // for string
#include <cctype>    // for tolower
#include <ctime>     // for time
#include <cstdlib>   // for rand
#include <iomanip>   // for output format
#include <fstream>   // for output file
#include <sstream>   // for ostringstream

using namespace std;

// Specification Bonus: Using enum to increase code readable
enum arrayElement { na, description, quantity, cost };
enum menu { none, add, del, edit, display, quit };

// Specification B1 - OOP
class Inventory {
  private:
    string itemDescription;
    string dateAdded;
    int quantity;
    int retailCost;
    const string ReturnDate();
  public:
    Inventory();
    ~Inventory();
    void SetInv();
    string GetInv(int);
    void SetCost();
    void SetQuantity();
    void SetDescription();
};

Inventory::Inventory() { // constructor
  itemDescription = "";
  dateAdded = "";
  quantity = 0;
  retailCost = 0;
}

Inventory::~Inventory() { // destructor
  itemDescription = "";
  dateAdded = "";
  quantity = 0;
  retailCost = 0;
}

// Function Prototype
void Header(string);
void EditInv(Inventory**, int);
Inventory** DelInv(Inventory**, int);
Inventory** newArray(Inventory**, int);
void WriteToFile(string, Inventory**, int);
int CheckValidMenu();

void Inventory::SetInv() {
  //char* timeVar;
  SetDescription();
  SetQuantity();
  SetCost();
  dateAdded = ReturnDate();
  //dateAdded = "NEEDS WORK";
}

// Specification A2 - Validate Inventory
void Inventory::SetDescription() {
  bool isValid;
  do {
    cout << "\tEnter a Description (22 chars max): ";
    //cin >> itemDescription;
    cin.ignore();
    getline(cin,itemDescription);
    // Conditional ternary operator
    ((itemDescription.length() > 22) ? (isValid = false) : (isValid = true));
  } while (!isValid);
}

// Sets the Cost
void Inventory::SetCost() {
  bool isValid;
  do {
    cout << "\tEnter a postive price for the retail cost: ";
    cin >> retailCost;
    if (retailCost >= 0) {
      retailCost = (retailCost + retailCost);
      isValid = true;
    } else {
      cout << "A negative number is invalid\n";
      isValid = false;
    }
  } while (!isValid);
}

// Sets the Quantity
void Inventory::SetQuantity() {
  bool isValid;
  do {
    cout << "\tEnter a postive quantity: ";
    cin >> quantity;
    if (quantity >= 0) {
      isValid = true;
    } else {
      cout << "A negative number is invalid\n";
      isValid = false;
    }
  } while (!isValid);
}

// From Googling to return the date
const string Inventory::ReturnDate() {
  const int MAXLEN = 80;
  char timeVar[MAXLEN];
  time_t t = time(0); // current date
  strftime(timeVar, MAXLEN, "%m/%d/%y", localtime(&t));
  return timeVar;
}

// Specification C3 - Display Option
string Inventory::GetInv(int index) {
  ostringstream ostr;
  ostr << "\tItem " << index;
  ostr << ": Description: " << itemDescription;
  ostr << ", Quantity: " << quantity;
  ostr << ", Retail Cost: " << retailCost;
  ostr << ", Date Added: " << dateAdded << "\n";
  // Returns the string from ostr
  return ostr.str();
}

int main() {
  const string filename = "inventory.txt";
  menu choice;
  int index = 0;
  Inventory** inv;
  inv = nullptr;

  // Program Greeting
  Header("Inventory tracker tool");

  do {
    choice = static_cast<menu>(CheckValidMenu());
    // Specification C4 - Main Menu
    switch(choice) {
      // Specification C2 - Add Option
      case add:
        inv = newArray(inv, index); //newArray(*inv, arraySize);
        inv[index] = new Inventory(); // creates new object that the element in array points to
        inv[index]->SetInv(); // Same as (*inv[index]).SetInv();
        index++;
        break;
      //Specification B2 - Delete Inventory Item
      case del:
        for(int i=0; i < index; i++)
          cout << inv[i]->GetInv(i);
        index--;
        inv = DelInv(inv, index);
        break;
      // Specification A1 - Edit Inventory
      case edit:
        EditInv(inv, index);
        break;
      case display:
        for(int i=0; i < index; i++)
          cout << inv[i]->GetInv(i);
        break;
      case quit:
        cout << "Thanks for using inventory tracker!\n";
        WriteToFile(filename, inv, index);
        cout << "Your file is saved to: " << filename << endl;
        break;
      default:
        choice = none;
    }
  } while (choice != quit);

  // clean up to prevent memory leaks
  delete [] inv;
  inv = nullptr;

  return 0;
}

// Specification C1 - Dynamic Array
Inventory** newArray(Inventory** inv, int index) {
  Inventory** tempArray;
  tempArray = new Inventory*[index+1]; // Increase array size by +1
  for (int i = 0; i < index; i++) { // copying array to temp array
    tempArray[i] = inv[i]; // Setting address in the ptr inv now the pointer
  }
  if (inv != nullptr) {
    delete [] inv;   // deleting old array
  }
  return tempArray;
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

// Edits the inventory
void EditInv(Inventory** inv, int index) {
  int changeIndex;
  int option;
  arrayElement changeField;
  bool isValid = true;

  // prints all items in the inventory
  for (int i = 0; i < index; i++) {
    cout << inv[i]->GetInv(i);
  }
  do {
    do {
      cout << "Which index would you like to edit: ";
      cin >> changeIndex;
      if (cin.fail()) {
        cin.clear(); // Removes the error
        cin.ignore(1000,'\n'); // Removes the error
        isValid = false;
      } else {
        isValid = true;
      }
    } while(!isValid);
    if (changeIndex > index-1) {
      cout << "That element isn't in the inventory list\n";
      isValid = false;
      continue; // skips rest of this iteration and rerun
    } else {
      isValid = true;
    }
    cout << "Which field would you like to edit: (1. Description, 2. Quantity, 3. Cost): ";
    cin >> option;
    changeField = static_cast<arrayElement>(option); // Converts option to enum type arrayElement

    // Specification Bonus: Allows user to edit a particular field instead of the entire inventory
    switch(changeField) {
      case description:
        inv[changeIndex]->SetDescription();
        isValid = true;
        break;
      case quantity:
        inv[changeIndex]->SetQuantity();
        isValid = true;
        break;
      case cost:
        inv[changeIndex]->SetCost();
        isValid = true;
        break;
      default:
        isValid = false;
        break;
    }
  } while (!isValid);
}

Inventory** DelInv(Inventory** inv, int index) {
  int delIndex;
  Inventory** temp = nullptr;
  bool isValid = true;
  do {
    do {
      cout << "\tWhich item# would you like to delete: ";
      cin >> delIndex;
      if (cin.fail()) {
        cin.clear(); // Removes the error
        cin.ignore(1000,'\n'); // Removes the error
        isValid = false;
      } else {
        isValid = true;
      }
    } while(!isValid);
    if (delIndex > index) {
      cout << "That element isn't in the inventory list\n";
      isValid = false;
    } else {
      isValid = true;
    }
  } while (!isValid);
  delete inv[delIndex]; // Deletes the requested element's deferenced value
  inv[delIndex] = nullptr; // Clears the delIndex ptr
  // Specification B3 - Shrink Dynamic Array
  temp = new Inventory*[index];
  for (int i = 0; i < delIndex; i++) {
    temp[i] = inv[i];
  }
  // Shift element left by 1 until reached user index
  for (int i = delIndex; i < index; i++) {
    temp[i] = inv[i+1];
  }
  delete [] inv;
  return temp;
}


// Specification A3 - Logfile
void WriteToFile(string filename, Inventory** inv, int index) {
  char choice;
  bool isValid;
  ofstream file;

  do {
    cout << "\tDo you want to (o)verwrite or (a)ppend to file?: ";
    cin >> choice;
    choice = tolower(choice);
    if (cin.fail()) {
      cin.clear(); // Removes the error
      cin.ignore(1000,'\n'); // Removes the error
      isValid = false;
    } else if ((choice == 'o') || (choice == 'a')) {
      isValid = true;
    } else {
      isValid = false;
    }
  } while(!isValid);

  if (choice == 'o') { // override
    file.open(filename);
  // Specification Bonus - Option to append to LogFile instead
  } else { // append
    file.open(filename, ios::app);
  }

  for (int i = 0; i < index; i++) {
    file << inv[i]->GetInv(i); // writes inventory to file
  }
  file.close();
}

// Specification C5 - Validate Menu
int CheckValidMenu() {
  int option;
  bool isValid;
  do {
    cout << "1. Add Inventory,"
            " 2. Delete Inventory,"
            " 3. Edit Inventory,"
            " 4. Display Inventory,"
            " 5. Quit Program: ";
    cin >> option;
    if (cin.fail()) {
      cin.clear(); // Removes the error
      cin.ignore(1000,'\n'); // Removes the error
      isValid = false;
    } else {
      isValid = true;
    }
  } while(!isValid);
  return option;
}
