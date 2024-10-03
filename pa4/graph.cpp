#include "graph.h"
#include <fstream>
#include <iostream>
#include <string>
#define INF 2147483647 
using namespace std;


/////////////////////////////////////////////////////////
//////////  TODO: Implement From Here      //////////////
/*  Write your codes if you have additional functions  */


void Graph::dfs(int start, string &answer, string *nodes) {


    string ndname = nodes[start];
    answer += ndname; 
    answer += " ";
    visit[start] = true;         //방문 표시
    for (int i = 0; i < Node.size; i++) {
        if (graph[start][i] != 0 && !visit[i]) {

            dfs(i, answer, nodes);
        }
    }

   
}

void Graph::dfsAll(string &answer) { //모든 정점에 대해서 dfs

//그래프가 여러개일 수 있으므로 모든 정점에 대해 수행

    //디버깅

    for (int i = 0; i < Node.size; i++) {
        if (!visit[i]) { 

            dfs(i, answer, this->Node.nodes);
            answer += "\n";

        } 
   
        

    }

}

void Graph::getcount(int start, int &count) {

    visit[start] = true; //방문 표시
    for (int i = 0; i < Node.size; i++) {
        if (graph[start][i] != 0 && !visit[i]) {

            getcount(i, count);
        }
    }

}

void Graph::getAllcount(int &count) { //모든 정점에 대해서 dfs

    int parent[101] = { };

    for (int i = 0; i < Node.size; i++) {
        if (!visit[i]) {
            getcount(i, count);
            count++;

        }
    }

    //cyclic한 경우?

}

void Graph::dfsKosarajou(int now, int scc_size) {

        visit[now] = true;  //방문 표시

        for (int i = 0; i < Node.size; i++) {

            if (graph[now][i] != 0 && !visit[i]) {

                dfsKosarajou(i, scc_size);
            }
        }

    dfsseq[scc_size].push(now); //스택에 넣어줌 


}

void Graph::reversedfsKosarajou(int now, int scc_num, int scc_size) {


    visit[now] = true;
    scc[scc_num][scc_size] = now;
    sizeofscc[scc_num]++;

    for (int i = 0; i < Node.size; i++) {

         if (transpose[now][i] != 0 && !visit[i]) {

                scc_size++;
                reversedfsKosarajou(i, scc_num, scc_size);
         }

    }

   

}

int Graph::Kosarajou() {

    clean();

    int dfsseq_size = 0;

    for (int i = 0; i < Node.size; i++) { // 모든 정점에 대해 수행 

        if (visit[i]) continue;

        else {

            dfsKosarajou(i, dfsseq_size);
            dfsseq_size++;

        }
    }


    return make_scc(dfsseq_size);

  
   
}

int Graph::make_scc(int dfsseq_size){

    clean();
    int scc_num = 0;

    for (int i = 0; i <= dfsseq_size; i++) { // stack 개수 만큼 dfs 해줌 

        while (!dfsseq[i].isempty()) {
            
            int here = dfsseq[i].top(); // 위에부터 불러서 역방향 tree에 대해 DFS
            dfsseq[i].pop();

            if (visit[here]) continue;

            else {
 
                reversedfsKosarajou(here, scc_num, 0);
                scc_num++;
   
            }

        }
    }

    // SCC 순서대로 정렬 

 

    return scc_num;

}

int Graph::sort_scc(int scc_size) {

    int max = -1; 

    for (int k = 0; k < scc_size; k++) {

        if (max < sizeofscc[k]) max = sizeofscc[k];

        for (int i = 0; i < sizeofscc[k]; i++) {

            for (int j = 0; j < sizeofscc[k] - 1; j++) {

                if (scc[k][j] > scc[k][j + 1]) {

                    int temp = scc[k][j];
                    scc[k][j] = scc[k][j + 1];
                    scc[k][j + 1] = temp;

                }

            }
        }
    }
      
    return max;
}


void Graph::sort_answer(string* answer, int answer_size, int answer_idx[][101]) { // answer에 들어가는 애들만 들어와있음. 

    for (int i = 0; i < answer_size; i++) {

        for (int j = 0; j < answer_size-1; j++) {

            for (int k = 0; k < answer_size; k++) {

                if (answer_idx[j][k] > answer_idx[j + 1][k]) {

                    string temp = answer[j]; //바꾸고 
                    answer[j] = answer[j + 1];
                    answer[j + 1] = temp;
                    break;

                }

                else if (answer_idx[j][k] < answer[j + 1][k]) break;
            }
        }
    }





}
void Graph::clean() {

    for (int i = 0; i < 101; i++) {

        visit[i] = false;
        trans_visit[i] = false;
    }
}

