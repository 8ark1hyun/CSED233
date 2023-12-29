#pragma once
#include <string>

using namespace std;

class MultiNode {
public:
    MultiNode() : key1(0), key2(0), height(0), left(NULL), middle(NULL), right(NULL) {}
    int key1;
    int key2;
    int height;
    MultiNode *left;
    MultiNode *middle;
    MultiNode *right;
    /* Add public members if required*/

    string print_key() {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
        string keys = "";

        string key1_str;
        string key2_str;

        if(key1 == 0)
        {
          key1_str = "";
        } else
        {
          key1_str = to_string(key1);
        }
      
        if(key2 == 0)
        {
          key2_str = "";
        } else
        {
          key2_str = to_string(key2);
        }
      
        keys = keys + key1_str;
        if (key2_str != "")
        {
          keys = keys + " " + key2_str;
        }
      
        return keys;
    ///////////      End of Implementation      /////////////
    ///////////////////////////////////////////////////////
    };
};

class MultiWayTree {
public:
    MultiWayTree() { _root = NULL; };
    ~MultiWayTree() {
        delete[] _root;
        _root = NULL;
    };
    string preOrder();

protected:
    MultiNode *_root;

private:
    void _preOrder(string& output, MultiNode *cur);
};

class MultiWaySearchTree: public MultiWayTree {
public:
    MultiWaySearchTree() { };
    ~MultiWaySearchTree() { };

    int insert(int key);
    int remove(int key);

private:
    /////////////////////////////////////////////////////////
    //////  TODO: Add private members if required ///////////

    MultiNode *search(int key);
    MultiNode *find_min_key(MultiNode *root);
    MultiNode *find_max_key(MultiNode *root);
    MultiNode *parent_node(int key);

    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
};
