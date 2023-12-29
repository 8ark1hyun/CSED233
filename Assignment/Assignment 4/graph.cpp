#include "graph.h"
#include <fstream>
#include <iostream>
#include <string>
#define INF 2147483647
using namespace std;

/////////////////////////////////////////////////////////
//////////  TODO: Implement From Here      //////////////
/*  Write your codes if you have additional functions  */

void Node::insertionSort() {

  for (int i = 1; i < count; i++) {
    string _string = arr[i];
    int _weight = weight[i];
    int j = i - 1;
    while ((j >= 0) && (arr[j] > _string)) {
      arr[j + 1] = arr[j];
      weight[j + 1] = weight[j];
      j--;
    }
    arr[j + 1] = _string;
    weight[j + 1] = _weight;
  }
}

///////////      End of Implementation      /////////////
/////////////////////////////////////////////////////////

string Graph::DFS() {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////

  int start_num = -1;
  string answer = "";

  for (int i = 0; i < vertex_num; i++) {
    if (visited[i] == false) {
      start_num = i;
      break;
    }
  }

  if (start_num == -1) {
    DFS_answer = to_string(connected_component) + '\n' + DFS_answer;
    return DFS_answer;
  }

  for (int i = 0; i < vertex_num; i++) {
    if (visited[i] == false && node[i].vertex < node[start_num].vertex) {
      start_num = i;
    }
  }

  answer += node[start_num].vertex;
  visited[start_num] = true;

  int k = start_num;
  bool repeat = false;
  bool end = false;
  int previous[101] = {0};

  while (1) {

    if (previous[k] == 0) {
      end = true;
      for (int i = 0; i < node[k].count; i++) {
        for (int j = 0; j < vertex_num; j++) {
          if (node[k].arr[i] == node[j].vertex) {
            if (visited[j] == false) {
              end = false;
              break;
            } else {
              break;
            }
          }
        }
        if (end == false) {
          break;
        }
      }
    }

    if (end == true) {
      connected_component++;
      if (DFS_answer != "") {
        DFS_answer += '\n';
      }
      DFS_answer += answer;
      DFS();
      break;
    } else {
      while (1) {
        for (int i = 0; i < node[k].count; i++) {
          for (int j = 0; j < vertex_num; j++) {
            if (node[k].arr[i] == node[j].vertex) {
              if (visited[j] == false) {
                answer += " ";
                answer += node[j].vertex;
                visited[j] = true;
                previous[j] = k + 1;
                k = j;
                repeat = true;
                break;
              } else {
                break;
              }
            } else {
              continue;
            }
          }
          if (repeat == true) {
            break;
          }
        }
        if (repeat == true) {
          repeat = false;
          continue;
        } else {
          break;
        }
      }

      k = previous[k] - 1;
    }
  }

  return DFS_answer;

  ///////////      End of Implementation      /////////////
  ///////////////////////////////////////////////////////
}

string Graph::BFS() {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////

  int start_num = -1;
  string answer = "";

  for (int i = 0; i < vertex_num; i++) {
    if (visited[i] == false) {
      start_num = i;
      break;
    }
  }

  if (start_num == -1) {
    BFS_answer = to_string(connected_component) + '\n' + BFS_answer;
    return BFS_answer;
  }

  for (int i = 0; i < vertex_num; i++) {
    if (visited[i] == false && node[i].vertex < node[start_num].vertex) {
      start_num = i;
    }
  }

  answer += node[start_num].vertex;
  visited[start_num] = true;

  int k = start_num;
  bool end = false;
  int previous[101] = {0};

  while (1) {
    if (previous[k] == 0) {
      end = true;
      for (int i = 0; i < node[k].count; i++) {
        for (int j = 0; j < vertex_num; j++) {
          if (node[k].arr[i] == node[j].vertex) {
            if (visited[j] == false || check[j] == false) {
              end = false;
              break;
            } else {
              break;
            }
          }
        }
        if (end == false) {
          break;
        }
      }
    }

    if (end == true) {
      connected_component++;
      if (BFS_answer != "") {
        BFS_answer += '\n';
      }
      BFS_answer += answer;
      BFS();
      break;
    } else {
      while (1) {
        int repeat = 0;
        int next = 0;

        check[k] = true;
        for (int i = 0; i < node[k].count; i++) {
          for (int j = 0; j < vertex_num; j++) {
            if (node[k].arr[i] == node[j].vertex) {
              if (visited[j] == false) {
                if (next == 0) {
                  next = j;
                }
                answer += " ";
                answer += node[j].vertex;
                visited[j] = true;
                previous[j] = k + 1;
                break;
              } else {
                break;
              }
            } else {
              continue;
            }
          }
        }

        if (next != 0) {
          k = next;
          continue;
        } else {
          for (int i = 0; i < node[k].count; i++) {
            for (int j = 0; j < vertex_num; j++) {
              if (node[k].arr[i] == node[j].vertex) {
                if (check[j] == false) {
                  k = j;
                  repeat = -1;
                  break;
                }
              }
            }
            if (repeat == -1) {
              break;
            }
          }
          if (repeat == 0) {
            break;
          }
        }
      }

      k = previous[k] - 1;
    }
  }

  return BFS_answer;

  ///////////      End of Implementation      /////////////
  ///////////////////////////////////////////////////////
}

