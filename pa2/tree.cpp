#include "tree.h"
#include <iostream>
#include <cstring>
#include <string>

using namespace std;

/* This is given function. DO NOT MODIFY THIS FUNCTION */
int findIndex(const char* str, int start, int end) {
    if (start > end)
        return -1;

    string s;

    for (int i = start; i <= end; i++) {

        // if open parenthesis, push it
        if (str[i] == '(')
            s.push_back(str[i]); // string � �, string� � (� �޾� 

          // if close parenthesis
        else if (str[i] == ')') {
            if (s.back() == '(') {
                s.pop_back();

                if (!s.length())
                    return i;
            }
        }
    }
    // if not found return -1
    return -1;
}

/* This is given function. DO NOT MODIFY THIS FUNCTION */
Node* BinaryTree::_buildFromString(const char* data, int start, int end) { // BianryTree class� � �Լ� , string� � �ͼ� �Ʈ� �ٲ�ִ� �. 
    if (start > end)
        return NULL;

    Node* root = new Node(data[start]);
    int index = -1;

    if (start + 1 <= end && data[start + 1] == '(')
        index = findIndex(data, start + 1, end);

    if (index != -1) {
        root->left = _buildFromString(data, start + 2, index - 1);
        root->right = _buildFromString(data, index + 2, end - 1);
    }
    return root;
}

/* This is given function. DO NOT MODIFY THIS FUNCTION */
void BinaryTree::buildFromString(const char* data) {
    Node* root = _buildFromString(data, 0, strlen(data) - 1);
    _root = root;
}

string BinaryTree::preOrder() {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////

    if (_root == NULL) return ""; // tree� �ƹ�͵� � � 

    struct preorder {

        string answer = "";

        void preOrderf(Node* cur) {

            if (cur == NULL) return;
            answer = answer += to_string(cur->value - 48) + " ";
            preOrderf(cur->left);
            preOrderf(cur->right);
            return;

        }

    } PrO;

    PrO.preOrderf(_root);

    return PrO.answer;
    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////

}

string BinaryTree::postOrder() {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////


    if (_root == NULL) return ""; // tree� �ƹ�͵� � � 

    struct postorder {

        string answer = "";
        void postOrderf(Node* cur) {

            if (cur == NULL) return;
            postOrderf(cur->left);
            postOrderf(cur->right);
            answer = answer += to_string(cur->value - 48) + " ";
            return;

        }

    } PO;

    PO.postOrderf(_root);

    return PO.answer;
    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}


string BinaryTree::inOrder() {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////

    if (_root == NULL) return ""; // tree� �ƹ�͵� � � 

    struct inorder {

        string answer = "";
        void inOrderf(Node* cur) {

            if (cur == NULL) return;
            inOrderf(cur->left);
            answer = answer += to_string(cur->value - 48) + " ";
            inOrderf(cur->right);
            return;

        }

    } IO;

    IO.inOrderf(_root);

    return IO.answer;


    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}

