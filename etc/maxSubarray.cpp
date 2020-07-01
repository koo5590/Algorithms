#include <iostream>
using namespace std;

/**
 * find the maximum subarray of an array of n integers
 */

int nums[100000];
int n;

int main(){
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);

    cin>>n;
    for(int i=0; i<n; i++)
        cin>>nums[i];

    long long max_sum; //max subarray sum
    long long sum;     //current subarray sum

    bool neg = true;
    max_sum = nums[0];
    //check if all integers int the array are negative or not
    for(int i=0; i<n; i++){
        if(nums[i]>=0) { //positive int found
            neg = false;
            break;
        }
        //find the largest negative int
        if(max_sum<nums[i]) max_sum = nums[i];
    }

    //if not all int are negative
    if(!neg) {
        sum = 0; max_sum = 0;
        for (int i = 0; i < n; i++) {
            if (sum < 0) //if the sum is negative, start again from i
                sum = 0;
            sum += nums[i];

            //find the largest sum
            if (max_sum < sum) max_sum = sum;
        }
    }

    cout<<max_sum;
}
