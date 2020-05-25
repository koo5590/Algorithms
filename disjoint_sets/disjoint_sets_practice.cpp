#include <iostream>

using namespace std;

int n, m;
//disjoint_set[a] is index of the parent node of a
//if a is a root node, disjoint_set[a] is -(number of nodes in the set)
int disjoint_set[1000001];

/**
 * find the root node of set where x belongs
 * @param x
 * @return the root node of set where x belongs
 */
int parent(int x){
    //track parent node until root node
    while(disjoint_set[x]>0)
        x = disjoint_set[x];
    //return index of root node
    return x;
}

/**
 * join two sets where a and b belong
 * @param a
 * @param b
 */
void join(int a, int b){
    //find the root index of each set
    int pa = parent(a);
    int pb = parent(b);

    //the two already exist in the same set
    if(pa==pb) return;

    //pa has more nodes
    if(disjoint_set[pa]<disjoint_set[pb]){
        //add # of nodes of pb to pa
        disjoint_set[pa] += disjoint_set[pb];
        //the parent node of pb is pa
        disjoint_set[pb] = pa;
    }
    //pb has more nodes or the two have the same number of nodes
    else{
        //add # of nodes of pa to pb
        disjoint_set[pb] += disjoint_set[pa];
        //the parent node of pa is pb
        disjoint_set[pa] = pb;
    }
}

/**
 * if a and b belong to the same set, return true
 * if not, return false
 * @param a
 * @param b
 */
bool same_set(int a, int b){
    return (parent(a)==parent(b));
}

/**
 * main
 */
int main(){
    ios_base::sync_with_stdio(false); cin.tie(0);
    int op; int a, b;

    cin >> n >> m;

    //each node is itself a set
    for(int i=1; i<=n; i++){
        disjoint_set[i] = -1;
    }

    for(int i=0; i<m; i++){
        cin >> op >> a >> b;
        //join two sets of a and b
        if(op==0)
            join(a,b);
        else{
            //a and b belong to the same set
            if(same_set(a,b))
                cout<<"YES\n";
            //a and b does not belong to the same set
            else
                cout<<"NO\n";
        }
    }


}
