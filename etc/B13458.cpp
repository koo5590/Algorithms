#include <iostream>

using namespace std;

int main(){
    int N;
    int cases[1000000];
    int B, C;
    int min;
    long long total;

    ios_base::sync_with_stdio(false);

    cin >> N;
    for(int i=0; i<N; i++)
        cin >> cases[i];

    cin>>B; cin>>C;
    total = 0;

    for(int i=0; i<N; i++){
        if(cases[i]-B>0) {
            min = (cases[i] - B) / C +1;
            if ((cases[i] - B) % C) min++;
        }
        else min = 1;

        total += min;
    }

    cout << total;
}
