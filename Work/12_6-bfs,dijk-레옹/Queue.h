#ifndef QUEUE_H
#define QUEUE_H

#ifndef NULL
#define NULL    0
#endif

#define MAX_SIZE 101

template<class T> class Queue
{
public:
    int front;
    int rear;
    int size; //Free to define (recommand 100 or 200)
    T *values;

    Queue() {
        values = new T[size];
        //Needs extra init
        size = MAX_SIZE;
        front = 0;
        rear = 0;
        
    }
    
    ~Queue() {
        delete[] values;
    }
    
    void Push(T value) {
        //Input data
        if(!IsFull()) {
            values[rear] = value;
            rear = (rear + 1) % size;
        } else
            cout << "Queue is Full" << endl;
    }

    void Pop() {
        //Change front
        if(!Empty()) front = (front + 1) % size;
        else cout << "Queue is Empty" << endl;
    }

    bool Empty() {
        //Check its empty or not
        if(rear == front) return true;
        else return false;
    }

    bool IsFull() {
        //Check queue is full or not
        if((rear + 1) % size == front) return true;
        else return false;
    }
};


#endif
