#pragma once
#include <fstream>
#include <iostream>
#include <string>
#define NodeMaxCount 101
#define INF 2147483647 
using namespace std;

/////////////////////////////////////////////////////////
///  TODO: Add Your Struct or Functions if required /////


struct Stack {


    int arr[101] = {};
    int size = 0;

    void clear() {

        for (int i = 0; i < size; i++) {
            arr[i] = 0;
        }
        size = 0;
    }

    int top() {

        return arr[size - 1];
    }

    int pop() {

        size--;
        return arr[size];
    }

    void push(int data) {

        arr[size] = data;
        size++;
    }

    bool isempty() {

        return size == 0 ? true : false;
    }


};



class Node {

public:
    
    Node(): size(0) {}
    ~Node(){}
    string nodes[101] = {};
    int size=0;

    void sort() {

        string temp;

        for (int i = 0; i < size; i++)    // ����� ������ŭ �ݺ�
        {
            for (int j = 0; j < size - 1; j++)   // ����� ���� - 1��ŭ �ݺ�
            {
                if (nodes[j] > nodes[j + 1])          // ���� ����� ���� ���� ����� ���� ���Ͽ�
                {                                 // ū ����
                    temp = nodes[j];
                    nodes[j] = nodes[j + 1];
                    nodes[j + 1] = temp;            // ���� ��ҷ� ����
                }
            }
        }


    }

    int searchNodeidx(string node, int size) {

        for (int i = 0; i < size; i++) {

            if (nodes[i] == node) return i;
        }

        return -1;


    }


};



class Edge {

public:

    Edge() : size(0) {}
    ~Edge(){}
    string StartEdge[101] = {};
    string desEdge[101] = {};
    int weight[101] = { };
    int size=0;
    void sort() {

        string temp;
        int itemp;

        // step 1. ���� ���� �׷��������� MST�̹Ƿ� Edge�� ���� ��尡 �տ� ���Բ� ����  

            for (int i = 0; i < size; i++)   
            {
                if (StartEdge[i] > desEdge[i])          
                {                                 
                    temp = StartEdge[i];
                    StartEdge[i] = desEdge[i];
                    desEdge[i] = temp;            // ���� ��ҷ� ����
                }
            }
       
        // step 2. �����鳢�� weight�� ���� �������� ���� 

            for (int i = 0; i < size; i++)    // ����� ������ŭ �ݺ�
            {
                for (int j = 0; j < size - 1; j++)   // ����� ���� - 1��ŭ �ݺ�
                {
                    if (weight[j] > weight[j+1]) // ���� ��峢�� �� 
                    {                                
                        temp = StartEdge[j]; // ���۳�� ��ȯ
                        StartEdge[j] = StartEdge[j+1];
                        StartEdge[j + 1] = temp;

                        temp = desEdge[j]; // ������� ��ȯ
                        desEdge[j] = desEdge[j + 1];
                        desEdge[j + 1] = temp;

                        itemp = weight[j]; // ����ġ ��ȯ
                        weight[j] = weight[j + 1];
                        weight[j + 1] = itemp;
                    }

                    else if (weight[j] == weight[j + 1]) {

                        if (StartEdge[j] > StartEdge[j + 1]) {

                                temp = StartEdge[j]; // ���۳�� ��ȯ
                                StartEdge[j] = StartEdge[j + 1];
                                StartEdge[j + 1] = temp;

                                temp = desEdge[j]; // ������� ��ȯ
                                desEdge[j] = desEdge[j + 1];
                                desEdge[j + 1] = temp;

                                itemp = weight[j]; // ����ġ ��ȯ
                                weight[j] = weight[j + 1];
                                weight[j + 1] = itemp;

                        }

                        else if (StartEdge[j] == StartEdge[j + 1]) {

                            if (desEdge[j] > desEdge[j + 1]) {

                                temp = StartEdge[j]; // ���۳�� ��ȯ
                                StartEdge[j] = StartEdge[j + 1];
                                StartEdge[j + 1] = temp;

                                temp = desEdge[j]; // ������� ��ȯ
                                desEdge[j] = desEdge[j + 1];
                                desEdge[j + 1] = temp;

                                itemp = weight[j]; // ����ġ ��ȯ
                                weight[j] = weight[j + 1];
                                weight[j + 1] = itemp;

                            }
                        }

                    }
                }
            }

    }



};



///////////      End of Implementation      /////////////
/////////////////////////////////////////////////////////

class Graph{
public:
    Graph() { };
    ~Graph() { };

    int addDirectedEdge(string nodeA, string nodeB);
    int addDirectedEdge(string nodeA, string nodeB, int weight);
    int addUndirectedEdge(string nodeA, string nodeB);
    int addUndirectedEdge(string nodeA, string nodeB, int weight);

    string DFS();
    int getTreeCount();
    string getStronglyConnectedComponent();
    string getDijkstraShortestPath(string source, string destination);
    string getFloydShortestPath(string source, string destination);
    int primMST(ofstream &, string startNode);
    int kruskalMST(ofstream &);


private:
    /////////////////////////////////////////////////////////
    //////  TODO: Add private members if required ///////////

    int graph[101][101]= {};
    int transpose[101][101] = {};
    bool visit[101] = {};
    bool trans_visit[101] = {};
    int num_scc = 0;
    int scc[101][101] = {};
    void dfs(int start, string& answer, string *nodes);
    void dfsAll(string& answer);
    void getcount(int start, int &count);
    void getAllcount(int &count);
    void clean();
    void setundirectedGraphwithoutweight();
    void setundirectedGraphwithweight();
    void setdirectedGraphwithoutweight();
    void setdirectedGraphwithweight();
    void settransposeGraph();
    void cleangraph();
    void dfsKosarajou(int now, int dfsseq_size);
    void reversedfsKosarajou(int now, int scc_num, int scc_size);
    int Kosarajou();
    int make_scc(int scc_size);
    int sizeofscc[101] = { };
    int sort_scc(int scc_size);
    void sort_answer(string* answer, int answer_size, int answer_idx[][101]);
    int getShortestNode(long long int* dis_arr);
    void update_dis(int node, long long int * dis_arr, string *path);
    bool setfloydpath(int path[101], int next[101][101], int &path_size, int source, int des);
    void getnextNode(int &cur, int& cost);
    bool sameparent(int i, int parent[]);
    int findparent(int i, int parent[]);

    class Stack dfsseq[101];

    class Node Node;
    class Edge Edge;

    
    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
};
