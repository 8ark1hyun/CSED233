#include "sort.h"
#include <fstream>
#include <iostream>
#include <string>

sortAlg::sortAlg() {
  arr_size = 0;
  arr = new int[100];  // Each test case will be less than 100 values
  temp = new int[100]; // Each test case will be less than 100 values
  num = 0;
}

using namespace std;

void sortAlg::printArray(ofstream &fout) {
  string answer;
  for (int i = 0; i < arr_size - 1; i++)
    answer += to_string(arr[i]) + " ";
  answer += to_string(arr[arr_size - 1]);
  fout << answer << endl;
}

void sortAlg::insertionSort(ofstream &fout) {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////

  for (int i = 1 + num; i < arr_size; i++) {
    int value = arr[i];
    int j = i - 1;
    while ((j >= 0) && (arr[j] > value)) {
      arr[j + 1] = arr[j];
      j--;
    }
    arr[j + 1] = value;

    printArray(fout); // DO NOT ERASE THIS LINE
  }

  num = arr_size - 1;

  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}

void sortAlg::merge(int left, int right, int &count) {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////

  int *arr_l = new int[(right - left + 1) / 2];
  int *arr_r = new int[(right - left + 1) / 2];

  int k;

  k = 0;
  for (int i = left; i < (left + right) / 2 + 1; i++) {
    arr_l[k] = arr[i];
    k++;
  }
  k = 0;
  for (int i = (left + right) / 2 + 1; i <= right; i++) {
    arr_r[k] = arr[i];
    k++;
  }

  int pos = left;
  int l = 0;
  int r = 0;

  while ((l < (right - left + 1) / 2) && (r < (right - left + 1) / 2)) {
    if (arr_l[l] < arr_r[r]) {
      arr[pos] = arr_l[l];
      l++;
    } else if (arr_l[l] > arr_r[r]) {
      arr[pos] = arr_r[r];
      r++;
      count++;
    }
    pos++;
  }

  for (int i = l; i < (right - left + 1) / 2; i++) {
    arr[pos] = arr_l[i];
    pos++;
  }
  for (int i = r; i < (right - left + 1) / 2; i++) {
    arr[pos] = arr_r[i];
    pos++;
  }

  delete[] arr_l;
  delete[] arr_r;

  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}

void sortAlg::mergeSort(ofstream &fout, int left, int right, int &count) {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////

  if (left < right) {

    mergeSort(fout, left, (left + right) / 2, count);
    mergeSort(fout, (left + right) / 2 + 1, right, count);
    merge(left, right, count);

    printArray(fout); // DO NOT ERASE THIS LINE
  }

  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}
