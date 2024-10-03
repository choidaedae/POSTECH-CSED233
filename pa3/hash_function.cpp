#include "hash_function.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;


int HashFunction::hashing(int key) {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
    //return -1;
    long long val = key * key;
    //int * arr = new int[key_size*2]{};
    int arr[100] = {};
    dectobin(val);
    return getidx(index_size);
    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////
//////////  TODO: Implement From Here      //////////////

int HashFunction::getidx(int index_size) {

    
    int start = (key_size*2 - index_size) / 2 ; //시작 인덱스 지점 
    int idx = 0;
    int digit = 1; //자릿수 
    for (int i = start; i < start + index_size; i++) {
        
        idx += arr[i]*digit;
        digit *= 2;

    }

    return idx; //인덱스 값 리턴 

}

void HashFunction::dectobin(long long num) { // 10진수를 2진수로 변환, 배열에 넣어줌. 


        int size = 1;
        int *a = new int[2*key_size+1]{};
        for (int i = 0; num != 0; i++) {

            if (i == 2 * key_size) break;

             a[i] = num % 2;
             num = num / 2;
             size++;
             //if (i == 2 * key_size) break;
           
        }

        int idx = 0;

        arr = a;

       // for (int i = 0; i < 2*key_size; i++) {
         //  arr[i] = a[i];

       // }

        return;

    

}

/*  Write your codes if you have additional functions  */

///////////      End of Implementation      /////////////
/////////////////////////////////////////////////////////
