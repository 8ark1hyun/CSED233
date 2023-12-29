#include "avl.h"
#include "bst.h"
#include "tree.h"
#include <iostream>
#include <string>

using namespace std;

/////////////////////////////////////////////////////////
//////////  TODO: Implement From Here      //////////////

Node *AVLTree::search(int key) {

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

int AVLTree::getHeight(Node *node) {
  if (node == NULL) {
    return -1;
  } else {
    int left_height = getHeight(node->left);
    int right_height = getHeight(node->right);

    return 1 + (left_height > right_height ? left_height : right_height);
  }
}

int AVLTree::BalanceFactor(Node *node) {
  return getHeight(node->left) - getHeight(node->right);
}

void AVLTree::Balance(Node *node, int key) {
  int bf = BalanceFactor(node);

  if (bf > 1) {
    if (key < node->left->key) {
      node = right_rotation(node);
    } else if (key > node->left->key) {
      node->left = left_rotation(node->left);
      node = right_rotation(node);
    }
  } else if (bf < -1) {
    if (key > node->right->key) {
      node = left_rotation(node);
    } else if (key < node->right->key) {
      node->right = right_rotation(node->right);
      node = left_rotation(node);
    }
  }
}

Node *AVLTree::left_rotation(Node *node) {

  Node *temp = node->right;

  if (node == _root) {
    _root = temp;
  } else {
    if (node->parent->left == node) {
      node->parent->left = temp;
    } else if (node->parent->right == node) {
      node->parent->right = temp;
    }
  }

  node->right = temp->left;
  if (temp->left != NULL) {
    temp->left->parent = node;
  }
  temp->left = node;
  temp->parent = node->parent;
  node->parent = temp;

  int left_height;
  int right_height;

  left_height = getHeight(node->left);
  right_height = getHeight(node->right);

  node->height = 1 + (left_height > right_height ? left_height : right_height);

  left_height = getHeight(temp->left);
  right_height = getHeight(temp->right);

  temp->height = 1 + (left_height > right_height ? left_height : right_height);

  return temp;
}

Node *AVLTree::right_rotation(Node *node) {

  Node *temp = node->left;

  if (node == _root) {
    _root = temp;
  } else {
    if (node->parent->left == node) {
      node->parent->left = temp;
    } else if (node->parent->right == node) {
      node->parent->right = temp;
    }
  }

  node->left = temp->right;
  if (temp->right != NULL) {
    temp->right->parent = node;
  }
  temp->right = node;
  temp->parent = node->parent;
  node->parent = temp;

  int left_height;
  int right_height;

  left_height = getHeight(node->left);
  right_height = getHeight(node->right);

  node->height = 1 + (left_height > right_height ? left_height : right_height);

  left_height = getHeight(temp->left);
  right_height = getHeight(temp->right);

  temp->height = 1 + (left_height > right_height ? left_height : right_height);

  return temp;
}

Node *AVLTree::find_pivot_node(Node *node) {

  while (node != NULL) {
    int bf = BalanceFactor(node);

    if (!(bf >= -1 && bf <= 1)) {
      return node;
    } else {
      node = node->parent;
    }
  }

  return node;
}

///////////      End of Implementation      /////////////
/////////////////////////////////////////////////////////

int AVLTree::insert(int key) {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////

  int i = BinarySearchTree::insert(key);

  if (i == -1) {
    return -1;
  } else {
    Node *new_node = search(key);
    Node *pivot = find_pivot_node(new_node);
    if (pivot != NULL) {
      Balance(pivot, key);
    }
    return 0;
  }

  ///////////      End of Implementation      /////////////
  ///////////////////////////////////////////////////////
}

int AVLTree::remove(int key) {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////

  Node *deleted_node = search(key);
  if (deleted_node == NULL) {
    return -1;
  } else if (deleted_node == _root) {
    int i = BinarySearchTree::remove(key);
    return i;
  } else {
    Node *pivot = deleted_node->parent;

    int i = BinarySearchTree::remove(key);
    pivot = find_pivot_node(pivot);
    if (pivot != NULL) {
      Balance(pivot, key);
    }
    return 0;
  }

  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}
