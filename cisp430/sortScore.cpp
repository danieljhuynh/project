// Daniel Huynh
// assignment 10

#include <iostream>  // for cout
#include <string>    // for string
#include <cctype>    // for tolower
#include <iomanip>   // for output format

using namespace std;

// Specification A1 - OOP
class Gpa {
  private:
    int arraySize;
    void SwapArray(float *, float *);
    void BubbleSortScores(int);
  public:
    Gpa();
    ~Gpa();
    float* scoreArray;
    float ComputeGPA();
    char GetLetterGrade(float);
    void SetScore(int, float);
    void PrintScores();
};

Gpa::Gpa() { // constructor
  arraySize = 1; // min array size
  scoreArray = new float[arraySize];
}

Gpa::~Gpa() { // destructor
  arraySize = 0;
  delete [] scoreArray;
  scoreArray = nullptr;
}

// Function Prototype
bool isFloat(string);
void Header(string);

// Print Letter Grade
char Gpa::GetLetterGrade(float score){
  if (score >= 90) {
    return 'A';
  } else if (score >= 80) {
    return 'B';
  } else if (score >= 70) {
    return 'C';
  } else if (score >= 60) {
    return 'D';
  } else {
    return 'F';
  }
}

// Compute GPA
float Gpa::ComputeGPA() {
  float sum = 0;
  for(int i = 0; i < arraySize; i++) {
    sum += scoreArray[i];
  }
  return (sum/arraySize);
}

// Printing for scores and grades
void Gpa::PrintScores() {
  BubbleSortScores(arraySize);
  cout << "\n";
  cout << left << setw(3) << "# " << fixed << setw(7) << "Score " << setw(5) << "Grade\n";
  for(int i = 0; i < arraySize; i++) {
    cout << left << setw(3) << i+1 << fixed << setw(7) << setprecision(2) << scoreArray[i] << setw(5) << GetLetterGrade(scoreArray[i]) << endl;
  }
}

// Recursive Bubble Sort
void Gpa::BubbleSortScores(int subArraySize) {
  // Base return
  if (subArraySize == 1) {
    return;
  }
  // Iterating through entire array once, stopping at the second
  // to last element because if statement will search the last element
  for (int i=0; i < subArraySize-1; i++) {
    if (scoreArray[i] > scoreArray[i+1]) {
      // Swapping the value of the current and next element
      SwapArray(&scoreArray[i], &scoreArray[i+1]);
    }
  }
  // Decrementing recursive loop
  BubbleSortScores(subArraySize-1);
}

// Swaps the two values
void Gpa::SwapArray(float *var1, float *var2) {
  float temp;
  temp = *var1;
  *var1 = *var2;
  *var2 = temp;
}

// Dynamic Array
void Gpa::SetScore(int dataSize, float data) {
  // copying array and increasing the size by 1
  if (dataSize >= arraySize) {
    arraySize += 1; // increasing array size by 1 to maintain smallest array size
    float *temp = new float[arraySize]; // creating a new array with +1 to previous array size
    for (int i=0; i < dataSize; i++) {
      temp[i] = scoreArray[i]; // copying current array to temp array
    }
    delete [] scoreArray; // deallocate the heap of scoreArray
    scoreArray = temp; // setting new array to temp array
  }
  scoreArray[dataSize] = data; // appending new score to array
}

int main() {
  Gpa student;
  string score;
  int scoreIndex = 0;
  bool cont = true;

  // Program Greeting
  Header("Welcome to GPA Analyzer");
  cout << "When finish entering your scores, type 'calc'" << endl;
  // Enter the scores
  do {
    cout << "Enter score: ";
    cin >> score;

    // Since tolower only works on chars, I need a for loop to iterate through the string
    for (auto& c: score)
      c = tolower(c);

    if (score == "calc") {
      student.PrintScores();
      cont = false;
    } else if (isFloat(score)) {
      if (stof(score) < 0) {
        cout << "You can't have a negative score\n";
        cont = true;
      } else {
        student.SetScore(scoreIndex, stof(score));
        scoreIndex++; // increment the array index
        cont = true;
      }
    } else {
      cout << "Not a valid score:\n";
      cont = true;
    }
  } while (cont);
  Header("Average GPA");
  cout << student.ComputeGPA() << " " <<  student.GetLetterGrade(student.ComputeGPA()) << endl << endl;
  return 0;
}

// Allow floats for scores not just whole number
bool isFloat(string value) {
  try {
    stof(value);
    return true;
  }
  catch(const exception& e) {
    return false;
  }
}

// Template for printing headers
void Header(string output) {
  string separator; // for header separator
  separator.assign(output.length(), '=');
  
  // Since tolower only works on chars, I need a for loop to iterate through the string
  for (auto& c: output) 
    c = toupper(c);
  cout << "\n"      << output << endl;
  cout << separator << endl   << endl;
}