int BinaryTree::getDepth(int node_value) { // 
  /////////////////////////////////////////////////////////
  //////////  TODO: Implement From Here      //////////////

    typedef struct node {

        Node* data;
        int _data;
        node* next;

    }NODE;

    typedef struct queue {

        int count;
        NODE* front;
        NODE* rear;

    }QUEUE;



    struct getdepth {

        bool isvalid = false;
        int depth = 0;
        int a[1050] = {};

        int visit(int a[], Node* cur_node) {

            if (a[cur_node->value] == 1) return 1;
            else return 0;

        }

        bool check(Node* node, int value, int a[]) {

            bool isvalid = true;
            if (a[value] == 1) isvalid = false;
            if (node == NULL) isvalid = false;

            return isvalid;

        }

        int search(QUEUE qnode, QUEUE qcnt, Node* cur, int node_value, int a[], bool& isvalid) {

            int cnt = 0;
            int idx = 0;

            while (!isEmpty(&qnode)) { // while� �ȿ� break�Ŵ 

                Node* cur_node = qnode.front->data; dequeue(&qnode); //front � �޾ƿ� dequeue
                int c = qcnt.front->_data; dequeue(&qcnt); //front � �޾ƿ� dequeue

                if (a[cur_node->value] == 1) continue; //�̹� �湮� �̸� � ĭ� Ž�
                a[cur_node->value] = 1;

                if (cur_node->value == node_value + 48) { // �尡 �ġ�ϸ� �ݺ� � � � search�Լ� return�. 
                    cnt = c;
                    isvalid = true;
                    break;
                }

                if (cur_node->left != NULL) {
                    if (check(cur_node->left, cur_node->left->value, a)) { // � � � �ִ� � 

                        enqueue(&qnode, cur_node->left);
                        enqueue(&qcnt, c + 1);

                    }
                }

                if (cur_node->right != NULL) {

                    if (check(cur_node->right, cur_node->right->value, a)) { // � � � �ִ� �  

                        enqueue(&qnode, cur_node->right);
                        enqueue(&qcnt, c + 1); // cnt� �ϳ� � 
                    }
                }


            }

            return cnt; //cnt = �Ÿ� 

        }

        int enqueue(QUEUE* q, Node* data) //FIFO � queue� rear� node� �ִ� �Լ�̴�. 
        {
            NODE* temp = new NODE;


            if (!temp)
                return 0;

            temp->data = data;
            temp->next = NULL;


            if (isEmpty(q))
            {
                q->front = temp;
                q->rear = temp;
                q->count++;

            }
            else
            {
                q->rear->next = temp;
                q->rear = temp;
                q->count++;
            }


            return 1;
        }

        int enqueue(QUEUE* q, int _data) //FIFO � queue� rear� node� �ִ� �Լ�̴�. 
        {
            NODE* temp = new NODE;


            if (!temp)
                return 0;

            temp->_data = _data;
            temp->next = NULL;


            if (isEmpty(q))
            {
                q->front = temp;
                q->rear = temp;
                q->count++;

            }
            else
            {
                q->rear->next = temp;
                q->rear = temp;
                q->count++;
            }


            return 1;
        }

        int	dequeue(QUEUE* q) //queue� front� �ġ� node� �ִ� �Լ�̴�. 
        {
            NODE* temp = new NODE;

            if (isEmpty(q)) return 0; // ť� � �ִ� �

            temp = q->front;
            q->front = q->front->next;
            q->count--;


            return 1;
        }

        int isEmpty(QUEUE* q) // queue� � �ִ� Ȯ�ϴ� �Լ�̴�. 
        {
            return q->front == NULL;
        }



    } GD;

    QUEUE qnode;
    QUEUE qcnt;

    qnode.count = 0; qnode.front = NULL; qnode.rear = NULL;
    qcnt.count = 0; qcnt.front = NULL; qcnt.rear = NULL;
    GD.enqueue(&qnode, _root); GD.enqueue(&qcnt, 0);

    GD.depth = GD.search(qnode, qcnt, _root, node_value, GD.a, GD.isvalid);

    if (GD.isvalid == false) return -1;
    else return GD.depth;


    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}

bool BinaryTree::isProper() {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
    //

    struct isproper {

        bool answer = true;

        void check(Node* cur) {

            if (cur == NULL) return;
            if (cur->left == NULL && cur->right != NULL) {
                answer = false;
                return;
            }
            if (cur->left != NULL && cur->right == NULL) {
                answer = false;
                return;
            }
            else {
                check(cur->left);
                check(cur->right);
            }
            return;

        }

    } IP;

    IP.check(_root);

    return IP.answer;


    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////
//////////  TODO: Implement From Here      //////////////

/*  Write your codes if you have additional private functions  */


///////////      End of Implementation      /////////////
/////////////////////////////////////////////////////////