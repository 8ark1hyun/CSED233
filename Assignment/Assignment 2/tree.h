#pragma once
#include <string>

using namespace std;

struct Node {
  Node(char input_value) : value(input_value), left(NULL), right(NULL) {}
  char value;
  Node *left;
  Node *right;
};

class BinaryTree {
public:
  BinaryTree() { _root = NULL; };
  ~BinaryTree() {
    delete[] _root;
    _root = NULL;
  };
  void buildFromString(const char *data);

  string preOrder(int node_value);
  string postOrder(int node_value);
  string inOrder(int node_value);
  int getDepth(int node_value);
  bool isReverseComplete();

private:
  Node *_root;
  Node *_buildFromString(const char *data, int start, int end);
  /////////////////////////////////////////////////////////
  //////  TODO: Add Private members if required ///////////
  string pre_str;
  int depth = 0;
  int cur_depth = 0;
  int height = 0;
  int cur_height = 0;
  bool true_or_false = true;
  int check[100] = {0};
  int index = 0;
  void search_root(Node *root, int node_value);
  void _preOrder(Node *root);
  void _postOrder(Node *root);
  void _inOrder(Node *root);
  void _getDepth(Node *root, int node_value);
  int _getMaxHeight(Node *root);
  void _isReverseComplete(Node *root);
  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
};
