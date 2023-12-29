#include "utils.h"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

/*
    [Task 1] Choose the TIGHT bound of the following arrayInsert function

    *arrayInsert*
        Input
        - int n: the length of the input arrays (n >=1)
        - int* A: an array storing n integers
        - int x: an element to insert
        - int pos : index position to insert element
        Output
        - int: The maximum product of elements from each A and B
        void arrayInsert(int n, int* A, int x, int pos) {
            n++;
            for (int i = n; i >= pos; i--)
                A[i] = A[i-1];
            A[pos – 1] = x;
            return;
        }

    Choices
        1: O( 1 )
        2: O( n )
        3: O( n log(n) )
        4: O( n^2 )
*/
void task_1(ofstream &fout) {
  int answer = 2; // TODO: Change to your answer

  fout << "[Task 1]" << endl;
  fout << answer << endl;

  return;
}

/*
    [Task 2] Choose the TIGHT bound of the following maxSubarraySum function

    *maxSubarraySum*
        Input
        - int n: the length of the input array (n >=1)
        - int* A: an array with n >=1 integers
        Output
        - int: maximum value of sum of subarray of A. Define subarray as { A[i],
   A[i+1], …, A[j] } for all integer i <= j < n. int maxSubarraySum(int n, int
   *A) { int max_sum = 0; for (int i = 0; i < n; i++) { for (int j = i; j < n;
   j++) { int cur_sum = 0; for (int k = i; k <= j; k++) { cur_sum += A[k];
                    }
                    if (cur_sum > max_sum){
                        max_sum = cur_sum;
                    }
                }
            }
            return max_sum;
        }

    Choices
        1: O( n log(n) )
        2: O( n )
        3: O( n^2 )
        4: O( n^3 )
*/
void task_2(ofstream &fout) {
  int answer = 4; // TODO: Change to your answer

  fout << "[Task 2]" << endl;
  fout << answer << endl;

  return;
}

