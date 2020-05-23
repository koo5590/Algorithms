#include <iostream>

using namespace std;

int N;                //연산 개수
int min_heap[1000001];//min heap
int size=0;           //힙 사이즈
int dir[1000000];     //연산 담을 배열

/**
 * inserts a number in min-heap
 * adjust the heap so that the array maintains the heap property
 * @param x number to insert in min-heap
 */
void insert(int x){
    size++;

    int child = size; //current node
    //heap was empty
    if(size==1){
        min_heap[1] = x;
        return;
    }

    //find a place for new number in heap
    while(child>1){
        //x is larger than the parent of current node
        if(min_heap[child/2]<x)
            break;
        //x is smaller than the parent of current node => adjust
        min_heap[child] = min_heap[child/2];
        //move to the parent node
        child /= 2;
    }
    //save new number
    min_heap[child] = x;
}

/**
 * delete the smallest number in heap and return the number
 * @return smallest number
 */
int delete_min(){
    //heap is empty
    if(size==0)
        return 0;
    //heap has only one number
    if(size==1){
        size--;
        return min_heap[1];
    }
    //smallest number
    int min_val = min_heap[1];
    //last element in heap
    int temp = min_heap[size--];
    int child=2;

    //compare temp and value of the child of current node
    while(child<=size){
        //find the min value between two children nodes
        if(child<size && min_heap[child]>min_heap[child+1]) child++;
        //value of child node is larger than temp
        if(min_heap[child]>temp)
            break;
        //value of child node is smaller than temp => adjust
        min_heap[child/2] = min_heap[child];
        //move to child node
        child *= 2;
    }
    //save temp value in the current node
    min_heap[child/2] = temp;
    
    return min_val;
}

int main(){

    cin >> N;
    for(int i=0; i<N; i++){
        cin >> dir[i];
    }

    for(int i=0; i<N; i++){
        if(dir[i]==0)
            cout<<delete_min()<<"\n";
        else
            insert(dir[i]);
    }
}
