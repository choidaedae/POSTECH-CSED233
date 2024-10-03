#pragma once
#include "bst.h"

using namespace std;

class AVLTree: public BinarySearchTree {
public:
    AVLTree() { };
    ~AVLTree() { };

    int insertion(int key);
    int deletion(int key);
    

private:
    /////////////////////////////////////////////////////////
    //////  TODO: Add private members if required ///////////

    //void rotate(Node* node, int command);
    int isleaf(Node* cur);
    int isonenode(Node* cur);
    int height(Node* node);
    int getheight(Node* node);
    int getbfactor(Node* node);
    void balance(Node* node, int key);
    Node* LLrotate(Node* node);
    Node* LRrotate(Node* node);
    Node* RLrotate(Node* node);
    Node* RRrotate(Node* node);
    Node* rebalance(Node* node);
    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
};