/*
    [Task 3] List

    Description:
        Implement a function that can insert or replace an integer in the list.
        A user can insert or replace an element at the specific index.
        If the specified index is out of range of the given list, print “error”.

    Input:
        Sequence of commands, which is one of the following
        - (‘insert’,i): insert i into the i-th index in the list. i-th index
   indicates zero-based index.
        - (‘replace_at’,index): replace an element at the index to 0. index
   indicates zero-based index.

    Output:
        - An array after insertion/deletion in a string separated with the
   spacebar
        - “error” if the index is out of range
*/
void task_3(ofstream &fout, InstructionSequence *instr_seq) {
  string answer;

  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////

  struct NODE // list의 NODE 구조체
  {
    int data;   // NODE의 data
    NODE *next; //다음 NODE를 가리키는 포인터
  };

  NODE *head = NULL; //첫 NODE를 가리키는 포인터 선언 및 NULL로 초기화
  NODE *ppre = NULL; //이전 NODE를 가리키는 포인터 선언 및 NULL로 초기화
  NODE *pcur = NULL; //현재 NODE를 가리키는 포인터 선언 및 NULL로 초기화
  int count = 0;       // NODE 개수 선언 및 0으로 초기화
  string insert_value; //삽입할 값
  int error_value = 0; // error를 확인하는 변수 선언 및 0으로 초기화

  for (int i = 0; i < instr_seq->length; i++) {
    string command = instr_seq->instructions[i].command;
    if (command.compare("insert") == 0) {
      /* TODO: Implement */

      if (instr_seq->instructions[i].value >= count + 1 ||
          instr_seq->instructions[i].value < 0) { //값의 범위가 올바르지 않으면
        error_value = -1; // error를 확인하는 변수 = -1
        answer = "error"; // answer string에 error 입력
        break;            //반복문 종료
      }

      ppre = head; // ppre는 head를 가리킴

      NODE *node = new NODE;                         //새 node 생성
      node->data = instr_seq->instructions[i].value; //새 node의 data에 값 입력
      node->next = NULL; //다음 NODE를 가리키는 포인터 NULL로 초기화

      if (head == NULL) { //빈 list이면
        head = node;      //새 node를 head로 지정
        count++;          // NODE 총 개수 1 증가
      } else {            //빈 list가 아니면
        if (node->data == 0) { // data 값이 0이면 (삽입할 곳이 첫 번째 NODE이면)
          node->next = head; //새 node의 next는 head를 가리킴
          head = node;       //새 node를 head로 지정
          count++;           // NODE 총 개수 1 증가
        } else { // data 값이 0이 아니면 (삽입할 곳이 NODE의 중간 혹은 끝이면)
          for (int j = 0; j < node->data - 1; j++) { //삽입할 곳 직전까지 반복
            ppre = ppre->next; // ppre는 ppre의 next를 가리킴
          }
          pcur = ppre->next; // pcur는 ppre의 next를 가리킴
          ppre->next = node; // ppre의 next는 새 node를 가리킴
          node->next = pcur; //새 node의 next는 pcur를 가리킴
          count++;           // NODE 총 개수 1 증가
        }
      }

    } else if (command.compare("replace_at") == 0) {
      /* TODO: Implement */

      if (instr_seq->instructions[i].value >= count ||
          instr_seq->instructions[i].value < 0) { //값의 범위가 올바르지 않으면
        error_value = -1; // error를 확인하는 변수 = -1
        answer = "error"; // answer string에 error 입력
        break;            //반복문 종료
      }

      pcur = head; // pcur는 head를 가리킴

      for (int j = 0; j < instr_seq->instructions[i].value;
           j++) {          //입력받은 값만큼 반복
        pcur = pcur->next; // pcur는 pcur의 next를 가리킴
      }
      pcur->data = 0; //현재 NODE의 data 값을 0으로 대체

    } else {
      cerr << "Invalid command" << endl;
      exit(-1);
    }
  }

  if (error_value == 0) {             // error가 없으면
    pcur = head;                      // pcur는 head를 가리킴
    for (int a = 0; a < count; a++) { // NODE 총 개수만큼 반복
      insert_value = to_string(
          pcur->data); // answer string에 삽입할 값 입력 (to_string 함수를
                       // 이용하여 int형인 NODE의 data를 string형으로 변환)
      answer += insert_value; // answer string에 값 입력
      answer += ' ';          //공백 추가
      pcur = pcur->next;      //다음 NODE를 가리킴
    }
  }

  while (head != NULL) { // head가 NULL일 때까지 반복
    pcur = head;         // pcur는 head를 가리킴
    head = head->next;   // head는 head의 next를 가리킴
    count--;             // NODE 총 개수 1 감소
    delete pcur;         // pcur NODE 동적 할당 해제
    pcur = NULL;         // pcur NULL로 초기화
  }
  ppre = NULL; // ppre NULL로 초기화

  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////

  fout << "[Task 3]" << endl;
  fout << answer << endl;
}

