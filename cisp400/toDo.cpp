// todo.cpp
// Daniel Huynh, CISP 400
// 11/12/19

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

using namespace std;

class date {
  private:
    string timeOut;
  public:
    date();
    const string ReturnDate();
    friend ostream & operator << (ostream &out, const date &dt);
};

// constructor
date::date() {
  timeOut = ReturnDate();
}

// Returns the MM/DD/YY
const string date::ReturnDate() {
  const int MAXLEN = 80;
  char timeVar[MAXLEN];
  time_t t = time(0); // current date
  strftime(timeVar, MAXLEN, "%m/%d/%y", localtime(&t));
  return timeVar;
}

ostream & operator << (ostream &out, const date &dt) {
  out << dt.timeOut;
  return out;
}

class todo {
  private:
    string dateAdded;
    string toDoList;
    static int _id; // This will increment each time the constructor is called
  public:  
    int id = 0;
    todo(string);
    todo(string, string);
    todo(const todo &); // copy constructor
    todo & operator = (const todo &); // Assignment operator
    friend ostream & operator << (ostream &, const todo &);
};

int todo::_id = 0;

// Constructor to setup list
todo::todo(string _toDoList) {
  date timeNow;
  dateAdded = timeNow.ReturnDate();
  toDoList = _toDoList;
  this->id = _id;
  _id++;
}

// Constructor to setup list and date, use only for loading the file
todo::todo(string _toDoList, string _date) {
  dateAdded = _date;
  toDoList = _toDoList;
  this->id = _id;
  _id++;
}

// Specification A2 - Copy Constructor
todo::todo(const todo &singleItem) {
  dateAdded = singleItem.dateAdded;
  toDoList  = singleItem.toDoList;
  id        = singleItem.id;
}

// Specification A3 - Assignment operator
todo& todo::operator = (const todo &SingleItem) {
  dateAdded = SingleItem.dateAdded;
  toDoList  = SingleItem.toDoList;
  id        = SingleItem.id;
  return *this;
}

// Specification Bonus: Challenged myself, by creating a class that inherit vector from STL. This is usually frown upon but necessary because I want to use vector and operator overloading
class supervector : public std::vector<todo> { // vector is a template class that will generate based on its parameter, in this case it'll be a vector of class todo
  private:
    string SplitString(const string, const string &);
  public:
    friend ostream & operator << (ostream &out, const todo &tdo);
    const supervector operator + (const string);
    const supervector operator - (const string);
    void load();
};

// Specification A1 - Overload symbols
// Specification C1 - + Symbol
const supervector supervector::operator + (const string _toDoList) {
  supervector newvector;
  newvector = *this; // uses the vector = operator
  todo newlist(_toDoList);
  newvector.push_back(newlist); // pushes the honeydo input into the supervector class
  return newvector;
};

// Specification C3 - - symbol
const supervector supervector::operator - (const string index) {
  int _index = stoi(index);
  supervector newvector;
  newvector = *this; // uses the vector = operator
  for (auto index = newvector.begin(); index != newvector.end(); index++) {
    if (index->id == _index) {
      newvector.erase(index);
      break;
    }
  }
  return newvector;
};

// Specification Bonus: Created a function to return a string split based off argument
string supervector::SplitString(const string title, const string& str) {
  size_t found = str.find_last_of(" ");
  if (title == "todolist") {
    return str.substr(2,found-2); // Turns all words except the first word and last word
  } else if (title == "date") {
    return str.substr(found+1);   // Returns the last word of the string
  } else {
    return "";
  }
}

void supervector::load() {
  ifstream myFile("To_Do_List.txt");
  if (myFile.is_open()) {
    cout << "Found previous To_Do_List.txt file for loading\n";
    while (!myFile.eof()) { // Reads line by line
      istringstream inStream;
      string line;
      string _toDoList;
      string _date;
      string oldIndex;
      getline(myFile, line); // retrieve the entire line from file
      inStream.str(line);    // Set it up as a input stream
      inStream >> oldIndex; // unused old index
      if (oldIndex != "") { // Ignore any newlines
        _toDoList = SplitString("todolist", line);
        _date = SplitString("date", line);
        todo newlist(_toDoList, _date);
        this->push_back(newlist); // pushes the honeydo input into the supervector class       
      }
    }
    myFile.close();
  } else {
    cout << "No previous To_Do_List.txt file found for loading\n";
  }
}

// Specification B1 - Overload <<
ostream & operator << (ostream &out, const todo &tdo) {
  out << tdo.id << " " << tdo.toDoList << " " << tdo.dateAdded; // This prints the ID, List, and Date
  return out;
}

// Function Prototype
void Print(const supervector, const string);
void Header(string);

int main() {
  const string filename = "To_Do_List.txt";
  bool cont = true;
  // Program Greeting
  Header("To Do List");
  supervector honeyDos;
  honeyDos.load();

  cout << "Instructions\n"
       << "'+' Add To-Do List\n"
       << "'-' Remove ID from To-Do List\n"
       << "'?' Display All To-Do List\n"
       << "'*' Write to File and Quit Program\n";
       
  do {
    char symbol;
    string toDoList;
    istringstream inStream;
    ostringstream outputStream;
    string input;
    
    cout << "What do you want to do?: ";
    getline(cin, input);
    inStream.str(input);
    inStream >> symbol; // Gets the first char of string
    input.erase(0,2); // Removes the first 2 char of string
    switch(symbol) {
      case '+': // Add to list
        honeyDos = honeyDos + input;
        break;
      case '-': // Remove from list
        honeyDos = honeyDos - input;
        break;
      // Specification C2 - ? Symbol
      case '?': 
        for (auto i = honeyDos.begin(); i != honeyDos.end(); i++) {
          cout << *i << endl;
        }
        break;
      // Specification B3 - Quit symbol
      case '*':   
        Print(honeyDos, filename);
        cout << "Exiting program, please review your list, which is saved to " << filename << endl;
        cont = false;
        break;
      default:
        cout << "Not a valid input\n";
        break;
    }
  } while (cont);
  return 0;
}

// Specification B2 - Save to disk
void Print(const supervector _honeyDos, const string filename) {
  ofstream file;
  file.open(filename); // open for writing
  for (auto i = _honeyDos.begin(); i != _honeyDos.end(); i++) {
    file << *i << endl;
  }
  file.close();
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