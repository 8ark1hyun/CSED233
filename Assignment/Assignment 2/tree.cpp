#include "tree.h"
#include <cstring>
#include <iostream>
#include <string>

using namespace std;

/* This is given function. DO NOT MODIFY THIS FUNCTION */
int findIndex(const char *str, int start, int end) {
  if (start > end)
    return -1;

  string s;

  for (int i = start; i <= end; i++) {

    // if open parenthesis, push it
    if (str[i] == '(')
      s.push_back(str[i]);

    // if close parenthesis
    else if (str[i] == ')') {
      if (s.back() == '(') {
        s.pop_back();

        if (!s.length())
          return i;
      }
    }
  }
  // if not found return -1
  return -1;
}

/* This is given function. DO NOT MODIFY THIS FUNCTION */
Node *BinaryTree::_buildFromString(const char *data, int start, int end) {
  if (start > end)
    return NULL;

  Node *root = new Node(data[start]);
  int index = -1;

  if (start + 1 <= end && data[start + 1] == '(')
    index = findIndex(data, start + 1, end);

  if (index != -1) {
    root->left = _buildFromString(data, start + 2, index - 1);
    root->right = _buildFromString(data, index + 2, end - 1);
  }
  return root;
}

/* This is given function. DO NOT MODIFY THIS FUNCTION */
void BinaryTree::buildFromString(const char *data) {
  Node *root = _buildFromString(data, 0, strlen(data) - 1);
  _root = root;
}

string BinaryTree::preOrder(int node_value) {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////

  search_root(_root, node_value);

  if (int(_root->value) - 48 != node_value) {
    return "error";
  } else {
    _preOrder(_root);
    return pre_str;
  }

  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}

string BinaryTree::postOrder(int node_value) {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////

  search_root(_root, node_value);

  if (int(_root->value) - 48 != node_value) {
    return "error";
  } else {
    _postOrder(_root);
    return pre_str;
  }

  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}

string BinaryTree::inOrder(int node_value) {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////

  search_root(_root, node_value);

  if (int(_root->value) - 48 != node_value) {
    return "error";
  } else {
    _inOrder(_root);
    return pre_str;
  }

  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}

int BinaryTree::getDepth(int node_value) {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////

  _getDepth(_root, node_value);

  if (int(_root->value) - 48 != node_value) {
    return -1;
  } else {
    return depth;
  }

  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}

bool BinaryTree::isReverseComplete() {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////

  height = _getMaxHeight(_root) - 1;

  _isReverseComplete(_root);

  int leaf_num = 1;
  for (int i = 0; i < height; i++) {
    leaf_num = leaf_num * 2;
  }

  if (check[0] == 0) {
    true_or_false = false;
  } else {
    for (int i = 1; i < leaf_num; i++) {
      if (check[i] == 1 && check[i - 1] == 0) {
        true_or_false = false;
        break;
      } else if (check[i] == 0) {
        continue;
      }
    }
  }

  if (true_or_false == true) {
    return true;
  }

  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
  return false;
}

/////////////////////////////////////////////////////////
//////////  TODO: Implement From Here      //////////////

void BinaryTree::search_root(Node *root, int node_value) {

  if (root == NULL) {
    return;
  }

  if (int(root->value) - 48 == node_value) {
    _root = root;
    return;
  }

  search_root(root->left, node_value);
  search_root(root->right, node_value);
}

void BinaryTree::_preOrder(Node *root) {

  if (root == NULL) {
    return;
  }

  pre_str += root->value;
  pre_str += " ";
  _preOrder(root->left);
  _preOrder(root->right);
}

void BinaryTree::_postOrder(Node *root) {

  if (root == NULL) {
    return;
  }

  _postOrder(root->left);
  _postOrder(root->right);
  pre_str += root->value;
  pre_str += " ";
}

void BinaryTree::_inOrder(Node *root) {

  if (root == NULL) {
    return;
  }

  _inOrder(root->left);
  pre_str += root->value;
  pre_str += " ";
  _inOrder(root->right);
}

void BinaryTree::_getDepth(Node *root, int node_value) {

  if (root == NULL) {
    return;
  }

  if (int(root->value) - 48 == node_value) {
    _root = root;
    depth = cur_depth;
    return;
  }

  cur_depth++;
  _getDepth(root->left, node_value);
  _getDepth(root->right, node_value);
  cur_depth--;
}

int BinaryTree::_getMaxHeight(Node *root) {

  int left_height = 0;
  int right_height = 0;

  if (root == NULL) {
    return 0;
  }

  left_height = _getMaxHeight(root->left);
  right_height = _getMaxHeight(root->right);

  return ++(left_height > right_height ? left_height : right_height);
}

void BinaryTree::_isReverseComplete(Node *root) {

  if (cur_height == height && root == NULL) {
    check[index] = 0;
    index++;
    return;
  } else if (cur_height == height && root != NULL) {
    check[index] = 1;
    index++;
    return;
  }

  cur_height++;
  _isReverseComplete(root->right);
  _isReverseComplete(root->left);
  cur_height--;

  return;
}

///////////      End of Implementation      /////////////
/////////////////////////////////////////////////////////
