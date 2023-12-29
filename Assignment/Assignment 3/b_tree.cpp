#include "b_tree.h"
#include <iostream>
#include <string>

using namespace std;

/*  Write your codes for other b_tree functions  */

void BTree::split_child(Node *node, Node *parent) {
  int mid = order / 2;
  Node *left = new Node(order);
  Node *right = new Node(order);

  int i = 0;
  if (order % 2 == 0) {
    for (int j = 0; j < mid - 1; j++) {
      left->key[j] = node->key[i];
      left->count++;
      i++;
    }
    i++;
    for (int j = 0; j < order - mid; j++) {
      right->key[j] = node->key[i];
      right->count++;
      i++;
    }
  } else if (order % 2 == 1) {
    for (int j = 0; j < mid; j++) {
      left->key[j] = node->key[i];
      left->count++;
      i++;
    }
    i++;
    for (int j = 0; j < order - mid - 1; j++) {
      right->key[j] = node->key[i];
      right->count++;
      i++;
    }
  }

  if (node->leaf == false) {
    if (order % 2 == 0) {
      i = 0;
      for (int j = 0; j < mid; j++) {
        left->child[j] = node->child[i];
        node->child[i]->_parent = left;
        i++;
      }
      for (int j = 0; j < order + 1 - mid; j++) {
        right->child[j] = node->child[i];
        node->child[i]->_parent = right;
        i++;
      }
      left->leaf = false;
      right->leaf = false;
    } else if (order % 2 == 1) {
      i = 0;
      for (int j = 0; j < mid + 1; j++) {
        left->child[j] = node->child[i];
        node->child[i]->_parent = left;
        i++;
      }
      for (int j = 0; j < order - mid; j++) {
        right->child[j] = node->child[i];
        node->child[i]->_parent = right;
        i++;
      }
      left->leaf = false;
      right->leaf = false;
    }
  }

  if (parent == NULL) {
    Node *root = new Node(order);
    if (order % 2 == 0) {
      root->key[0] = node->key[mid - 1];
      root->count++;
    } else if (order % 2 == 1) {
      root->key[0] = node->key[mid];
      root->count++;
    }
    left->_parent = root;
    root->child[0] = left;
    right->_parent = root;
    root->child[1] = right;
    root->leaf = false;
    _root = root;

    delete node;
  } else {
    for (i = 0; i < parent->count; i++) {
      if (order % 2 == 0) {
        if (parent->key[i] < node->key[mid - 1]) {
          continue;
        } else {
          break;
        }
      } else if (order % 2 == 1) {
        if (parent->key[i] < node->key[mid]) {
          continue;
        } else {
          break;
        }
      }
    }

    int arr[order];
    for (int a = 0; a < parent->count; a++) {
      arr[a] = parent->key[a];
    }

    int k = 0;
    if (order % 2 == 0) {
      for (int j = 0; j < parent->count + 1; j++) {
        if (j != i) {
          parent->key[j] = arr[k];
          k++;
        } else {
          parent->key[j] = node->key[mid - 1];
        }
      }
      parent->count++;
    } else if (order % 2 == 1) {
      for (int j = 0; j < parent->count + 1; j++) {
        if (j != i) {
          parent->key[j] = arr[k];
          k++;
        } else {
          parent->key[j] = node->key[mid];
        }
      }
      parent->count++;
    }

    Node *_arr[order + 1];
    for (int a = 0; a < parent->count; a++) {
      _arr[a] = parent->child[a];
    }

    k = 0;
    for (int j = 0; j < parent->count + 1; j++) {
      if (j != i) {
        parent->child[j] = _arr[k];
        k++;
      } else {
        left->_parent = parent;
        parent->child[j] = left;
        right->_parent = parent;
        parent->child[j + 1] = right;
        j++;
        k++;
      }
    }

    if (parent->count == order) {
      split_child(parent, parent->_parent);
    }
  }

  return;
}

void BTree::sort(Node *node) {
  for (int i = 0; i < node->count; i++) {
    int value = node->key[i];
    int j = i - 1;
    while ((j >= 0) && (node->key[j] > value)) {
      node->key[j + 1] = node->key[j];
      j--;
    }
    node->key[j + 1] = value;
  }

  return;
}

BTree::Node *BTree::find_max_node(Node *node) {
  Node *temp = node;

  while (temp->leaf == false) {
    temp = temp->child[temp->count];
  }

  return temp;
}

BTree::Node *BTree::find_min_node(Node *node) {
  Node *temp = node;

  while (temp->leaf == false) {
    temp = temp->child[0];
  }

  return temp;
}

void BTree::merge(Node *node, int i) {
  Node *left_child = node->child[i];
  Node *right_child = node->child[i + 1];

  int mid;
  if (order % 2 == 0) {
    mid = order / 2;
  } else if (order % 2 == 1) {
    mid = order / 2 + 1;
  }

  left_child->key[mid - 1] = node->key[i];

  for (int j = 0; j < right_child->count; ++j)
    left_child->key[j + mid] = right_child->key[j];

  if (!left_child->leaf) {
    for (int j = 0; j <= right_child->count; ++j)
      left_child->child[j + mid] = right_child->child[j];
  }

  for (int j = i + 1; j < node->count; ++j)
    node->key[j - 1] = node->key[j];

  for (int j = i + 2; j <= node->count; ++j)
    node->child[j - 1] = node->child[j];

  left_child->count += right_child->count + 1;
  node->count--;

  delete right_child;

  return;
}

