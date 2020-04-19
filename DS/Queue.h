//
// Created by Hyunjung Kim on 2020-04-19.
//

#ifndef GRAPH_QUEUE_H
#define GRAPH_QUEUE_H

template <typename T>
class Queue{
private:
    T* data;
    int size;
    int capacity;
    int front;
    int back;

public:
    Queue();
    Queue(int n);
    ~Queue();
    void push(T element);
    T pop();
    bool isEmpty();
};


#endif //GRAPH_QUEUE_H