/*
    [Task 4] Stack

    Description:
        Implement a function that prints the top values of the stack when “top”
   operation is called after the sequence of “push” or “pop” operations. If the
   “top” operation is called for an empty stack, print “-1”, If “pop” operation
   is called for an empty stack, print “error” and the program terminates. The
   stack can contain positive integers.

    Input:
        Sequence of commands, which is one of the following,
        - (‘push’,integer): push integer into the current stack, if integer is
   negative, skip the push step
        - (‘pop’,NULL): pop the top value of the current stack (this operation
   will print nothing)
        - (‘top’,NULL): print the top value of the current stack (print ‘-1’ if
   the current stack is empty)

    Output:
        - Expected printed values after processing the whole sequence, in a
   string separated with the spacebar
        - “error” if the pop operation is executed on an empty stack, and then
   the program terminates.

*/
void task_4(ofstream &fout, InstructionSequence *instr_seq) {
  string answer;

  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////

  struct NODE { // stack의 NODE 구조체
    int data;   // NODE의 data
    NODE *next; //다음 NODE를 가리키는 포인터
  };

  NODE *ptop = NULL; // top NODE를 가리키는 포인터 선언 및 NULL로 초기화
  NODE *pcur = NULL; //현재 NODE를 가리키는 포인터 선언 및 NULL로 초기화
  int count = 0;       // NODE 개수 선언 및 0으로 초기화
  string insert_value; //삽입할 값
  int error_value = 0; // error를 확인하는 변수 선언 및 0으로 초기화

  for (int i = 0; i < instr_seq->length; i++) {
    string command = instr_seq->instructions[i].command;
    if (command.compare("push") == 0) {
      /* TODO: Implement */

      if (instr_seq->instructions[i].value < 0) { //입력받은 값이 음수이면
        continue;                                 // push skip
      }

      NODE *node = new NODE;                         //새 node 생성
      node->data = instr_seq->instructions[i].value; //새 node의 data에 값 입력
      node->next = NULL; //다음 NODE를 가리키는 포인터 NULL로 초기화

      if (ptop == NULL) {  //빈 stack이면
        ptop = node;       //새 node를 ptop으로 지정
        count++;           // NODE 총 개수 1 증가
      } else {             //빈 stack이 아니면
        node->next = ptop; //새 node의 next는 ptop을 가리킴
        ptop = node;       //새 node를 ptop으로 지정
        count++;           // NODE 총 개수 1 증가
      }

    } else if (command.compare("pop") == 0) {
      /* TODO: Implement */

      if (ptop == NULL) //빈 stack이면
      {
        error_value = -1; // error를 확인하는 변수 = -1
        answer = "error"; // answer string에 error 입력
        break;            //반복문 종료
      }

      pcur = ptop;       // pcur는 ptop을 가리킴
      ptop = ptop->next; // ptop은 ptop의 next를 가리킴
      count--;           // NODE 총 개수 1 감소
      delete pcur;       // pcur NODE 동적 할당 해제
      pcur = NULL;       // pcur NULL로 초기화

    } else if (command.compare("top") == 0) {
      /* TODO: Implement */

      if (ptop == NULL) { //빈 stack이면
        error_value = -1; // error를 확인하는 변수 = -1
        insert_value = to_string(
            error_value); // answer string에 삽입할 값 입력 (to_string 함수를
                          // 이용하여 int형인 error_value를 string형으로 변환)
        error_value = 0; // error를 확인하는 변수 = 0
      } else {           //빈 stack이 아니면
        insert_value = to_string(
            ptop->data); // answer string에 삽입할 값 입력 (to_string 함수를
                         // 이용하여 int형인 NODE의 data를 string형으로 변환)
      }
      answer += insert_value; // answer string에 값 입력
      answer += ' ';          //공백 추가

    } else {
      cerr << "Invalid command" << endl;
      exit(-1);
    }
  }

  while (ptop != NULL) { // ptop이 NULL일 때까지 반복
    pcur = ptop;         // pcur는 ptop을 가리킴
    ptop = ptop->next;   // ptop은 ptop의 next를 가리킴
    count--;             // NODE 총 개수 1 감소
    delete pcur;         // pcur NODE 동적 할당 해제
    pcur = NULL;         // pcur NULL로 초기화
  }

  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////

  fout << "[Task 4]" << endl;
  fout << answer << endl;
}