void Graph::setundirectedGraphwithoutweight() {

    Node.sort();
    cleangraph();
    //디버깅
    for (int i = 0; i < Edge.size; i++) {
        //디버깅
        int start = Node.searchNodeidx(Edge.StartEdge[i], Node.size);
        int des = Node.searchNodeidx(Edge.desEdge[i], Node.size);

        graph[start][des] = graph[des][start] = 1;
    }


}

void Graph::setundirectedGraphwithweight() {

    Node.sort();
    cleangraph();

    for (int i = 0; i < Edge.size; i++) {

        int start = Node.searchNodeidx(Edge.StartEdge[i], Node.size);
        int des = Node.searchNodeidx(Edge.desEdge[i], Node.size);
        int weight = Edge.weight[i];

        graph[start][des] = graph[des][start] = weight;

    }

}

void Graph::setdirectedGraphwithoutweight() {
    
    //디버깅
    Node.sort();
    cleangraph();

    for (int i = 0; i < Edge.size; i++) {
    //디버깅
        int start = Node.searchNodeidx(Edge.StartEdge[i], Node.size);
        int des = Node.searchNodeidx(Edge.desEdge[i], Node.size);

        graph[start][des] = 1;
    }


}

void Graph::setdirectedGraphwithweight() {

    Node.sort();
    cleangraph();

    for (int i = 0; i < Node.size; i++) { //cost = 처음에 모두 무한대로 초기화

        for (int j = 0; j < Node.size; j++) {

            if (i == j) graph[i][j] = 0;
            else graph[i][j] = INF;
        }
    }
    

    for (int i = 0; i < Edge.size; i++) {

        int start = Node.searchNodeidx(Edge.StartEdge[i], Node.size);
        int des = Node.searchNodeidx(Edge.desEdge[i], Node.size);
        int weight = Edge.weight[i];

        graph[start][des] = weight;
    }


}

void Graph::settransposeGraph() { //directed Graph에 대해서 전치행렬(역방향) 그래프 만듦 

    for (int i = 0; i < Node.size; i++) {

        for (int j = 0; j < Node.size; j++) {

            transpose[i][j] = graph[j][i];
        }
    }

}

void Graph::cleangraph() { 

    for (int i = 0; i < 101; i++) {

        for (int j = 0; j < 101; j++) {

            graph[i][j] = 0;
        }
    }
}

int Graph::getShortestNode(long long int* dis_arr) {
// 디버깅
    int min = INF;
    int min_idx = -1;

    for (int i = 0; i < Node.size; i++) {

        if (visit[i]) continue;
        if (dis_arr[i] < min) {
            min = dis_arr[i];
            min_idx = i;

        }

    }
 // 디버깅
    return min_idx;

}

void Graph::update_dis(int node, long long int* dis_arr, string *paths) {
// 디버깅 
    for (int i = 0; i < Node.size; i++) {
        if (visit[i]) continue; //이미 체크했을 경우 빠져나감 
        if (dis_arr[i] > dis_arr[node] + graph[node][i]) { // 거리 갱신 
            dis_arr[i] = dis_arr[node] + graph[node][i];
            paths[i] = paths[node] + Node.nodes[i] + " ";
        }
    }


}

bool Graph::setfloydpath(int path[101], int next[101][101], int &path_size,  int source, int des) { // 디버깅

    if (next[source][des] == -1) return false;

    path_size = 0;
    path[0] = source;
    path_size++;

    while (source != des) {

        source = next[source][des];
        path[path_size] = source;
        path_size++;

    }

    return true; 
}

void Graph::getnextNode(int &cur, int& cost) {

    int min_cost = INF;
    int min_idx = 0;

    for (int i = 0; i < Node.size; i++) {

        if(min_cost > graph[cur][i] && graph[cur][i]>0) {

            if (!visit[i]) {

                min_cost = graph[cur][i];
                min_idx = i;
            }    

        }

    }


    visit[min_idx] = true;
    cur = min_idx;

    

}

bool Graph::sameparent(int i, int parent[]) {

    int n1 = Node.searchNodeidx(Edge.StartEdge[i], Node.size);
    int n2 = Node.searchNodeidx(Edge.desEdge[i], Node.size);
    n1 = findparent(n1, parent);
    n2 = findparent(n2, parent);
    if (n1 == n2) return true;
    else {

        parent[n2] = n1;
        return false;
    }


}

