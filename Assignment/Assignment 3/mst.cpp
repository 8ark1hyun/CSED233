#include "mst.h"
#include <iostream>
#include <string>

using namespace std;

string MultiWayTree::preOrder() {
  string output;
  _preOrder(output, _root);
  if (!output.empty())
    output.pop_back();
  return output;
}

void MultiWayTree::_preOrder(string& output, MultiNode *cur) {
  if(cur == NULL)
      return;

  output.append(cur->print_key());
  output.append(" ");
  _preOrder(output, cur->left);
  _preOrder(output, cur->middle);
  _preOrder(output, cur->right);
}

int MultiWaySearchTree::insert(int key) {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////

    if(_root == NULL)
    {
      MultiNode* new_node = new MultiNode;
      new_node->key1 = key;
      _root = new_node;
      
      return 0;
    }
    else 
    {
      MultiNode* pos = _root;

      while(pos != NULL)
        {
          if(key < pos->key1)
          {
            if(pos->key2 == 0)
            {
              int k = pos->key1;
              pos->key1 = key;
              pos->key2 = k;
              break;
            }
            else
            {
             if(pos->left == NULL)
            {
              MultiNode* new_node = new MultiNode;
              new_node->key1 = key;
              pos->left = new_node;
              break;
            }
            else
            {
              pos = pos->left;
              continue;
            } 
            }
          }
          else if (key > pos->key1)
          {
            if(pos->key2 == 0)
            {
              pos->key2 = key;
              break;
            }
            else
            {
              if(key < pos->key2)
              {
                if(pos->middle == NULL)
                {
                  MultiNode* new_node = new MultiNode;
                  new_node->key1 = key;
                  pos->middle = new_node;
                  break;
                } else 
                {
                  pos = pos->middle;
                  continue;
                }
              }
              else if (key > pos->key2)
              {
                if(pos->right == NULL)
                {
                  MultiNode* new_node = new MultiNode;
                  new_node->key1 = key;
                  pos->right = new_node;
                  break;
                } else
                {
                  pos = pos->right;
                  continue;
                }
              }
              else
              {
                return -1;
              }
            }
          }
          else
          {
            return -1;
          }
        }
    }

    return 0;
    ///////////      End of Implementation      /////////////
    ///////////////////////////////////////////////////////
}

int MultiWaySearchTree::remove(int key) {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////

    MultiNode* node = search(key);

    if(node == NULL)
    {
      return -1;
    }
  
    if(key == node->key1)
    {
      if(node->key2 != 0)
      {
        if(node->middle != NULL)
        {
          MultiNode* min = find_min_key(node->middle);
          int k = min->key1;
          remove(min->key1);
          node->key1 = k;
        }
        else
        {
          if(node->right != NULL)
          {
            int k = node->key2;
            remove(node->key2);
            node->key1 = k;
          }
          else
          {
            if(node->left != NULL)
            {
              MultiNode* max = find_max_key(node->left);
              if(max->key2 != 0)
              {
                int k = max->key2;
                remove(max->key2);
                node->key1 = k;
              }
              else
              {
                int k = max->key1;
                remove(max->key1);
                node->key1 = k;
              }
            }
            else
            {
              node->key1 = node->key2;
              node->key2 = 0;
            }
          }
        }
      }
      else
      {
        if(node == _root)
        {
          if(node->left != NULL)
          {
            _root = node->left;
          }
          else
          {
            _root = NULL;
          }
          delete node;
        }
        else
        {
          MultiNode* parent = parent_node(key);
          if(parent == NULL)
          {
            return -1;
          }
          else
          {
            if(parent->left == node)
            {
              if(node->left != NULL)
              {
                parent->left = node->left;
              }
              else
              {
                parent->left = NULL;
              }
            }
            else if (parent->right == node)
            {
              if(node->left != NULL)
              {
                parent->right = node->left;
              }
              else
              {
                parent->right = NULL;
              }
            }
            else if (parent->middle == node)
            {
              if(node->left != NULL)
              {
                parent->middle = node->left;
              }
              else
              {
                parent->middle = NULL;
              }
            }
          }
          delete node;
        }
      }
    } else if (key == node->key2)
    {
      if(node->right != NULL)
      {
        MultiNode* min = find_min_key(node->right);
        int k = min->key1;
        remove(min->key1);
        node->key2 = k;
      }
      else
      {
        if(node->middle != NULL)
        {
          MultiNode* max = find_max_key(node->middle);
          
          if(max->key2 != 0)
          {
            int k = max->key2;
            remove(max->key2);
            node->key2 = k;
          }
          else
          {
            int k = max->key1;
            remove(max->key1);
            node->key2 = k;
          }
        }
        else
        {
          node->key2 = 0;
        }
      }
    }

  
    return 0;
    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////
//////////  TODO: Implement From Here      //////////////

MultiNode *MultiWaySearchTree::search(int key) {

  MultiNode *temp = _root;

  while (temp != NULL) {
    if(temp->key1 > key)
    {
      temp = temp->left;
    } else if (temp->key1 < key) {
      if(temp->key2 == 0)
      {
        temp = temp->middle;
      }
      else
      {
        if(temp->key2 > key)
        {
          temp = temp->middle;
        }
        else if (temp->key2 < key)
        {
          temp = temp->right;
        } else
        {
          break;
        }
      }
    } else 
    {
      break;
    }
  }

  return temp;
}

MultiNode *MultiWaySearchTree::find_min_key(MultiNode *root) {

  MultiNode *temp = root;

  while (temp->left != NULL) {
    temp = temp->left;
  }

  return temp;
}

MultiNode *MultiWaySearchTree::find_max_key(MultiNode* root) 
{
  MultiNode* temp = root;

  while (temp->right != NULL)
    {
      temp = temp->right;
    }

  return temp;
}

MultiNode *MultiWaySearchTree::parent_node(int key)
{
  MultiNode *temp = _root;
  MultiNode *parent;

  while (temp != NULL) {
    if(temp->key1 > key)
    {
      parent = temp;
      temp = temp->left;
    } else if (temp->key1 < key) {
      if(temp->key2 == 0)
      {
        parent = NULL;
        break;
      }
      else
      {
        if(temp->key2 > key)
        {
          parent = temp;
          temp = temp->middle;
        }
        else if (temp->key2 < key)
        {
          parent = temp;
          temp = temp->right;
        } else
        {
          return parent;
        }
      }
    } else 
    {
      return parent;
    }
  }

  return parent;
}

///////////      End of Implementation      /////////////
/////////////////////////////////////////////////////////
