public class Main {
    public static void main(String[] args) {
        MyStack s = new MyStack();
        MyQueue q = new MyQueue();

        for (int i = 0; i < 10; i++) {
            s.push(i + 1);
            q.enqueue(i + 1);
        }

        while (!s.isEmpty())
            System.out.println("Pop from Stack: " + Integer.toString(s.pop()));
        while (!q.isEmpty())
            System.out.println("Dequeue from Queue: " + Integer.toString(q.dequeue()));
    }
}
