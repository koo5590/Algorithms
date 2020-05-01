/**
 * N integers and N-1 arithmetic operators(+,-,*,/) are given.
 * While the sequence of the integers remains the same,
 * find the max and min values of expressions that can be created by permutation of the operators
 *
 * intput: number of integers
 *         a sequence of integers
 *         number of each operator (in order of +,-,*,/)
 * output: max value
 *         min value
 */
#include <iostream>

using namespace std;

int operators[10];    //array of operators
bool in[10];          //true if operators[i] has been chosen
int numbers[11];      //sequence of N integers        
int N;                //number of integers
int res_min;          //minimum value
int res_max;          //maximum value

/** 
 * find every permutation recursively
 * m: number of operators chosen 
 * value: value of the expression created so far
 */
void op_rec(int m, int value){
    //one new permutation created
    if(m==N-1){
        //check if the value is min or max
        if(value<res_min)
            res_min = value;
        if(value>res_max)
            res_max = value;
    }
    //create new permutation
    else{
        //true is corresponding operator's already chosen
        bool chosen[4];
        for(int i=0; i<4; i++)
            chosen[i] = false;

        for(int i=0; i<N-1; i++){
            //take an operator that is not in the permutation yet and is new
            if(!in[i] && !chosen[operators[i]]) {
                in[i] = true;                 //operators[i] is chosen
                chosen[operators[i]] = true;  //the same type as operators[i] has already been considered
                int temp = value;

                //calculate new value accordingly
                switch (operators[i]){
                    case op::plus:
                        temp += numbers[m+1];
                        break;
                    case op::minus:
                        temp -= numbers[m+1];
                        break;
                    case op::mult:
                        temp *= numbers[m+1];
                        break;
                    case op::divs:
                        temp /= numbers[m+1];
                        break;
                }
                //choose next operator
                op_rec(m+1, temp);
                in[i] = false;
            }
        }
    }

}

int main(){

    cin >> N;   
    for(int i=0; i<N; i++)
        cin >> numbers[i];

    int index=0;
    for(int i=0; i<4; i++) {
        int n;
        cin >> n;
        for(int j=0; j<n; j++)
            operators[index++] = i;
    }

    for(int i=0; i<N-1; i++)
        in[i] = false;
    res_min = INT32_MAX;
    res_max = INT32_MIN;
    
    op_rec(0, numbers[0]);

    cout<<res_max<<"\n"<<res_min;

}
