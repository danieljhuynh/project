// Daniel Huynh
// Hashing

#include<iostream>
#include<string>
using namespace std;

#define SIZE 20

struct DataItem {
  int data;   
  int key;
};

struct DataItem* hashArray[SIZE]; 
struct DataItem* dummyItem;
struct DataItem* item;

int hashCode(int key) {
  return key % SIZE;
}

struct DataItem *search(int key) {
  //get the hash 
  int hashIndex = hashCode(key);  
  
  //move in array until an empty 
  while(hashArray[hashIndex] != NULL) {
   if(hashArray[hashIndex]->key == key)
     return hashArray[hashIndex]; 
   //go to next cell
   ++hashIndex;
   //wrap around the table
   hashIndex %= SIZE;
  }
  return NULL;        
}

struct DataItem *remove(int key) {
  int hashIndex = hashCode(key);
  
  if(hashArray[hashIndex] != NULL) {
    cout << "Removing key: " << hashArray[hashIndex]->key << endl;
    cout << "Removing data: " << hashArray[hashIndex]->data << endl;
    hashArray[hashIndex]->key = -1;
    hashArray[hashIndex]->data = -1;
  }
  else {
    cout << "Sorry, key: " << key << " doesn't exist in the hash table" << endl;
  }
  return NULL;
}

struct DataItem *remove(int key, int value) {
  int hashIndex = hashCode(key);
  
  if(hashArray[hashIndex] != NULL) {
    cout << "Removing key: " << hashArray[hashIndex]->key << endl;
    cout << "Removing data: " << hashArray[hashIndex]->data << endl;
    if (hashArray[hashIndex]->data == value) {
      cout << "Removing key: " << hashArray[hashIndex]->key << endl;
      cout << "Removing data: " << hashArray[hashIndex]->data << endl;
      hashArray[hashIndex]->key = -1;
      hashArray[hashIndex]->data = -1;
    } else {
    cout << "Sorry, found the key " << hashArray[hashIndex]->key << " but the value doesn't match " << value << endl;
    }
  }
  else {
    cout << "Sorry, key: " << key << " doesn't exist in the hash table" << endl;
  }
  return NULL;
}

void insert(int key,int data) {
  struct DataItem *item = (struct DataItem*) malloc(sizeof(struct DataItem));
  item->data = data;  
  item->key = key;

  //get the hash 
  int hashIndex = hashCode(key);

  //move in array until an empty or deleted cell
  while(hashArray[hashIndex] != NULL && hashArray[hashIndex]->key != -1) {
    //go to next cell
    ++hashIndex;
	
    //wrap around the table
    hashIndex %= SIZE;
  }
  hashArray[hashIndex] = item;
}

void display() {
  int i = 0;
  for(i = 0; i<SIZE; i++) {
    if(hashArray[i] != NULL && hashArray[i]->key != -1)
      cout << hashArray[i]->key << " " << hashArray[i]->data << endl;
    else
      cout<<"";
  }
  cout<<"\n";
}

int main() {
  bool cont = true;
  int option;
  dummyItem = (struct DataItem*) malloc(sizeof(struct DataItem));
  dummyItem->data = -1;  
  dummyItem->key = -1; 
  
  while (cont) {
    int key, data;
    cout << "What do you want to do?" << endl;
    cout << " \t 1.Insert " << endl;
    cout << " \t 2.Delete(key)" << endl;
    cout << " \t 3.Delete(key and value)" << endl;
    cout << " \t 4.Search " << endl;
    cout << " \t 5.Display " << endl;
    cout << " \t 6.Exit: " << endl;
    cout << " \t ";
    cin >> option;
    switch(option) {
      case 1: // Insert
        cout << "What key to add? ";
        cin >> key;
        cout << "What's the data to add? ";
        cin >> data;
        insert(key, data);
        break;
      case 2: // Delete key
        cout << "What key to delete? ";
        cin >> key;
        remove(key);
        break;
      case 3: // Delete key and value
        cout << "What key to delete? ";
        cin >> key;
        cout << "What data to delete? ";
        cin >> data;
        remove(key,data);
        break;
      case 4: // Search
        cout << "What key do you want to search for? ";
        cin >> key;
        item = search(key);
        if(item != NULL) {
           cout << "Element found: " << item->data << endl;
        } else {
           cout << "Element not found" << endl;
        }
        break;
      case 5: // Display
        display();
        break;
      case 6: // Exit
        cont = false;
        break;
    }
  }
}
