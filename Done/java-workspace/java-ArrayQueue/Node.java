public class Node {
    private String name;
    private Node children[];
    private int size = 0;
    private int capacity = 5;

    public Node(String name) {
        this.name = name;
        this.children = new Node[capacity];
    }

    public String getName() {
        return name;
    }

    public Node[] getChildren() {
        return children;
    }

    public int getSize() {
        return size;
    }

    public Node findChild(String name) {
        for (int i = 0; i < size; i++) {
            if (children[i].getName().equals(name))
                return children[i];
        }
        return null;
    }

    public void addChild(Node child) {
        if (size < capacity) {
            this.children[size] = child;
            size++;
        } else {
            Node tmp[] = new Node[size + capacity];
            System.arraycopy(children, 0, tmp, 0, size);
            children = tmp;
            addChild(child);
        }
    }
}