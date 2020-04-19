//
// Created by Hyunjung Kim on 2020-04-19.
//

#ifndef GRAPH_STACK_H
#define GRAPH_STACK_H

template<typename T> class Stack {
private:
    T* data;
    int top;
    int size;
    int capacity;

public:
    Stack();
    Stack(int n);
    ~Stack();
    int getSize();
    int getCapacity();
    void push(T element);
    T pop();
    bool isEmpty();
};


#endif //GRAPH_STACK_H
