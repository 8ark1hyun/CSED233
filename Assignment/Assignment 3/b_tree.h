#pragma once
#include <string>

using namespace std;

class BTree {
public:
  /////////////////////////////////////////////////////////
  //////  TODO: Implement BTree class, Add public members if required
  //////////////
  class Node {
  public:
    int *key;
    Node **child;
    Node *_parent;
    bool leaf;
    int count;

    Node(int M) {
      key = new int[M];
      child = new Node *[M + 1];
      for (int i = 0; i < M + 1; i++) {
        child[i] = NULL;
      }
      _parent = NULL;
      leaf = true;
      count = 0;
    }
  };

  BTree(int M) {
    order = M;
    _root = NULL;
  };
  ~BTree(){};

  void split_child(Node *node, Node *parent);
  void sort(Node *node);
  Node *find_max_node(Node *node);
  Node *find_min_node(Node *node);
  void merge(Node *node, int i);
  void remove_elem(Node *node, int key);
  void _postOrder(string &output, Node *cur);

  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////

  int has_elem(int key);
  int insert_elem(int key);
  int delete_elem(int key);
  string postOrder();

private:
  /////////////////////////////////////////////////////////
  //////  TODO: Add private members if required ///////////
  int order;
  Node *_root;
  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
};