int Graph::addDirectedEdge(string nodeA, string nodeB) {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////

  bool pass = false;

  for (int i = 0; i < vertex_num; i++) {
    if (node[i].vertex == nodeA) {
      for (int j = 0; j < node[i].count; j++) {
        if (node[i].arr[j] == nodeB) {
          return 0;
        }
      }
      node[i].arr[node[i].count] = nodeB;
      node[i].count++;
      node[i].insertionSort();
      pass = true;
    }
  }

  if (pass != true) {
    node[vertex_num].vertex = nodeA;
    node[vertex_num].arr[node[vertex_num].count] = nodeB;
    node[vertex_num].count++;
    node[vertex_num].insertionSort();
    vertex_num++;
  }

  return 0;

  ///////////      End of Implementation      /////////////
  ///////////////////////////////////////////////////////
}

int Graph::addDirectedEdge(string nodeA, string nodeB, int weight) {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////

  return 0;
  ///////////      End of Implementation      /////////////
  ///////////////////////////////////////////////////////
}

int Graph::addUndirectedEdge(string nodeA, string nodeB) {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////

  bool pass = false;

  for (int i = 0; i < vertex_num; i++) {
    if (node[i].vertex == nodeA) {
      for (int j = 0; j < node[i].count; j++) {
        if (node[i].arr[j] == nodeB) {
          return 0;
        }
      }
      node[i].arr[node[i].count] = nodeB;
      node[i].count++;
      node[i].insertionSort();
      pass = true;
    }
  }

  if (pass != true) {
    node[vertex_num].vertex = nodeA;
    node[vertex_num].arr[node[vertex_num].count] = nodeB;
    node[vertex_num].count++;
    node[vertex_num].insertionSort();
    vertex_num++;
  }

  pass = false;

  for (int i = 0; i < vertex_num; i++) {
    if (node[i].vertex == nodeB) {
      for (int j = 0; j < node[i].count; j++) {
        if (node[i].arr[j] == nodeA) {
          return 0;
          ;
        }
      }
      node[i].arr[node[i].count] = nodeA;
      node[i].count++;
      node[i].insertionSort();
      pass = true;
    }
  }

  if (pass != true) {
    node[vertex_num].vertex = nodeB;
    node[vertex_num].arr[node[vertex_num].count] = nodeA;
    node[vertex_num].count++;
    node[vertex_num].insertionSort();
    vertex_num++;
  }

  return 0;

  ///////////      End of Implementation      /////////////
  ///////////////////////////////////////////////////////
}

int Graph::addUndirectedEdge(string nodeA, string nodeB, int weight) {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////

  bool pass = false;
  int _case = 0;
  int a = -1;

  for (int i = 0; i < vertex_num; i++) {
    if (node[i].vertex == nodeA) {
      for (int j = 0; j < node[i].count; j++) {
        if (node[i].arr[j] == nodeB) {
          return 0;
        }
      }
      _case = 2;
      a = i;
      node[i].arr[node[i].count] = nodeB;
      node[i].weight[node[i].count] = weight;
      node[i].count++;
      node[i].insertionSort();
      pass = true;
    }
  }

  if (pass != true) {
    for (int i = 0; i < vertex_num; i++) {
      if (node[i].vertex == nodeB) {
        _case = 1;
        a = i;
        break;
      }
    }
    node[vertex_num].vertex = nodeA;
    node[vertex_num].arr[node[vertex_num].count] = nodeB;
    node[vertex_num].weight[node[vertex_num].count] = weight;
    node[vertex_num].count++;
    node[vertex_num].insertionSort();
    if (_case == 0) {
      connected[vertex_num] = con_num;
    } else if (_case == 1) {
      connected[vertex_num] = connected[a];
    }
    vertex_num++;
  }

  pass = false;

  for (int i = 0; i < vertex_num; i++) {
    if (node[i].vertex == nodeB) {
      for (int j = 0; j < node[i].count; j++) {
        if (node[i].arr[j] == nodeA) {
          return 0;
        }
      }
      node[i].arr[node[i].count] = nodeA;
      node[i].weight[node[i].count] = weight;
      node[i].count++;
      node[i].insertionSort();
      pass = true;
      int k = connected[i];
      for (int l = 0; l < vertex_num; l++) {
        if (connected[l] == k) {
          connected[l] = connected[a];
        }
      }
    }
  }

  if (pass != true) {
    node[vertex_num].vertex = nodeB;
    node[vertex_num].arr[node[vertex_num].count] = nodeA;
    node[vertex_num].weight[node[vertex_num].count] = weight;
    node[vertex_num].count++;
    node[vertex_num].insertionSort();
    if (_case == 0) {
      connected[vertex_num] = con_num;
      con_num++;
    } else if (_case == 2) {
      connected[vertex_num] = connected[a];
    }
    vertex_num++;
  }

  return 0;

  ///////////      End of Implementation      /////////////
  ///////////////////////////////////////////////////////
}

