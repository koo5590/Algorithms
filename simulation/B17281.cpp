#include <iostream>
#include <vector>

using namespace std;

int inning[50][10];   //각 이닝에서의 각 선수의 결과
int N;                //이닝 횟수
bool in[10];          //순열에 포함되어있는지 아닌지
int max_points = -1;  //얻을 수 있는 최대 점수
vector<int> players;  //선수 순열

/**
 * 재귀적으로 선수들의 순열을 찾아서 해당 타순일 때의 경기 점수를 구함
 */
void solve(){
    int len = players.size();
    //순열이 완성됨
    if(len==9){
        int out = 0; //아웃 횟수
        int nth = 0; //n+1번째 이닝
        int base[4] = {0,0,0,0};  //루, base[3]이 홈
        int p = 0;   //타자 순서

        //모든 이닝이 끝날 때 까지
        while(nth<N){
            //(nth+1)번 째 이닝에서 players[p]번 타자의 결과
            switch(inning[nth][players[p]]){
                case 0: //아웃
                    out++;
                    break;
                case 1: //안타
                    base[3]+=base[2]; base[2]=base[1];
                    base[1]=base[0]; base[0]=1;
                    break;
                case 2: //2루타
                    base[3]+=(base[2]+base[1]);
                    base[2]=base[0];
                    base[1]=1; base[0]=0;
                    break;
                case 3: //3루타
                    base[3]+=(base[2]+base[1]+base[0]);
                    base[2]=1; base[1]=base[0]=0;
                    break;
                case 4:  //홈런
                    base[3]+=(base[2]+base[1]+base[0]+1);
                    base[2]=base[1]=base[0]=0;
                    break;
            }
            p = (p+1)%9;
            //삼진
            if(out==3){
                out=0;
                base[2]=base[1]=base[0]=0;
                //다음 이닝
                nth++;
            }
        }
        //최댓값 구함
        if(max_points<base[3])
            max_points = base[3];
    }
    //1번 주자는 4번으로 고정된다
    else if(len==3){
        players.push_back(1);
        solve();
        players.pop_back();
    }
    else{
        for(int i=2; i<=9; i++){
            if(in[i]) continue;
            in[i] = true;
            players.push_back(i);
            solve();
            in[i] = false;
            players.pop_back();
        }
    }
}

int main(){
    ios_base::sync_with_stdio(false); cin.tie(0);

    cin >> N;
    for(int i=0; i<N; i++){
        for(int j=1; j<=9; j++)
            cin >> inning[i][j];
    }

    solve();
    cout<<max_points;
}
