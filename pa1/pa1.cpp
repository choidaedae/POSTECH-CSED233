#include <iostream>
#include <fstream>
#include <string>
#include "utils.h"
#include <climits>
using namespace std;


/* 
    [Task 1] Choose the TIGHT bound of the following maxProduct function
    
    *maxProduct*
        Input
        - int n: the length of the input arrays (n >=1)
        - int* A: an array storing n >= 1 integers
        - int* B: an array storing n >= 1 integers
        Output
        - int: The maximum product of elements from each A and B
        int maxProduct(int n, int* A, int* B) { 
            int currMax = 0; 
            for (int i = 1; i < n; i++) 
                for (int j = 1; j < n; j++) 
                    if (currMax < A[i]*B[j]) 
                        currMax = A[i]*B[j]; 
            return currMax; 
        } 

    Choices
        1: O( 1 )
        2: O( n )
        3: O( n log(n) )
        4: O( n^2 )
*/
void task_1(ofstream &fout) {
    int answer = 4;  // TODO: Change to your answer

    fout << "[Task 1]" << endl;
    fout << answer << endl;

    return;
}

/*
    [Task 2] Choose the TIGHT bound of the following medianSearch function

    *medianSearch*
        Input
        - int n: the length of the input array (n >=2)
        - double* A: an ascending sorted array with n >=2 integers
        Output
        - double*: An array B which contains n-th, n/2-th, n/4-th, .. elements of A
        double* medianSearch(int n, double* A) { 
            double *B = new double[n]; 
            //B is allocated as same size as A  
            int j = 0; 
            for (int i = n; i >= 1; i = i/2) { 
                B[j] = A[i-1]; 
                j++; 
            } 
            return B; 
        } 

    Choices
        1: O( log(n) )
        2: O( n log(n) )
        3: O( n )
        4: O( n^2 )
*/
void task_2(ofstream &fout) {

    int answer = 1;  // TODO: Change to your answer

    fout << "[Task 2]" << endl;
    fout << answer << endl;

    return;
}

/*
    [Task 3] List

    Description:
        Implement a function that can insert or delete an integer into the ascending order “sorted” list. 
        An user can delete a specified smallest element. 
        If the specified element is out of range of the given list, print “error” 
 
        Tips: Please do not try to implement sorting algorithm for this task

    Input:
        Sequence of commands, which is one of the following
        - (‘insert’,integer): insert integer into the appropriate position in the sorted list.  
        - (‘delete_at’,i): delete an item that is i-th smallest element in the list. i indicates zero-based index. 

    Output: 
        - An array after insertion/deletion in a string separated with the spacebar 
        - “error” if the index is out of range
*/

void task_3(ofstream &fout, InstructionSequence* instr_seq) {

    string answer;

    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////

    typedef struct node {

        int data;
        node* next;

    } NODE;

     typedef struct { // head와 tail이 존재하는 단방향 연결 리스트 

        int size; 
        node* head;
      

    } LIST;

    
     LIST list; 
     list.size = 0; list.head = NULL;
     NODE head;
     head.next = NULL; head.data = INT_MIN; 
     list.head = &head;
     
     NODE* pnode = list.head->next;
     bool error = false;
     int nodes = 0; // node를 몇 칸 옮겼는지 나타내는 변수 

    for (int i=0; i<instr_seq->length; i++) {
        string command = instr_seq->instructions[i].command;
 

        if (command.compare("insert") == 0) {
            /* TODO: Implement */
            NODE* temp = new NODE; // 노드 동적 할당 
            NODE* pPre = NULL;
            temp->next = NULL;
            temp->data = instr_seq->instructions[i].value; // (insert, n) 에 해당하는 n 값 가져와서 대입 
            

            if (list.head->next == NULL) { // 빈 리스트에 삽입 

                list.head->next = temp; // head와 tail을 모두 temp로 만들어줌 

            }

            
            else { // 채워진 리스트에 삽입

                pnode = list.head->next;
                pPre = list.head; 
                nodes = 0;
                
                for (int i = 0; i < list.size; i++) {

                    if (temp->data > pnode->data) { 

                        pPre = pnode; // 다음 노드로 이동 
                        pnode = pnode->next;
                        nodes++;
                    }

                    else // 노드를 삽입해야 하는 경우 
                    {
                        temp->next = pPre->next;
                        pPre->next = temp;
                        nodes++;
                        break;
                    }
                   
                }

                if (pnode==NULL) { // 끝 노드에 삽입 

                    pPre->next = temp;
                  

                }


                  
            }
            
            list.size++;

        } else if(command.compare("delete_at") == 0) { 
            /* TODO: Implement */

            NODE* temp = new NODE; // 노드 동적 할당 
            pnode = list.head->next;
             int cnt = instr_seq->instructions[i].value; // delete할 노드의 순서를 가져옴 

             if (list.size <= cnt) { // 유효한 입력: list.size가 cnt보다 큰 경우 (cnt는 zero-based index) 

                 error = true;
                 break; //반복문을 즉시 빠져나옴 
             
             }
              
             else if(list.size==1 && cnt == 0){ // 리스트에 하나만 채워져 있는 경우 

                 temp = list.head->next;
                 delete(temp);
                 list.head->next = NULL;
               
             }

             else { // 올바른 delete command가 입력되었고 cnt가 1 이상인 경우 

                 for (int i = 0; i < cnt - 1; i++) pnode = pnode->next; // pnode == pPre(delete하려는 대상의 바로 이전을 나타낼 때까지 for문 돌림)
                 temp = pnode->next;
                 pnode->next = temp->next;
                 delete(temp); // 동적할당 해제
                 
             }

            list.size--; 

        } else {
            cerr << "Invalid command" << endl;
            exit(-1);
        }
    }

    if (error == true) answer = "error";

    else {

        pnode = list.head->next;

        
        for (int i = 0; i < list.size; i++) {

            answer = answer + to_string(pnode->data) + " ";
            pnode = pnode->next;

        }
    
    }

   
    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////

    
    fout << "[Task 3]" << endl;
    fout << answer << endl;
   
}