string Graph::StronglyConnectedComponent() {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////

  string str[101];
  int str_num = 0;
  string answer[101];
  int answer_num = 0;
  string graph_str[101];
  int graph_num = 0;
  string reverse_str[101];
  int reverse_num = 0;
  int vertex_count[101];
  int ver_num = 0;
  int reverse_count[101];
  int rev_num = 0;

  Graph reverse;

  for (int i = 0; i < vertex_num; i++) {
    graph_str[graph_num] = node[i].vertex;
    graph_num++;
    vertex_count[ver_num] = node[i].count;
    ver_num++;
    for (int j = 0; j < node[i].count; j++) {
      bool add1 = true;
      bool add2 = true;
      for (int k = 0; k < str_num; k++) {
        if (str[k] == node[i].vertex) {
          add1 = false;
        }
        if (str[k] == node[i].arr[j]) {
          add2 = false;
        }
      }
      if (add1 == true) {
        str[str_num] = node[i].vertex;
        str_num++;
      }
      if (add2 == true) {
        str[str_num] = node[i].arr[j];
        str_num++;
      }
      reverse.addDirectedEdge(node[i].arr[j], node[i].vertex);
    }
  }

  string graph_DFS = DFS();
  string reverse_DFS = reverse.DFS();

  for (int i = 0; i < reverse.vertex_num; i++) {
    reverse_str[reverse_num] = reverse.node[i].vertex;
    reverse_num++;
    reverse_count[rev_num] = reverse.node[i].count;
    rev_num++;
  }

  while (1) {
    bool end = true;

    for (int i = 0; i < str_num; i++) {
      bool exist = false;
      for (int j = 0; j < graph_num; j++) {
        if (str[i] == graph_str[j]) {
          exist = true;
          break;
        }
      }
      if (exist == false) {
        bool _continue = true;
        for (int a = 0; a < answer_num; a++) {
          if (str[i] == answer[a]) {
            _continue = false;
          }
        }
        if (_continue == true) {
          end = false;
          answer[answer_num] = str[i];
          answer_num++;
          for (int a = 1; a < answer_num; a++) {
            string _string = answer[a];
            int b = a - 1;
            while ((b >= 0) && (answer[b] > _string)) {
              answer[b + 1] = answer[b];
              b--;
            }
            answer[b + 1] = _string;
          }
          for (int k = 0; k < vertex_num; k++) {
            for (int l = 0; l < node[k].count; l++) {
              if (node[k].arr[l] == answer[answer_num - 1]) {
                vertex_count[k]--;
                if (vertex_count[k] == 0) {
                  graph_str[k] = "";
                }
                break;
              }
            }
          }
        }
      }
    }

    for (int i = 0; i < str_num; i++) {
      bool exist = false;
      for (int j = 0; j < reverse_num; j++) {
        if (str[i] == reverse_str[j]) {
          exist = true;
          break;
        }
      }
      if (exist == false) {
        bool _continue = true;
        for (int a = 0; a < answer_num; a++) {
          if (str[i] == answer[a]) {
            _continue = false;
          }
        }
        if (_continue == true) {
          end = false;
          answer[answer_num] = str[i];
          answer_num++;
          for (int a = 1; a < answer_num; a++) {
            string _string = answer[a];
            int b = a - 1;
            while ((b >= 0) && (answer[b] > _string)) {
              answer[b + 1] = answer[b];
              b--;
            }
            answer[b + 1] = _string;
          }
          for (int k = 0; k < reverse.vertex_num; k++) {
            for (int l = 0; l < reverse.node[k].count; l++) {
              if (reverse.node[k].arr[l] == answer[answer_num - 1]) {
                reverse_count[k]--;
                if (reverse_count[k] == 0) {
                  reverse_str[k] = "";
                }
                break;
              }
            }
          }
        }
      }
    }

    if (end == true) {
      break;
    }
  }

  string _DFS[101][101];
  int a = 0;
  int b[101] = {0};

  if (graph_DFS[0] > reverse_DFS[0]) {
    for (int i = 2; i < graph_DFS.size(); i++) {
      if (graph_DFS[i] == '\n') {
        b[a]++;
        for (int x = 1; x < b[a]; x++) {
          string _string = _DFS[a][x];
          int y = x - 1;
          while ((y >= 0) && (_DFS[a][y] > _string)) {
            _DFS[a][y + 1] = _DFS[a][y];
            y--;
          }
          _DFS[a][y + 1] = _string;
        }
        a++;
        continue;
      } else {
        if (graph_DFS[i] == char(32)) {
          b[a]++;
          for (int x = 1; x < b[a]; x++) {
            string _string = _DFS[a][x];
            int y = x - 1;
            while ((y >= 0) && (_DFS[a][y] > _string)) {
              _DFS[a][y + 1] = _DFS[a][y];
              y--;
            }
            _DFS[a][y + 1] = _string;
          }
          continue;
        } else {
          _DFS[a][b[a]] += graph_DFS[i];
        }
      }
    }
    b[a]++;
    for (int x = 1; x < b[a]; x++) {
      string _string = _DFS[a][x];
      int y = x - 1;
      while ((y >= 0) && (_DFS[a][y] > _string)) {
        _DFS[a][y + 1] = _DFS[a][y];
        y--;
      }
      _DFS[a][y + 1] = _string;
    }
    a++;
  } else {
    for (int i = 2; i < reverse_DFS.size(); i++) {
      if (reverse_DFS[i] == '\n') {
        b[a]++;
        for (int x = 1; x < b[a]; x++) {
          string _string = _DFS[a][x];
          int y = x - 1;
          while ((y >= 0) && (_DFS[a][y] > _string)) {
            _DFS[a][y + 1] = _DFS[a][y];
            y--;
          }
          _DFS[a][y + 1] = _string;
        }
        a++;
        continue;
      } else {
        if (reverse_DFS[i] == char(32)) {
          b[a]++;
          for (int x = 1; x < b[a]; x++) {
            string _string = _DFS[a][x];
            int y = x - 1;
            while ((y >= 0) && (_DFS[a][y] > _string)) {
              _DFS[a][y + 1] = _DFS[a][y];
              y--;
            }
            _DFS[a][y + 1] = _string;
          }
          continue;
        } else {
          _DFS[a][b[a]] += reverse_DFS[i];
        }
      }
    }
    b[a]++;
    for (int x = 1; x < b[a]; x++) {
      string _string = _DFS[a][x];
      int y = x - 1;
      while ((y >= 0) && (_DFS[a][y] > _string)) {
        _DFS[a][y + 1] = _DFS[a][y];
        y--;
      }
      _DFS[a][y + 1] = _string;
    }
    a++;
  }

  for (int i = 0; i < a; i++) {
    for (int j = 0; j < b[i]; j++) {
      bool pass = false;
      for (int k = 0; k < answer_num; k++) {
        if (_DFS[i][j] == answer[k]) {
          pass = true;
          break;
        }
      }
      if (pass == true) {
        continue;
      }
      if (answer[answer_num] != "") {
        answer[answer_num] += " ";
      }
      answer[answer_num] += _DFS[i][j];
    }
    if (answer[answer_num] != "") {
      answer_num++;
      for (int x = 1; x < answer_num; x++) {
        string _string = answer[x];
        int y = x - 1;
        while ((y >= 0) && (answer[y] > _string)) {
          answer[y + 1] = answer[y];
          y--;
        }
        answer[y + 1] = _string;
      }
    }
  }

  task4_answer = to_string(answer_num) + '\n';
  for (int i = 0; i < answer_num; i++) {
    task4_answer += answer[i];
    if (i != answer_num - 1) {
      task4_answer += '\n';
    }
  }

  return task4_answer;

  ///////////      End of Implementation      /////////////
  ///////////////////////////////////////////////////////
}

