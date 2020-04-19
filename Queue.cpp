//
// Created by Hyunjung Kim on 2020-04-19.
//

#include "Queue.h"
#include <iostream>

/** constructor **/
template <typename T>
Queue<T>::Queue():Queue(8){

}

template <typename T>
Queue<T>::Queue(int n){
    size = 0;
    capacity = n;
    data = new T[n];
    front = 0;
    back = 0;
}

/** destructor **/
template <typename T>
Queue<T>::~Queue(){
    delete[] data;
}

template <typename T>
bool Queue<T>::isEmpty(){
    return size==0;
}

/** push **/
template <typename T>
void Queue<T>::push(T element){
    if(size==capacity){
        capacity *= 2;
        int j = 0;
        T temp[size];
        for(int i=front; i<size; i++)
            temp[j++] = data[i];
        for(int i=0; i<front; i++)
            temp[j++] = data[i];
        delete[] data;
        data = new T[capacity];
        for(int i=0; i<size; i++)
            data[i] = temp[i];
        front = 0; back = size;
    }
    data[back] = element;
    back = (back+1)%capacity;
    size++;
}

/** pop **/
template <typename T>
T Queue<T>::pop(){
    if(size==0) return (T)NULL;
    T temp = data[front];
    front = (front+1)%capacity;
    size--;

    return temp;
}