void BTree::remove_elem(Node *node, int key) {

  int i;
  for (i = 0; i < node->count; i++) {
    if (node->key[i] < key) {
      continue;
    } else {
      break;
    }
  }

  int mid;
  if (order % 2 == 0) {
    mid = order / 2;
  } else if (order % 2 == 1) {
    mid = order / 2 + 1;
  }

  if (i < node->count && node->key[i] == key) {
    if (node->leaf == true) {
      for (int j = i + 1; j < node->count; ++j) {
        node->key[j - 1] = node->key[j];
      }

      node->count--;
    } else {
      int k = node->key[i];

      if (node->child[i]->count >= mid) {
        Node *max = find_max_node(node->child[i]);
        node->key[i] = max->key[max->count - 1];
        remove_elem(node->child[i], node->key[i]);
      } else if (node->child[i + 1]->count >= mid) {
        Node *min = find_min_node(node->child[i + 1]);
        node->key[i] = min->key[0];
        remove_elem(node->child[i + 1], node->key[i]);
      } else {
        merge(node, i);
        remove_elem(node->child[i], k);
      }
    }
  } else {
    int x;
    if (i == node->count) {
      x = 1;
    } else {
      x = -1;
    }

    if (node->child[i]->count < mid) {
      if (i != 0 && node->child[i - 1]->count >= mid) {
        for (int j = node->child[i]->count - 1; j >= 0; --j) {
          node->child[i]->key[j + 1] = node->child[i]->key[j];
        }

        if (node->child[i]->leaf == false) {
          for (int j = node->child[i]->count; j >= 0; --j) {
            node->child[i]->child[j + 1] = node->child[i]->child[j];
          }
        }

        node->child[i]->key[0] = node->key[i - 1];

        if (node->child[i]->leaf == false) {
          node->child[i]->child[0] =
              node->child[i - 1]->child[node->child[i - 1]->count];
        }

        node->key[i - 1] =
            node->child[i - 1]->key[node->child[i - 1]->count - 1];

        node->child[i]->count++;
        node->child[i - 1]->count--;
      } else if (i != node->count && node->child[i + 1]->count >= mid) {
        node->child[i]->key[node->child[i]->count] = node->key[i];

        if (node->child[i]->leaf == false) {
          node->child[i]->child[node->child[i]->count + 1] =
              node->child[i + 1]->child[0];
        }

        node->key[i] = node->child[i + 1]->key[0];

        for (int j = 1; j < node->child[i + 1]->count; ++j) {
          node->child[i + 1]->key[j - 1] = node->child[i + 1]->key[j];
        }

        if (node->child[i + 1]->leaf == false) {
          for (int j = 1; j <= node->child[i + 1]->count; ++j) {
            node->child[i + 1]->child[j - 1] = node->child[i + 1]->child[j];
          }
        }

        node->child[i]->count++;
        node->child[i + 1]->count--;
      } else {
        if (i != node->count) {
          merge(node, i);
        } else {
          merge(node, i - 1);
        }
      }
    }
    if (x == 1 && i > node->count) {
      remove_elem(node->child[i - 1], key);
    } else {
      remove_elem(node->child[i], key);
    }
  }
  return;
}

void BTree::_postOrder(string &output, Node *cur) {
  string answer;

  if (cur == NULL) {
    return;
  }

  for (int i = 0; i < cur->count; i++) {
    if (cur->leaf == false) {
      _postOrder(output, cur->child[i]);
    }
    if (answer == "") {
      if (output == "") {
        answer += "[";
      } else {
        answer += " [";
      }
    }
    answer += to_string(cur->key[i]);
    if (i < cur->count - 1) {
      answer += ", ";
    } else if (i == cur->count - 1) {
      answer += "]";
    }
  }

  if (cur->leaf == false) {
    _postOrder(output, cur->child[cur->count]);
  }
  output += answer;
}

///////////      End of Implementation      /////////////
/////////////////////////////////////////////////////////

string BTree::postOrder() {
  /*  Write your codes for b_tree functions  */
  string output;

  if (_root->count == 0 && _root->leaf == true) {
    output = "-1";
    return output;
  }
  _postOrder(output, _root);
  return output;
  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}

int BTree::has_elem(int key) {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////
  Node *node = _root;
  while (node != NULL) {
    int i;
    for (i = 0; i < node->count; i++) {
      if (key < node->key[i]) {
        break;
      } else if (key == node->key[i]) {
        return 0;
      } else {
        continue;
      }
    }

    node = node->child[i];
  }

  return 1;
  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}

int BTree::insert_elem(int key) {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////
  Node *node;

  if (_root == NULL) {
    node = new Node(order);
    node->key[0] = key;
    node->count++;
    _root = node;
    return 0;
  } else {
    node = _root;

    while (!(node->leaf)) {
      int i;
      for (i = 0; i < node->count; i++) {
        if (key < node->key[i]) {
          break;
        } else {
          continue;
        }
      }
      node = node->child[i];
    }

    node->key[node->count] = key;
    node->count++;
    sort(node);

    if (node->count == order) {
      split_child(node, node->_parent);
    }
  }

  return 0;
  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}

int BTree::delete_elem(int key) {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////

  remove_elem(_root, key);

  if (_root->count == 0) {
    Node *temp = _root;
    if (_root->leaf) {
      _root = NULL;
    } else {
      _root = _root->child[0];
    }
    delete temp;
  }

  return 0;
  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}
