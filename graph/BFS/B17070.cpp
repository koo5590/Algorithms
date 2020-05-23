#include <iostream>
#include <queue>

using namespace std;

int N;
bool house[16][16];

enum direction{horz=0, vert=1, diag=2};

/**
 * 파이프가 (x,y)에 위치해 있을 때, dir 방향으로 밀 수 있는지 확인하는 함수
 * @param x 현재 위치한 행
 * @param y 현재 위치한 열
 * @param dir 이동하고자 하는 방향
 * @return dir 방향으로 이동 가능하면 true, 그렇지 않으면 false
 */
bool isInRange(int x, int y, int dir){
    switch(dir){
        //가로로 이동
        case horz:
            return (y+1<N && !house[x][y+1]);
        //세로로 이동
        case vert:
            return (x+1<N && !house[x+1][y]);
        //대각선으로 이동
        case diag:
            return (x+1<N && y+1<N && !house[x+1][y+1] &&
                    !house[x+1][y] && !house[x][y+1]);
        default:
            return false;
    }
}

//파이프의 위치
typedef struct pos{
    int x;
    int y;
    int dir;
}pos;

/**
 * main 함수 
 */
int main(){
    queue<pos> path;

    //집 상태를 입력 받음 (N*N)
    cin >> N;
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            cin >> house[i][j];
        }
    }


    int count = 0;
    //시작 위치 큐에 삽입
    pos pipe;
    pipe.x = 0; pipe.y = 1; pipe.dir = horz;
    path.push(pipe);
    //bfs를 사용하여 파이프가 (N-1,N-1)까지 도달하는 모든 경우의 수를 구함
    while(!path.empty()){
        pipe = path.front(); path.pop();
        int x = pipe.x; int y = pipe.y; int dir = pipe.dir;
        //목표 지점에 도달함
        if(x==N-1 && y==N-1){
            count++;
            continue;
        }
        pos next;

        //대각선 방향으로 이동 가능한지 확인
        if(isInRange(x,y,diag)){
            next.x=x+1; next.y=y+1; next.dir = diag;
            path.push(next);
        }
        //현재 방향에 따라 이동 가능한 방향이 다름
        switch(dir){
            //현재 가로 방향
            case horz:
                //가로 방향으로 파이프를 밀 수 있는지 확인
                if(isInRange(x,y,horz)){
                    next.x=x; next.y=y+1; next.dir = horz;
                    path.push(next);
                }
                break;
            //현재 새로 방향
            case vert:
                //세로 방향으로 파이프를 밀 수 있는지 확인
                if(isInRange(x,y,vert)){
                    next.x=x+1; next.y=y; next.dir = vert;
                    path.push(next);
                }
                break;
            //현재 대각선 방향
            case diag:
                //가로 방향으로 파이프를 밀 수 있는지 확인
                if(isInRange(x,y,horz)){
                    next.x=x; next.y=y+1; next.dir = horz;
                    path.push(next);
                }
                //세로 방향으로 파이프를 밀 수 있는지 확인
                if(isInRange(x,y,vert)){
                    next.x=x+1; next.y=y; next.dir = vert;
                    path.push(next);
                }
                break;
        }
    }

    cout << count;
}
