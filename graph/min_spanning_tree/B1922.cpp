#include <iostream>
#include <queue>
#include <algorithm>
#include <tuple>

/** 크루스칼 알고리즘을 이용한 최소신장트리 찾기 **/

using namespace std;

int sets[1001];
int N, M;
priority_queue<tuple<int,int,int>> lines;
int cost=0;

int parent(int x){
    if(sets[x]==x)
        return x;
    return sets[x] = parent(sets[x]);
}

void join(int x, int y){
    int px = parent(x);
    int py = parent(y);

    if(px==py) return;
    sets[px] = py;
}

bool same_set(int x, int y){
    return parent(x)==parent(y);
}


int main(){
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

    int a,b,c;
    cin>>N>>M;

    while(M--){
        cin>>a>>b>>c;
        lines.push({-c,a,b});
    }

    for(int i=1; i<=N; i++)
        sets[i]=i;

    N--;
    while(N--){
        do{
            tie(c,a,b) = lines.top(); lines.pop();
        }while(same_set(a,b));
        join(a,b);
        cost += -c;
    }

    cout<<cost;
}
