#include <stdio.h>

using namespace std;

int main(){
    //input string
    char buf[1000001];
    //true if a new word was found
    bool ch;
    //true if a space was found
    bool space;
    //total number of words
    int count=0;


    //get a line from user and save it in buf
    fgets(buf, sizeof(buf), stdin);

    //count total number of words
    //each word is separated by a space
    //the input string might begin/end with some spaces
    ch = false; space = true;
    for(int i=0; buf[i]!='\n' && buf[i] != '\0'; i++){
        if(buf[i]==' ' && ch){ //buf[i] is a space and there has been a constant stream of characters
            //a new word
            count++;
            //set the flags
            ch = false;
            space = true;
        }
        else if(buf[i]!=' ' && space){ //buf[i] is the first character of new word
            ch = true; space = false;
        }
    }

    //check if the last word wasn't counted
    if(ch)
        count ++;

    //print out the total number of words
    printf("%d",count);
}
