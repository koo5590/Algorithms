#include <iostream>
using namespace std;

/**
 * find a total number of 'group' words among N words given
 * in 'group' word, same letters appear only consecutively(in a group)
 * ex) 'aabb' is a group word while 'aaba' is not a group word
 * with given N words, find the total number of group words
 */

int main(){
    //number of words
    int N;
    //array of N words
    string word[101];
    //alphabets a~z
    bool alpha[26];
    //number of 'group word'
    int count = 0;

    //input from user: N
    cin >> N;
    //save N words
    for(int i=0; i<N; i++)
        cin >> word[i];

    //find total number of group words
    for(int i=0; i<N; i++){
        int j;
        //alpha[j] is true when this letter already appeared in the word
        for(j=0; j<26; j++)
            alpha[j] = false;
        //check each character in the word
        for(j=0; j<word[i].length(); j++){
            //if jth character already appeared in this word and
            //it is different from j-1th character, this is not a group word
            if(alpha[word[i][j]-'a'] && word[i][j-1]!=word[i][j])
                break;
            //check jth character
            alpha[word[i][j]-'a'] = true;
        }
        //if j reached the end, word[i] is a group word
        if(j==word[i].length())
            count++;
    }
    //print out the result
    cout << count;

}
