#include "dabst.h"
#include "bst.h"
#include "tree.h"
#include <iostream>
#include <string>

using namespace std;

string DABSTree::inOrder() {
  string output;
  _inOrder(output, _root);
  if (!output.empty())
    output.pop_back();
  return output;
}

string DABSTree::preOrder() {
  string output;
  _preOrder(output, _root);
  if (!output.empty())
    output.pop_back();
  return output;
}

void DABSTree::_inOrder(string &output, Node *cur) {
  if (cur == NULL)
    return;
  _inOrder(output, cur->left);
  output.append(cur->print_key());
  output.append("(");
  output.append(cur->print_count());
  output.append(")");
  output.append(" ");
  _inOrder(output, cur->right);
}

void DABSTree::_preOrder(string &output, Node *cur) {
  if (cur == NULL)
    return;
  output.append(cur->print_key());
  output.append("(");
  output.append(cur->print_count());
  output.append(")");
  output.append(" ");
  _preOrder(output, cur->left);
  _preOrder(output, cur->right);
}

int DABSTree::insert(int key) {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////

  Node *node = search(key);

  if (node == NULL) {
    int value = BinarySearchTree::insert(key);
    return value;
  } else {
    node->count++;
    return 0;
  }

  ///////////      End of Implementation      /////////////
  ///////////////////////////////////////////////////////
}

int DABSTree::remove(int key) {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////

  Node *node = search(key);

  if(node == NULL)
  {
    return -1;
  } else if(node->count > 1)
  {
    node->count--;
    return 0;
  } else 
  {
    int value = BinarySearchTree::remove(key);
    return value;
  }
  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////
//////////  TODO: Implement From Here      //////////////

Node *DABSTree::search(int key) {

  Node *temp = _root;

  while (temp != NULL) {
    if (temp->key > key) {
      temp = temp->left;
    } else if (temp->key < key) {
      temp = temp->right;
    } else if (temp->key == key) {
      break;
    }
  }

  return temp;
}

///////////      End of Implementation      /////////////
/////////////////////////////////////////////////////////