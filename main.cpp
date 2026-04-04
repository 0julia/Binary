#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;

struct Node{
  Node* left=NULL;
  Node* right=NULL;
  int data;
  Node* parent=NULL;
};

int main(){
  fstream f("nums.txt");
  int fnum;
  bool done = false;
  
  do{
    string input;
    cout << "What would you like to do?(add, search, delete, print, quit) ";
    cin >> input;

    if(input == "add"){
      //ask input
      cout << "input a number to add please (If you would like to insert a number input '-1') ";
      int num;
      cin >> num;
      if (num == -1){
	while (f >> fnum){
	  cout << fnum << " ";
	}
	cout <<endl;
      }
    }else if(input == "search"){
      cout << "sorry, the number isn't here :(" << endl;
    }else if(input == "delete"){
      cout << "cool"<<endl;
    }else if(input == "print"){
      cout << "You printed!" <<endl;
    }else if(input == "quit"){
      done=true;
    }else{
      cout<<"Sorry, that was an invalid command" << endl;
    }
    cout << endl;
  }while(done==false);
  
  f.close();
  return 0;
}
