//
// Created by Hyunjung Kim on 2020-04-19.
//

#include "Graph.h"
#include "Stack.h"
#include "Queue.h"
#include "Stack.cpp"
#include "Queue.cpp"
#include <iostream>

using namespace std;

/** constructor **/
Graph::Graph(int n) {
    vertices_num = n;
    degree = new int[n];
    V = new edge_node*[n];
    for(int i=0; i<n; i++) {
        degree[i] = 0;
        V[i] = nullptr;
    }
}

/** destructor **/
Graph::~Graph(){
    for(int i=0; i<vertices_num; i++){
        edge_node* temp = V[i];
        while(temp){
            edge_node* del = temp;
            temp = temp->next;
            delete del;
        }
    }
    delete V;
    delete degree;
}

/** add edge(s)**/
void Graph::addEdge(int v, int w) {
    degree[v]++; degree[w]++;
    auto temp = new edge_node(v);
    temp->next = V[w]; V[w] = temp;
    temp = new edge_node(w);
    temp->next = V[v]; V[v] = temp;
}
void Graph::addEdges(int v, int n, ...){
    va_list arg_list;
    va_start(arg_list, n);

    degree[v] += n;
    for(int i=0; i<n; i++)
        addEdge(v, va_arg(arg_list, int));

    va_end(arg_list);
}

/** DFS **/
void Graph::dfs(int v){
    auto S = new Stack<int>();
    bool* visited = new bool[vertices_num];
    for(int i=0; i<vertices_num; i++)
        visited[i] = false;

    S->push(v);
    while(!S->isEmpty()){
        int u = S->pop();
        if(!visited[u]) {
            cout << u + 1 << " ";
            visited[u] = true;

            for (edge_node *node = V[u]; node; node = node->next) {
                if (!visited[node->value])
                    S->push(node->value);
            }
        }
    }

    delete[] visited;
    delete S;
}

/** BFS **/
void Graph::bfs(int v){
    int visited[vertices_num];
    for(int i=0 ;i<vertices_num; i++)
        visited[i] = false;
    Queue<int> queue;

    queue.push(v);
    visited[v] = true;
    cout << v+1 << " ";

    while(!queue.isEmpty()){
        int u = queue.pop();
        for(edge_node* temp = V[u]; temp; temp=temp->next){
            int w = temp->value;
            if(!visited[w]){
                visited[w] = true;
                cout << w+1 << " ";
                queue.push(w);
            }
        }
    }
}

/** show graph **/
void Graph::showGraph() {
    for(int i=0; i<vertices_num; i++){
        cout << "[" << i+1 << "]: ";
        for(edge_node* temp = V[i]; temp; temp = temp->next)
            cout << temp->value+1 << " ";
        cout << "\n";
    }
    cout<<endl;
}
