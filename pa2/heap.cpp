#include "heap.h"
#include <iostream>
#include <string>

using namespace std;


MaxHeap::MaxHeap() {
    heap_size = 0;
    heap_arr = new int[100]; // Default array of size 100
}

string MaxHeap::printHeap(){
    string answer;
    for (int i = 1; i <= heap_size; i++) // heap 배열 자체를 1번 인덱스부터 구현하였음.
        answer += to_string(heap_arr[i]) + " ";
   
    return answer;
}

void MaxHeap::insertKey(int k) {

    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
    
    heap_size++;
    heap_arr[heap_size] = k;
    int child = heap_size; 
    int parent = child/2;
    
    while (child >= 2 &&(heap_arr[child] > heap_arr[parent])) {

            int temp = heap_arr[child];
            heap_arr[child] = heap_arr[parent];
            heap_arr[parent] = temp;
            child = parent;
            parent = child / 2;
    }
  
    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}


void MaxHeap::deleteMax() {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////

 
    heap_arr[1] = -1; // 가장 큰 값 삭제 
    heap_arr[1] = heap_arr[heap_size]; // 맨 뒤 인덱스 가져옴 
    heap_arr[heap_size] = -1; // 맨 뒤 인덱스 값 삭제 
    int cur = 1; int max = 0; // cur: 바꿔주는 노드의 인덱스 , max: 맞바꿀 노드의 인덱스

    heap_size--; // 최종적으로 heap_size가 1 줄어듦 

    while (cur <= heap_size) {

        if (cur * 2 >= heap_size) break; // 유효한 범위여야 함 
        max = heap_arr[cur * 2] > heap_arr[cur * 2 + 1] ? cur * 2 : cur * 2 +1; // 바꿔줄 인덱스 찾아줌 
        int temp = heap_arr[cur]; // swap 과정
        heap_arr[cur] = heap_arr[max];
        heap_arr[max] = temp;
        
        cur = max; // 현재 인덱스는 max값임. 
    }
    //heap_size--; // 최종적으로 heap_size가 1 줄어듦 
   
    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}


void MaxHeap::maxHeapProp(int i) {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////


    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}