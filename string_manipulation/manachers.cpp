/**
 * find the total number of palindromic substrings of a given string s,
 * using Manacher's algorithm
 */

class Solution {
public:
    int countSubstrings(string s) {
        int count = 0;  //# of palindromic substrings in s
        int mod_len = 2*s.size()+1; 
        int* P = new int[mod_len]();        //longest expanded substring length
        char* modified = new char[mod_len]; //augmented string of s
        
        int i=0;
        //create an array of characters which have '#' in between every char of s
        //such that every palindromic substring has an odd length
        for(auto c: s){
            modified[i++] = '#';
            modified[i++] = c;
        }
        modified[i] = '#';
        
        //the furthest expanded palindromic substring
        int center=0; int right=0;
        
        for(int i=1; i<mod_len-1; i++){
            if(i<right) 
                P[i] = min(P[2*center-i], right-i); //right-i: in case P[i'] expands beyond left end of palindrom centered at "center"
            
            //expand palindrom from i
            int l, r;
            l=i-P[i]-1; r=i+P[i]+1;
            while(l>=0 && r<mod_len && modified[l]==modified[r]){
                l--; r++;
                P[i]++;
            }
            
            //check if the new palindrom extends further than the current one centered at "center"
            if(i+P[i]>right){
                center = i;
                right = i+P[i];
            }
        }
        
        //calculate the total number of palindromic substrings
        for(int i=1; i<mod_len-1; i++){
            count += (P[i]+1)/2;
        }
        
        return count;
    }
};
