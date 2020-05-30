#include <iostream>
#include <climits>

using namespace std;

int result[500][500];         //중간 결과 저장
pair<int,int> matrices[500];  //행렬
int N;                        //행렬 개수


/**
 * [i,j) 범위의 행렬 곱의 최소 계산수를 구함
 * @param i 시작 인덱스
 * @param j 마지막+1 인덱스
 * @return 최솟값
 */
int solve(int i, int j){
    int min_sum=INT_MAX;
    int subsum1, subsum2;
    int sum;

    //행렬 i와 행렬 j-1이 같은 행렬 (base case)
    if(i==j-1)
        return 0;

    //[i,k-1]의 최소 계산횟수와 [k,j-1]의 최소 계산횟수를 각각 구해서 더함
    for(int k=i+1; k<j; k++){
        //이미 값을 구했으면 result 배열에서 가져다 사용
        subsum1 = result[i][k-1]?result[i][k-1]:solve(i,k);  //[i,k-1]
        subsum2 = result[k][j-1]?result[k][j-1]:solve(k,j);  //[k,j-1]
        //총 계산횟수 구해줌
        sum = subsum1+ subsum2 + matrices[i].first*matrices[k].first*matrices[j-1].second;
        //최솟값 구함
        if(sum<min_sum) min_sum = sum;
    }

    //결과 배열에 저장
    result[i][j-1] = min_sum;
    return min_sum;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);

    cin >> N;
    for(int i=0; i<N; i++){
        cin>>matrices[i].first;
        cin>>matrices[i].second;
    }

    cout<<solve(0,N);
}
