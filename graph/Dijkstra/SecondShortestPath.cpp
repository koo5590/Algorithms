#include <iostream>
#include <vector>
#include <queue>
#include <cstring>

/**
 * find the length of the second shortest path from S to D
 * N: number of nodes
 * M: number of edges
 */

using namespace std;

int N,M;  //N: # of nodes  M: # of edges
int S,D;  //S: source  D: destination
const int MAXVAL = 1000001; //larger than any possible cost of shortest paths

int cost[500];          //length of the path from S to i
vector<int> path[500];  //points to the node followed by i in the shortest path to i
bool visited[500];      //true if shortest path has been found already
vector<pair<int,int>> edges[500];  //edges[i]: edges from i as (destination, cost)


/**
 * find the shortest path from source node to every other nodes
 * using Dijkstra's algorithm.
 * @param s : source node
 */
void dijkstra(int s){
    priority_queue<pair<int,int>> shortest;

    cost[s] = 0; path[s].push_back(-1);
    shortest.push({0,s});
    while(!shortest.empty()){
        int a = shortest.top().second;
        int c = -shortest.top().first;
        shortest.pop();

        if(visited[a]) continue;
        visited[a] = true;

        for(const auto& road: edges[a]){
            if(cost[road.first]>=road.second+c){
                if(cost[road.first]>road.second+c){
                    path[road.first].clear();
                    cost[road.first] = road.second+c;
                    shortest.push({-cost[road.first], road.first});
                }
                path[road.first].push_back(a);
            }
        }
    }
}

/**
 * track the shortest path from s,
 * and adjust the cost of edges included in the shortest path
 * @param s : starting node
 */
void dfs(int s){
    if(path[s][0]==-1) return; //reached source node

    //edge in the shortest path: x->s
    for(auto x:path[s]){
        for(auto &node:edges[x]){
            //adjust the cost to MAXVAL
            if(node.first==s)
                node.second = MAXVAL;
        }
        //adjust edges in the shortest path from x
        dfs(x);
    }
}

int main(){
    ios::sync_with_stdio(false); cin.tie(0);
    int a,b,c;

    while(true){
        cin>>N>>M;
        if(N==0 && M==0) break;

        //initialization
        memset(visited, false, N);
        memset(cost, MAXVAL, N*sizeof(int));
        for(auto &x:path) x.clear();
        for(auto& x:edges) x.clear();

        cin>>S>>D;
        //process edges
        while(M--){
            cin>>a>>b>>c;  //from,to,cost
            edges[a].push_back({b,c});
        }

        //find the shortest path
        dijkstra(S);
        //adjust the cost of all edges in the shortest path
        dfs(D);

        //initialization
        memset(visited, false, N);
        memset(cost, MAXVAL, N*sizeof(int));
        //apply dijkstra again to find the second shortest path
        dijkstra(S);

        //there is no second shortest path
        if(cost[D]>=MAXVAL) cost[D] = -1;

        cout<<cost[D]<<"\n";
    }
}
