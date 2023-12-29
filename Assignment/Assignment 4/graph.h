#pragma once
#include <fstream>
#include <iostream>
#include <string>
#define NodeMaxCount 101
#define INF 2147483647
using namespace std;

/////////////////////////////////////////////////////////
///  TODO: Add Your Struct or Functions if required /////
class Node {
public:
  Node() {
    arr = new string[NodeMaxCount]();
    weight = new int[NodeMaxCount]();
    check = new bool[NodeMaxCount]();
    count = 0;
    edge = new bool[NodeMaxCount]();
  }
  ~Node() {
    delete[] arr;
    delete[] weight;
    delete[] edge;
  }

  void insertionSort();

  string vertex;
  string *arr;
  int *weight;
  bool *check;
  int count;
  bool *edge;
};
///////////      End of Implementation      /////////////
/////////////////////////////////////////////////////////

class Graph {
public:
  Graph() {
    connected_component = 0;
    DFS_answer = "";
    BFS_answer = "";
    task4_answer = "";
    task5_answer = "";
    task6_answer = "";
    task7_answer = "";
    task8_answer = "";
    task5_arr = new string[NodeMaxCount]();
    task6_arr = new string[NodeMaxCount]();
    node = new Node[NodeMaxCount];
    visited = new bool[NodeMaxCount]();
    check = new bool[NodeMaxCount]();
    min_length = new int[NodeMaxCount]();
    min_path = new string *[NodeMaxCount];
    for (int i = 0; i < NodeMaxCount; i++) {
      min_path[i] = new string[NodeMaxCount]();
    }
    vertex_num = 0;
    _source = "";
    _destination = "";
    task5_count = 0;
    task6_count = 0;
    path_count = new int[NodeMaxCount]();
    connected = new int[NodeMaxCount]();
    con_num = 1;
    comp_s = -1;
    comp_d = -1;
  }
  ~Graph() {
    delete[] task5_arr;
    delete[] task6_arr;
    delete[] node;
    delete[] visited;
    delete[] check;
    delete[] min_length;
    for (int i = 0; i < path_count[i]; i++) {
      delete[] min_path[i];
    }
    delete[] min_path;
    delete[] path_count;
    delete[] connected;
  }

  string DFS();
  string BFS();

  int addDirectedEdge(string nodeA, string nodeB);
  int addDirectedEdge(string nodeA, string nodeB, int weight);
  int addUndirectedEdge(string nodeA, string nodeB);
  int addUndirectedEdge(string nodeA, string nodeB, int weight);

  string StronglyConnectedComponent();

  string getShortestPath_task5(string source, string destination);
  string getShortestPath_task6(string source, string destination);
  int primMST(ofstream &, string startNode);
  int kruskalMST(ofstream &, string endNode);

private:
  /////////////////////////////////////////////////////////
  //////  TODO: Add private members if required ///////////
  int connected_component;
  string DFS_answer;
  string BFS_answer;
  string task4_answer;
  string task5_answer;
  string task6_answer;
  string task7_answer;
  string task8_answer;
  string *task5_arr;
  string *task6_arr;
  Node *node;
  bool *visited;
  bool *check;
  int *min_length;
  string **min_path;
  int vertex_num;
  string _source;
  string _destination;
  int task5_count;
  int task6_count;
  int *path_count;
  int *connected;
  int con_num;
  int comp_s;
  int comp_d;
  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
};
