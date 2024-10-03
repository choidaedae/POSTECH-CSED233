#include "shift_register.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;


int ShiftRegister::getSeqNumber(int idx) {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
   
   
    int num = initial_seed;


    for (int i = 0; i < idx-1 ; i++) {

        num *= 2;

        if (num >= M) {
            num -= M;
            num = num ^ k;
        }

       
    }

    return num;

    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////
//////////  TODO: Implement From Here      //////////////

/*  Write your codes if you have additional functions  */

///////////      End of Implementation      /////////////
/////////////////////////////////////////////////////////
