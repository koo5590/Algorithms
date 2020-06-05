#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int matrix[50][50];  //입력 배열
int copy_m[50][50];  //입력 배열 복사배열
int N,M;             //배열의 크기 N*M
int k;               //회전 연산의 개수
int rot[6][3];       //회전 연산 정보
int min_val=1e9;     //배열값의 최솟값
vector<int> order;   //회전 연산 순서


void solve(){
    int r,c,s, temp;
    //가능한 모든 회전 연산 순서의 경우의 수를 따짐
    do{
        //입력 배열을 새로 복사함
        for(int i=0; i<N; i++){
            for(int j=0; j<M; j++)
                copy_m[i][j] = matrix[i][j];
        }

        //order 벡터에 저장된 순서대로 회전 연산 수행
        for(int i=0; i<k; i++){
            int o = order[i];
            r=rot[o][0]-1; c=rot[o][1]-1; s=rot[o][2];

            //(r,c)와 가장 가까운 안 쪽 사각형부터 차례로 회전
            for(int v=1; v<=s; v++){
                //현재 사각형의 가장 왼쪽 위의 값 저장
                temp = copy_m[r-v][c-v];

                //왼쪽 열에서 회전
                for(int l=r-v; l<r+v; l++)
                    copy_m[l][c-v] = copy_m[l+1][c-v];
                //아래쪽 행에서 회전
                for(int l=c-v; l<c+v; l++)
                    copy_m[r+v][l] = copy_m[r+v][l+1];
                //오른쪽 열에서 회전
                for(int l=r+v; l>r-v; l--)
                    copy_m[l][c+v] = copy_m[l-1][c+v];
                //위쪽 행에서 회전
                for(int l=c+v; l>c-v+1; l--)
                    copy_m[r-v][l] = copy_m[r-v][l-1];

                copy_m[r-v][c-v+1] =temp;
            }
        }

        //각 행의 합을 구한 뒤 최솟값 구함 
        for(int i=0; i<N; i++){
            int sum = 0;
            for(int j=0; j<M; j++)
                sum += copy_m[i][j];
            if(min_val>sum)
                min_val = sum;
        }

    }while(next_permutation(order.begin(), order.end()));
}

int main(){
    ios_base::sync_with_stdio(false); cin.tie(0);

    cin >> N >> M >> k;

    for(int i=0; i<N; i++){
        for(int j=0; j<M; j++){
            cin >> matrix[i][j];
        }
    }
    for(int i=0; i<k; i++){
        for(int j=0; j<3; j++)
            cin >> rot[i][j];
    }

    for(int i=0; i<k; i++)
        order.push_back(i);

    solve();
    cout<<min_val;
}
