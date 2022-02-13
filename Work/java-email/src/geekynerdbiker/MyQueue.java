package geekynerdbiker;

public class MyQueue {
    int len;
    int size;
    int front;
    int rear;
    double[] queue;

    public MyQueue(int size) {
        len = 0;
        front = rear = 0;
        queue = new double[size];
    }

    public boolean isEmpty() {
        return front == rear;
    }

    public boolean isFull() {
        return rear == size - 1;
    }

    public int size() {
        return rear - front;
    }

    public void push(double value) {
        if (isFull()) {
            return;
        }
        queue[rear++] = value;
        this.len++;
    }

    public double pop() {
        if (isEmpty()) {
            return -1;
        }
        this.len--;
        return queue[front++];
    }

    public double peek() {
        if (isEmpty()) {
            return -1;
        }
        return queue[front];
    }
}

