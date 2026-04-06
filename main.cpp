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

void add(Node*& head, int info);
void print(Node* head, int depth);
Node* search(Node* head, int query);
void del(Node*& head, int info);
Node* nextLargest(Node* head);
void allDone(Node* head);

int main(){
  fstream f("nums.txt");
  int fnum;
  bool done = false;
  Node* head = NULL;
  
  do{ // keep going till quit
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
      //search
    }else if(input == "search"){
      cout << "What number would you like to search for? ";
      int query;
      cin >> query;
      Node* temp = search(head, query);
      if(temp != NULL){
	cout << query << " is in the tree";
      }
      //delete
    }else if(input == "delete"){
      cout << "What number would you like to delete? ";
      int query;
      cin >> query;
      del(head,query);
      //print
    }else if(input == "print"){
      print(head, 0);
    }else if(input == "quit"){
      //leave
      done=true;
    }else{
      cout<<"Sorry, that was an invalid command" << endl;
    }
    cout << endl;
  }while(done==false);
  //close file
  f.close();

  // Delete all the nodes
  allDone(head);
  
  return 0;
}

//deletes the stuff:
void allDone(Node* head){
  if (head==NULL){
    return;}
  allDone(head->left);
  allDone(head->right);
  delete head;
}

void del(Node*& head, int info){
  if(!head){
    cout << "tree empty";
    return;
  }
  Node* current = search(head, info);
  if(current == NULL){
    return;
  }
  
  //deletes things with no leafs
  if(current->left == NULL && current->right == NULL){
    if (current->parent != NULL){
      if(current->parent->left == current){
	current->parent->left = NULL;
      }else if (current->parent->right == current){
	current->parent->right = NULL;
      }
    }else{
      head = NULL;
    }
    delete current;
    return;
  }


  //deletes things with one leaf
  if(current->left == NULL && current->right != NULL){
    if (current->parent ==NULL){
      head = current->right;
      current->right->parent = NULL;
      delete current;
      return;
    }

    if(current->parent->left == current){
      current->parent->left = current->right;
    }else{
      current->parent->right = current->right;
    }
    current->right->parent=current->parent;
    delete current;
    return;
  }

  if(current->left != NULL && current->right == NULL){
    if (current->parent ==NULL){
      head = current->left;
      current->left->parent = NULL;
      delete current;
      return;
    }
      if(current->parent->right == current){
      current->parent->right = current->left;
    }else{
      current->parent->left = current->left;
    }
    current->left->parent=current->parent;
    delete current;
    return;
    
  }



  //deletes 2 leafs
  if(current->left != NULL && current->right != NULL){
    Node* next = nextLargest(current->right);
    //if next has a right child, need to attach that child to its parent
    if(next != current->right){//if next biggest isn't hte imediet next one
      if(next->right != NULL){
	next->right->parent=next->parent;
      }
      if(next->parent->right==next){
      next->parent->right = next->right;
      }else{
	next->parent->left = next->right;
    }
      next->left=current->left;
      next->right=current->right;
    }
    
    current->left->parent = next;
    current->right->parent=next;
    next->parent=current->parent;

    //if the one being replaced is the first thinger
    if(current->parent==NULL){
      head=next;
    }else if(current->parent->right==current){
      current->parent->right=next;
    }else{
      current->parent->left=next;
    }
    delete current;
    return;
  }
}


//when calling the first time make sure you call wtvr thing you want's right child
Node* nextLargest(Node* head){
  if (head->left == NULL){
    return head;
  }
  return nextLargest(head->left);
}
  



Node* search(Node* head, int query){
  if(!head){//at end of thread and its not there
    cout << "Sorry, that number is not in the tree";
    return NULL;
  }
  //if found, return it
  if(head->data == query){
    return head;
  }else if(head->data > query){
    //recursive
    return search(head->left, query);
  }else if(head->data < query){
    return search(head->right, query);
  }else{ // debug
    cout <<"Problem!" << endl;
  }
  return NULL;
}


void add(Node*& head, int info){
  //add leafs
  if (head == NULL){
    Node* new_current = new Node();
    head = new_current;
    head->data = info;
    head->parent=NULL;
    return;
  }
  //if input is less than head and at end, add 
  if(head->data > info && head->left==NULL){
    Node* new_current = new Node();
    head->left=new_current;
    new_current->data=info;
    new_current->parent = head;
    return;
  }else if(head->data < info && head->right==NULL){
  //if input is more than head and at end, add 
    Node* new_current = new Node();
    head->right=new_current;
    new_current->data=info;
    new_current->parent = head;
    return;
  }else if(head->data > info){
  //if input is less than head and not at end
    add(head->left, info);
  }else if(head->data < info){
    add(head->right, info);
  }else{
  //if input is more than head and not at end
    cout<< "problem";
  }
}


void print(Node* current, int depth){
  if(current == NULL){ //if leaf, end that
    return;
  }
  //print right then middle then left
  print(current->right, depth+1);
  for (int i = 0; i< depth; i++){
    cout << "   ";
  }
  cout << current->data << endl;
  print(current->left, depth+1);
}
