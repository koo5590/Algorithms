/**
 * There is a board of size N*M,
 * with each 1*1 sized square colored either in black(B) or white(W).
 * We are trying to cut a 8*8 sized part out of it to make a chessboard.
 * Find the minimum number of squares to recolor to make a chessboard.
 */

#include <iostream>
using namespace std;

char board[50][50];
int min_col;  //minimum number of squares to recolor
int N, M;     //N:# of rows  M:# of columns

int main(){
    int count;  //number of squares to recolor for each case

    //get input
    cin >> N >> M;
    for(int i=0; i<N; i++){
        for(int j=0; j<M; j++)
            cin >> board[i][j];
    }

    min_col = 64;  //set maximum value
    //choose a starting point (i,j)
    for(int i=0; i+8<=N; i++){
        for(int j=0; j+8<=M; j++){
            count = 0;
            //chessboard made with squares from (i~i+7),(j~j+7)
            for(int k=i; k<i+8; k++){
                for(int l=j; l<j+8; l++){
                    //assume chessboard starts with B
                    if(k%2==0){  //this row starts with B
                        if((l%2==0 && board[k][l]!='B') || (l%2 && board[k][l]!='W'))
                            count++;
                    }
                    else{        //this row starts with W
                        if((l%2==0 && board[k][l]!='W') || (l%2 && board[k][l]!='B'))
                            count++;
                    }
                }
            }
            if(count > 64-count)  //does the other way need less squares to be recolored?
                count = 64-count;
            if(count < min_col)   //find the minimum number of squares
                min_col = count;
        }
    }

    //print out the result
    cout << min_col;

}