/*
    [Task 4] Stack

    Description:
        Implement a function that prints the top values of the stack when “top” operation is called after the sequence of “push” or “pop” operations. 
        If the stack is empty, and the “top” operation is called, then print “-1”, If “pop” operation from the empty stack then print “error” 

    Input:
        Sequence of commands, which is one of the following,
        - (‘push’,integer): push integer into the current stack (integer is always positive) 
        - (‘pop’,NULL): pop the top value of the current stack (this operation will print nothing) 
        - (‘top’,NULL): print the top value of the current stack (print ‘-1’ if the current stack is empty) 

    Output:
        - Expected printed values after processing the whole sequence, in a string separated with the spacebar 
        - “error” if the pop operation is executed on an empty stack 
*/

void task_4(ofstream &fout, InstructionSequence* instr_seq) {
    string answer;
    
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////

    typedef struct node {

        node* next;
        int data;

    }NODE;

    typedef struct stack { // 가장 윗부분을 가리키는 포인터와 스택 내 node 수를 세는 count 저장 

        int count;
        NODE* top; 

    }STACK;

    STACK stack; 
    stack.count = 0; stack.top = NULL;
    bool error = false;

    for (int i=0; i<instr_seq->length; i++) {
        string command = instr_seq->instructions[i].command;
        if (command.compare("push") == 0) {
            /* TODO: Implement */

            NODE* temp = new NODE;
            temp->data = instr_seq->instructions[i].value;
            temp->next = stack.top;
            stack.top = temp; 
            stack.count++;
            

        } else if (command.compare("pop") == 0 ){
            /* TODO: Implement */

            if (stack.count == 0) { // 빈 스택에서 pop을 시도하는 경우 

                error = true;
                break; // 즉시 반복문 빠져나옴

            }


            else {

                NODE* temp = new NODE;
                temp = stack.top;
                stack.top = stack.top->next;
                delete(temp);
                stack.count--;
            }


        } else if ( command.compare("top") == 0 ){      

            /* TODO: Implement */
            string top;
            if (stack.count == 0) top = "-1"; // 빈 리스트에서 top을 출력 시도할 경우 
            else top = to_string(stack.top->data) + " ";

            answer = answer + top;
              
          
        } else {
            cerr << "Invalid command" << endl;
            exit(-1);
        }
    }

    if (error == true) answer = "error"; // error일 경우 

    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
    
    fout << "[Task 4]" << endl;
    fout << answer << endl;

}

