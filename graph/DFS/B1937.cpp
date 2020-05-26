#include <iostream>

using namespace std;

int dir_x[] = {-1,0,1,0};
int dir_y[] = {0,1,0,-1};

int forest[500][500];  //대나무숲 각 칸의 대나무 수
int path[500][500];    //각 칸에서 시작했을 때 판다가 살 수 있는 최대 일수
int n;                 //대나무숲 크기
int max_dist = 0;      //판다가 살 수 있는 최대 일수

/**
 * (x,y)가 n*n 배열 범위 내에 있는지 확인한다
 * @param x 행
 * @param y 열
 * @return (x,y)가 n*n 배열 범위 내에 있으면 true, 아니면 false
 */
bool inRange(int x, int y){
    return (0<=x && x<n && 0<=y && y<n);
}

/**
 * (x,y)에서 이동 가능한 모든 칸을 탐색하고, 최대 일수를 구한다
 * @param x 현재 위치한 행
 * @param y 현재 위치한 열
 * @return 현재 칸에서부터 시작했을 때의 최대 일수
 */
int dfs(int x, int y){
    int temp;
    path[x][y] = 1;

    //동서남북 방향으로 이동 했을 때의 최대 일수를 각각 구하고
    //그 값들 중에서 최대값을 구해서 path[x][y]에 저장한다
    for(int i=0; i<4; i++){
        int nx = x+dir_x[i]; int ny = y+dir_y[i];
        //이웃 노드로 이동 가능한 경우
        if(inRange(nx,ny) && forest[nx][ny]>forest[x][y]) {
            //이미 최대 일수가 계산되어 있을 때 (이미 방문한 칸)
            if (path[nx][ny] != 0)
                temp = path[nx][ny]+1;
            //최대 일수가 계산되어 있지 않을 때
            else
                temp = dfs(x + dir_x[i], y + dir_y[i])+1;
            //최댓값을 구해준다
            if(temp>path[x][y])
                path[x][y] = temp;
        }
    }
    //현재 칸에서 시작했을 때의 최대일수를 반환해준다 
    return path[x][y];
}


int main(){
    ios_base::sync_with_stdio(false); cin.tie(0);
    int dist;

    //대나무 숲에 대한 정보를 입력 받는다 
    cin >> n;
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++)
            cin >> forest[i][j];
    }

    //각 칸 별로 dfs()를 수행해서 각 칸에서 시작했을 때의 최대 일수를 구한다
    //이미 구한 경우, path[i][j]를 이용한다
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if(path[i][j]==0)
                dist = dfs(i,j);
            else
                dist = path[i][j];
            //최대값을 구해준다 
            if(dist>max_dist)
                max_dist = dist;
        }
    }

    cout<<max_dist;
}
