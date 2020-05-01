#include <iostream>

using namespace std;

int main(){
    int N;      //size of the map
    int L;      //length of a ramp
    int** map;  //shows height of each space
    int count;  //number of contiguous spaces with the same height
    int path;   //number of passable paths
    bool avail; //false if not passable

    //get input
    cin >> N;
    cin >> L;
    map = new int*[N];

    //initialize map
    for(int i=0; i<N; i++){
        map[i] = new int[N];
        for(int j=0; j<N; j++)
            cin >> map[i][j];
    }
    path = 0;

    //check each row if it's passable or not
    for(int i=0; i<N; i++){
        //initialize
        count = 1; avail = true; //start comparing the second element with the first element
        //keep comparing the heights of two neighbouring spaces
        for(int j=1 ;j<N;j++){
            //if the two are of the same height
            if(map[i][j]==map[i][j-1])
                //count up
                count++;
            //if map[i][j] is higher than map[i][j-1] and there is enough space to put a ramp of length L
            else if(map[i][j]-1==map[i][j-1] && count>=L)
                //ramp can be installed, start counting new consecutive spaces with the same height
                count = 1;
            //if map[i][j] is lower than map[i][j-1]
            else if(map[i][j]+1==map[i][j-1]){
                //check if a ramp can be installed
                //count the number of consecutive spaces with the same height as map[i][j-1]
                count = 1;
                while(++j<N && map[i][j]==map[i][j-1])
                    count++;
                //can install a new ramp
                if(count>=L) {
                    //delete the number of spaces required to install the ramp
                    count -= L;
                    j--;
                }
                //cannot install a new ramp
                else {
                    //this path is not passable
                    avail = false;
                    break;
                }
            }
            //if the heights are different and cannot be adjusted by putting a ramp
            else {
                //this path is not passable
                avail = false;
                break;
            }
        }
        //count passable paths
        if(avail)
            path++;
    }

    //check each col if it's passable or not (same as above)
    for(int j=0; j<N; j++){
        count = 1; avail = true;
        for(int i=1; i<N; i++){
            if(map[i][j]==map[i-1][j])
                count++;
            else if(map[i][j]-1==map[i-1][j] && count>=L)
                count = 1;
            else if(map[i][j]+1==map[i-1][j]){
                count = 1;
                while(++i<N && map[i][j]==map[i-1][j])
                    count++;
                if(count>=L) {
                    count -= L;
                    i--;
                }
                else {
                    avail = false;
                    break;
                }
            }
            else {
                avail = false;
                break;
            }
        }
        //count passable paths
        if(avail)
            path++;
    }

    //print out the result
    cout << path;
}
