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

    // 후위 순회 구조 
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
    Node* par = _root; //parent node 저장하는 포인터 

    while (1) { // root부터 체크해서 가장 깊은 노드로 감. 

        if (getbfactor(cur) > 1){ // 조건에 위배되면 


            if (key > cur->key) {
                
         
                if (getbfactor(cur->left) > 0) cur = LLrotate(cur); // LL 회전
                else cur = LRrotate(cur); // LR 회전 
                break;
            }


           // else 

        }

        else if (getbfactor(cur) < -1) {

            if (getbfactor(cur->right) < 0) cur = RRrotate(cur); // RR 회전 상황에 맞는 회전
            else cur = RLrotate(cur); //RL 회전 
            break;

        }

        //조건에 위배되지 않는 경우 
        
        if (key > cur->key) cur = cur->right; // key node를 찾기 위해 계속 감. 
        else if (key < cur->key) cur = cur->left;
        else return; // (현재 node의 키 값과 같은 경우) 삽입한 node 의 아래는 볼 필요 없음. 

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
    //ChangeLeftSubTree(parent, RRrotate(child)); //부분 RR회전
    return LLrotate(parent); //LL회전 

}


Node* AVLTree::RLrotate(Node* node) {


    Node* parent = node;
    Node* child = parent->right;
    parent->right = LLrotate(child);
    //ChangeRightSubTree(parent, LLrotate(child)); //부분 LL회전
    return RRrotate(parent); //RR 회전


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

    if (_root == NULL) { //루트 노드인 경우 

        _root = newnode;
        getheight(_root);
        return 0;


    }

    else if (_root->key == key) return -1;

    while (1) {

        if (key < cur->key) { // 왼쪽으로 가야 하는 경우 

            if (cur->left == NULL) { // 왼쪽 노드가 없는 경우 
                cur->left = newnode;

                break;
            }


            else cur = cur->left;

        }

        else if (key > cur->key) { //오른쪽으로 가야 하는 경우 


            if (cur->right == NULL) { // 오른쪽 노드가 없는 경우 
                cur->right = newnode;
                
                break;
            }

            else cur = cur->right;
            
        }
        else return -1; //키값이 같은 노드가 이미 있는 경우 
         
    }

    getheight(_root); // insertion 후 높이 업데이트 
    _root = rebalance(_root);
    //balance(_root, key); // 높이 체크, 높이 안 맞으면 조정 
    getheight(_root);  // balancing 후 높이 업데이트 
    
    return 0;

    ///////////      End of Implementation      /////////////
    ///////////////////////////////////////////////////////
}

int AVLTree::deletion(int key) {
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
                break;

            }

            else if (isonenode(cur)) {

                if (cur->left != NULL) { //자식노드가 왼쪽에 달린 경우 


                    cur = cur->left;
                    if (rightc) par->right = cur;
                    else if (leftc) par->left = cur;
                    break;
                }

                else if (cur->right != NULL) { //자식노드가 오른쪽에 달린 경우 


                    cur = cur->right;
                    if (rightc) par->right = cur;
                    else if (leftc) par->left = cur;
                    break;
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
                else cur = NULL; //root node인 경우 
                break;

            }


        }

    }
    
    getheight(_root); // deletion 후 높이 업데이트 
    _root = rebalance(_root);
    //balance(_root, key); // 높이 체크, 높이 안 맞으면 조정 
    getheight(_root); // balancing 후 높이 업데이트 

    return 0;

    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}
