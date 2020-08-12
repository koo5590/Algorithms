#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>
#include <cmath>

using namespace std;

class Element{
public:
    bool isVal;
    int val = 0;
    char bracket = '-';

    Element(int v) {
        isVal = true;
        val = v;
    }
    Element(char b){
        isVal = false;
        bracket = b;
    }
};


int main(){
    ios_base::sync_with_stdio(false); cin.tie(0);

    string str;
    cin>>str;
    stack<Element> stk;
    int ans = 0;

    for(auto c:str){
        if(c=='(' || c=='[')
            stk.push(c);
        else if(c==')'){
            int sum = 0;
            //현재 괄호 안에 포함되어있는 값을 전부 더함
            while(!stk.empty() && stk.top().isVal){
                sum += stk.top().val;
                stk.pop();
            }
            //올바르지 못한 괄호가 있는 경우
            if(stk.empty() || stk.top().bracket!='('){
                break;
            }
            stk.pop();
            if(!sum) sum = 1; //괄호 안에 아무것도 없는 경우
            stk.push(Element(sum*2));
        }
        else if(c==']'){
            int sum = 0;
            while(!stk.empty() && stk.top().isVal){
                sum += stk.top().val;
                stk.pop();
            }
            if(stk.empty() || stk.top().bracket!='['){
                break;
            }
            stk.pop();
            if(!sum) sum = 1;
            stk.push(Element(sum*3));
        }
    }

    //최종 결과 합산
    while(!stk.empty()){
        if(!stk.top().isVal){ //올바르지 못한 괄호가 있는 경우
            ans = 0;
            break;
        }
        ans += stk.top().val; stk.pop();
    }

    cout<<ans;
}
