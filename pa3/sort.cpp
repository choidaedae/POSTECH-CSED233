#include "sort.h"
#include <iostream>
#include <fstream>
#include <string>


sortAlg::sortAlg() {
    arr_size = 0;
    arr = new int[100]; // Each test case will be less than 100 values
}

using namespace std;

void sortAlg::printArray(ofstream &fout) {
    string answer;
    for (int i = 0; i < arr_size - 1; i++)
        answer += to_string(arr[i]) + " ";
    answer += to_string(arr[arr_size - 1]);
    fout << answer << endl;
    //cout << answer << endl;
}


void sortAlg::selectionSort(ofstream &fout) {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////


    for (int i = 0; i < arr_size - 1; i++) {

        int min = i;
        for (int j = i; j < arr_size; j++) {

            if (arr[min] > arr[j]) min = j;
        }
        swap(arr[min], arr[i]);
        printArray(fout); // DO NOT ERASE THIS LINE
    }
    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}


void sortAlg::merge(int left, int right) {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////

    
    int t1[20] = {};
    int t2[20] = {};
    int data = right - left + 1; 
    int mid = 0;

    switch (data) {

    case 2:
        mid = left;
        break;
    case 3:
    case 4:
        mid = left + 1;
        break;
    case 5:
    case 6: 
    case 7:
    case 8:
        mid = left + 3;
        break;
    case 9:
    case 10:
    case 11:
    case 12:
    case 13:
    case 14:
    case 15:
    case 16:
        mid = left + 7;
        break;
    case 17:
    case 18:
    case 19:
    case 20:
        mid = left + 15;
        break;

    }
    //int mid = (left + right) / 2;
    int n1, n2, i, j, k;
    n1 = mid - left + 1; // t1 배열 개수 
    n2 = right - mid; // t2 배열 개수 
    for (i = 0; i < n1; i++)
        t1[i] = arr[left + i];
    for (j = 0; j < n2; j++)
        t2[j] = arr[mid + j + 1];

    i = 0; j = 0;

    for (k = left; k <= right; k++)  //process of combining two sorted arrays
    {
        if (j == n2) { //종료 조건 
            for (k; k <=right; k++) {
                arr[k] = t1[i];
                i++;  
            }
            return;
        }

        else if(i == n1) { //종료 조건 
            for (k; k <= right; k++) {
                arr[k] = t2[j];
                j++;
            }
            return;
        }

        if (t1[i] <= t2[j]) arr[k] = t1[i++];

        else arr[k] = t2[j++];
    }

    


    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}


