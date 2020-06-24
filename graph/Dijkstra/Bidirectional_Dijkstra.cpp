#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <climits>

/**
 * Bidirectional Dijkstra
 */

using namespace std;

int min_cost=INT_MAX;
int N, M;

vector<pair<int,int>> graph_f[1001];      //forward pass adjacency list
vector<pair<int,int>> graph_b[1001];      //backward pass adjacency list
priority_queue<pair<int,int>> forward_p;  //forward pass
priority_queue<pair<int,int>> backward_p; //backward pass
int dist_f[1001];  //forward pass shortest distance
int dist_b[1001];  //backward pass shortest distance
set<int> forward_visited;  //contains visited nodes in forward pass
set<int> backward_visited; //contains visited nodes in backward pass

/**
 * find the sum of weights of the shortest path from *src* to *dest*
 * @param src   source node
 * @param dest  destination node
 */
void Dijkstra(int src, int dest){
    //initialize the distance to all nodes to large number
    for(int i=1; i<=N; i++)
        dist_f[i] = dist_b[i] =INT_MAX;

    //starting node of forward pass
    forward_p.push({0,src});   dist_f[src] = 0;
    //starting node of backward pass
    backward_p.push({0,dest}); dist_b[dest] = 0;

    //find the meeting point of forward and backward passes
    while(!forward_p.empty() && !backward_p.empty()){
        /* forward pass */
        auto forward_node = forward_p.top(); forward_p.pop();
        int to = forward_node.second; int cost = -forward_node.first;
        //skip if the shortest path already found
        if(forward_visited.count(to)) continue;
        forward_visited.insert(to);

        //relax each edge from the current node
        for(auto edge:graph_f[to]){
            //update current shortest path
            if(!forward_visited.count(edge.first) && dist_f[edge.first] > cost + edge.second) {
                dist_f[edge.first] = cost + edge.second;
                forward_p.push({-(cost + edge.second), edge.first});
               
            }
        }

        /* backward pass */
        auto back_node = backward_p.top(); backward_p.pop();
        int from = back_node.second; cost = -back_node.first;

        //skip if the shortest path alreayd found
        if(backward_visited.count(from)) continue;
        backward_visited.insert(from);

        //relax each edge from the current node
        for(auto edge:graph_b[from]){
            //update current shortest path
            if(!backward_visited.count(edge.first) && dist_b[edge.first] > cost + edge.second) {
                dist_b[edge.first] = cost + edge.second;
                backward_p.push({-(cost + edge.second), edge.first});
            }
        }

        //if at least one of the current nodes is computed in both passes: done
        if(backward_visited.count(to) || forward_visited.count(from))
            break;
    }

    //find the shortest path
    for(int v=1; v<=N; v++){
        //check if both passes found ways to node v and
        //sum of the weights of the paths from the two passes
        //if smaller than the current min value
        if(dist_b[v]!=INT_MAX && dist_f[v]!=INT_MAX &&
           min_cost > dist_b[v]+dist_f[v]){
                min_cost = dist_b[v] + dist_f[v];
        }
    }

}

int main() {
    int from, to, cost;
    ios_base::sync_with_stdio(false); cin.tie(0);

    cin>>N>>M;
    for(int i=0; i<M; i++){
        cin>>from>>to>>cost;
        graph_f[from].push_back({to,cost});
        graph_b[to].push_back({from, cost});
    }
    cin>>from>>to;

    Dijkstra(from,to);
    cout<<min_cost;
}

