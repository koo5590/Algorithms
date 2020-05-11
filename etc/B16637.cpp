#include <iostream>
#include <deque>
#include <climits>
using namespace std;

deque<int> nums;    //numbers in final expression
deque<char> ops;    //operators in final expression
int num[10];        //input numbers
char operators[9];  //input operators
bool in[9];         //true: parenthesized  false: X
int len;            //length of expression
int eval_max;       //maximum value of given expression

/**
 * evaluate the final expression
 * with numbers in nums and operators in ops
 * in the given order
 *
 * @return value of the expression
 */
int cal_expr(){
    //initialize the first operand
    int accum = nums.front(); nums.pop_front();
    while(!nums.empty() && !ops.empty()){
        //get the second operand
        int n = nums.front(); nums.pop_front();
        //get operator and calculate the value
        switch(ops.front()){
            case '+':
                accum += n;
                break;
            case '-':
                accum -= n;
                break;
            case '*':
                accum *= n;
                break;
        }
        ops.pop_front();
    }
    //return the value
    return accum;
}

/**
 * find all subsets of operators
 * operators that are in the subset are the ones with parentheses
 *
 * @param index: index of an element currently being considered
 */
void build_expr(int index){
    int op_num = len/2; //number of operators

    //a subset completed
    if(index==op_num){
        //push first number on nums
        nums.push_back(num[0]);
        for(int i=0; i<op_num; i++){
            //expression is parenthesized
            if(in[i]){
                //delete the first operand from nums
                nums.pop_back();
                //evaluate: num[i] operators[i] num[i+1]
                //and push the value on nums
                switch(operators[i]){
                    case '+':
                        nums.push_back(num[i]+num[i+1]);
                        break;
                    case '-':
                        nums.push_back(num[i]-num[i+1]);
                        break;
                    case '*':
                        nums.push_back(num[i]*num[i+1]);
                        break;
                }
            }
            //expression is not parenthesized
            else {
                //push the operator on ops
                ops.push_back(operators[i]);
                //push the first second operand on nums
                nums.push_back(num[i+1]);
            }
        }
        //evaluate the final expression
        int res = cal_expr();
        //find the maximum value
        if(res>eval_max) eval_max = res;
    }

    //include or not include operators[index]
    else{
        //if operator[index-1] gets parenthesized,
        //operator[index] cannot be parenthesized
        in[index] = !(index>0&&in[index-1]);
        //subset with operator[index]
        build_expr(index+1);
        if(in[index]) {
            in[index]= false;
            //subset without operator[index]
            build_expr(index + 1);
        }

    }

}

/**
 * A string of expression is given with the length of N.
 * Any sub-expression(operand operator operand) can be parenthesized.
 * EX) 4+5*6+7-8  =>  (4+5)*6+(7-8)
 * computation is done => (1)parenthesized expressions first (2)from left to right
 * find the maximum possible value of the expression
 */
int main(){
    char buffer[20];
    bool same = true;

    //get input
    cin >> len;
    cin >> buffer;
    for(int i=0; i<len; i++){
        //save numbers in num array
        if(i%2==0)
            num[i/2] = buffer[i]-48;
        //save operators in operators array
        else
            operators[i/2] = buffer[i];
    }

    //check if all operators are the same
    for(int i=1; i<len/2; i++){
        if(operators[i]!=operators[i-1]){
            same = false;
            break;
        }
    }

    //if all the operators are the same and it is either '*' or '+
    if(same && (operators[0]=='+' || operators[0]=='*')){
        //repeat each computation
        eval_max = num[0];
        switch (operators[0]) {
            case '+':
                for(int i=1; i<len/2+1; i++)
                    eval_max += num[i];
                break;
            case '*':
                for(int i=1; i<len/2+1; i++)
                    eval_max *= num[i];
                break;
        }
    }
    //find the maximum value of the expression
    else {
        eval_max = INT_MIN;
        build_expr(0);
    }
    //print out the result
    cout << eval_max;
}
