#include "hash_function.h"
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int BinaryMidSquareHash::hashing(int key) {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////

  int square = pow(key, 2);
  int value = 0;
  int count = index_size - 1;

  for (int i = pow(2, 2 * key_size - 1); i >= 1; i /= 2) {
    if (i <= pow(2, key_size + index_size / 2 - 1) &&
        i >= pow(2, key_size - index_size / 2)) {
      if (square / i == 1) {
        value += pow(2, count);
      }
      count--;
    }
    if (count < 0) {
      return value;
    }
    square = square % i;
  }

  return -1;
  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}

int DigitFoldingHash::hashing(int key) {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////

  int value = 0;

  for (int i = pow(2, key_size - 1); i >= 1; i /= 2) {
    value += key / i;
    key = key % i;
  }

  return value;

  return -1;
  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}

int MultiplicationHash::hashing(int key) {
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////

  return floor(pow(2, index_size) * fmod(A * key, 1));

  return -1;
  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////
//////////  TODO: Implement From Here      //////////////

/*  Write your codes if you have additional functions  */

///////////      End of Implementation      /////////////
/////////////////////////////////////////////////////////
