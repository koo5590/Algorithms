#include <iostream>
#include <cmath>

using namespace std;

/**
 * 1) x-1 이하의 수들 중에서 x와 서로소인 수들의 개수를 구한다
 *    ex) (4,2)는 (2,1)로 약분이 되기 때문에 이미 다른 직선을 통과했음
 * 2) y=x를 기준으로 대칭되기 때문에 *2를 해준다
 * 3) x,y=1 일 때 3가지 경우를 더해준다
 */

bool map[1001];   //false 이면 서로소
int dp[1001];
int size = 1001;

// 에라토스테네스의 체를 이용하여 size까지의 소수를 구한다
void eratos(){
    for(int i=2; i<=size; i++){
        if(!map[i]){ //소수인 경우
            for(int j=2; j*i<size; j++){
                //이 소수를 약수로 가지는 수를 모두 제외한다
                if(!map[j*i]) map[j*i] = true;
            }
        }
    }
};


int points(int n){
    if(dp[n]!=-1) return dp[n]; //이미 개수를 구한 경우

    if(map[n]==0){  //소수인 경우
        return dp[n] = n-1;
    }

    //소수가 아닌 경우
    dp[n] = 1;
    for(int i=2; i<=n; i++){
        //n보다 작은 수 들 중에서 소수이면서 n의 약수인 i를 찾는다
        if(map[i]==0 && n%i==0){
            int count = 0;
            int num = n;
            //n이 i로 몇 번 약분되는지 계산
            while(num%i==0){
                count++;
                num /= i;
            }
            //(소수)^m 으로 n이 약분 될 때, (소수)^m의 서로소 개수를 모두 곱해줌
            int temp = pow(i, count);
            dp[n] *= temp - temp/i;
        }
    }

    return dp[n];
}

//시간 복잡도 O(sqrt(n))
int euler(int n){
    int result = 1;

    for(int p=2; p*p<=n; p++){
        if(n%p==0){
            int pm = 1;
            while(n%p==0){
                n/=p;
                pm *= p;
            }
            result *= (pm-(pm/p));
        }
    }

    //소수가 남음
    if(n!=1){
        result *= n-1;
    }

    return result;
}

int main(){
    ios_base::sync_with_stdio(false); cin.tie(0);

    int C, N;

    cin>>C;

    for(int i=0; i<=1000; i++) dp[i] = -1; //초기화
    eratos();  //소수 구하기

    while(C--){
        cin>>N;

        int count = 0;
        //2부터 N까지 각 수의 서로소 개수 구해서 합해주기
        for(int i=2; i<=N; i++)
            count += euler(i);

        cout<< count*2+3<<"\n";
    }
}