/*
    [Task 5] Circular Queue

    Desctiption:
        Implement a function that shows the values in a circular queue with a
   Boolean indicator. If the queue after the operations is empty, print “empty”.
        If “enqueue” operates on a full queue or if “dequeue” operates on an
   empty queue, print “error”. The maximum number of elements (n) in the queue
   is four.

    Input:
        Sequence of commands, which is one of the following,
        - (‘enqueue’,integer): enqueue integer into the current queue
        - (‘dequeue’,NULL): dequeue from the current queue

    Output
        - Values in the circular queue (mod size n = 4), from the front to the
   rear. String separated with the spacebar, empty memory shows NULL
        - “empty” if the queue is empty when the operations are terminated
   normally
        - “error” if the “dequeue” operation is executed on an empty queue or if
   the “enqueue” operation is executed on a full queue
*/
void task_5(ofstream &fout, InstructionSequence *instr_seq) {
  string answer;
  int queue_size = 4;
  int queue[4] = {};
  bool is_empty = true;

  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////

  struct NODE { // circular queue의 NODE 구조체
    int data;   // NODE의 data
    NODE *next; //다음 NODE를 가리키는 포인터
  };

  NODE *front = NULL; // front NODE를 가리키는 포인터 선언 및 NULL로 초기화
  NODE *rear = NULL; // rear NODE를 가리키는 포인터 선언 및 NULL로 초기화
  NODE *pcur = NULL; //현재 NODE를 가리키는 포인터 선언 및 NULL로 초기화
  int count = 0;       // NODE 개수 선언 및 0으로 초기화
  string insert_value; //삽입할 값
  int error_value = 0; // error를 확인하는 변수 선언 및 0으로 초기화

  for (int i = 0; i < instr_seq->length; i++) {
    string command = instr_seq->instructions[i].command;
    if (command.compare("enqueue") == 0) {
      /* TODO: Implement */

      if (count == 4) // full queue이면
      {
        error_value = -1; // error를 확인하는 변수 = -1
        answer = "error"; // answer string에 error 입력
        break;            //반복문 종료
      }

      NODE *node = new NODE;                         //새 node 생성
      node->data = instr_seq->instructions[i].value; //새 node의 data에 값 입력
      node->next = NULL; //다음 NODE를 가리키는 포인터 NULL로 초기화

      if (front == NULL) //빈 queue이면
      {
        front = node;      //새 node를 front로 지정
        rear = node;       //새 node를 rear로 지정
        count++;           // NODE 총 개수 1 증가
      } else {             //빈 queue가 아니면
        rear->next = node; // rear의 next는 새 node를 가리킴
        rear = node;       //새 node를 rear로 지정
        count++;           // NODE 총 개수 1 증가
      }

    } else if (command.compare("dequeue") == 0) {
      /* TODO: Implement */

      if (count == 0) {        //빈 queue이면
        error_value = -1;      // error를 확인하는 변수 = -1
        answer = "error";      // answer string에 error 입력
        break;                 //반복문 종료
      } else if (count == 1) { // queue의 요소가 1개이면
        pcur = front;          // pcur는 front를 가리킴
        count--;               // NODE 총 개수 1 감소
        delete pcur;           // pcur NODE 동적 할당 해제
        pcur = NULL;           // pcur NULL로 초기화
        front = NULL;          // front NULL로 초기화
        rear = NULL;           // rear NULL로 초기화
      } else {                 // queue의 요소가 2개 이상이면
        pcur = front;          // pcur는 front를 가리킴
        front = front->next;   // front는 front의 next를 가리킴
        count--;               // NODE 총 개수 1 감소
        delete pcur;           // pcur NODE 동적 할당 해제
        pcur = NULL;           // pcur NULL로 초기화
      }

    } else {
      cerr << "Invalid command" << endl;
      exit(-1);
    }
  }

  if (error_value == 0) {               // error가 없으면
    if (count == 0) {                   //빈 queue이면
      answer = "empty";                 // answer string에 empty 입력
    } else {                            //빈 queue가 아니면
      pcur = front;                     // pcur는 front를 가리킴
      for (int a = 0; a < count; a++) { // NODE 총 개수만큼 반복
        insert_value = to_string(
            pcur->data); // answer string에 삽입할 값 입력 (to_string 함수를
                         // 이용하여 int형인 NODE의 data를 string형으로 변환)
        answer += insert_value; // answer string에 값 입력
        answer += ' ';          //공백 추가
        pcur = pcur->next;      //다음 NODE를 가리킴
      }
    }
  }

  while (front != NULL) { // front가 NULL일 때까지 반복
    pcur = front;         // pcur는 front를 가리킴
    front = front->next;  // front는 front의 next를 가리킴
    count--;              // NODE 총 개수 1 감소
    delete pcur;          // pcur NODE 동적 할당 해제
    pcur = NULL;          // pcur NULL로 초기화
  }
  rear = NULL; // rear NULL로 초기화

  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////

  fout << "[Task 5]" << endl;
  fout << answer << endl;
}

