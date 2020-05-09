#include<iostream>
#include <string>

using namespace std;
string alpha[] = {"c=", "c-", "dz=", "d-", "lj", "nj", "s=","z="};

int main(){
    ios_base::sync_with_stdio(false);
    string word;

    cin >> word;
    //replace all strings from alpha array with "?" in word
    for(int i=0; i<8; i++){
        int index = word.find(alpha[i]);
        //repeat replacement until alpha[i] string appears no more
        while(0<=index && index<word.length()){
            //replace alpha[i] with "?"
            word.replace(index, alpha[i].length(), "?");
            index = word.find(alpha[i]);
        }
    }
    //print out the length of the word
    cout << word.length();
}
