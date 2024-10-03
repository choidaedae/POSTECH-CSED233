#include "tree.h"
#include "bst.h"
#include <iostream>
#include <string>

using namespace std;

int BinarySearchTree::insertion(int key) {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////

    Node* newnode = new Node(key);
    Node* cur = _root;
    Node* par = _root; 

    if (_root == NULL) {

        _root = newnode;
        return 0;

    }

    else if (_root->key == key) return -1;

    while (1) {

        if (key < cur->key) { // 왼쪽으로 가야 하는 경우 

            if (cur->left == NULL)  { // 왼쪽 노드가 없는 경우 
                cur->left = newnode;
                return 0;
            }


            else { 

                cur = cur->left;

            }


        }

        else if (key > cur->key) { //오른쪽으로 가야 하는 경우 

           
            if (cur->right == NULL) { // 오른쪽 노드가 없는 경우 
                cur->right = newnode;
                return 0;
            }

            else {
                
                cur = cur->right;
            }

        }

        else { //키값이 같은 노드가 이미 있는 경우 

            return -1;

        }

    }
    return 0;

    ///////////      End of Implementation      /////////////
    ///////////////////////////////////////////////////////
}

int BinarySearchTree::deletion(int key) {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////

    if (_root == NULL) return -1; // 빈 트리 

    Node* cur = _root;
    Node* par = _root; //부모 노드 
    bool leftc = false, rightc = false;

    while (1) {


        if (key < cur->key) { // 왼쪽으로 가야 하는 경우 


            if (cur->left == NULL) return -1; // 못 찾는 경우 

            else {

                par = cur;
                cur = cur->left;
                rightc = false;
                leftc = true;

            }


        }


        else if (key > cur->key) { //오른쪽으로 가야 하는 경우 

            if (cur->right == NULL) return -1; // 못 찾는 경우 

            else {
                par = cur;
                cur = cur->right;
                rightc = true;
                leftc = false;
            }

        }

        else { // 현재 삭제하려는 노드인 경우 

            if (isleaf(cur)) { //leaf node인 경우 

               
                if (rightc) par->right = NULL;
                else if (leftc) par->left = NULL;
                else _root = NULL; //root node인 경우 

                return 0;

            }

            else if (isonenode(cur)) {

                if (cur->left != NULL) { //자식노드가 왼쪽에 달린 경우 


                    cur = cur->left;
                    if (rightc) par->right = cur;
                    else if (leftc) par->left = cur;
                 
                    return 0;
                }

                else if (cur->right != NULL) { //자식노드가 오른쪽에 달린 경우 

                    
                    cur = cur->right;
                    if (rightc) par->right = cur;
                    else if (leftc) par->left = cur;
           
                    return 0;
                }

            }

            else { //자식이 2개인 노드 

                Node* del = cur;//삭제 대상 노드 
                par = cur;
                cur = cur->right; // right subtree로 접근
                rightc = true; leftc = false;

                while (cur->left != NULL) { // leftmost of right subtree(smallest of right subtree)
                    par = cur;
                    cur = cur->left;
                    rightc = false; leftc = true;
                }

                int temp = del->key; // 노드의 키값 바꿔줌 
                del->key = cur->key;
                cur->key = temp;

                if (leftc) par->left = NULL;
                else if (rightc) par->right = NULL;
                else cur = NULL;
                return 0;

            }


        }

    }

    
       
    return 0;

    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////
//////////  TODO: Implement From Here      //////////////

/*  Write your codes if you have additional functions  */

int BinarySearchTree::isleaf(Node* cur) {

    if (cur->left == NULL && cur->right == NULL) return 1;
    else return 0;

}

int BinarySearchTree::isonenode(Node* cur) {

    if (cur->left != NULL && cur->right == NULL) return 1;
    else if (cur->left == NULL && cur->right != NULL) return 1;
    else return 0;

}



///////////      End of Implementation      /////////////
/////////////////////////////////////////////////////////
