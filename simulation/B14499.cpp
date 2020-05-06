#include <iostream>

using namespace std;

//opposite face
#define opposite(n) (7-n)
//directions(East, West, North, South)
enum dir{E=1, W=2, N=3, S=4};
//TOP: upper surface, UP: face on the upper side of TOP, RGHT: face on the right side of TOP
int TOP, UP, RGHT;
//value of each surface
int dice[7] = {0};

//changes in the position of the dice according to the rolling direction
int dir_x[] = {0,0,0,-1,1};
int dir_y[] = {0,1,-1,0,0};

/**
 * check if the coordinates are within the range
 * @param (x,y): (row,col)
 * @param n: rows
 * @param m: cols
 * @return true if (x,y) is within the range, false if not
 */
bool isInRange(int x, int y, int n, int m){
    return (0<=x && x<n && 0<=y && y<m);
}

/**
 * roll the dice towards the direction of d
 * and change the values of TOP, UP, RGHT accordingly
 * @param d: direction to which the dice rolls
 */
void roll_dice(int d){
    int temp;
    switch(d){
        case E:  //to East
            temp = RGHT; RGHT =TOP; TOP = opposite(temp);
            break;
        case W:  //to West
            temp = RGHT; RGHT = opposite(TOP); TOP = temp;
            break;
        case N:  //to North
            temp = UP; UP = TOP; TOP = opposite(temp);
            break;
        case S:  //to South
            temp = UP; UP = opposite(TOP); TOP = temp;
        break;
        default: break;
    }
}

int main(){
    int N, M;  //number of rows(N) and columns(M) of the board
    int x, y;  //current position of the dice
    int k;     //number of rolls
    int board[20][20];
    int rolls[1000];

    ios_base::sync_with_stdio(false);

    //get input from user
    cin >> N; cin >> M;
    cin >> x; cin >> y;
    cin >> k;

    //each block of board has a value ranges from 0 to 10
    for(int i=0; i<N; i++){
        for(int j=0; j<M; j++)
            cin >> board[i][j];
    }
    //save the directions
    for(int i=0; i<k; i++)
        cin >> rolls[i];

    //upper surface is 1
    TOP = 1; UP = 2; RGHT = 3;
    //for each roll
    for(int i=0; i<k; i++) {
        int roll = rolls[i];  //get direction
        //range check
        if(!isInRange(x+dir_x[roll], y+dir_y[roll],N,M))
            continue;
        //update the current position of the dice
        x += dir_x[roll]; y += dir_y[roll];
        //update the upper surface and rest of the faces
        roll_dice(roll);

        if(!board[x][y]) //value of (x,y) is 0
            //copy the value of the bottom surface to (x,y)
            board[x][y] = dice[opposite(TOP)];
        else{   //value of (x,y) is not 0
            //copy the value to the bottom surface
            dice[opposite(TOP)] = board[x][y];
            //set the value of (x,y) to 0
            board[x][y] = 0;
        }
        //print out the value of upper surface
        cout << dice[TOP] << "\n";
    }

}
