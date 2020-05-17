#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

//적에 대한 정보
typedef struct pos{
    int x;   //위치한 행
    int y;   //위치한 열
    int dis; //궁수까지의 거리 초기값
}pos;

/**
 * pos struct a와 b 두 개를 비교함
 * @return 비교값
 */
bool compare(pos a, pos b){
    //거리가 같으면 가장 오른쪽에 있는 것 선택
    if(b.dis==a.dis){
        return a.y>b.y;
    }
    //거리가 먼 것 먼저 선택
    return a.dis>b.dis;
}

bool field[15][15];      //격자판
bool copy_field[15][15]; //field 복사본
int range;               //가능한 사격 거리
int N, M;                //격자판 크기
int maxCount = 0;        //공격 가능한 최대 적의 수


int main(){
    int count;

    cin >> N >> M >> range;

    //격자판에 대한 정보 입력 받음
    for(int i=0; i<N; i++){
        for(int j=0; j<M; j++){
            cin >> field[i][j];
        }
    }

    //궁수 배치 가능한 모든 경우의 수를 따짐
    //i,j,k 열에 궁수를 배치함
    for(int i=0; i<M; i++){
        for(int j=i+1; j<M; j++){
            for(int k=j+1; k<M; k++){
                //공격 가능한 적의 수
                count = 0;
                //각 궁수에 위치를 기준으로 적에 대한 정보를 저장하는 벡터
                vector<pos> archer1; vector<pos> archer2; vector<pos> archer3;
                //격자판을 복사하고 각 벡터에 적에 대한 정보를 저장함
                for(int l=0; l<N; l++){
                    for(int m=0; m<M; m++){
                        //격자판 복사
                        copy_field[l][m] = field[l][m];
                        //적이 있다면
                        if(copy_field[l][m]) {
                            pos enemy;
                            //적의 현재 좌표 저장
                            enemy.x = l; enemy.y = m;
                            //i열에 위치한 궁수까지의 거리 계산해서 벡터1에 적 정보를 저장
                            enemy.dis = (N - l) + abs(m - i);
                            archer1.push_back(enemy);
                            //j열에 위치한 궁수까지의 거리 계산해서 벡터2에 적 정보를 저장
                            enemy.dis = (N - l) + abs(m - j);
                            archer2.push_back(enemy);
                            //k열에 위치한 궁수까지의 거리 계산해서 벡터3에 적 정보를 저장
                            enemy.dis = (N - l) + abs(m - k);
                            archer3.push_back(enemy);
                        }
                    }
                }

                //거리가 가장 먼 순서대로 적 정보를 정렬함
                sort(archer1.begin(), archer1.end(), compare);
                sort(archer2.begin(), archer2.end(), compare);
                sort(archer3.begin(), archer3.end(), compare);

                int add = 0; //턴이 지나간 횟수
                //세 개의 벡터 중 어느 하나라도 비게 되면 적이 다 사라지고 게임 끝
                while(!archer1.empty() && !archer2.empty() && !archer3.empty()){
                    pos en1;
                    while(!archer1.empty()) {
                        en1 = archer1.back();
                        //아직 공격받지 않았고 격자판 밖으로 사라진 적이 아닌 경우
                        if (copy_field[en1.x][en1.y] && N>en1.x+add) {
                            //공격 가능 범위에 있는지 확인
                            if(en1.dis - add <= range) {
                                //적을 공격
                                archer1.pop_back();
                                count++;
                                copy_field[en1.x][en1.y] = false;
                            }
                            //다음 턴으로 넘어감
                            break;
                        }
                        //아직 격자판 위에 있는 적을 찾아야 함
                        else archer1.pop_back();
                    }
                    pos en2;
                    while(!archer2.empty()) {
                        en2 = archer2.back();
                        //아직 공격받지 않았고 격자판 밖으로 사라진 적이 아닌 경우
                        if (copy_field[en2.x][en2.y] && N>en2.x+add) {
                            //공격 가능 범위에 있는지 확인
                            if(en2.dis - add <= range) {
                                //적을 공격
                                archer2.pop_back();
                                count++;
                                copy_field[en2.x][en2.y] = false;
                            }
                            break;
                        }
                        //아직 격자판 위에 있는 적을 찾아야 함
                        else {
                            archer2.pop_back();
                            //동시에 공격하는 적이라면 다음 턴으로 넘어감
                            if(en1.x==en2.x && en1.y&&en2.y)
                                break;
                        }
                    }
                    pos en3;
                    while(!archer3.empty()) {
                        en3 = archer3.back();
                        //아직 공격받지 않았고 격자판 밖으로 사라진 적이 아닌 경우
                        if (copy_field[en3.x][en3.y] && N>en3.x+add) {
                            //공격 가능 범위에 있는지 확인
                            if(en3.dis - add <= range) {
                                //적을 공격
                                archer3.pop_back();
                                count++;
                                copy_field[en3.x][en3.y] = false;
                            }
                            break;
                        }
                        //아직 격자판 위에 있는 적을 찾아야 함
                        else {
                            archer3.pop_back();
                            //동시에 공격하는 적이라면 다음 턴으로 넘어감
                            if((en1.x==en3.x && en1.y&&en3.y) || (en2.x==en3.x && en2.y&&en3.y))
                                break;
                        }
                    }
                    //턴 한 번이 지나감
                    add++;
                }
                //각 경우의 수에서 최댓값을 구함
                if(count>maxCount) maxCount = count;
            }
        }
    }

    cout << maxCount;
}