int Graph::findparent(int i, int parent[]) {

    if (parent[i] == i) return i; 
    else return parent[i] = findparent(parent[i], parent);

}

///////////      End of Implementation      /////////////
/////////////////////////////////////////////////////////


int Graph::addDirectedEdge(string nodeA, string nodeB) {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////

    if (Node.size == 0) { // 처음 넣어주는 경우 

        Node.nodes[0] = nodeA;
        Node.nodes[1] = nodeB;
        Edge.StartEdge[0] = nodeA;
        Edge.desEdge[0] = nodeB;
        Edge.size = 1;
        Node.size = 2;
        return 0;
    }

    for (int i = 0; i < Edge.size; i++) { // 완전히 같은 edge일 경우 

        if (nodeA == Edge.StartEdge[i] && nodeB == Edge.desEdge[i]) return -1; // 중복되면 return 

    }

    Edge.StartEdge[Edge.size] = nodeA;
    Edge.desEdge[Edge.size] = nodeB;
    Edge.size++;

    for (int i = 0; i < Node.size; i++) {  // 중복된 node인지 검사 

        if (nodeA == Node.nodes[i]) break;
        if (i == Node.size - 1) {
            Node.nodes[Node.size] = nodeA;
            Node.size++;
        }
    }

    for (int i = 0; i < Node.size; i++) { // 중복된 node인지 검사 

        if (nodeB == Node.nodes[i]) break;
        if (i == Node.size - 1) {
            Node.nodes[Node.size] = nodeB;
            Node.size++;
        }
    }


    return 0;
    ///////////      End of Implementation      /////////////
    ///////////////////////////////////////////////////////
}

int Graph::addDirectedEdge(string nodeA, string nodeB, int weight) {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////

    if (Node.size == 0) { // 처음 넣어주는 경우 

        Node.nodes[0] = nodeA;
        Node.nodes[1] = nodeB;
        Edge.StartEdge[0] = nodeA;
        Edge.desEdge[0] = nodeB;
        Edge.weight[0] = weight;
        Edge.size = 1;
        Node.size = 2;
        
        return 0;
    }

    for (int i = 0; i < Edge.size; i++) { // 완전히 같은 edge일 경우 

        if (nodeA == Edge.StartEdge[i] && nodeB == Edge.desEdge[i]) return -1; // 중복되면 return 

    }

    Edge.StartEdge[Edge.size] = nodeA;
    Edge.desEdge[Edge.size] = nodeB;
    Edge.weight[Edge.size] = weight;
    Edge.size++;

    for (int i = 0; i < Node.size; i++) {  // 중복된 node인지 검사 

        if (nodeA == Node.nodes[i]) break;
        if (i == Node.size - 1) {
            Node.nodes[Node.size] = nodeA;
            Node.size++;
        }
    }

    for (int i = 0; i < Node.size; i++) { // 중복된 node인지 검사 

        if (nodeB == Node.nodes[i]) break;
        if (i == Node.size - 1) {
            Node.nodes[Node.size] = nodeB;
            Node.size++;
        }
    }


    return 0;
    ///////////      End of Implementation      /////////////
    ///////////////////////////////////////////////////////
}

int Graph::addUndirectedEdge(string nodeA, string nodeB) {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
    //디버깅
    if (Node.size == 0) { // 처음 넣어주는 경우 

        Node.nodes[0] = nodeA;
        Node.nodes[1] = nodeB;
        Edge.StartEdge[0] = nodeA;
        Edge.desEdge[0] = nodeB;
        Edge.size = 1;
        Node.size = 2;
        return 0;
    }
    //디버깅
    for (int i = 0; i < Edge.size; i++) { // 완전히 같은 edge일 경우 

        if (nodeA == Edge.StartEdge[i] && nodeB == Edge.desEdge[i]) return -1; // 중복되면 return 
        if (nodeB == Edge.StartEdge[i] && nodeA == Edge.desEdge[i]) return -1; // undirected Edge -> (A,B) == (B,A)
    }

    Edge.StartEdge[Edge.size] = nodeA;
    Edge.desEdge[Edge.size] = nodeB;
    Edge.size++;

    //디버깅
    for (int i = 0; i < Node.size; i++) {  // 중복된 node인지 검사 

        if (nodeA == Node.nodes[i]) break;
        if (i == Node.size - 1) {
            Node.nodes[Node.size] = nodeA;
            Node.size++;
        }
    }
    //디버깅
    for (int i = 0; i < Node.size; i++) { // 중복된 node인지 검사 

        if (nodeB == Node.nodes[i]) break;
        if (i == Node.size - 1) {
            Node.nodes[Node.size] = nodeB;
            Node.size++;
        }
    }
    
    //디버깅
    return 0;
    ///////////      End of Implementation      /////////////
    ///////////////////////////////////////////////////////
}