/*
    [Task 6] Double-Ended Queue

    Description:
        Implement a function that shows the values in a double-ended queue
   (deque) whose maximum number of elements is four. If “insert” is called for
   an already full deque or the “erase” operation is called for an empty deque,
   there should be no changes to the queue.

    Input:
        Sequence of commands, which is one of the following,
        - (‘insert_front’,integer): insert integer at the beginning of the
   deque.
        - (‘insert_back’,integer): insert integer at the end of the deque.
        - (‘erase_front’,NULL): erase the first element the queue.
        - (‘erase_back’,NULL): erase the last element the queue.

    Output
        - Values in the queue from the beggining to the end, in a string
   separated with spacebar
        - “empty” if the queue is empty
*/
void task_6(ofstream &fout, InstructionSequence *instr_seq) {
  string answer;

  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////

  struct NODE { // double-ended queue의 NODE 구조체
    int data;   // NODE의 data
    NODE *next; //다음 NODE를 가리키는 포인터
    NODE *prev; //이전 NODE를 가리키는 포인터
  };

  NODE *header = new NODE;  // header NODE 생성
  NODE *trailer = new NODE; // trailer NODE 생성
  NODE *pcur = NULL; //현재 NODE를 가리키는 포인터 선언 및 NULL로 초기화
  int count = 0;       // NODE 개수 선언 및 0으로 초기화
  string insert_value; //삽입할 값

  header->next = trailer; // header의 next는 trailer를 가리킴
  trailer->prev = header; // trailer의 prev는 header를 가리킴

  for (int i = 0; i < instr_seq->length; i++) {
    string command = instr_seq->instructions[i].command;
    if (command.compare("insert_front") == 0) {
      /* TODO: Implement */

      if (count == 4) // full queue이면
      {
        continue;              // insert_front skip
      } else {                 // full queue가 아니면
        NODE *node = new NODE; //새 node 생성
        node->data =
            instr_seq->instructions[i].value; //새 node의 data에 값 입력
        node->next = NULL; //다음 NODE를 가리키는 포인터 NULL로 초기화
        node->prev = NULL; //이전 NODE를 가리키는 포인터 NULL로 초기화

        if (count == 0) //빈 queue이면
        {
          header->next = node;  // header의 next는 새 node를 가리킴
          node->prev = header;  //새 node의 prev는 header를 가리킴
          trailer->prev = node; // trailer의 prev는 새 node를 가리킴
          node->next = trailer; //새 node의 next는 trailer를 가리킴
          count++;              // NODE 총 개수 1 증가
        } else {                //빈 queue가 아니면
          node->next = header->next; //새 node의 next는 header의 next를 가리킴
          header->next->prev = node; // header의 next의 prev는 새 node를 가리킴
          header->next = node; // header의 next는 새 node를 가리킴
          node->prev = header; //새 node의 prev는 header를 가리킴
          count++;             // NODE 총 개수 1 증가
        }
      }

    } else if (command.compare("insert_back") == 0) {
      /* TODO: Implement */

      if (count == 4) // full queue이면
      {
        continue;              // insert_back skip
      } else {                 // full queue가 아니면
        NODE *node = new NODE; //새 node 생성
        node->data =
            instr_seq->instructions[i].value; //새 node의 data에 값 입력
        node->next = NULL; //다음 NODE를 가리키는 포인터 NULL로 초기화
        node->prev = NULL; //이전 NODE를 가리키는 포인터 NULL로 초기화

        if (count == 0) //빈 queue이면
        {
          header->next = node;  // header의 next는 새 node를 가리킴
          trailer->prev = node; // trailer의 prev는 새 node를 가리킴
          node->prev = header;  //새 node의 prev는 header를 가리킴
          node->next = trailer; //새 node의 next는 trailer를 가리킴
          count++;              // NODE 총 개수 1 증가
        } else {                //빈 queue가 아니면
          trailer->prev->next =
              node; // trailer의 prev의 next는 새 node를 가리킴
          node->prev = trailer->prev; //새 node의 prev는 trailer의 prev를 가리킴
          trailer->prev = node; // trailer의 prev는 새 node를 가리킴
          node->next = trailer; //새 node의 next는 trailer를 가리킴
          count++;              // NODE 총 개수 1 증가
        }
      }

    } else if (command.compare("erase_front") == 0) {
      /* TODO: Implement */

      if (count == 0) {            //빈 queue이면
        continue;                  // erase_front skip
      } else if (count == 1) {     // queue의 요소가 1개이면
        pcur = header->next;       // pcur는 header의 next를 가리킴
        header->next = trailer;    // header의 next는 trailer를 가리킴
        trailer->prev = header;    // trailer의 prev는 header를 가리킴
        delete pcur;               // pcur NODE 동적 할당 해제
        pcur = NULL;               // pcur NULL로 초기화
        count--;                   // NODE 총 개수 1 감소
      } else {                     // queue의 요소가 2개 이상이면
        pcur = header->next;       // pcur는 header의 next를 가리킴
        header->next = pcur->next; // header의 next는 pcur의 next를 가리킴
        pcur->next->prev = header; // pcur의 next의 prev는 header를 가리킴
        delete pcur;               // pcur NODE 동적 할당 해제
        pcur = NULL;               // pcur NULL로 초기화
        count--;                   // NODE 총 개수 1 감소
      }

    } else if (command.compare("erase_back") == 0) {
      /* TODO: Implement */

      if (count == 0) {             //빈 queue이면
        continue;                   // erase_back skip
      } else if (count == 1) {      // queue의 요소가 1개이면
        pcur = trailer->prev;       // pcur는 trailer의 prev를 가리킴
        header->next = trailer;     // header의 next는 trailer를 가리킴
        trailer->prev = header;     // trailer의 prev는 header를 가리킴
        delete pcur;                // pcur NODE 동적 할당 해제
        pcur = NULL;                // pcur NULL로 초기화
        count--;                    // NODE 총 개수 1 감소
      } else {                      // queue의 요소가 2개 이상이면
        pcur = trailer->prev;       // pcur는 trailer의 prev를 가리킴
        trailer->prev = pcur->prev; // trailer의 prev는 pcur의 prev를 가리킴
        pcur->prev->next = trailer; // pcur의 prev의 next는 trailer를 가리킴
        delete pcur;                // pcur NODE 동적 할당 해제
        pcur = NULL;                // pcur NULL로 초기화
        count--;                    // NODE 총 개수 1 감소
      }

    } else {
      cerr << "Invalid command" << endl;
      exit(-1);
    }
  }

  if (count == 0) {                   //빈 queue이면
    answer = "empty";                 // answer string에 empty 입력
  } else {                            //빈 queue가 아니면
    pcur = header->next;              // pcur는 header의 next를 가리킴
    for (int a = 0; a < count; a++) { // NODE 총 개수만큼 반복
      insert_value = to_string(
          pcur->data); // answer string에 삽입할 값 입력 (to_string 함수를
                       // 이용하여 int형인 NODE의 data를 string형으로 변환)
      answer += insert_value; // answer string에 값 입력
      answer += ' ';          //공백 추가
      pcur = pcur->next;      //다음 NODE를 가리킴
    }
  }

  pcur = header->next;      // pcur는 header의 next를 가리킴
  NODE *temp = NULL;        //임시 NODE 생성
  while (pcur != trailer) { // pcur가 trailer일 때까지 반복
    temp = pcur->next;      // temp는 pcur의 next를 가리킴
    count--;                // NODE 총 개수 1 감소
    delete pcur;            // pcur NODE 동적 할당 해제
    pcur = temp;            // pcur는 temp를 가리킴
  }
  delete header;  // header 동적 할당 해제
  delete trailer; // trailer 동적 할당 해제
  header = NULL;  // header NULL로 초기화
  trailer = NULL; // trailer NULL로 초기화
  pcur = NULL;    // pcur NULL로 초기화
  temp = NULL;    // temp NULL로 초기화

  ///////////      End of Implementation      /////////////
  /////////////////////////////////////////////////////////

  fout << "[Task 6]" << endl;
  fout << answer << endl;
}

