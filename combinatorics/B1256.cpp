#include <iostream>
#include <cmath>

using namespace std;

//n개의 a개을 몇 개의 칸에 넣을지 선택하는 경우의 수
//nCi : i개의 칸을 선택해서 그 자리에 a를 넣음

char str[201];
int in = 0;
long dp[201][201];
bool unsolvable = false;
int MAX = 1e9;

//aCb를 구함
long binom(int a, int b){
    if(dp[a][b]) return dp[a][b];
    if(a==b || b==0) return dp[a][b] = 1;

    long temp = binom(a-1,b-1) + binom(a-1, b);
    if(temp>MAX) temp = MAX; //1e9를 넘어가는 순간 값을 MAX로 바꿔줌
    return dp[a][b] = temp;
}

void solve(int a, int b, int k){
    if(a==0){  //letter z만 남은 경우
        while(b--) //남은 문자를 z로 채움
            str[in++] = 'z';
        return;
    }
    if(b==0){  //letter a만 남은 경우
        if(k!=1){ //문자열의 수가 k보다 작음
            unsolvable = true;
            return;
        }
        while(a--) //남은 문자를 a로 채움
            str[in++] = 'a';
        return;
    }

    //a를 선택했을 때의 그 다음 이어지는 substring의 경우의 수
    int boundary = (int)binom(a+b-1, a-1);

    if(k<=boundary){ //a 선택
        str[in++] = 'a';
        solve(a-1, b, k);
    }
    else{           //b 선택 
        str[in++] = 'z';
        solve(a,b-1,k-boundary);
    }
}

int main(){
    ios_base::sync_with_stdio(false); cin.tie(0);

    int N,M,K;

    cin>>N>>M>>K;

    solve(N,M,K);
    if(unsolvable) cout<<-1;
    else{
        for(int i=0; i<in; i++)
            cout<<str[i];
    }

}