string Graph::getShortestPath_task5(string source, string destination) {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////

  int minimum = INF;
  string next_source = "";
  int start = 0;

  if (_source == "" && _destination == "") {
    _source = source;
    _destination = destination;

    for (int i = 0; i < vertex_num; i++) {
      if (node[i].vertex == source) {
        comp_s = i;
      }
      if (node[i].vertex == destination) {
        comp_d = i;
      }
    }
    if (connected[comp_s] != connected[comp_d]) {
      task5_answer = "error";
      return task5_answer;
    }

    for (int i = 0; i < vertex_num; i++) {
      min_length[i] = INF;
    }
    if (_source == _destination) {
      task5_answer += _source;
      task5_answer += " ";
      task5_answer += to_string(0);
      return task5_answer;
    }
    start = 1;
  }

  bool end = true;
  for (int i = 0; i < vertex_num; i++) {
    if (connected[comp_s] == connected[i] && visited[i] == false) {
      end = false;
      if (source == "") {
        source = node[i].vertex;
        visited[i] = true;
      }
      break;
    }
  }

  if (end == true) {
    for (int i = 0; i < vertex_num; i++) {
      if (node[i].vertex == _destination) {
        task5_count = 0;
        for (int j = 0; j < path_count[i]; j++) {
          task5_arr[task5_count] = min_path[i][j] + " " + node[i].vertex;
          task5_count++;
          for (int a = 1; a < task5_count; a++) {
            string _string = task5_arr[a];
            int b = a - 1;
            while ((b >= 0) && (task5_arr[b] > _string)) {
              task5_arr[b + 1] = task5_arr[b];
              b--;
            }
            task5_arr[b + 1] = _string;
          }
        }
        task5_answer = "";
        for (int n = 0; n < task5_count; n++) {
          task5_answer += task5_arr[n];
          task5_answer += " ";
          task5_answer += to_string(min_length[i]);
          if (n != task5_count - 1) {
            task5_answer += '\n';
          }
        }
        break;
      }
    }
    return task5_answer;
  }

  int c = -1;
  if (start == 1) {
    for (int i = 0; i < vertex_num; i++) {
      if (node[i].vertex == source) {
        min_length[i] = 0;
        visited[i] = true;
        for (int j = 0; j < node[i].count; j++) {
          for (int k = 0; k < vertex_num; k++) {
            if (node[k].vertex == node[i].arr[j]) {
              min_length[k] = node[i].weight[j];
              min_path[k][path_count[k]] = node[i].vertex;
              path_count[k]++;
              if (minimum > node[i].weight[j]) {
                next_source = node[k].vertex;
                minimum = node[i].weight[j];
                c = k;
              }
              node[i].edge[j] = true;
              for (int e = 0; e < node[k].count; e++) {
                if (node[k].arr[e] == node[i].vertex) {
                  node[k].edge[e] = true;
                }
              }
              break;
            }
          }
        }

        if (c != -1) {
          visited[c] = true;
        }
        getShortestPath_task5(next_source, destination);
        break;
      }
    }
  } else {
    for (int i = 0; i < vertex_num; i++) {
      if (node[i].vertex == source) {
        if (node[i].vertex == destination) {
          next_source = "";
          getShortestPath_task5(next_source, destination);
          break;
        }
        for (int j = 0; j < node[i].count; j++) {
          for (int k = 0; k < vertex_num; k++) {
            if (node[k].vertex == node[i].arr[j]) {
              if (node[i].edge[j] == false) {
                if (min_length[k] > min_length[i] + node[i].weight[j] &&
                    (min_length[i] != INF)) {
                  min_length[k] = min_length[i] + node[i].weight[j];
                  path_count[k] = 0;
                  for (int l = 0; l < path_count[i]; l++) {
                    min_path[k][l] = min_path[i][l] + " " + node[i].vertex;
                    path_count[k]++;
                    for (int a = 1; a < path_count[k]; a++) {
                      string _string = min_path[k][a];
                      int b = a - 1;
                      while ((b >= 0) && (min_path[k][b] > _string)) {
                        min_path[k][b + 1] = min_path[k][b];
                        b--;
                      }
                      min_path[k][b + 1] = _string;
                    }
                  }
                } else if (min_length[k] == min_length[i] + node[i].weight[j] &&
                           (min_length[i] != INF)) {
                  for (int l = 0; l < path_count[i]; l++) {
                    int no_add = -1;
                    for (int c = 0; c < path_count[k]; c++) {
                      if (min_path[k][c] ==
                          min_path[i][l] + " " + node[i].vertex) {
                        no_add = 1;
                      }
                    }
                    if (no_add != 1) {
                      min_path[k][path_count[k]] =
                          min_path[i][l] + " " + node[i].vertex;

                      path_count[k]++;
                    }
                    for (int a = 1; a < path_count[k]; a++) {
                      string _string = min_path[k][a];
                      int b = a - 1;
                      while ((b >= 0) && (min_path[k][b] > _string)) {
                        min_path[k][b + 1] = min_path[k][b];
                        b--;
                      }
                      min_path[k][b + 1] = _string;
                    }
                  }
                } else if (min_length[i] == INF) {
                  int min = INF;
                  int which;
                  for (int m = 0; m < node[i].count; m++) {
                    for (int n = 0; n < vertex_num; n++) {
                      if (node[i].arr[m] == node[n].vertex) {
                        if (min > min_length[n] + node[i].weight[m]) {
                          min = min_length[n] + node[i].weight[m];
                          min_length[i] = min_length[n] + node[i].weight[m];
                          which = n;
                        }
                        break;
                      }
                    }
                  }
                  path_count[i] = 0;
                  for (int x = 0; x < path_count[which]; x++) {
                    min_path[i][x] =
                        min_path[which][x] + " " + node[which].vertex;
                    path_count[i]++;

                    for (int a = 1; a < path_count[i]; a++) {
                      string _string = min_path[i][a];
                      int b = a - 1;
                      while ((b >= 0) && (min_path[i][b] > _string)) {
                        min_path[i][b + 1] = min_path[i][b];
                        b--;
                      }
                      min_path[i][b + 1] = _string;
                    }
                  }
                }

                if (minimum > node[i].weight[j]) {
                  next_source = node[k].vertex;
                  minimum = node[i].weight[j];
                  c = k;
                }
                node[i].edge[j] = true;
                for (int e = 0; e < node[k].count; e++) {
                  if (node[k].arr[e] == node[i].vertex) {
                    node[k].edge[e] = true;
                  }
                }
                break;
              }
            }
          }
        }

        if (c != -1) {
          visited[c] = true;
        } else {
          check[i] = true;
          for (int j = 0; j < node[i].count; j++) {
            for (int k = 0; k < vertex_num; k++) {
              if (node[k].vertex == node[i].arr[j]) {
                if (check[k] == false) {
                  if (min_length[k] > min_length[i] + node[i].weight[j] &&
                      (min_length[i] != INF)) {
                    min_length[k] = min_length[i] + node[i].weight[j];
                    path_count[k] = 0;
                    for (int l = 0; l < path_count[i]; l++) {
                      min_path[k][l] = min_path[i][l] + " " + node[i].vertex;
                      path_count[k]++;
                      for (int a = 1; a < path_count[k]; a++) {
                        string _string = min_path[k][a];
                        int b = a - 1;
                        while ((b >= 0) && (min_path[k][b] > _string)) {
                          min_path[k][b + 1] = min_path[k][b];
                          b--;
                        }
                        min_path[k][b + 1] = _string;
                      }
                    }
                  } else if (min_length[k] ==
                                 min_length[i] + node[i].weight[j] &&
                             (min_length[i] != INF)) {
                    for (int l = 0; l < path_count[i]; l++) {
                      int no_add = -1;
                      for (int c = 0; c < path_count[k]; c++) {
                        if (min_path[k][c] ==
                            min_path[i][l] + " " + node[i].vertex) {
                          no_add = 1;
                        }
                      }
                      if (no_add != 1) {
                        min_path[k][path_count[k]] =
                            min_path[i][l] + " " + node[i].vertex;

                        path_count[k]++;
                      }
                      for (int a = 1; a < path_count[k]; a++) {
                        string _string = min_path[k][a];
                        int b = a - 1;
                        while ((b >= 0) && (min_path[k][b] > _string)) {
                          min_path[k][b + 1] = min_path[k][b];
                          b--;
                        }
                        min_path[k][b + 1] = _string;
                      }
                    }
                  } else {
                    break;
                  }
                  next_source = node[k].vertex;
                  getShortestPath_task5(next_source, destination);
                  break;
                }
              }
            }
          }
        }
        getShortestPath_task5(next_source, destination);
        break;
      }
    }
  }

  return task5_answer;

  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}

