#include <iostream>

using namespace std;

typedef struct _pos{
    int value;
    int modified;
}pos;

int R, C, T;      //R: row, C: column, T: T times
int air_x, air_y; //coordinates of air cleaner
pos** board;


int main(){
    int n;

    //get input from user
    cin >> R;
    cin >> C;
    cin >> T;

    board = new pos*[R];
    for(int i=0; i<R; i++)
        board[i] = new pos[C];

    //initialize values
    for(int i=0; i<R; i++){
        for(int j=0; j<C; j++){
            cin >> n;
            board[i][j].value = n;
            board[i][j].modified = 0;

            //location of air cleaner
            if(n==-1){
                air_x = i; air_y = j;
            }
        }
    }


    for(int t=0; t<T; t++) {
        for (int i = 0; i < R; i++) {
            for (int j = 0; j < C; j++) {
                //calculate the amount diffused
                int diffuse = board[i][j].value / 5;
                int count = 0;

                //flow of dust from current block to adjacent blocks
                //upwards
                if (i - 1 >= 0 && board[i - 1][j].value != -1) {
                    board[i - 1][j].modified += diffuse;
                    count++;
                }
                //leftwards
                if(j-1 >= 0 && board[i][j-1].value != -1) {
                    board[i][j-1].modified += diffuse;
                    count++;
                }
                //downwards
                if(i+1<R && board[i+1][j].value != -1 ){
                    board[i+1][j].modified += diffuse;
                    count++;
                }
                //rightwards
                if(j+1<C && board[i][j+1].value != -1){
                    board[i][j+1].modified += diffuse;
                    count++;
                }
                //calculate total amount of in&out
                board[i][j].modified -= count*diffuse;
            }
        }

        //calculate new amount
        for(int i=0; i<R; i++){
            for(int j=0; j<C; j++){
                board[i][j].value += board[i][j].modified;
                board[i][j].modified = 0;
            }
        }

        //flow of air (upper)
        //downwards
        for(int k=air_x-2; k>0; k--)
            board[k][0] = board[k-1][0];
        //rightwards
        for(int k=1; k<C; k++)
            board[0][k-1] = board[0][k];
        //upwards
        for(int k=1; k<=air_x-1; k++)
            board[k-1][C-1] = board[k][C-1];
        //leftwards
        for(int k=C-2; k>=1; k--)
            board[air_x-1][k+1] = board[air_x-1][k];
        board[air_x-1][1].value = 0;

        //flow of air (lower)
        //upwards
        for(int k=air_x+1; k<R-1; k++)
            board[k][0] = board[k+1][0];
        //leftwards
        for(int k=1; k<C; k++)
            board[R-1][k-1] = board[R-1][k];
        //downwards
        for(int k=R-1; k>air_x; k--)
            board[k][C-1] = board[k-1][C-1];
        //rightwards
        for(int k=C-1; k>1; k--)
            board[air_x][k] = board[air_x][k-1];
        board[air_x][1].value = 0;
    }

    //calculate the final value
    int total = 0;
    for(int i=0; i<R; i++){
        for(int j=0; j<C; j++){
            if(board[i][j].value != -1)
                total += board[i][j].value;
        }
    }
    //print out answer
    cout<<total;
}
