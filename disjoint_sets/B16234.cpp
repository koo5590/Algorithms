#include <iostream>

using namespace std;

int nations[2500];      //disjoint sets
int nations_pop[2500];  //population of each nation
int sum_pop[2500];      //total population of each union

//directions: up,left,down,right
int dir_x[] = {0,1};
int dir_y[] = {1,0};

//check if the indices are within the valid range
bool isInRange(int r, int c, int n){
    return (0 <= r && r < n && 0 <= c && c < n);
}

/**
 * find root node of the set that contains x
 * @param x index of a node
 * @return  the index of the root node
 */
int parent(int x){
    //follow the parent nodes
    while(nations[x]>=0)
        x = nations[x];
    return x;
}

/**
 * join two disjoint sets
 * @param x index of a node
 * @param y index of a node
 */
void join(int x, int y){
    //find root node of each set
    int xp = parent(x);
    int yp = parent(y);

    //if root nodes are same, they are already in the same set
    if(xp==yp) return;

    //nations[xp] has bigger population
    if(nations[xp] < nations[yp]){
        //add total # of nations in set yp to total # of nations in set xp
        nations[xp] += nations[yp];
        //set yp is attached to set xp
        nations[yp] = xp;
        //update total population of the union
        sum_pop[xp] += sum_pop[yp];
    }
    //nations[yp] has bigger population or both are the same
    else{
        //add total # of nations in set xp to total # of nations in set yp
        nations[yp] += nations[xp];
        //set xp is attached to set yp
        nations[xp] = yp;
        //update total population of the union
        sum_pop[yp] += sum_pop[xp];
    }
}

int main(){
    int N, L, R;   //N: size of space, L: lower bound, R: upper bound
    int total;     //total number of nations
    bool united;   //true if at least one union has been created
    int count = 0; //number of migration happened

    //get input data
    cin >> N;
    cin >> L;
    cin >> R;
    total = N*N;

    //initialize nations, nations_pop, sum_pop
    for(int i=0; i<total; i++) {
        cin >> nations_pop[i];
        nations[i] = -1;
        sum_pop[i] = nations_pop[i];
    }

    united = true;
    //repeat until no migration happens
    while(united) {
        united = false;
        //look through every nation and see if it forms union with its neighbor nations
        for (int k = 0; k < total; k++) {
            int i = k / N; int j = k % N;  //indices as in 2d array
            //search for neighbor nations upwards,leftwards,downwards,rightwards
            for (int l = 0; l < 2; l++) {
                //check if the indices are not out of range
                if (isInRange(i + dir_x[l], j + dir_y[l], N)) {
                    int index = (i + dir_x[l]) * N + (j + dir_y[l]);
                    //calculate the difference between population of the two nations
                    int diff = abs(nations_pop[k] - nations_pop[index]);
                    //if the difference is within the range
                    if (L <= diff && diff <= R) {
                        //join them into one union
                        join(k, index);
                        united = true;
                    }
                }
            }
        }

        //if at least one union has been formed
        if(united){
            count++;
            //update population of each nation
            for(int k=0; k<total; k++) {
                int p = parent(k);
                //(total population of the union/total # of nations in the union)
                nations_pop[k] = sum_pop[p] / (nations[p]*(-1));
            }
            //initialize sum_pop and nations for the next calculation
            for(int k=0; k<total; k++){
                sum_pop[k] = nations_pop[k];
                nations[k] = -1;
            }
        }
    }

    //print out the result
    cout << count;
}