string Graph::getShortestPath_task6(string source, string destination) {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////

  int minimum = INF;
  string next_source = "";
  int start = 0;

  if (_source == "" && _destination == "") {
    _source = source;
    _destination = destination;

    for (int i = 0; i < vertex_num; i++) {
      if (node[i].vertex == source) {
        comp_s = i;
      }
      if (node[i].vertex == destination) {
        comp_d = i;
      }
    }
    if (connected[comp_s] != connected[comp_d]) {
      task6_answer = "INF";
      return task6_answer;
    }

    for (int i = 0; i < vertex_num; i++) {
      min_length[i] = INF;
    }
    if (_source == _destination) {
      task6_answer += _source;
      task6_answer += " ";
      task6_answer += to_string(0);
      return task6_answer;
    }
    start = 1;
  }

  bool end = true;
  for (int i = 0; i < vertex_num; i++) {
    if (connected[comp_s] == connected[i] && visited[i] == false) {
      end = false;
      if (source == "") {
        source = node[i].vertex;
        visited[i] = true;
      }
      break;
    }
  }

  if (end == true) {
    for (int i = 0; i < vertex_num; i++) {
      if (node[i].vertex == _destination) {
        task6_count = 0;
        for (int j = 0; j < path_count[i]; j++) {
          task6_arr[task6_count] = min_path[i][j] + " " + node[i].vertex;
          task6_count++;
          for (int a = 1; a < task6_count; a++) {
            string _string = task6_arr[a];
            int b = a - 1;
            while ((b >= 0) && (task6_arr[b] > _string)) {
              task6_arr[b + 1] = task6_arr[b];
              b--;
            }
            task6_arr[b + 1] = _string;
          }
        }
        task6_answer = "";
        for (int n = 0; n < task6_count; n++) {
          task6_answer += task6_arr[n];
          task6_answer += " ";
          task6_answer += to_string(min_length[i]);
          if (n != task6_count - 1) {
            task6_answer += '\n';
          }
        }
        return task6_answer;
      }
    }
  }

  int c = -1;
  if (start == 1) {
    for (int i = 0; i < vertex_num; i++) {
      if (node[i].vertex == source) {
        min_length[i] = 0;
        visited[i] = true;
        for (int j = 0; j < node[i].count; j++) {
          for (int k = 0; k < vertex_num; k++) {
            if (node[k].vertex == node[i].arr[j]) {
              min_length[k] = node[i].weight[j];
              min_path[k][path_count[k]] = node[i].vertex;
              path_count[k]++;
              if (minimum > node[i].weight[j]) {
                next_source = node[k].vertex;
                minimum = node[i].weight[j];
                c = k;
              }
              node[i].edge[j] = true;
              for (int e = 0; e < node[k].count; e++) {
                if (node[k].arr[e] == node[i].vertex) {
                  node[k].edge[e] = true;
                }
              }
              break;
            }
          }
        }

        if (c != -1) {
          visited[c] = true;
        }
        getShortestPath_task6(next_source, destination);
        break;
      }
    }
  } else {
    for (int i = 0; i < vertex_num; i++) {
      if (node[i].vertex == source) {
        if (node[i].vertex == destination) {
          next_source = "";
          getShortestPath_task6(next_source, destination);
          break;
        }
        for (int j = 0; j < node[i].count; j++) {
          for (int k = 0; k < vertex_num; k++) {
            if (node[k].vertex == node[i].arr[j]) {
              if (node[i].edge[j] == false) {
                if (min_length[k] > min_length[i] + node[i].weight[j] &&
                    (min_length[i] != INF)) {
                  min_length[k] = min_length[i] + node[i].weight[j];
                  path_count[k] = 0;
                  for (int l = 0; l < path_count[i]; l++) {
                    min_path[k][l] = min_path[i][l] + " " + node[i].vertex;
                    path_count[k]++;
                    for (int a = 1; a < path_count[k]; a++) {
                      string _string = min_path[k][a];
                      int b = a - 1;
                      while ((b >= 0) && (min_path[k][b] > _string)) {
                        min_path[k][b + 1] = min_path[k][b];
                        b--;
                      }
                      min_path[k][b + 1] = _string;
                    }
                  }
                } else if (min_length[k] == min_length[i] + node[i].weight[j] &&
                           (min_length[i] != INF)) {
                  for (int l = 0; l < path_count[i]; l++) {
                    int no_add = -1;
                    for (int c = 0; c < path_count[k]; c++) {
                      if (min_path[k][c] ==
                          min_path[i][l] + " " + node[i].vertex) {
                        no_add = 1;
                      }
                    }
                    if (no_add != 1) {
                      min_path[k][path_count[k]] =
                          min_path[i][l] + " " + node[i].vertex;

                      path_count[k]++;
                    }
                    for (int a = 1; a < path_count[k]; a++) {
                      string _string = min_path[k][a];
                      int b = a - 1;
                      while ((b >= 0) && (min_path[k][b] > _string)) {
                        min_path[k][b + 1] = min_path[k][b];
                        b--;
                      }
                      min_path[k][b + 1] = _string;
                    }
                  }
                } else if (min_length[i] == INF) {
                  int min = INF;
                  int which;
                  for (int m = 0; m < node[i].count; m++) {
                    for (int n = 0; n < vertex_num; n++) {
                      if (node[i].arr[m] == node[n].vertex) {
                        if (min > min_length[n] + node[i].weight[m]) {
                          min = min_length[n] + node[i].weight[m];
                          min_length[i] = min_length[n] + node[i].weight[m];
                          which = n;
                        }
                        node[i].edge[m] = true;
                        for (int e = 0; e < node[n].count; e++) {
                          if (node[n].arr[e] == node[i].vertex) {
                            node[n].edge[e] = true;
                          }
                        }
                        break;
                      }
                    }
                  }
                  path_count[i] = 0;
                  for (int x = 0; x < path_count[which]; x++) {
                    min_path[i][x] =
                        min_path[which][x] + " " + node[which].vertex;
                    path_count[i]++;

                    for (int a = 1; a < path_count[i]; a++) {
                      string _string = min_path[i][a];
                      int b = a - 1;
                      while ((b >= 0) && (min_path[i][b] > _string)) {
                        min_path[i][b + 1] = min_path[i][b];
                        b--;
                      }
                      min_path[i][b + 1] = _string;
                    }
                  }
                }
                if (minimum > node[i].weight[j]) {
                  next_source = node[k].vertex;
                  minimum = node[i].weight[j];
                  c = k;
                }
                node[i].edge[j] = true;
                for (int e = 0; e < node[k].count; e++) {
                  if (node[k].arr[e] == node[i].vertex) {
                    node[k].edge[e] = true;
                  }
                }
                break;
              }
            }
          }
        }

        if (c != -1) {
          visited[c] = true;
        } else {
          check[i] = true;
          for (int j = 0; j < node[i].count; j++) {
            for (int k = 0; k < vertex_num; k++) {
              if (node[k].vertex == node[i].arr[j]) {
                if (check[k] == false && !(node[i].weight[j] < 0)) {
                  if (min_length[k] > min_length[i] + node[i].weight[j] &&
                      (min_length[i] != INF)) {
                    min_length[k] = min_length[i] + node[i].weight[j];
                    path_count[k] = 0;
                    for (int l = 0; l < path_count[i]; l++) {
                      min_path[k][l] = min_path[i][l] + " " + node[i].vertex;
                      path_count[k]++;
                      for (int a = 1; a < path_count[k]; a++) {
                        string _string = min_path[k][a];
                        int b = a - 1;
                        while ((b >= 0) && (min_path[k][b] > _string)) {
                          min_path[k][b + 1] = min_path[k][b];
                          b--;
                        }
                        min_path[k][b + 1] = _string;
                      }
                    }
                  } else if (min_length[k] ==
                                 min_length[i] + node[i].weight[j] &&
                             (min_length[i] != INF)) {
                    for (int l = 0; l < path_count[i]; l++) {
                      int no_add = -1;
                      for (int c = 0; c < path_count[k]; c++) {
                        if (min_path[k][c] ==
                            min_path[i][l] + " " + node[i].vertex) {
                          no_add = 1;
                        }
                      }
                      if (no_add != 1) {
                        min_path[k][path_count[k]] =
                            min_path[i][l] + " " + node[i].vertex;

                        path_count[k]++;
                      }
                      for (int a = 1; a < path_count[k]; a++) {
                        string _string = min_path[k][a];
                        int b = a - 1;
                        while ((b >= 0) && (min_path[k][b] > _string)) {
                          min_path[k][b + 1] = min_path[k][b];
                          b--;
                        }
                        min_path[k][b + 1] = _string;
                      }
                    }
                  } else {
                    break;
                  }
                  next_source = node[k].vertex;
                  getShortestPath_task6(next_source, destination);
                  break;
                }
              }
            }
          }
        }
        getShortestPath_task6(next_source, destination);
        break;
      }
    }
  }

  return task6_answer;

  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}

