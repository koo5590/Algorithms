#include <iostream>

using namespace std;

int main(){
    int N;
    int num;
    int count;

    cin >> N;

    count = 0;
    for(num=1;;num++){
        int temp = num; int six = 0;
        while(temp){
            int digit = temp%10;
            if(digit==6) six++;
            else if(six<3) six = 0;
            
            if(six==3) break;
            temp /= 10;
        }
        if(six==3) count++;
        if(count==N) break;
    }

    cout << num;
}
