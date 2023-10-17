public class MyStack extends MyArray<Integer> {
    private int top;

    MyStack() {
        super();
        this.top = -1;
    }

    void push(int k) {
        add(++this.top, k);
    }

    int pop() {
        if (top < 0)
            return -1;
        return (int) remove(this.top--);
    }

    int top() {
        return this.top;
    }
}
