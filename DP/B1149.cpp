#include <iostream>

using namespace std;

int N;               //집의 수
int house[1000][3];  //각 집의 칠하는 가격
int cost;            //최소 가격
int rgb[3];          //마지막 집을 빨강, 초록, 파란색으로 칠했을 때의 최소 가격

int main(){
    int red, green, blue;

    cin >> N;
    for(int i=0; i<N; i++){
        for(int j=0; j<3; j++)
            cin >> house[i][j];
    }

    //첫 집의 각 색으로 칠하는 가격
    rgb[0]=house[0][0];
    rgb[1]=house[0][1];
    rgb[2]=house[0][2];

    //두 번째 집 부터 rgb 각 색으로 마지막 집을 칠했을 때의 최소 가격을 rgb 배열에 저장한다
    for(int i=1; i<N; i++){
        red = rgb[1]<rgb[2]?rgb[1]:rgb[2]; red+=house[i][0];     //i번째 집을 빨간색으로 칠한 경우
        green = rgb[0]<rgb[2]?rgb[0]:rgb[2]; green+=house[i][1]; //i번째 집을 초록색으로 칠한 경우
        blue = rgb[0]<rgb[1]?rgb[0]:rgb[1]; blue+=house[i][2];   //i번째 집을 파란색으로 칠한 경우
        rgb[0]=red; rgb[1]=green; rgb[2]=blue;
    }
    //최솟값을 구한다 
    cost = rgb[0]<rgb[1]?rgb[0]:rgb[1];
    cost = cost<rgb[2]?cost:rgb[2];

    cout<<cost;
}
