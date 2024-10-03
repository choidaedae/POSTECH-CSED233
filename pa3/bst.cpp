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

        if (key < cur->key) { // �������� ���� �ϴ� ��� 

            if (cur->left == NULL)  { // ���� ��尡 ���� ��� 
                cur->left = newnode;
                return 0;
            }


            else { 

                cur = cur->left;

            }


        }

        else if (key > cur->key) { //���������� ���� �ϴ� ��� 

           
            if (cur->right == NULL) { // ������ ��尡 ���� ��� 
                cur->right = newnode;
                return 0;
            }

            else {
                
                cur = cur->right;
            }

        }

        else { //Ű���� ���� ��尡 �̹� �ִ� ��� 

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

    if (_root == NULL) return -1; // �� Ʈ�� 

    Node* cur = _root;
    Node* par = _root; //�θ� ��� 
    bool leftc = false, rightc = false;

    while (1) {


        if (key < cur->key) { // �������� ���� �ϴ� ��� 


            if (cur->left == NULL) return -1; // �� ã�� ��� 

            else {

                par = cur;
                cur = cur->left;
                rightc = false;
                leftc = true;

            }


        }


        else if (key > cur->key) { //���������� ���� �ϴ� ��� 

            if (cur->right == NULL) return -1; // �� ã�� ��� 

            else {
                par = cur;
                cur = cur->right;
                rightc = true;
                leftc = false;
            }

        }

        else { // ���� �����Ϸ��� ����� ��� 

            if (isleaf(cur)) { //leaf node�� ��� 

               
                if (rightc) par->right = NULL;
                else if (leftc) par->left = NULL;
                else _root = NULL; //root node�� ��� 

                return 0;

            }

            else if (isonenode(cur)) {

                if (cur->left != NULL) { //�ڽĳ�尡 ���ʿ� �޸� ��� 


                    cur = cur->left;
                    if (rightc) par->right = cur;
                    else if (leftc) par->left = cur;
                 
                    return 0;
                }

                else if (cur->right != NULL) { //�ڽĳ�尡 �����ʿ� �޸� ��� 

                    
                    cur = cur->right;
                    if (rightc) par->right = cur;
                    else if (leftc) par->left = cur;
           
                    return 0;
                }

            }

            else { //�ڽ��� 2���� ��� 

                Node* del = cur;//���� ��� ��� 
                par = cur;
                cur = cur->right; // right subtree�� ����
                rightc = true; leftc = false;

                while (cur->left != NULL) { // leftmost of right subtree(smallest of right subtree)
                    par = cur;
                    cur = cur->left;
                    rightc = false; leftc = true;
                }

                int temp = del->key; // ����� Ű�� �ٲ��� 
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
