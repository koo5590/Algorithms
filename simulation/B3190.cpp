#include <iostream>
#include <deque>
#include <queue>

using namespace std;

//changing directions
#define turn_left(n) (n=(n+3)%4)
#define turn_right(n) (n=(n+5)%4)

typedef pair<int,int> pos;     //positions of the snake
typedef pair<int,char> path;   //<sec, direction>: tells when the snake changes its direction

//game board
int board[100][100];
//N: size of the board  K: number of apples
int N, K;
//save positions where the snake's body is located
deque<pos> snake;
//current direction the snake is heading to
int dir;
//tells when the snake changes its direction
queue<path> moves;
//time it takes the game to finish
int total_t;

int main(){
    int i,j,turns;
    char c;
    bool crash;

    //get input from user
    cin >> N;
    cin >> K;

    //locate apples on the board
    for(int k=0; k<K; k++){
        cin >> i; cin >> j;
        board[i-1][j-1] = 2;
    }

    //direction changes
    cin >> turns;
    for(i=0; i<turns; i++){
        cin >> j; cin >> c;
        path temp = {j,c};
        moves.push(temp);
    }


    //snake starts moving at the upper-left corner
    pos temp = {0,0};
    snake.push_back(temp);

    total_t = 0;
    dir = 1;       //snake is heading toward the right
    crash = false;
    //repeat until the snake does not bump into itself or the wall
    while(!crash){
        //check if it's time for the snake to make a turn
        if(moves.front().first == total_t++){
            c = moves.front().second; moves.pop(); //remove the element from the queue
            if(c=='L') turn_left(dir);  //turn left
            else  turn_right(dir);      //turn right
        }

        //get the current position of the head
        pos head = snake[0];
        //move one block forward
        switch(dir){
            case 0: head.first--; break;   //upwards
            case 1: head.second++; break;  //rightwards
            case 2: head.first++; break;   //downwards
            case 3: head.second--; break;  //leftwards
            default: break;
        }
        //check if the snake hits the wall
        if(!(0<=head.first && head.first<N) || !(0<=head.second && head.second<N))
            break;
        //check itf the head hits its body
        for(auto it=snake.begin()+1; it!=snake.end(); ++it){
            if(head.first==it->first && head.second==it->second) {
                crash = true;
                break;
            }
        }
        //add new position of the head to the deque
        snake.push_front(head);

        //if there is an apple, the size increases
        if(board[head.first][head.second]==2)
            board[head.first][head.second] = 0;
        //if there is no apple, the tail also moves one block forward
        else
            snake.pop_back();
    }
    //print out the total time
    cout << total_t;
}
