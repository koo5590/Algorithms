#include <iostream>
#include <queue>

using namespace std;

//up,left,right,down
int dir_x[] = {-1,0,0,1};
int dir_y[] = {0,-1,1,0};

//position
typedef struct pos{
    int x;     //row
    int y;     //column
    int depth; //depth in the bfs tree
}pos;

//baby shark
class baby_shark{
private:
    int r, c; //current position of the shark
    int size; //size of the shark
    int exp;  //size-exp: the amount of fish the shark needs to get bigger

public:
    int sec;  //the amount of time the shark moved (in seconds)

    /**
     * initialize the state of the shark
     * @param x: row
     * @param y: col
     */
    void initialize(int x, int y){
        r=x; c=y;
        size = 2;
        exp = sec = 0;
    }

    /**
     * find a fish that can be eaten by the shark
     * @param space: 2d int array, tells where fish are
     * @param n: size of the space (n*n)
     * @return true if fish is found, false if no fish is found
     */
    bool find_fish(int** space, int n){
        queue<pos> q;
        pos cur, next;
        bool** found; //true if (i,j) is already accessed
        int x,y;

        //initialize the array 'found'
        found = new bool* [n];
        for(int i=0; i<n; i++){
            found[i] = new bool[n];
            for(int j=0; j<n; j++)
                found[i][j] = false;
        }

        //start from the current location of the shark
        cur.x = r; cur.y = c; cur.depth = 0;
        q.push(cur);
        while(!q.empty()){
            cur = q.front(); q.pop();

            //look for any fish in the adjacent blocks(up->left->right->down)
            for(int i=0; i<4; i++){
                //row and column values of the adjacent blocks
                x = cur.x+dir_x[i]; y = cur.y+dir_y[i];
                //check if the shark can pass by this block
                if(0<=x && x<n && 0<=y && y<n && !found[x][y] && space[x][y]<=size){
                    //the shark can pass by this block, push the block to the queue
                    found[x][y] = true;
                    next.depth = cur.depth+1;
                    next.x = x; next.y = y;
                    q.push(next);

                    //check if there is a fish that is smaller than the shark in this block
                    if(0<space[x][y] && space[x][y]<size){
                        //check if there is any other fish that is within the same distance
                        while(!q.empty() && q.front().depth == cur.depth){
                            pos temp = q.front(); q.pop();
                            //search in the adjacent blocks(up->left->right->down)
                            for(int j=0; j<4; j++){
                                x = temp.x+dir_x[j]; y = temp.y+dir_y[j];
                                //check if there is a fish that is smaller than the shark
                                if(0<=x && x<n && 0<=y && y<n && 0<space[x][y] && space[x][y]<size){
                                    //compare (row,col) values of the fish
                                    if((x==next.x && y<next.y) || x<next.x){
                                        next.x = x; next.y = y; next.depth = cur.depth+1;
                                    }
                                }
                            }
                        }
                        //The shark eats the fish
                        space[next.x][next.y] = 0;
                        //The shark is now moved to the new location
                        r = next.x; c = next.y;
                        //did the shark get bigger?
                        if(++exp==size){
                            exp = 0; size++;
                        }
                        //the shark moved (next.depth) seconds to eat the fish
                        sec +=next.depth;
                        return true;
                    }
                }
            }
        }
        //no fish available
        return false;
    }
};

/**
 * main function
 */
int main(){
    baby_shark babyShark;
    int** space; //gives info of the space where the fish and the shark are
    int n;       //size of the space (n*n)
    int fish;    //total number of fish

    //get the size of the space from user input
    cin>>n;
    space = new int*[n];
    fish = 0;

    //get info of the space
    for(int i=0; i<n; i++){
        space[i] = new int[n];
        for(int j=0; j<n; j++){
            cin >> space[i][j];
            //shark
            if(space[i][j]==9){
                //initialize the state of the shark
                babyShark.initialize(i,j);
                space[i][j] = 0;
            }
            //fish
            else if(space[i][j]>0)
                fish++;
        }
    }

    //search until there is no fish left that the shark can eat
    for(int i=0; i<fish; i++){
        if(!babyShark.find_fish(space, n))
            break;
    }
    //print out the result
    cout << babyShark.sec;
}
