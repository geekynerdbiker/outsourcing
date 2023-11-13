public class ArrayQueue {
    private int front;
    private int rear;
    private int queueSize;
    private Node queueArr[];

    public ArrayQueue(int queueSize) {
        front = -1;
        rear = -1;
        this.queueSize = queueSize;
        queueArr = new Node[this.queueSize];
    }

    public boolean isEmpty() {
        if (front == rear) {
            front = -1;
            rear = -1;
        }

        return (front == rear);
    }

    public boolean isFull() {
        return (rear == this.queueSize - 1);
    }

    public void enqueue(Node item) {
        if (!isFull()) {
            queueArr[++rear] = item;
        }
    }

    public Node dequeue() {
        if (isEmpty()) {
            return null;
        } else {
            front = (front + 1) % this.queueSize;

            return queueArr[front];
        }

    }

    public void print() {
        for (int i = 0; i < queueSize; i++) {
            System.out.print(queueArr[i].getName());
            if (i < queueSize - 1)
                System.out.print(" ");
        }
    }
}
