#include <iostream>
#include <algorithm>

using namespace std;

int x;              //구멍의 너비
int n;              //레고 조각수
int lego[1000000];  //레고 조각들
string buffer;
bool flag;          //답 찾으면 true

int main(){
    ios_base::sync_with_stdio(false); cin.tie(0);

    while (getline(cin, buffer) && !buffer.empty()){
        flag = false;
        //입력
        x = atoi(buffer.c_str());
        cin>>n;
        for (int i = 0; i < n; i++)
            cin >> lego[i];
        cin.ignore();

        //크기의 오름차순으로 레고 조각 정렬
        sort(lego, lego + n);

        int l = 0;     //가장 왼쪽에서 시작
        int r = n - 1; //가장 오른쪽에서 시작
        x *= 1e7;

        //양 옆에서 한 칸씩 중간으로 이동하면서 답을 찾음
        while (l < r) {
            int sum = lego[l] + lego[r];
            //구멍에 맞는 조각 2개 찾음
            if(sum == x){
                flag = true;
                break;
            }
            else if(sum<x)
                l++;
            else
                r--;

        }
        if(flag)
            cout << "yes " << lego[l] << " " << lego[r] << "\n";
        else
            cout << "danger\n";
    }
}