int Graph::addUndirectedEdge(string nodeA, string nodeB, int weight) {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////

    if (Node.size == 0) { // 처음 넣어주는 경우 

        Node.nodes[0] = nodeA;
        Node.nodes[1] = nodeB;
        Edge.StartEdge[0] = nodeA;
        Edge.desEdge[0] = nodeB;
        Edge.weight[0] = weight;
        Edge.size = 1;
        Node.size = 2;

        return 0;
    }

    for (int i = 0; i < Edge.size; i++) { // 완전히 같은 edge일 경우 

        if (nodeA == Edge.StartEdge[i] && nodeB == Edge.desEdge[i]) return -1; // 중복되면 return 
        if (nodeB == Edge.StartEdge[i] && nodeA == Edge.desEdge[i]) return -1; // undirected Edge -> (A,B) == (B,A)
    }

    Edge.StartEdge[Edge.size] = nodeA;
    Edge.desEdge[Edge.size] = nodeB;
    Edge.weight[Edge.size] = weight;
    Edge.size++;


    for (int i = 0; i < Node.size; i++) {

        if (nodeA == Node.nodes[i]) break;
        if (i == Node.size - 1) {
            Node.nodes[Node.size] = nodeA;
            Node.size++;
        }
    }

    for (int i = 0; i < Node.size; i++) {

        if (nodeB == Node.nodes[i]) break;
        if (i == Node.size - 1) {
            Node.nodes[Node.size] = nodeB;
            Node.size++;
        }
    }

    return 0;
    ///////////      End of Implementation      /////////////
    ///////////////////////////////////////////////////////
}

string Graph::DFS() {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
 //디버깅
    clean();
    setundirectedGraphwithoutweight();
    string answer = "";
    dfsAll(answer);
    answer.pop_back();
    return answer;    
    ///////////      End of Implementation      /////////////
    ///////////////////////////////////////////////////////
}

int Graph::getTreeCount() {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////

    clean();
    setundirectedGraphwithoutweight();
    int count = 0;
    getAllcount(count);

    return count;
    ///////////      End of Implementation      /////////////
    ///////////////////////////////////////////////////////
}

string Graph::getStronglyConnectedComponent() {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////

    clean();
    setdirectedGraphwithoutweight();
    settransposeGraph();

    //코사라주 

    string answer[101] = {};
    string real_answer = "";
    int answer_size = 0;
    int answer_idx[101][101] = { };
    int scc_size = Kosarajou();

    int max = sort_scc(scc_size);

    for (int i = 0; i < scc_size; i++) {

        if (sizeofscc[i] == max) {
            for (int j = 0; j < max; j++) {

                answer_idx[answer_size][j] = scc[i][j];
                answer[answer_size] = answer[answer_size] + Node.nodes[scc[i][j]] + " ";
                
            }
            answer_size++;
          
        }
    }

    sort_answer(answer, answer_size, answer_idx);

    real_answer = answer[0];
 
    return real_answer;

    ///////////      End of Implementation      /////////////
    ///////////////////////////////////////////////////////
}

string Graph::getDijkstraShortestPath(string source, string destination) {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////

    string answer = "";
    string paths[101] = {};

    clean();
    setdirectedGraphwithweight();

    long long int dis_arr[101] = {};
    for (int i = 0; i < 101; i++) {
        dis_arr[i] = INF;
    }

    int source_key = Node.searchNodeidx(source, Node.size);
    int des_key = Node.searchNodeidx(destination, Node.size);
    int cur = source_key; // source_key부터 시작
    paths[source_key] = source + " "; //시작 노드 
    int min_idx = 0;
      

    for (int i = 0; i < Node.size; i++) dis_arr[i] = graph[cur][i];
    dis_arr[cur] = 0;
    visit[cur] = true;

    cur = getShortestNode(dis_arr);
    visit[cur] = true;
    paths[cur] = Node.nodes[cur] + " "; //path 업데이트 
    update_dis(cur, dis_arr, paths);

    for (int i = 0; i < Node.size - 2; i++) {

        int cur = getShortestNode(dis_arr);
        visit[cur] = true;
        update_dis(cur, dis_arr, paths);

    }
   
    
   if (dis_arr[des_key] == INF) answer = "error";
   else answer = paths[source_key] + paths[des_key] + to_string(dis_arr[des_key]);

   if (source_key == des_key) answer = paths[source_key] + "0";
    
   return answer;
    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}