int Graph::primMST(ofstream &fout, string startNode) {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////

  int final_weight = 0;
  int start_vertex;
  int check[101];
  int check_num = 0;
  string previous[101];

  for (int i = 0; i < vertex_num; i++) {
    if (node[i].vertex == startNode) {
      visited[i] = true;
      start_vertex = i;
      check[0] = i;
      previous[i] = startNode;
      check_num++;
      break;
    }
  }

  while (1) {
    bool end = true;

    int min = INF;
    int _previous;
    int _next;
    for (int i = 0; i < check_num; i++) {
      for (int j = 0; j < node[i].count; j++) {
        if (min > node[check[i]].weight[j]) {
          for (int k = 0; k < vertex_num; k++) {
            if (node[check[i]].arr[j] == node[k].vertex) {
              if (visited[k] == false) {
                end = false;
                _next = k;
                _previous = check[i];
                min = node[check[i]].weight[j];
                break;
              }
            }
          }
        } else if (min == node[check[i]].weight[j]) {
          for (int k = 0; k < vertex_num; k++) {
            if (node[check[i]].arr[j] == node[k].vertex) {
              if (visited[k] == false) {
                if (node[_next].vertex > node[k].vertex) {
                  end = false;
                  _next = k;
                  _previous = check[i];
                  min = node[check[i]].weight[j];
                  break;
                } else {
                  break;
                }
              }
            }
          }
        }
      }
    }

    if (end == true) {
      break;
    }

    visited[_next] = true;
    final_weight += min;
    check[check_num] = _next;
    previous[_next] = previous[_previous] + " " + node[_next].vertex;
    task7_answer += previous[_next] + '\n';
    check_num++;
  }

  fout << task7_answer;

  return final_weight;

  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}

