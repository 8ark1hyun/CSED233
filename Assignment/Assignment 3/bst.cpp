#include "bst.h"
#include "tree.h"
#include <iostream>
#include <string>

using namespace std;

int BinarySearchTree::insert(int key) {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////

  Node *new_node = new Node(key);

  if (_root == NULL) {
    _root = new_node;
  } else {
    Node *pos = _root;

    while (pos != NULL) {
      if (pos->key > key) {
        if (pos->left == NULL) {
          new_node->parent = pos;
          pos->left = new_node;
          break;
        } else {
          pos = pos->left;
        }
      } else if (pos->key < key) {
        if (pos->right == NULL) {
          new_node->parent = pos;
          pos->right = new_node;
          break;
        } else {
          pos = pos->right;
        }
      } else {
        return -1;
      }
    }
  }

  new_node->height = getHeight(new_node);

  return 0;

  ///////////      End of Implementation      /////////////
  ///////////////////////////////////////////////////////
}

int BinarySearchTree::remove(int key) {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////

  if (_root == NULL) {
    return -1;
  } else {
    Node *pos = search(key);

    if (pos == NULL) {
      return -1;
    } else {
      if (pos->left == NULL && pos->right == NULL) {
        if (pos == _root) {
          delete pos;
        } else {
          if (pos->parent->left == pos) {
            pos->parent->left = NULL;
          } else if (pos->parent->right == pos) {
            pos->parent->right = NULL;
          }
        }
        delete pos;
      } else if (pos->left != NULL && pos->right == NULL) {
        if (pos == _root) {
          Node *max = find_max_key(pos->left);
          int key_value = max->key;
          int count_value = max->count;

          remove(key_value);

          pos->key = key_value;
          pos->count = count_value;
        } else {
          if (pos->parent->left == pos) {
            pos->parent->left = pos->left;
            delete pos;
          } else if (pos->parent->right == pos) {
            pos->parent->right = pos->left;
            delete pos;
          }
        }
      } else if (pos->left == NULL && pos->right != NULL) {
        if (pos == _root) {
          Node *min = find_min_key(pos->right);
          int key_value = min->key;
          int count_value = min->count;

          remove(key_value);

          pos->key = key_value;
          pos->count = count_value;
        } else {
          if (pos->parent->left == pos) {
            pos->parent->left = pos->right;
            delete pos;
          } else if (pos->parent->right == pos) {
            pos->parent->right = pos->right;
            delete pos;
          }
        }
      } else if (pos->left != NULL && pos->right != NULL) {
        Node *min = find_min_key(pos->right);
        int key_value = min->key;
        int count_value = min->count;

        remove(key_value);

        pos->key = key_value;
        pos->count = count_value;
      }

      return 0;
    }
  }

  return 0;
  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////
//////////  TODO: Implement From Here      //////////////

int BinarySearchTree::getHeight(Node *node) {
  if (node == NULL) {
    return 0;
  } else {
    int left_height = getHeight(node->left);
    int right_height = getHeight(node->right);

    return 1 + (left_height > right_height ? left_height : right_height);
  }
}

Node *BinarySearchTree::search(int key) {

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

Node *BinarySearchTree::find_min_key(Node *root) {

  Node *temp = root;

  while (temp->left != NULL) {
    temp = temp->left;
  }

  return temp;
}

Node *BinarySearchTree::find_max_key(Node *root) {

  Node *temp = root;

  while (temp->right != NULL) {
    temp = temp->right;
  }

  return temp;
}

///////////      End of Implementation      /////////////
/////////////////////////////////////////////////////////
