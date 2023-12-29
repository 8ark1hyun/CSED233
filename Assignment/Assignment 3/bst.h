#pragma once
#include "tree.h"

using namespace std;

class BinarySearchTree : public BinaryTree {
public:
  BinarySearchTree(){};
  ~BinarySearchTree(){};

  int insert(int key);
  int remove(int key);

private:
  /////////////////////////////////////////////////////////
  //////  TODO: Add private members if required ///////////
  int getHeight(Node *node);
  Node *search(int key);
  Node *find_min_key(Node *pos);
  Node *find_max_key(Node *pos);
  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
};