void sortAlg::mergeSort(ofstream &fout, int left, int right) {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////

    // sort.mergeSort(fout, 0, sort.arr_size - 1); 로 호출함

    //return;

    if (left < right) {

        int data = right - left + 1;

        switch (data) {

        case 1:
            printArray(fout);
            break;

        case 2: 
            merge(0, 1);
            printArray(fout);
            break;

        case 3:
            merge(0, 1);
            printArray(fout);
            merge(left, right);
            printArray(fout);
            return;

        case 4:
            merge(0, 1);
            printArray(fout);
            merge(2, 3);
            printArray(fout);
            merge(left, right);
            printArray(fout);
            break;

        case 5:
            merge(0, 1);
            printArray(fout);
            merge(2, 3);
            printArray(fout);
            merge(0, 3);
            printArray(fout);
            merge(left, right);
            printArray(fout);
            break;

        case 6:
            merge(0, 1);
            printArray(fout);
            merge(2, 3);
            printArray(fout);
            merge(4, 5);
            printArray(fout);
            merge(0, 3);
            printArray(fout);
            merge(left, right);
            printArray(fout);
            return;


        case 7:
            merge(0, 1);
            printArray(fout);
            merge(2, 3);
            printArray(fout);
            merge(4, 5);
            printArray(fout);
            merge(0, 3);
            printArray(fout);
            merge(4, 6);
            printArray(fout);
            merge(left, right);
            printArray(fout);
            break;
            
        case 8:
            merge(0, 1);
            printArray(fout);
            merge(2, 3);
            printArray(fout);
            merge(4, 5);
            printArray(fout);
            merge(6, 7);
            printArray(fout);
            merge(0, 3);
            printArray(fout);
            merge(4, 7);
            printArray(fout);
            merge(left, right);
            printArray(fout);
            break;

        case 9:
            merge(0, 1);
            printArray(fout);
            merge(2, 3);
            printArray(fout);
            merge(4, 5);
            printArray(fout);
            merge(6, 7);
            printArray(fout);
            merge(0, 3);
            printArray(fout);
            merge(4, 7);
            printArray(fout);
            merge(0, 7);
            printArray(fout);
            merge(left, right);
            printArray(fout);
            break;

        case 10:
            merge(0, 1);
            printArray(fout);
            merge(2, 3);
            printArray(fout);
            merge(4, 5);
            printArray(fout);
            merge(6, 7);
            printArray(fout);
            merge(8, 9);
            printArray(fout);
            merge(0, 3);
            printArray(fout);
            merge(4, 7);
            printArray(fout);
            merge(0, 7);
            printArray(fout);
            merge(left, right);
            printArray(fout);
            break;

        case 11:
            merge(0, 1);
            printArray(fout);
            merge(2, 3);
            printArray(fout);
            merge(4, 5);
            printArray(fout);
            merge(6, 7);
            printArray(fout);
            merge(8, 9);
            printArray(fout);
            merge(0, 3);
            printArray(fout);
            merge(4, 7);
            printArray(fout);
            merge(8, 10);
            printArray(fout);
            merge(0, 7);
            printArray(fout);
            merge(left, right);
            printArray(fout);
            break;

        case 12:
            merge(0, 1);
            printArray(fout);
            merge(2, 3);
            printArray(fout);
            merge(4, 5);
            printArray(fout);
            merge(6, 7);
            printArray(fout);
            merge(8, 9);
            printArray(fout);
            merge(10, 11);
            printArray(fout);
            merge(0, 3);
            printArray(fout);
            merge(4, 7);
            printArray(fout);
            merge(8, 11);
            printArray(fout);
            merge(0, 7);
            printArray(fout);
            merge(left, right);
            printArray(fout);
            break;

        case 13:
            merge(0, 1);
            printArray(fout);
            merge(2, 3);
            printArray(fout);
            merge(4, 5);
            printArray(fout);
            merge(6, 7);
            printArray(fout);
            merge(8, 9);
            printArray(fout);
            merge(10, 11);
            printArray(fout);
            merge(0, 3);
            printArray(fout);
            merge(4, 7);
            printArray(fout);
            merge(8, 11);
            printArray(fout);
            merge(0, 7);
            printArray(fout);
            merge(8, 12);
            printArray(fout);
            merge(left, right);
            printArray(fout);
            break;

        case 14:
            merge(0, 1);
            printArray(fout);
            merge(2, 3);
            printArray(fout);
            merge(4, 5);
            printArray(fout);
            merge(6, 7);
            printArray(fout);
            merge(8, 9);
            printArray(fout);
            merge(10, 11);
            printArray(fout);
            merge(12, 13);
            printArray(fout);
            merge(0, 3);
            printArray(fout);
            merge(4, 7);
            printArray(fout);
            merge(8, 11);
            printArray(fout);
            merge(0, 7);
            printArray(fout);
            merge(8, 13);
            printArray(fout);
            merge(left, right);
            printArray(fout);
            break;

        case 15:
            merge(0, 1);
            printArray(fout);
            merge(2, 3);
            printArray(fout);
            merge(4, 5);
            printArray(fout);
            merge(6, 7);
            printArray(fout);
            merge(8, 9);
            printArray(fout);
            merge(10, 11);
            printArray(fout);
            merge(12, 13);
            printArray(fout);
            merge(0, 3);
            printArray(fout);
            merge(4, 7);
            printArray(fout);
            merge(8, 11);
            printArray(fout);
            merge(12, 14);
            printArray(fout);
            merge(0, 7);
            printArray(fout);
            merge(8, 14);
            printArray(fout);
            merge(left, right);
            printArray(fout);
            break;

        case 16:
            merge(0, 1);
            printArray(fout);
            merge(2, 3);
            printArray(fout);
            merge(4, 5);
            printArray(fout);
            merge(6, 7);
            printArray(fout);
            merge(8, 9);
            printArray(fout);
            merge(10, 11);
            printArray(fout);
            merge(12, 13);
            printArray(fout);
            merge(14, 15);
            printArray(fout);
            merge(0, 3);
            printArray(fout);
            merge(4, 7);
            printArray(fout);
            merge(8, 11);
            printArray(fout);
            merge(12, 15);
            printArray(fout);
            merge(0, 7);
            printArray(fout);
            merge(8, 15);
            printArray(fout);
            merge(left, right);
            printArray(fout);
            break;
        
        case 17:
            merge(0, 1);
            printArray(fout);
            merge(2, 3);
            printArray(fout);
            merge(4, 5);
            printArray(fout);
            merge(6, 7);
            printArray(fout);
            merge(8, 9);
            printArray(fout);
            merge(10, 11);
            printArray(fout);
            merge(12, 13);
            printArray(fout);
            merge(14, 15);
            printArray(fout);
            merge(0, 3);
            printArray(fout);
            merge(4, 7);
            printArray(fout);
            merge(8, 11);
            printArray(fout);
            merge(12, 15);
            printArray(fout);
            merge(0, 7);
            printArray(fout);
            merge(8, 15);
            printArray(fout);
            merge(0, 15);
            printArray(fout);
            merge(left, right);
            printArray(fout);
            break;

        case 18:
            merge(0, 1);
            printArray(fout);
            merge(2, 3);
            printArray(fout);
            merge(4, 5);
            printArray(fout);
            merge(6, 7);
            printArray(fout);
            merge(8, 9);
            printArray(fout);
            merge(10, 11);
            printArray(fout);
            merge(12, 13);
            printArray(fout);
            merge(14, 15);
            printArray(fout);
            merge(16, 17);
            printArray(fout);
            merge(0, 3);
            printArray(fout);
            merge(4, 7);
            printArray(fout);
            merge(8, 11);
            printArray(fout);
            merge(12, 15);
            printArray(fout);
            merge(0, 7);
            printArray(fout);
            merge(8, 15);
            printArray(fout);
            merge(0, 15);
            printArray(fout);
            merge(left, right);
            printArray(fout);
            break;

        case 19:
            merge(0, 1);
            printArray(fout);
            merge(2, 3);
            printArray(fout);
            merge(4, 5);
            printArray(fout);
            merge(6, 7);
            printArray(fout);
            merge(8, 9);
            printArray(fout);
            merge(10, 11);
            printArray(fout);
            merge(12, 13);
            printArray(fout);
            merge(14, 15);
            printArray(fout);
            merge(16, 17);
            printArray(fout);
            merge(0, 3);
            printArray(fout);
            merge(4, 7);
            printArray(fout);
            merge(8, 11);
            printArray(fout);
            merge(12, 15);
            printArray(fout);
            merge(16, 18);
            printArray(fout);
            merge(0, 7);
            printArray(fout);
            merge(8, 15);
            printArray(fout);
            merge(0, 15);
            printArray(fout);
            merge(left, right);
            printArray(fout);
            break;

        case 20:
            merge(0, 1);
            printArray(fout);
            merge(2, 3);
            printArray(fout);
            merge(4, 5);
            printArray(fout);
            merge(6, 7);
            printArray(fout);
            merge(8, 9);
            printArray(fout);
            merge(10, 11);
            printArray(fout);
            merge(12, 13);
            printArray(fout);
            merge(14, 15);
            printArray(fout);
            merge(16, 17);
            printArray(fout);
            merge(18, 19);
            printArray(fout);
            merge(0, 3);
            printArray(fout);
            merge(4, 7);
            printArray(fout);
            merge(8, 11);
            printArray(fout);
            merge(12, 15);
            printArray(fout);
            merge(16, 19);
            printArray(fout);
            merge(0, 7);
            printArray(fout);
            merge(8, 15);
            printArray(fout);
            merge(0, 15);
            printArray(fout);
            merge(left, right);
            printArray(fout);
            break;

        }
      

       // merge(left, right);
       //printArray(fout);
        
    }

   // printArray(fout);// DO NOT ERASE THIS LINE

    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////

}
