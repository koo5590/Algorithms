#include <iostream>
#include <climits>
#include <queue>

using namespace std;

//Dijkstra's algorithm using priority queue

vector<pair<int,int>> graph[20001];
int cost[20001];    //shortest distance 
priority_queue<pair<int,int>> vertices;  //vertices to which the shortest path not yet found
int V, E;
int K;

int main(){
    int u, v,w;
    int cur;

    ios_base::sync_with_stdio(false); cin.tie(0);

    cin >> V >> E >> K;

    for(int i=0; i<E; i++){
        cin>>u; cin>>v; cin>>w;
        graph[u].push_back({v,w});
    }

    for(int i=1; i<=V; i++)
        cost[i] = INT_MAX;

    cost[K] = 0;
    vertices.push({0,K});

    while(!vertices.empty()){
        cur = vertices.top().second; vertices.pop();

        //relaxation of edges
        for(auto it:graph[cur]){
            if(cost[cur] + it.second < cost[it.first]){
                cost[it.first] = cost[cur] + it.second;
                vertices.push({-cost[it.first], it.first});
            }
        }
    }

    for(int i=1; i<=V; i++){
        if(cost[i] == INT_MAX)
            cout<<"INF\n";
        else
            cout << cost[i] << "\n";
    }

}
