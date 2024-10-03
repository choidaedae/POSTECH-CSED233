#include "tree.h"
#include "bst.h"
#include "avl.h"
#include <iostream>
#include <string>

using namespace std;


/////////////////////////////////////////////////////////
//////////  TODO: Implement From Here      //////////////

/*  Write your codes if you have additional functions  */

int AVLTree::getbfactor(Node* node) {

    return (height(node->left) - height(node->right));

}

Node* AVLTree:: rebalance(Node* node) {

    if (node == NULL) {
        return NULL;
    }

    // ���� ��ȸ ���� 
    node->left = rebalance(node->left);
    node->right = rebalance(node->right);
    int bfactor = getbfactor(node);

    if (-1 <= bfactor && bfactor <= 1) {
        return node;
    }

    if (bfactor > 1) {
        node = (getbfactor(node->left) > 0) ? LLrotate(node) : LRrotate(node);
        return node;
    }

    node = (getbfactor(node->right) < 0) ? RRrotate(node) : RLrotate(node);
    return node;
}

void AVLTree::balance(Node* _root, int key) {

    Node* cur = _root;
    Node* par = _root; //parent node �����ϴ� ������ 

    while (1) { // root���� üũ�ؼ� ���� ���� ���� ��. 

        if (getbfactor(cur) > 1){ // ���ǿ� ����Ǹ� 


            if (key > cur->key) {
                
         
                if (getbfactor(cur->left) > 0) cur = LLrotate(cur); // LL ȸ��
                else cur = LRrotate(cur); // LR ȸ�� 
                break;
            }


           // else 

        }

        else if (getbfactor(cur) < -1) {

            if (getbfactor(cur->right) < 0) cur = RRrotate(cur); // RR ȸ�� ��Ȳ�� �´� ȸ��
            else cur = RLrotate(cur); //RL ȸ�� 
            break;

        }

        //���ǿ� ������� �ʴ� ��� 
        
        if (key > cur->key) cur = cur->right; // key node�� ã�� ���� ��� ��. 
        else if (key < cur->key) cur = cur->left;
        else return; // (���� node�� Ű ���� ���� ���) ������ node �� �Ʒ��� �� �ʿ� ����. 

    }

    return;
    

}

Node *AVLTree::LLrotate(Node* node) {


    Node* parent = node;
    Node* child = parent->left;
    parent->left = child->right;
    //ChangeLeftSubTree(parent, child->right);
    child->right = parent;
    //ChangeRightSubTree(child, parent);
    return child;

}

Node* AVLTree::LRrotate(Node* node) {


    Node* parent = node;
    Node* child = parent->left;
    parent->left = RRrotate(child);
    //ChangeLeftSubTree(parent, RRrotate(child)); //�κ� RRȸ��
    return LLrotate(parent); //LLȸ�� 

}


Node* AVLTree::RLrotate(Node* node) {


    Node* parent = node;
    Node* child = parent->right;
    parent->right = LLrotate(child);
    //ChangeRightSubTree(parent, LLrotate(child)); //�κ� LLȸ��
    return RRrotate(parent); //RR ȸ��


}

Node* AVLTree::RRrotate(Node* node) {


    Node* parent = node;
    Node* child = parent->right;
    parent -> right = child->left;
    child->left = parent;
    //ChangeLeftSubTree(child, parent);
    return child;


}

int AVLTree::isonenode(Node* cur) {


        if (cur->left != NULL && cur->right == NULL) return 1;
        else if (cur->left == NULL && cur->right != NULL) return 1;
        else return 0;

    
}

int AVLTree::height(Node* node) {

    if (node == NULL)
        return -1;
    else
        return node->height;
}

int AVLTree::isleaf(Node* cur) {

    if (cur->left == NULL && cur->right == NULL) return 1;
    else return 0;

}

int AVLTree::getheight(Node* node) {

    int leftH;
    int rightH;

    if (node == NULL) return -1;

    leftH = getheight(node->left);

    rightH = getheight(node->right);

    if (leftH > rightH) {
        node->height = leftH + 1;
        return leftH + 1;
    }

    else {
        node->height = rightH + 1;
        return rightH + 1;
    }
}



///////////      End of Implementation      /////////////
/////////////////////////////////////////////////////////

int AVLTree::insertion(int key) {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////

    Node* newnode = new Node(key);
    Node* cur = _root;
    Node* par = _root;

    if (_root == NULL) { //��Ʈ ����� ��� 

        _root = newnode;
        getheight(_root);
        return 0;


    }

    else if (_root->key == key) return -1;

    while (1) {

        if (key < cur->key) { // �������� ���� �ϴ� ��� 

            if (cur->left == NULL) { // ���� ��尡 ���� ��� 
                cur->left = newnode;

                break;
            }


            else cur = cur->left;

        }

        else if (key > cur->key) { //���������� ���� �ϴ� ��� 


            if (cur->right == NULL) { // ������ ��尡 ���� ��� 
                cur->right = newnode;
                
                break;
            }

            else cur = cur->right;
            
        }
        else return -1; //Ű���� ���� ��尡 �̹� �ִ� ��� 
         
    }

    getheight(_root); // insertion �� ���� ������Ʈ 
    _root = rebalance(_root);
    //balance(_root, key); // ���� üũ, ���� �� ������ ���� 
    getheight(_root);  // balancing �� ���� ������Ʈ 
    
    return 0;

    ///////////      End of Implementation      /////////////
    ///////////////////////////////////////////////////////
}

int AVLTree::deletion(int key) {
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
                break;

            }

            else if (isonenode(cur)) {

                if (cur->left != NULL) { //�ڽĳ�尡 ���ʿ� �޸� ��� 


                    cur = cur->left;
                    if (rightc) par->right = cur;
                    else if (leftc) par->left = cur;
                    break;
                }

                else if (cur->right != NULL) { //�ڽĳ�尡 �����ʿ� �޸� ��� 


                    cur = cur->right;
                    if (rightc) par->right = cur;
                    else if (leftc) par->left = cur;
                    break;
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
                else cur = NULL; //root node�� ��� 
                break;

            }


        }

    }
    
    getheight(_root); // deletion �� ���� ������Ʈ 
    _root = rebalance(_root);
    //balance(_root, key); // ���� üũ, ���� �� ������ ���� 
    getheight(_root); // balancing �� ���� ������Ʈ 

    return 0;

    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}
