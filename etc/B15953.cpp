#include <iostream>
#include <string>

using namespace std;

#define NUM_2018 7  //number of contenders in 2018
#define NUM_2019 6  //number of contenders in 2019

//{ #of contenders, amount prize money these contenders receive } from the highest rank in 2018 (unit: 10,000won)
pair<int,int> priz1[NUM_2018]={{0,0},{1,500},{2, 300},{3,200},{4,50},{5,30},{6,10}};
//{ #of contenders, amount prize money these contenders receive } from the highest rank  in 2019 (unit: 10,000won)
pair<int,int> priz2[NUM_2019]={{0,0},{1,512},{2,256},{4,128},{8,64},{16,32}};

int main(){
    //cases
    short int fest1[1000];
    short int fest2[1000];
    //total amount of prize money for each case
    int total[1000];
    int T;  //number of cases

    //input from user
    cin >> T;
    for(int i=0; i<T; i++){
        cin>>fest1[i]; cin>>fest2[i];
    }

    //calculate the lowest possible rank to get priz1[i]
    for(int i=1; i<NUM_2018; i++)
        priz1[i].first += priz1[i-1].first;
    //calculate the lowest possible rank to get priz2[i]
    for(int i=1; i<NUM_2019; i++)
        priz2[i].first += priz2[i-1].first;

    //calculate the total prize money each case can get
    for(int i=0; i<T; i++){
        int sum = 0;
        //find the amount of prize money that a contender in fest1[i]th place gets
        for(int j=0; j<NUM_2018; j++){
            if(priz1[j].first >= fest1[i]) {
                sum = priz1[j].second;
                break;
            }
        }
        //find the amount of prize money that a contender in fest2[i]th place gets
        //and adds up to the sum
        for(int j=0; j<NUM_2019; j++){
            if(priz2[j].first >= fest2[i]) {
                sum += priz2[j].second;
                break;
            }
        }
        //save the total amount
        total[i] = sum;

    }

    //print out the total amount of money for each case
    for(int i=0; i<T; i++){
        cout << total[i]*10000<<"\n";
    }
}
