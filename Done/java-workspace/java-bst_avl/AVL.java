import java.util.Stack;
// AVL Binary Search Tree

public class AVL extends BST {
    public AVL() {
    }

    @Override
    public void insert(String key) {
        if (root == null) {
            this.size += 1;
            this.freq += 1;
            this.root = new Node(key);
            return;
        }

        Stack<Node> stack = new Stack<>();
        Node node = root;
        while (node != null) {
            stack.push(node);
            node = getNext(node, key);
        }

        while (!stack.empty()) {
            node = stack.peek();
            stack.pop();
            balancing(node);
        }
    }

    private void balancing(Node n) {
        n.refresh();

        if (n.getBalance() == 2) {
            if (n.getLeftSub().getBalance() == -1) {
                rotateL(n.getLeftSub());
                rotateR(n);
            } else
                rotateR(n);
        } else if (n.getBalance() == -2) {
            if (n.getRightSub().getBalance() == 1) {
                rotateR(n.getRightSub());
                rotateL(n);
            } else
                rotateL(n);
        }
    }

    private void rotateR(Node n) {
        Node node = Node.clone(n);
        Node left = Node.clone(n.getLeftSub());
        Node right = Node.clone(n.getRightSub());
        Node leftRight = Node.clone(n.getLeftSub().getRightSub());


        n.assignNode(left);
        n.setRightSub(node);
        n.getRightSub().setLeftSub(leftRight);
        n.getRightSub().setRightSub(right);

        n.getRightSub().refresh();
        n.refresh();
    }

    private void rotateL(Node n) {
        Node node = Node.clone(n);
        Node left = Node.clone(n.getLeftSub());
        Node right = Node.clone(n.getRightSub());
        Node rightLeft = Node.clone(n.getRightSub().getLeftSub());

        n.assignNode(right);
        n.setLeftSub(node);
        n.getLeftSub().setLeftSub(left);
        n.getLeftSub().setRightSub(rightLeft);

        n.getLeftSub().refresh();
        n.refresh();
    }
}
