#include <iostream>
#include <queue>
#include <cstring>

using namespace std;

//up:right:down:left
int dir_x[] = {-1,0,1,0};
int dir_y[] = {0,1,0,-1};

int N; //size of the painting
char picture[100][100]; //characters in the painting
bool found[100][100];   //check characters already passed by

int countA, countB;     //# of sections for non-rg colorblind / rg colorblind


/**
 * bfs through picture array and find a number of different "regions"
 * (each region contains a number of same characters that are directly adjacent)
 *
 * @param color  the color of the current region
 * @param x      starting row of the current region
 * @param y      starting col of the current region
 * @param flag   if true: colorblind, if false: non colorblind
 */
void search_color(char color, int x, int y, bool flag){
    int i,j;
    queue<pair<int,int>> path;

    path.push({x,y}); found[x][y] = true;
    while(!path.empty()){
        i=path.front().first; j=path.front().second; path.pop();

        //check each character adjacent to picture[i][j]
        for(int k=0; k<4; k++){
            //index of an adjacent character
            int ni = i+dir_x[k]; int nj = j+dir_y[k];
            //skip if out of index
            if(ni<0 || nj<0 || ni>=N || nj>=N) continue;

            //if an adjacent character is the same letter(color)
            if(picture[ni][nj]==color && !found[ni][nj]) {
                //push it on the queue
                path.push({ni, nj});
                found[ni][nj] = true;
            }
            //if the flag==true & color of the current region is red and
            //color of the adjacent character is green (and vice versa)
            else if(flag && ((color=='G' && picture[ni][nj]=='R')||
                    (color=='R' && picture[ni][nj]=='G')) && !found[ni][nj]){
                //push it on the queue
                path.push({ni, nj});
                found[ni][nj] = true;
            }
        }
    }
}

int main(){
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

    cin>>N;
    cin.ignore();
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            cin>>picture[i][j];
        }
    }

    //count number of regions to a non-rg colorblind
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            if(!found[i][j]){
                search_color(picture[i][j],i,j, false);
                countA++;
            }
        }
    }

    memset(found, false, sizeof(found));

    //count number of regions to a rg colorblind
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            if(!found[i][j]){
                search_color(picture[i][j],i,j, true);
                countB++;
            }
        }
    }
    
    cout<<countA<<" "<<countB;
}
