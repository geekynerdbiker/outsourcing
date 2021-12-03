#ifndef STACK_H
#define STACK_H

#ifndef NULL
#define NULL    0
#endif

#define MAX_SIZE 101

template<class T> class Stack
{
public:
    int top;
    int size;
    T *values;

    Stack() {
        size = MAX_SIZE;
        values = new T[size];
        top = -1;
    }
    
    ~Stack() {
        delete[] values;
    }

    void Push(T value) {
        if(!IsFull())
            values[++top] = value;
        else
            cout << "Stack is Full" << endl;
    }

    void Pop() {
        if(!Empty())
            top--;
        else
            cout << "Stack is Empty" << endl;
    }

    T Top() {
        if(!Empty())
            return values[top];
        else
            return NULL;
    }

    bool Empty() {
        if(top < 0)
            return true;
        else
            return false;
    }

    bool IsFull() {
        if(top+1 == size)
            return true;
        else
            return false;
    }
};

#endif
