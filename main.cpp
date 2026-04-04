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

void add(Node* head, int info);
void print(Node* head, int depth);

int main(){
  fstream f("nums.txt");
  int fnum;
  bool done = false;
  Node* head = NULL;
  
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
	  add(head,fnum);
	}
	cout <<endl;
      }else{
	add(head,num);
      }
      
    }else if(input == "search"){
      cout << "sorry, the number isn't here :(" << endl;
    }else if(input == "delete"){
      cout << "cool"<<endl;
    }else if(input == "print"){
      print(head, 0);
    }else if(input == "quit"){
      done=true;
    }else{
      cout<<"Sorry, that was an invalid command" << endl;
    }
    cout << endl;
  }while(done==false);
  
  f.close();

  // Delete all the nodes
  //  Node* current = head;
  //while(
  
  return 0;
}



void add(Node* current, int info){
  if (current == NULL){
    Node* current = new Node();
    //current->parent = NULL;//shouldn't need cuz already defined?
    current->data = info;
    return;
  }
  if(current->data > info){
    add(current->left, info);
  }else if(current->data < info){
    add(current->right, info);
  }else{
    cout<< "problem";
  }
}


void print(Node* current, int depth){
  cout<< "printed";
}
