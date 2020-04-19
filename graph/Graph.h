//
// Created by Hyunjung Kim on 2020-04-19.
//

#ifndef GRAPH_GRAPH_H
#define GRAPH_GRAPH_H

class edge_node{
public:
    int value;
    edge_node* next;

    edge_node(int v){
        value = v;
        next = nullptr;
    }
};

class Graph{
public:
    edge_node** V;
    int* degree;
    int vertices_num;

    Graph(int n);
    ~Graph();
    void addEdge(int v, int w);
    void addEdges(int v, int n, ...);
    void dfs(int v);
    void bfs(int v);
    void showGraph();
};



#endif //GRAPH_GRAPH_H
