#include <iostream>
#include <queue>
#include <tuple>

using namespace std;

//땅의 크기
int N,M;

//이동 방향
int dir_x[]={-1,0,1,0};
int dir_y[]={0,1,0,-1};

priority_queue<tuple<int,int,int>> edges;  //섬들간의 다리 정보
queue<pair<int,int>> bfsq;
int land[10][10];  //땅 정보
int islands[7];    //섬들의 disjoint set
int num_island;    //섬 개수
int total_cost;    //다리의 총 길이

/* ====disjoint set operations==== */
/**
 * x가 속한 set의 대표값을 찾아서 반환함
 */
int parent(int x){
    if(islands[x]==x) return x;
    return islands[x] = parent(islands[x]);
}

/**
 * x,y의 set을 합침
 */
void join(int x, int y){
    int xp = parent(x);
    int yp = parent(y);
    islands[xp] = yp;
}

/**
 * x,y가 같은 set에 속해 있으면 true, 아니면 false 반환
 */
bool sameSet(int x, int y){
    return parent(x)==parent(y);
}
/* ============================= */

/**
 * (x,y)가 범위 내에 있는지 확인
 * @return 범위 내에 있으면 true, 아니면 false
 */
bool isInRange(int x, int y){
    return (0<=x && 0<=y && x<N && y<M);
}

/**
 * main 함수
 */
int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int index = 1;

    cin>>N>>M;
    for(int i=0; i<N; i++){
        for(int j=0; j<M; j++) {
            cin >> land[i][j];
            if(land[i][j])
                land[i][j] = -1;
        }
    }

    for(int i=0; i<N; i++){
        for(int j=0; j<M; j++){
            //새로운 섬 발견
            if(land[i][j]==-1){
                //섬에 번호 붙여줌
                land[i][j]=index;
                //자기 자신만을 원소로 가지는 set 초기화
                islands[index] = index;
                //섬에 해당하는 칸의 값을 index로 변경해줌
                bfsq.push({i,j});
                while(!bfsq.empty()){
                    auto temp = bfsq.front(); bfsq.pop();
                    for(int k=0; k<4 ; k++){
                        int x = temp.first+dir_x[k];
                        int y = temp.second+dir_y[k];
                        if(isInRange(x,y) && land[x][y]==-1){
                            land[x][y] = index;
                            bfsq.push({x,y});
                        }
                    }
                }
                index++;
            }
        }
    }
    num_island = index-1;

    //섬들간 세울 수 있는 다리 전부 저장
    for(int i=0; i<N; i++){
        for(int j=0; j<M; j++){
            //섬 발견
            if(land[i][j]){
                for(int k=0; k<4; k++){
                    int x=i+dir_x[k]; int y=j+dir_y[k];
                    //범위에서 벗어나거나 바다가 근접한 칸이 아닌 경우
                    if(!isInRange(x,y) || land[x][y])
                        continue;

                    //다른 섬을 발견하거나 범위를 벗어날 때 까지 진행
                    int dist = 0;
                    while(isInRange(x,y) && !land[x][y]){
                        dist++; x+=dir_x[k]; y+=dir_y[k];
                    }
                    //새로운 섬 존재 & 다리 길이가 1이상
                    if(isInRange(x,y) && land[x][y]!=land[i][j] && dist>1){
                        //다리 정보를 저장
                        edges.push({-dist, land[i][j], land[x][y]});
                    }
                }//for문 끝
            }//섬 발견 if문 끝
        }
    }

    total_cost = 0;
    int node1, node2, w;
    //크루스칼 알고리즘으로 min spanning tree의 총 weight 계산
    while(!edges.empty()){
        tie(w, node1, node2) = edges.top(); edges.pop();
        //이미 두 섬이 같은 set에 포함되어 있음
        if(sameSet(node1, node2))
            continue;
        //새로운 간선 추가
        total_cost += -w;
        join(node1, node2);
    }

    for(int i=1; i<num_island; i++){
        if(!sameSet(i,i+1))
            total_cost = -1;
    }

    cout<<total_cost;
}
