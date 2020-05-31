#include <iostream>
#include <algorithm>

using namespace std;

//절댓값을 기준으로 오름차순으로 정리할 때 사용할 비교 함수
bool compare(int a, int b){
    if(a<0) a = -a;
    if(b<0) b = -b;

    return a<b;
}

int N;  //용액의 개수
int solution[1000000];  //용액 특성값
int min_val;            //0에 가장 가까운 특성값의 합
int a, b;               //min_val를 만들어내는 두 용액의 인덱스

int main(){
    int temp;
    ios_base::sync_with_stdio(false); cin.tie(0);

    //입력
    cin >> N;
    for(int i=0; i<N; i++)
        cin >> solution[i];

    //용액의 특성값의 절댓값을 기준으로 오름차순으로 정리
    sort(solution, solution+N, compare);
    //시작값
    min_val = abs(solution[0]+solution[1]);
    a = 0; b = 1;

    //i번째 용액과 i+1번째 용액을 합친 특성값이 최소가 되는지 확인 
    for(int i=1; i<N-1; i++){
        temp = abs(solution[i]+solution[i+1]);
        if(min_val>temp) {
            a = i; b = i+1;
            min_val = temp;
        }
    }

    //결과 출력
    if(solution[a]>solution[b])
        cout << solution[b] <<" "<< solution[a];
    else
        cout << solution[a] <<" "<< solution[b];
}
