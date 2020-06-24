#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <climits>

using namespace std;

/**
 * find the shortest path from start to end
 * :print out the cost and the shortest path
 */

int n, m;  //n: number of nodes, m: number of edges
vector<pair<int,int>> edges[1001];     //edges[i]: edges from ith node to other nodes each with its weight
priority_queue<pair<int,int>> min_val; //s
bool found[1001];   //true: min_path found
int parent[1001];   //precursor to ith node in the path
int cost[1001];     //cost of path from start node to ith node

int main(){
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int s,e,dis;
    int num=0;

    int start, end;   //start & destination node
    stack<int> path;  //min path to destination node

    cin>>n>>m;
    for(int i=0; i<m; i++){
        cin>>s>>e>>dis;
        edges[s].push_back({dis, e});
    }
    cin>>start>>end;

    //initialize cost
    for(int i=0; i<=n; i++)
        cost[i] =INT_MAX;

    //start from start node
    parent[start] =-1; cost[start] = 0;
    min_val.push({0, start});

    while(!min_val.empty()){
        //take the node with the smallest cost on the queue
        s = min_val.top().second; min_val.pop();
        //if shortest path already found, skip
        if(found[s]) continue;
        found[s] = true;

        //if shortest path to destination node found, stop
        if(s==end) break;

        //relax each edge from s
        for(auto x:edges[s]){
            //shorter path found
            if(!found[x.second] && cost[x.second] > cost[s]+x.first) {
                cost[x.second] = cost[s]+x.first;  //update the new cost value
                parent[x.second] = s;              //update precursor node
                min_val.push({-(cost[s] + x.first), x.second});
            }
        }
    }

    //track all the nodes in the path from the destination node
    e = end;
    path.push(end);
    while(parent[e]!=-1){
        path.push(parent[e]);
        e = parent[e];
    }
    path.push(start);
    //number of nodes in the path
    num = path.size();

    cout<<cost[end]<<"\n";
    cout<<num+1<<"\n";
    path.pop();
    while(!path.empty()){
        cout<<path.top()<<" ";path.pop();
    }
}
