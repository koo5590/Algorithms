#include <iostream>
#include <queue>

using namespace std;

int dir_x[] = {-1,0,1,0};
int dir_y[] = {0,1,0,-1};

int R,C;
char map[50][50];
bool visited[50][50];

bool inRange(int i, int j){
    return (0<=i && i<R && 0<=j && j<C);
}

int bfs(int sx, int sy){
    queue<pair<pair<int,int>,int>> pathq;

    pathq.push({{sx,sy},0});
    visited[sx][sy] = true;

    for(int i=0; i<R; i++){
        for(int j=0; j<C; j++){
            if(map[i][j]=='*')
                pathq.push({{i,j},-1});
        }
    }

    while(!pathq.empty()){
        int i = pathq.front().first.first;
        int j = pathq.front().first.second;
        int len = pathq.front().second;
        pathq.pop();

        if(map[i][j]=='*'){
            for(int k=0; k<4; k++){
                int ni = i+dir_x[k]; int nj = j+dir_y[k];

                if(inRange(ni,nj) && map[ni][nj]=='.'){
                    map[ni][nj] = '*';
                    pathq.push({{ni,nj},-1});
                }
            }
        }

        else {
            for (int k = 0; k < 4; k++) {
                int ni = i + dir_x[k]; int nj = j + dir_y[k];

                if(inRange(ni,nj)){
                    if(map[ni][nj]=='.' && !visited[ni][nj]) {
                        visited[ni][nj] = true;
                        pathq.push({{ni, nj}, len + 1});
                    }
                    else if(map[ni][nj]=='D')
                        return len+1;
                }
            }
        }
    }

    return -1;
}

int main(){
    ios::sync_with_stdio(false); cin.tie(0);

    cin>>R>>C;

    int si, sj;
    for(int i=0; i<R; i++){
        for(int j=0; j<C; j++){
            cin>>map[i][j];

            if(map[i][j]=='S'){
                si = i; sj = j;
                map[i][j] = '.';
            }
        }
    }

    int time = bfs(si,sj);

    if(time==-1) cout<<"KAKTUS";
    else cout<<time;

}

//물도 큐에 넣어서 고슴도치와 같이 움직인다고 생각하고 문제를 풀면 된다 
