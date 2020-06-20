#include <iostream>

using namespace std;

/** find the longest bitonic subsequence **/

int N;
int nums[1000];
int inc_seq[1000];
int dec_seq[1000];

int main(){
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);

    cin>>N;
    for(int i=0; i<N; i++)
        cin>>nums[i];

    for(int m=0; m<N; m++){
        //find the longest increasing subsequence from nums[0]~nums[m]
        inc_seq[m] = 1;
        for(int i=0; i<m; i++){
            if(nums[i]<nums[m])
                inc_seq[m] = max(inc_seq[m], inc_seq[i]+1);
        }

        //find the longest decreasing subsequence from nums[m]~nums[N-1]
        dec_seq[N-m-1] = 1;
        for(int i=N-1; i>N-m-1; i--){
            if(nums[i]<nums[N-m-1])
                dec_seq[N-m-1] = max(dec_seq[N-m-1], dec_seq[i]+1);
        }
    }

    //find the longest bitonic subsequence 
    int ans = inc_seq[0] + dec_seq[0] - 1;
    for(int i=1; i<N; i++)
        ans = max(ans, inc_seq[i]+dec_seq[i]-1);

    cout<<ans;
}
