public class MyQueue extends MyArray<Integer> {
    private int front, rear;

    MyQueue() {
        super();
        this.front = 0;
        this.rear = -1;
    }

    void enqueue(int k) {
        if (rear == 10)
            return;
        add(++rear, k);
    }

    int dequeue() {
        if (rear < front)
            return -1;

        front++;
        return (int) remove(0);
    }

    int front() {
        return this.front;
    }
}
