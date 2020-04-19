//
// Created by Hyunjung Kim on 2020-04-19.
//

#include "Stack.h"
#include <iostream>

/** constructor **/
template<typename T>
Stack<T>::Stack(){
    size = 0;
    top = -1;
    capacity = 8;
    data = new T[8];
}
template <typename T>
Stack<T>::Stack(int n){
    size = 0;
    top = -1;
    capacity = n;
    data = new T[n];
}
/** destructor **/
template<typename T>
Stack<T>::~Stack(){
    delete data;
}

/** getters **/
template<typename T>
int Stack<T>::getSize(){
    return size;
}
template<typename T>
int Stack<T>::getCapacity(){
    return capacity;
}

/** push **/
template<typename T>
void Stack<T>::push(T element){
    if(size==capacity){
        capacity*=2;
        T* temp = new T[size];
        for(int i=0; i<size; i++)
            temp[i] = data[i];
        delete[] data;
        data = new T[capacity];
        for(int i=0; i<size; i++)
            data[i] = temp[i];
        delete[] temp;
    }
    size++;
    data[++top] = element;
}

/** pop **/
template<typename T>
T Stack<T>::pop(){
    if(top==-1)
        return (T)NULL;
    size--;
    return data[top--];
}

template<typename T>
bool Stack<T>::isEmpty(){
    if(size==0) return true;
    return false;
}
