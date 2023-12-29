#pragma once
#include "bst.h"

using namespace std;

class AVLTree : public BinarySearchTree {
public:
  AVLTree(){};
  ~AVLTree(){};

  int insert(int key);
  int remove(int key);

private:
  /////////////////////////////////////////////////////////
  //////  TODO: Add private members if required ///////////

  Node* search(int key);
  int getHeight(Node* node);
  int BalanceFactor(Node *node);
  void Balance(Node* node, int key);
  Node* left_rotation(Node *node);
  Node* right_rotation(Node *node);
  Node* find_pivot_node(Node* node);

  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
};