/*
    [Task 5] Queue

    Description:
        - Implement a function which shows the value in the queue from the head to tail.

    Input:
        Sequence of commands, which is one of the following,
        -(‘enqueue’,integer): enqueue integer into the current queue

    Output: 
        - Values in the queue from the head to the tail, in a string separated with the spacebar 
        
*/
void task_5(ofstream &fout, InstructionSequence* instr_seq) { // enqueue 기능만 구현하는 queue
    string answer; 

    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////

    typedef struct node 
    {
        int data;
        node* next;

    } NODE;

   
    typedef struct //front와 rear이 있는 큐 
    {

        int count;
        NODE* front;
        NODE* rear;

    } QUEUE;

    QUEUE q;
    q.count = 0; q.front = NULL; q.rear = NULL;
    NODE* pnode = q.front;

    for (int i=0; i < instr_seq->length; i++) {
        string command = instr_seq->instructions[i].command;
        
        if (command.compare("enqueue") == 0) {
            /* TODO: Implement */

            NODE *temp = new NODE; // temp node 동적할당 
            temp->data = instr_seq->instructions[i].value; //데이터 채워줌 
            
            if (q.count == 0) { // 빈 큐에 삽입하는 경우 

                q.front = temp; // front와 rear 둘 다 temp임 
                q.rear =  temp;

            }

            else {

                q.rear->next = temp;
                q.rear = temp;

            }
            
            q.count++;

        } else {
            cerr << "Invalid command" << endl;
            exit(-1);
        }
    }

    pnode = q.front;

    for (int i = 0; i < q.count; i++) {

        answer = answer + to_string(pnode->data) + " ";
        pnode = pnode->next;
    }
    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
    


    fout << "[Task 5]" << endl;
    fout << answer << endl;

    
}

/*
    [Task 6] Queue

    Description: 
        Implement a function which shows the value of a queue after the sequence of arbitrary queue operation. 
        If the queue after the operations is empty, print “empty”. 
        If “dequeue” operates on an empty queue, print “error”.

    Input:
        Sequence of commands, which is one of the following,
        - (‘enqueue’,integer): enqueue integer into the current queue
        - (‘dequeue’,NULL): dequeue from the current queue 

    Output
        - Values in the queue from the head to the tail, in a string separated with spacebar 
        - “empty” if the queue is empty
        - “error” if the “dequeue” operation is executed on an empty queue
*/
void task_6(ofstream &fout, InstructionSequence* instr_seq) { // enqueue, dequeue 기능을 구현한 task 
    string answer;
    
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////

    typedef struct node
    {
        int data;
        node* next;

    } NODE;


    typedef struct //front와 rear이 있는 큐 
    {

        int count;
        NODE* front;
        NODE* rear;

    } QUEUE;

    QUEUE q;
    q.count = 0; q.front = NULL; q.rear = NULL;
    NODE* pnode = q.front;
    bool error = false;

    for (int i=0; i < instr_seq->length; i++) {
        string command = instr_seq->instructions[i].command;
       
        if (command.compare("enqueue") == 0) {
            /* TODO: Implement */
            NODE* temp = new NODE; // temp node 동적 할당 
            temp->data = instr_seq->instructions[i].value; // 값 넣어줌 

            if (q.count == 0) { // 빈 큐에 삽입

                q.front = temp;
                q.rear = temp;

            }

            else { // 차 있는 큐에 삽입 

                q.rear->next = temp;
                q.rear = temp;

            }

            q.count++;

        } else if (command.compare("dequeue") == 0) { 

            /* TODO: Implement */
            NODE* temp = new NODE;

            if (q.count == 0) {

                error = true; // 반복문을 즉시 빠져나옴
                break;

            }

            else {

                temp = q.front;
                q.front = q.front->next;
                delete(temp);
                q.count--;

            }



        } else {
            cerr << "Invalid command" << endl;
            exit(-1);
        }
    }
    
    if (q.count == 0) answer = "empty"; // queue가 비어 있는 경우 
    if (error == true) answer = "error"; // error인 경우 
    else { // queue가 일부 차 있는 경우 

        pnode = q.front;
        for (int i = 0; i < q.count; i++) {
            answer = answer + to_string(pnode->data) + " ";
            pnode = pnode->next;
        }
    }
    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
    
    fout << "[Task 6]" << endl;
    fout << answer << endl;
 
}


int main(int argc, char **argv) {
    string filename = "submit.txt";
    int task_num = 0;
    InstructionSequence* instr_seq = NULL;

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
        }
        catch (const char* e) {
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

            InstructionSequence* instr_seq_3;
            instr_seq_3 = ParseInstructions(TASK_3_DEFAULT_ARGUMENT);
            task_3(fout, instr_seq_3);
            
            InstructionSequence* instr_seq_4;
            instr_seq_4 = ParseInstructions(TASK_4_DEFAULT_ARGUMENT);
            task_4(fout, instr_seq_4);
            
            InstructionSequence* instr_seq_5;
            instr_seq_5 = ParseInstructions(TASK_5_DEFAULT_ARGUMENT);
            task_5(fout, instr_seq_5);
            
            InstructionSequence* instr_seq_6;
            instr_seq_6 = ParseInstructions(TASK_6_DEFAULT_ARGUMENT);
            task_6(fout, instr_seq_6);
            break;
        default:
            cout << "Wrong task number" << endl;
    }

    fout.close();
    return 0;
}