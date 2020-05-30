#include <iostream>
#include <set>
#include <stack>

using namespace std;

string input;      //입력
string code;       //코드
string cases[61];  //테스트 케이스
unsigned char memory[100000]; //unsigned 8bit 정수 배열

int pointer;     //배열 포인터
int inp_pointer; //입력 버퍼 포인터

int code_size;   //코드 크기
int input_size;  //입력 크기
int mem_size;    //메모리 크기

int N;           //테스트 케이스 개수

int loop_start, loop_end;  //루프 괄호 인덱스
bool infinite_loop;        //무한 루프이면 true
int loop[4096];            //루프 시작,끝 인덱스

/**
 * 배열을 초기화 해줌
 */
void mem_reset(){
    for(int i=0; i<mem_size; i++)
        memory[i] = 0;
    pointer = 0;
}

/**
 * 코드 안의 루프를 짝지어줌
 * loop 배열에 서로 대응되는 [ 혹은 ]의 인덱스 저장
 */
void find_loop(){
    stack<int> rb;

    for(int i=0; i<code_size; i++){
        //루프의 시작 -> 스택에 쌓음
        if(code[i]=='[')
            rb.push(i);
        //루프의 끝 -> 스택에서 가장 최근의 [의 인덱스를 꺼냄
        else if(code[i]==']'){
            //서로 대응되는 괄호의 인덱스 저장
            loop[rb.top()] = i;
            loop[i] = rb.top();
            rb.pop();
        }
    }
}

/**
 * 코드 실행
 */
void execute(){
    char x;
    int exe_count = 0;  //명령 실행 횟수
    set<int> infinite;  //무한 루프 내에 있는 루프 시작의 인덱스 저장

    //루프의 시작과 끝의 위치 저장
    find_loop();

    //코드 실행
    for(int i=0; i<code_size; i++){
        //명령어 하나씩 읽어서 처리
        x = code[i];
        switch(x){
            //pointer가 가리키는 수 1 감소
            case '-':
                memory[pointer]--;
                break;
            //pointer가 가리키는 수 1 증가
            case '+':
                memory[pointer]++;
                break;
            //pointer를 왼쪽으로 한 칸 이동
            case '<':
                pointer--;
                if(pointer<0) pointer = mem_size-1;
                break;
            //pointer를 오른쪽으로 한 칸 이동
            case '>':
                pointer = (pointer+1)%mem_size;
                break;
            //루프의 시작
            case '[':
                //루프 끝으로 건너뜀
                if(memory[pointer]==0)
                    i = loop[i]-1;
                break;
            //루프의 끝
            case ']':
                //무한 루프 진행 중
                if(infinite_loop) {
                    infinite.insert(i);
                }
                //루프 반복
                if(memory[pointer]!=0)
                    i = loop[i]-1;
                break;
            //출력
            case '.':
                //cout<<memory[pointer];
                break;
            //버퍼에서 입력 읽어들임
            case ',':
                //입력의 끝
                if(inp_pointer == input_size)
                    memory[pointer] = 255;
                else
                    memory[pointer] = input[inp_pointer++];
                break;
            default:
                break;
        }
        //실행 횟수 증가
        exe_count++;

        //무한 루프 반복 중
        if(exe_count>50000000 && infinite_loop){
            loop_end = 0;
            //가장 바깥의 루프 찾음
            for(auto l:infinite){
                if(l>loop_end)
                    loop_end = l;
            }
            //무한 루프 시작 인덱스 찾음
            loop_start = loop[loop_end];

            return;
        }

        //무한 루프 발견
        else if(exe_count>50000000) {
            infinite_loop = true;
            exe_count = 0;
        }
    }
    //프로그램 종료
}

int main() {

    cin >> N;
    cin.ignore();
    //N개의 테스트 케이스 한 줄씩 읽어서 저장
    for(int i=0; i<N*3; i++)
        getline(cin, cases[i]);
    //각 테스트 케이스 처리
    for(int i=0; i<N*3; i++){
        //메모리 리셋
        mem_reset();
        //초기화
        inp_pointer = 0;
        infinite_loop = false;

        //메모리 크기, 코드 길이, 입력 길이
        sscanf(cases[i].c_str(), "%d %d %d", &mem_size, &code_size, &input_size);
        code = cases[i + 1];
        input = cases[i + 2];
        i+=2;

        //코드 실행
        execute();
        //무한 루프 발견시
        if(infinite_loop)
            cout<<"Loops "<<loop_start<<" "<<loop_end<<"\n";
        //프로그램 정상적으로 종료 
        else
            cout<<"Terminates\n";
    }

}
