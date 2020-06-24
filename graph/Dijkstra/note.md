### 다익스트라 알고리즘 구현 문제 

처음에 다익스트라 알고리즘을 구현할 때는 boolean 타입의 배열을 사용해서 이미 출발 노드에서 최소 거리를 찾은 노드를 표시할 수 있게 했다.
~~~cpp
#include <iostream>
#include <climits>
#include <queue>

using namespace std;

//Dijkstra's algorithm using priority queue

vector<pair<int,int>> graph[20001];
int cost[20001];    //shortest distance 
bool found[20001];  //shortest path already found
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
        if(found[cur]) continue;
        found[cur] = true;

        //relaxation of edges
        for(auto it:graph[cur]){
            if(found[it.first]) continue;
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
~~~

하지만, 다른 사람들의 코드를 읽어보던 중 이 배열을 사용하지 않는 경우를 보았다.
그래서 코드를 다시 찬찬히 살펴보니 사용하지 않아도 문제없다는 것을 알게 되었다.
그렇다면 시간 복잡도 측면에서는 어떨까?
분명 이 배열을 사용하지 않아도 최소 값을 얻을 수 있는 것은 확실했다.
그렇다면 이미 최소 값을 얻은 노드를 반복해서 처리하는 경우가 생길 수 있을까?
우선 수정된 코드는 다음과 같다.

~~~cpp
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
~~~
여기서 핵심은, 우선순위 큐에는 더 작은 거리 값이 발견 될 때만 새로운 값이 추가된다는 것이다. 이 점은 수정 전이나 후의 코드 모두에 해당된다.
그리고 수정된 코드에서도, 최소 값이 발견된다면, if문 때문에 더 이상 이 노드까지의 거리 값이 큐에 저장되지 않는다. 따라서 이 경우만 보면 시간 수행에 차이가 없는
것 처럼 보인다. 

단, 거리 값을 계산하는 방식이 복잡한 경우 간단하게 bool 배열로만 처리하는 게 더 나을 수도 있겠다는 생각이 들었다. 또한, 최소 거리를 찾은 노드를 확인할 때, 
1byte 짜리 bool 값만을 가지고 비교하는게 더 효율적일 수도 있을 것 같다. 그리고 사실, 최솟값을 찾았더라도 우선순위 큐가 코드에서 사용된 방식에 따라 이전에 
넣어놨던 더 큰 값들이 뽑아져 나올 수 있고, 결과에 영향을 미치지 않지만 relaxation 여러 번 반복 될 수도 있다. 따라서 relaxation 과정의 비용이 크다면,
수행 시간에 유의미한 영향을 미칠 수 있을 것이라고 생각한다. 예를 들어 다음과 같이 relaxation 수행 전에 100,000,000 번 루프를 돌면서 아무 의미 없는
변수에 값을 할당하는 코드를 넣어놓고, 두 구현 방식에서 수행 속도에 차이가 있는지 보기 위해 간단한 실험을 해보았다. 
~~~cpp
for(auto it:graph[cur]){
            //if(found[it.first]) continue; 수정 전 
            for(int i=0; i<100000000; i++)
                int test = i;
            if(cost[cur] + it.second < cost[it.first]){
                cost[it.first] = cost[cur] + it.second;
                vertices.push({-cost[it.first], it.first});
            }
        }
~~~
테스트 케이스의 크기(노드, 간선 개수 등)가 작은 경우에는 크게 차이가 없었지만, 케이스가 꽤 커진 경우에는 bool 배열을 사용한 경우가 조금 더 빠른 것을 확인 할 수 있었다.
가령, 다음과 같은 두 개의 테스트 케이스를 두 구현마다 각 3번씩 실행해 보았다. 
~~~
7 24
3
1 2 2
2 1 2
1 3 2
3 1 2
2 4 2
4 2 2
2 5 2
5 2 2
3 6 2
6 3 2
3 7 2
7 3 2
1 2 1
2 1 1
1 3 1
3 1 1
2 4 1
4 2 1
2 5 1
5 2 1
3 6 1
6 3 1
3 7 1
7 3 1

9 24
1
1 2 1
2 1 1
2 3 1
3 2 1
1 3 1
3 1 1
3 4 1
4 3 1
3 7 1
7 3 1
4 7 1
7 4 1
4 5 1
5 4 1
5 6 1
6 5 1
4 6 1
6 4 1
7 8 1
8 7 1
7 9 1
9 7 1
8 9 1
9 8 1
~~~

그 결과,
1. 첫 번째 테스트 케이스
  * 수정 전: 2.25275 / 2.250341 / 2.256751 (초)
  * 수정 후: 7.886941 / 7.983141 / 7.94431 (초)
2. 두 번째 테스트 케이스 
  * 수정 전: 2.26190 / 2.558030 / 2.253390 (초)
  * 수정 후: 4.544890 / 2.584680 / 4.530350 (초)

많은 테스트 케이스도 아니고 제대로 된 실험도 아니지만 유의미한 차이가 발생했다는 것을 알 수 있다. 

일단 이렇게 생각해보았는데, 알고리즘의 효율성을 따지는 문제는 생각보다 어려운 것 같다. 내 의견이 틀렸을 수도 있다.
더 공부를 해보고 틀린 점이 있으면 더 많은 테스트를 수행해보고 추후에 수정이 필요할 것 같다. 

