#include <iostream>
#include <queue>

/** problem 13460
 * There is a board of size N*M, which is divided into cells of size 1*1
 * The outermost cells are blocked
 * One blue ball and one red ball are placed on one cell each
 * The goal is to make the red ball fall into a hole on the board
 * The blue ball should not fall into the hole
 * You can move around the balls ONLY by tilting the board (upwards,downwards,leftwards,rightwards)
 *
 * Input:
 *  N M
 *  the graphic representation of the board
 *  ('#': blocked, '.': empty cell, '0": hole, 'R': red ball, 'B': blue ball)
 */

using namespace std;

/** enum types **/
enum cell{block, empty, hole, red, blue};
enum dir{up=0,down=1,right=2,left=3};

/** global variables **/
int** board;  //board
int N, M;     //N:height, M:width
int found;    //true if the algorithm succeeds, false if not

/** position of each ball **/
typedef struct _pos{
    int x;
    int y;
    int level;
}pos;

/**
 * calculate new position of the ball after tilting towards a certain direction
 *
 * @param cur: current positon of the ball
 * @param d: direction of the shift
 * @return new position of the ball after the shift
 */
pos roll(pos cur, int d){
    int x = cur.x;  //(x,y) on board
    int y = cur.y;
    pos new_pos;    //new position of the ball
    int k;          //loop index

    //depends on the direction of shift
    switch(d){
        //upward tilt
        case up:
            for(k=x-1; k>0; k--) {
                //the ball meets the block
                if (board[k][y] == block)
                    break;
                //the ball falls into the hole
                if (board[k][y] == hole) {
                    found = 1;
                    break;
                }
            }
            new_pos.x = k+1; new_pos.y = y; //update the coordinate
            break;

        //downward tilt
        case down:
            for(k=x+1; k<N-1; k++) {
                //the ball meets the block
                if (board[k][y] == block)
                    break;
                //the ball falls into the hole
                if (board[k][y] == hole) {
                    found = 1;
                    break;
                }
            }
            new_pos.x = k-1; new_pos.y = y;
            break;

        //leftward tilt
        case dir::left:
            for(k=y-1; k>0; k--) {
                //the ball meets the block
                if (board[x][k] == block)
                    break;
                //the ball falls into the hole
                if(board[x][k] == hole){
                    found = 1;
                    break;
                }
            }
            new_pos.x = x; new_pos.y = k+1;
            break;

        //rightward tilt
        case dir::right:
            for(k=y+1; k<M-1; k++) {
                //the ball meets the block
                if (board[x][k] == block)
                    break;
                //the ball falls into the hole
                if(board[x][k] == hole){
                    found = 1;
                    break;
                }
            }
            new_pos.x = x; new_pos.y = k-1;
            break;
    }
    return new_pos;
}


int main() {
    string buffer;
    char number[30];
    queue<pos> q;

    //current positions of the balls
    pos redpos;   //red
    pos bluepos;  //blue
    //new positions of the balls after the shift
    pos nextposR; //red
    pos nextposB; //blue

    //get size of the board from stdin
    cin >> N;  //height
    cin >> M;  //width
    cin.ignore(10000, '\n');

    //initialize board
    board = new int*[N];
    for(int i=0; i<N; i++)
        board[i] = new int[M];

    for(int i=0; i<N; i++){
        cin >> buffer;
        cin.ignore(10000, '\n');
        for(int j=0; j<M; j++){
            switch(buffer[j]){
                case '#': board[i][j] = block;
                    break;
                case '.': board[i][j] = empty;
                    break;
                case 'O': board[i][j] = hole;
                    break;
                case 'R': board[i][j] = red;
                    redpos.x = i; redpos.y = j;
                    break;
                case 'B': board[i][j] = blue;
                    bluepos.x = i; bluepos.y = j;
                    break;
            }

        }
    }
    /*for(int i=0; i<N; i++) {
        for (int j = 0; j < M; j++)
            cout<<board[i][j];
        cout<<"\n";
    }*/


    found = 0;
    redpos.level = bluepos.level = 1;
    //push the current position of the balls to the queue
    q.push(redpos);
    q.push(bluepos);
    //use BFS to find the route
    while(!q.empty() && !found){
        //pop the positions of the balls from the queue
        redpos = q.front(); q.pop();
        bluepos = q.front(); q.pop();

        //if tree is too deep
        if(redpos.level>10) break;

        //position of the red ball
        int x = redpos.x; int y = redpos.y;

        //try upwards,downwards,leftwards,rightwards
        for(int i=0; i<4; i++){
            //find the new position of the blue ball
            nextposB = roll(bluepos, i);


            //check if blue ball falls into the hole
            if(found) {
                found = 0;
                continue; //ignore and check other cases
            }

            //find the new position of the red ball
            nextposR = roll(redpos, i);
            //red ball falls into the hole

            if(found)
                break;

            //if the ball doesn't move
            if((redpos.x==nextposR.x && redpos.y==nextposR.y) &&
               (bluepos.x==nextposB.x && bluepos.y==nextposB.y)){
                continue;
            }

            //two balls on the same row or col
            if(nextposB.x==nextposR.x && nextposB.y==nextposR.y){
                switch(i){
                    //upwards
                    case 0:
                        if(bluepos.x > redpos.x) //blue ball below the red ball
                            nextposB.x += 1;
                        else                     //red ball below the blue ball
                            nextposR.x += 1;
                        break;
                    //downwards
                    case 1:
                        if(bluepos.x > redpos.x) //blue ball below the red ball
                            nextposR.x -= 1;
                        else                     //red ball below the blue ball
                            nextposB.x -= 1;
                        break;
                    //rightwards
                    case 2:
                        if(bluepos.y > redpos.y) //blue ball on the right to the red ball
                            nextposR.y -= 1;
                        else
                            nextposB.y -= 1;      //red ball on the right to the blue ball
                        break;
                    //leftwards
                    case 3:
                        if(bluepos.y > redpos.y) //blue ball on the right to the red ball
                            nextposB.y += 1;
                        else                     //red ball on the right to the blue ball
                            nextposR.y += 1;
                        break;
                }
            }

            //add new position to the queue
            nextposB.level = nextposR.level = redpos.level+1;
            q.push(nextposR); q.push(nextposB);
        }
    }

    if(!found) std::cout<<-1;
    else std::cout<<redpos.level;

}