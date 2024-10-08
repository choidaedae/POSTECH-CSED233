#pragma once
#include <iostream>
#include <string>
using namespace std;

class HashFunction {

public:
    HashFunction(int n, int r) : key_size(n), index_size(r) { };

    int hashing(int key);

private:
    int key_size;
    int index_size;

    /////////////////////////////////////////////////////////
    //////  TODO: Add private members if required ///////////
    int *arr;
    void dectobin(long long num);
    int getidx(int index_size);
    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
};

