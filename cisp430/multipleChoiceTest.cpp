// assignment1.cpp
// Daniel Huynh, CISP 430
// 2/20/2020

#include <iostream>  // for cout
#include <string>    // for string
#include <cctype>    // for tolower/toupper and isdigit
#include <fstream>   // for stream class to read from files
#include <ctime>     // for time
#include <cstdlib>   // for rand
#include <string.h>  // for strstr

using namespace std;

void createRandomArray(int [], const int);

int main() {
  srand(time(0));     // to randomize the seed
  string line;
  ifstream myfile("question.txt");
  static const int QUESTION_NUM = 10;
  static const int CHOICE_NUM = 4;
  string choiceArray[QUESTION_NUM][CHOICE_NUM];
  string questionArray[QUESTION_NUM];
  string correctAnswerArray[QUESTION_NUM];
  int score = 0;
  
  // reads the file
  if(myfile.is_open()) {
    int i = -1;                               // setting this to -1 because the first question will increment i
    int j = 0;
    while(getline(myfile,line)) {
      if(strstr(line.c_str(),"?")) {          // if the line contains "?"
        i++;
        j=0;
        questionArray[i] = line;              // saves the question
      } else if(strstr(line.c_str(),"*")) {   // if the line contains "*"
        line.erase(line.end()-2);             // removes the last character, in this case the "*"
        correctAnswerArray[i] = line;         // Saves the correct answer
        choiceArray[i][j] = line;             // Saves the question and multiple choice
        j++;
      } else {
        choiceArray[i][j] = line;
        j++;
      }
    }
    myfile.close(); // closes the file
  } else {
    cout << "Unable to open file question.txt";  
  }
  
  // for player to take exam
  cout << "Welcome Player\n";
  int dupArray[QUESTION_NUM];
  createRandomArray(dupArray, QUESTION_NUM);
  for(int i =0; i < QUESTION_NUM; i++) {
    int answer;
    cout << "\nQuestion " << i+1 << ": " << questionArray[dupArray[i]] << endl;
    for(int j = 0; j < CHOICE_NUM; j++) {
      cout << "  " << choiceArray[dupArray[i]][j] << endl;
    }
    cout << "What's your answer? ";
    cin >> answer;
    if (answer == stoi(correctAnswerArray[dupArray[i]])) {
      cout << "You are correct!\n";
      score++;
    } else {
      cout << "Sorry, you are incorrect!\n";
    }
  }
  cout << "\nThanks for playing, your score is: " << score << endl;
  return 0;
}

void createRandomArray(int dupArray[], const int size) {
  for(int i = 0; i < size; i++) {
    bool isValid = false;
    int randNum;
    while(!isValid) {
      randNum = rand() % size; // generates a number between 0 to 9
      for(int j = 0; j <= i; j++) {
        if(dupArray[j] == randNum) {
          isValid = false;
          break;
        } else {
          isValid = true;
        }
      }
    }
    dupArray[i] = randNum;
  }
}