int main(int argc, char **argv) {
  string filename = "submit.txt";
  int task_num = 0;
  InstructionSequence *instr_seq;

  // Open file
  ofstream fout;
  fout.open(filename, fstream::app);
  if (!fout.is_open()) {
    cerr << "Unable to open file: " << filename << endl;
    return -1;
  }

  // Choosing task number. Default is running ALL tasks (0)
  if (argc >= 2)
    task_num = atoi(argv[1]);
  if (argc >= 3) {
    try {
      instr_seq = ParseInstructions(argv[2]);
    } catch (const char *e) {
      cerr << e << endl;
      return -1;
    }
  }

  // Running the task(s)
  switch (task_num) {
  case 1:
    task_1(fout);
    break;
  case 2:
    task_2(fout);
    break;
  case 3:
    task_3(fout, instr_seq);
    break;
  case 4:
    task_4(fout, instr_seq);
    break;
  case 5:
    task_5(fout, instr_seq);
    break;
  case 6:
    task_6(fout, instr_seq);
    break;
  case 0:
    task_1(fout);
    task_2(fout);

    InstructionSequence *instr_seq_3;
    instr_seq_3 = ParseInstructions(TASK_3_DEFAULT_ARGUMENT);
    task_3(fout, instr_seq_3);

    InstructionSequence *instr_seq_4;
    instr_seq_4 = ParseInstructions(TASK_4_DEFAULT_ARGUMENT);
    task_4(fout, instr_seq_4);

    InstructionSequence *instr_seq_5;
    instr_seq_5 = ParseInstructions(TASK_5_DEFAULT_ARGUMENT);
    task_5(fout, instr_seq_5);

    InstructionSequence *instr_seq_6;
    instr_seq_6 = ParseInstructions(TASK_6_DEFAULT_ARGUMENT);
    task_6(fout, instr_seq_6);
    break;
  default:
    cout << "Wrong task number" << endl;
  }

  fout.close();
  return 0;
}