int Graph::kruskalMST(ofstream &fout, string endNode) {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////

  int cycle[101];
  int final_weight = 0;
  Graph task8;

  for (int i = 0; i < vertex_num; i++) {
    cycle[i] = i;
  }

  while (1) {
    bool end = true;

    string answer = "";
    int min = INF;

    int other_vertex;
    int main_vertex;
    int connect;
    for (int i = 0; i < vertex_num; i++) {
      for (int j = 0; j < node[i].count; j++) {
        for (int k = 0; k < vertex_num; k++) {
          if (node[i].arr[j] == node[k].vertex && cycle[i] != cycle[k]) {
            if (node[i].check[j] == false && min > node[i].weight[j]) {
              end = false;
              if (node[i].vertex < node[k].vertex) {
                main_vertex = i;
                connect = j;
                other_vertex = k;

                min = node[i].weight[j];
              } else {
                main_vertex = k;
                for (int o = 0; o < node[k].count; o++) {
                  if (node[i].vertex == node[k].arr[o]) {
                    connect = o;
                  }
                }
                other_vertex = i;

                min = node[i].weight[j];
              }
            } else if (node[i].check[j] == false && min == node[i].weight[j]) {
              if (node[main_vertex].vertex > node[i].vertex) {
                main_vertex = i;
                connect = j;
                other_vertex = k;

                min = node[i].weight[j];
              }
            }
          }
        }
      }
    }

    if (end == true) {
      break;
    }

    final_weight += node[main_vertex].weight[connect];
    node[main_vertex].check[connect] = true;
    int c = cycle[other_vertex];
    cycle[other_vertex] = cycle[main_vertex];
    for (int i = 0; i < node[other_vertex].count; i++) {
      if (node[other_vertex].arr[i] == node[main_vertex].vertex) {
        node[other_vertex].check[i] = true;
      }
    }
    for (int i = 0; i < vertex_num; i++) {
      if (cycle[i] == c) {
        cycle[i] = cycle[main_vertex];
      }
    }

    answer = node[main_vertex].vertex + " " + node[other_vertex].vertex + " " +
             to_string(node[main_vertex].weight[connect]);

    task8.addUndirectedEdge(node[main_vertex].vertex, node[other_vertex].vertex,
                            node[main_vertex].weight[connect]);

    task8_answer += answer + '\n';
  }

  int startNode = 0;

  for (int i = 0; i < vertex_num; i++) {
    if (node[startNode].vertex > node[i].vertex) {
      startNode = i;
    }
  }

  string final_answer =
      task8.getShortestPath_task5(node[startNode].vertex, endNode);

  for (int i = 0; i < final_answer.size(); i++) {
    if (final_answer[i] >= 48 && final_answer[i] <= 57) {
      break;
    } else {
      task8_answer += final_answer[i];
    }
  }

  fout << task8_answer;

  return final_weight;

  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}
