#include <iostream>
#include <climits>
#include <vector>

using namespace std;

int N, M;                   //N: 도시의 크기  M: 남길 수 있는 최대 치킨집 수
int num_h, num_c;           //num_h: 집 수  num_c: 치킨집 수
pair<int,int> houses[100];  //집 위치 배열
pair<int,int> chicken[13];  //치킨집 위치 배열
vector<int> selected;       //폐업 안 되는 치킨집 인덱스
int min_dis=INT_MAX;        //도시의 최소 치킨 거리

/**
 * h와 c 사이의 거리를 구해준다 (|x좌표차|+|y좌표차|)
 * @param h :집이 위치한 좌표
 * @param c :치킨집이 위치한 좌표
 * @return 집과 치킨집 사이의 거리
 */
int distance(pair<int,int> h, pair<int,int> c){
    return abs(h.first-c.first)+abs(h.second-c.second);
}

/**
 * num_c개의 치킨집 중에서 남길 M개의 치킨집의 조합을 재귀함수를 이용하여 구함
 * =>부분집합을 구하는 경우
 * @param n :n+1번째 치킨집을 폐업시킬지 남길지 선택함
 */
void solve(int n){
    //M개의 치킨집을 다 선택했을 때
    if(selected.size()==M){
        int total = 0; //치킨 거리 총합
        //각 집에 대해서 가장 가까운 치킨 거리를 구한다
        for(int i=0; i<num_h; i++){
            int closest = distance(houses[i],chicken[selected[0]]);
            for(auto it=selected.begin()+1; it!=selected.end(); ++it){
                int cost = distance(houses[i], chicken[(*it)]);
                //현재 집에서의 가장 작은 치킨 거리 구함
                if(cost<closest) closest = cost;
            }
            //총합에 현재 집에서의 최소 치킨 거리 더함
            total += closest;
        }
        //최솟값 갱신
        if(total<min_dis) min_dis = total;
    }
    //M개 보다 적은 치킨집이 선택되었을 때
    else if(n==num_c){
        return;
    }
    //남길 치킨집을 선택한다
    else{
        //n+1번째 치킨집이 선택됨
        selected.push_back(n);
        solve(n+1);
        //n+1번째 치킨집이 폐업됨
        selected.pop_back();
        solve(n+1);
    }
}

/**
 * main 함수
 */
int main(){
    int place;

    //입력을 받는다
    cin >> N; cin >> M;
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            cin >> place;
            //집
            if(place==1){
                //집의 좌표를 저장
                houses[num_h].first = i; houses[num_h].second = j;
                num_h++; //집 개수 증가
            }
            //치킨집
            else if(place==2){
                //치킨집의 좌표를 저장
                chicken[num_c].first = i; chicken[num_c].second = j;
                num_c++;  //치킨집 개수 증가
            }

        }
    }

    //M개의 치킨집을 남겼을 때의 치킨 거리 최솟값을 구함
    solve(0);

    //최소 치킨거리 값 출력
    cout<<min_dis;
}