string Graph::getFloydShortestPath(string source, string destination) {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////
    
    clean();
    setdirectedGraphwithweight();
    string answer = "";
    int path[101] = {};
    int path_size = 0;

    long long int dis_arr[101][101] = {};
    for (int i = 0; i < Node.size; i++) { // overflow 발생 가능, ll int로 만들어준 뒤 옮겨줌 
        for (int j = 0; j < Node.size; j++) {
            dis_arr[i][j] = graph[i][j];
        }
    }

    int next[101][101] = {};
    for (int i = 0; i < Node.size; i++) { // overflow 발생 가능, ll int로 만들어준 뒤 옮겨줌 
        for (int j = 0; j < Node.size; j++) {
            if (graph[i][j] == INF) next[i][j] = -1;
            else next[i][j] = j; 
        }
    }


    int source_key = Node.searchNodeidx(source, Node.size);
    int des_key = Node.searchNodeidx(destination, Node.size);

    for (int k = 0; k < Node.size; k++) {

        for (int i = 0; i < Node.size; i++) {

            for (int j = 0; j < Node.size; j++) {

                if (dis_arr[i][k] == INF || dis_arr[k][j] == INF)continue;

                if (dis_arr[i][j] > dis_arr[i][k] + dis_arr[k][j]) {

                    dis_arr[i][j] = dis_arr[i][k] + dis_arr[k][j]; // 경유점이 생길 때 마다 경로 업데이트 
                    next[i][j] = next[i][k]; // 경유점 저장 

                }

            }
        }
    }


    //answer = answer +  Node.nodes[source_key] + " ";
    bool isvalid = setfloydpath(path, next, path_size, source_key, des_key);
    if (isvalid == false) return " ";

    int cost = 0; 

        for (int i = 0; i < path_size-1; i++) {

            answer = answer + Node.nodes[path[i]] + " ";
            cost += dis_arr[path[i]][path[i + 1]]; 
         }

        answer += Node.nodes[path[path_size-1]] + " " + to_string(cost);
  
    return answer;

  
    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}

int Graph::primMST(ofstream &fout, string startNode) {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////

    clean();
    setundirectedGraphwithweight();

    bool visited[101] = {};
    bool unvisited[101] = {};

    for (int i = 0; i < Node.size; i++) unvisited[i] = true;

    int start = Node.searchNodeidx(startNode, Node.size);

    visited[start] = true;
    unvisited[start] = false;
    int cost = 0; 


    for (int i = 0; i < Node.size-1; i++) //Node.size-1회 수행
    {
        int min_cost = INF;
        int min_idx = 0;
        int min_start = 0;

        for (int j = 0; j < Node.size; j++){

            for (int k = 0; k < Node.size; k++){

                if (visited[j] == true && unvisited[k] == true) {

                    if (graph[j][k] > 0 && graph[j][k] < min_cost) {

                        min_cost = graph[j][k];
                        min_start = j;
                        min_idx = k;
                    }

                }

            }
        }

        visited[min_idx] = true; 
        unvisited[min_idx] = false;
        fout << Node.nodes[min_start] << " " << Node.nodes[min_idx] << " " << min_cost << " " << endl;
        cost += min_cost;
    }


    return cost;
    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}

int Graph::kruskalMST(ofstream &fout) {
    /////////////////////////////////////////////////////////
    //////////  TODO: Implement From Here      //////////////

    clean();
    setdirectedGraphwithweight();
    Edge.sort();

    string nodeA, nodeB;
    int cost = 0;
    int min_cost = 0;
    
    int parent[101] = { };

    for (int i = 0; i < Node.size; i++) parent[i] = i; // 초기 상태: 자기 자신 
  
    for (int i = 0; i < Edge.size; i++) {

        if (sameparent(i, parent) == false) {

            fout << Edge.StartEdge[i] << " " << Edge.desEdge[i] << " " << Edge.weight[i] << endl;
            cost+=Edge.weight[i];


        }



    }
    return cost;
    ///////////      End of Implementation      /////////////
    /////////////////////////////////////////////////////////
}