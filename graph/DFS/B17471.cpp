#include <iostream>
#include <vector>
#include <set>

using namespace std;

int N;                 //구역 수
int population[11];    //구역 별 인구 수
bool division[11];     //선거구 구분
vector<int> adj[11];   //구역 별 인접 구역
int min_diff=-1;       //최소 인구 차


/**
 * 구역 s가 포함된 선거구 sector 내의 모든 구역이 서로 연결되어 있는지 확인한다
 * @param s       시작 구역
 * @param sector  같은 선거구에 포함된 구역들
 * @return        모든 구역이 서로 연결되어 있으면 true, 아니면 false
 */
bool dfs(int s, set<int> sector){
    vector<int> nodes;  //지나간 구역 저장

    //s 구역에서 탐색 시작
    nodes.push_back(s);
    sector.erase(s);

    while(!nodes.empty() && !sector.empty()){
        int v = nodes.back(); nodes.pop_back();
        //현재 구역에서 인접한 구역들 중, sector 집합에 포함된 구역들을 찾음
        for(auto x:adj[v]){
            if(sector.count(x)) {
                //벡터에 새로운 연결된 구역 저장
                nodes.push_back(x);
                //지나간 구역 집합에서 삭제
                sector.erase(x);
            }
        }
    }
    return sector.empty();
}


/**
 * n개의 구역들을 2개의 선거구로 나누는 순열 생성하고 그 때의 경우의 수에 대해 인구 수 차를 구함
 * @param n  구역 개수
 */
void perm(int n){
    //모든 구역에 대한 처리가 끝남
    if(n==N+1){
        int sum_a = 0; int sum_b = 0;    //각 선거구 총 인구 수
        int sa, sb;                      //탐색을 시작할 구역
        set<int> sec_a; set<int> sec_b;  //각 선거구에 포함된 구역

        for(int i=1; i<=N; i++){
            //선거구 A에 포함된 경우
            if(division[i]) {
                sum_a += population[i];
                sec_a.insert(i);
                sa = i;
            }
            //선거구 B에 포함된 경우
            else {
                sum_b += population[i];
                sec_b.insert(i);
                sb = i;
            }
        }

        //각 선거구에 구역이 최소 1개 포함되어 있는 지 확인
        if(sec_a.empty() || sec_b.empty())
            return;

        //각 선거구의 구역들이 전부 연결되어 있는 지 확인
        if(dfs(sa, sec_a) && dfs(sb, sec_b)){
            //최소 인구 수 구함
            int diff = abs(sum_a-sum_b);
            if(min_diff==-1 || min_diff>diff)
                min_diff = diff;
        }
    }
    else{
        //구역 n을 선거구 A에 포함하는 경우
        division[n] = true;
        perm(n+1);
        //구역 n을 선거구 B에 포함하는 경우
        division[n] = false;
        perm(n+1);
    }
}


/**
 * main 함수
 */
int main(){
    int v, n;
    ios_base::sync_with_stdio(false); cin.tie(0);

    //입력
    cin>>N;
    for(int i=1; i<=N; i++)
        cin>>population[i];
    for(int i=1; i<=N; i++){
        cin>>n;
        for(int j=0; j<n; j++){
            cin>>v;
            adj[i].push_back(v);
        }
    }

    //문제 해결
    perm(1);

    //결과 출력
    cout<<min_diff;
}
