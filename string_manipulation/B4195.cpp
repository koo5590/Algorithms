#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

const int M = 1e5+1;
const int P = 23;
int T, F;
int pow_val[M];

vector<pair<string,int>> hashT[M];  //hash table of strings and its ids
int sets[M]; //sets of strings represented as sets of ids of these strings
int counts;  //unique id given to each string that is in the hash table

/****** disjoint sets ******/

/**
 * find the root node of the set which k belongs to
 * @param k
 * @return root node of the set which k belongs to
 */
int parent(int k){
    while(sets[k]>=0)
        k = sets[k];
    return k;
}

/**
 * join two sets of x and y
 * @param x
 * @param y
 * @return the total number of elements in the joined set
 */
int join(int x, int y){
    int xp = parent(x);
    int yp = parent(y);

    //check if x and y already belong to the same set
    if(xp==yp)
        return -sets[xp];

    //set xp has more elements than set yp
    if(sets[xp]<sets[yp]){
        sets[yp] += sets[xp];
        sets[xp] = yp;
        return -sets[yp];
    }
    //set yp has more(or same amount of) elements than set xp
    else{
        sets[xp] += sets[yp];
        sets[yp] = xp;
        return -sets[xp];
    }
}

/****** disjoint sets - end ******/


/****** string hash ******/
/**
 * pre compute p^i
 */
void compute_pow(){
    pow_val[0] = 1;
    long long temp;
    for(int i=1; i<M; i++) {
        temp = (pow_val[i - 1] * P) % M;
        pow_val[i] = (int)temp;
    }
}

/**
 * compute the hash value of a string
 * @param str : a string of alphabets no longer than 20
 * @return hash value of the given string
 */
int compute_hash(const string& str){
    int hash_val = 0;

    for(int i=0; i<str.size(); i++)
        hash_val += ((str[i]-'A'+1) * pow_val[i]) % M;

    return hash_val%M;
}

/**
 * find the (unique)id of a string
 * @param str : a string of alphabets no longer than 20
 * @return if of the given string
 */
int findID(const string &str){
    //find the hash value of the string
    int hash_val = compute_hash(str);

    //find the id of the string using the hash value
    for(const auto &s:hashT[hash_val]){
        if(s.first==str) return s.second;
    }
    //if the string is not in the hash table, add it and give a new id
    hashT[hash_val].push_back({str, counts++});

    return counts-1;
}

int main(){
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    string a,b;
    int ah, bh;

    compute_pow();

    cin>>T;
    //for each test case
    while(T--){
        cin>>F;

        memset(sets, -1, sizeof(int)*M);
        while(F--){
            cin>>a>>b;
            //find ids of each string
            ah = findID(a); bh = findID(b);

            //join the two sets where string a and b belong to
            //and print out the total elements in the joined set
            cout<<join(ah,bh)<<"\n";
        }
    }

}
