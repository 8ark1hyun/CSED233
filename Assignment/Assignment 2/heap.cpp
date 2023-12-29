#include "heap.h"
#include <iostream>
#include <string>

using namespace std;

MaxHeap::MaxHeap() {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////

  MaxHeap_arr = new string[100];
  heap_size = 0;

  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}

string MaxHeap::printHeap() {
  string answer;
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////

  for (int i = 0; i < heap_size; i++) {
    answer += MaxHeap_arr[i];
    answer += " ";
  }

  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
  return answer;
}

void MaxHeap::insertKey(string sen) {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////

  int k = heap_size;

  if (sen[0] == '\'' || sen[0] == '"') {

    for (int i = 0; i < sen.size() - 2; i++) {
      MaxHeap_size = heap_size;
      MaxHeap_arr[i + k] = sen[i + 1];
      maxHeapProp(MaxHeap_arr);
      heap_size++;
    }

  } else {

    for (int i = 0; i < sen.size(); i++) {
      MaxHeap_size = heap_size;
      MaxHeap_arr[i + k] = sen[i];
      maxHeapProp(MaxHeap_arr);
      heap_size++;
    }
  }

  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}

void MaxHeap::deleteMax() {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////

  MaxHeap_arr[0] = MaxHeap_arr[heap_size - 1];

  heap_size--;

  heap_size--;
  MaxHeap_size = heap_size;
  maxHeapProp(MaxHeap_arr);
  heap_size++;

  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}

void MaxHeap::maxHeapProp(string *MaxHeap_arr) {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here   /////////////

  string temp;
  int k = 0;

  if (heap_size == 0) {
    return;
  }

  if (heap_size % 2 == 0) {

    if (int(MaxHeap_arr[heap_size][0]) <
            int(MaxHeap_arr[heap_size / 2 - 1][0]) &&
        int(MaxHeap_arr[heap_size - 1][0]) <
            int(MaxHeap_arr[heap_size / 2 - 1][0])) {
      if (int(MaxHeap_arr[heap_size][0]) <=
          int(MaxHeap_arr[heap_size - 1][0])) {
        temp = MaxHeap_arr[heap_size];
        MaxHeap_arr[heap_size] = MaxHeap_arr[heap_size / 2 - 1];
        MaxHeap_arr[heap_size / 2 - 1] = temp;

      } else {
        temp = MaxHeap_arr[heap_size - 1];
        MaxHeap_arr[heap_size - 1] = MaxHeap_arr[heap_size / 2 - 1];
        MaxHeap_arr[heap_size / 2 - 1] = temp;
      }
    } else if (int(MaxHeap_arr[heap_size][0]) <
                   int(MaxHeap_arr[heap_size / 2 - 1][0]) &&
               int(MaxHeap_arr[heap_size - 1][0]) >=
                   int(MaxHeap_arr[heap_size / 2 - 1][0])) {

      temp = MaxHeap_arr[heap_size];
      MaxHeap_arr[heap_size] = MaxHeap_arr[heap_size / 2 - 1];
      MaxHeap_arr[heap_size / 2 - 1] = temp;
    } else if (int(MaxHeap_arr[heap_size][0]) >=
                   int(MaxHeap_arr[heap_size / 2 - 1][0]) &&
               int(MaxHeap_arr[heap_size - 1][0]) <
                   int(MaxHeap_arr[heap_size / 2 - 1][0])) {
      temp = MaxHeap_arr[heap_size - 1];
      MaxHeap_arr[heap_size - 1] = MaxHeap_arr[heap_size / 2 - 1];
      MaxHeap_arr[heap_size / 2 - 1] = temp;
    } else {
      k = heap_size;
      heap_size = heap_size - 2;
      maxHeapProp(MaxHeap_arr);
      heap_size = k;

      return;
    }

    k = heap_size;
    if (2 * heap_size + 2 <= MaxHeap_size) {
      heap_size = 2 * k + 2;
      maxHeapProp(MaxHeap_arr);
      heap_size = k;
    } else {
      if (2 * heap_size + 1 == MaxHeap_size) {
        heap_size = 2 * k + 1;
        maxHeapProp(MaxHeap_arr);
        heap_size = k;
      }
    }
    heap_size = heap_size - 2;
    maxHeapProp(MaxHeap_arr);
    heap_size = k;
  } else {

    if (int(MaxHeap_arr[heap_size][0]) < int(MaxHeap_arr[heap_size / 2][0])) {

      temp = MaxHeap_arr[heap_size];
      MaxHeap_arr[heap_size] = MaxHeap_arr[heap_size / 2];
      MaxHeap_arr[heap_size / 2] = temp;
    }

    k = heap_size;
    heap_size = heap_size - 1;
    maxHeapProp(MaxHeap_arr);
    heap_size = k;
  }

  return;

  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}