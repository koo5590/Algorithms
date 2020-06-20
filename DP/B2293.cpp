#include <iostream>
using namespace std;

/**
 * coins of n different values are given.
 * find the total number of combinations of coins of value equal to k
 */

int n, k;
int value[10001];  //value[i] = number of combinations of coins of value equal to i
int coins[100];    //n different coins

int main(){
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);

    cin>>n>>k;
    for(int i=0; i<n; i++)
        cin>>coins[i];

    value[0] = 1;  //only one possible solution when k=0
    for(int i=0; i<n; i++){
        //adding coin[i] to all combinations of coins(0~i-1)
        for(int m=1; m<=k; m++){
            //find the # of combinations of coins of value equal to m
            if(m-coins[i]>=0){
                value[m] += value[m-coins[i]];
            }
        }
    }

    cout<<value[k];
}
