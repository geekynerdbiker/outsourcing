import java.util.Stack;
// AVL Binary Search Tree
// Bongki Moon (bkmoon@snu.ac.kr)

public class AVL extends BST {
    public AVL() {
    }

    @Override
    public void insert(String key) {
        if (root == null) {
            root = makeNewNode(key);
            return;
        }

        Stack<Node> stk = new Stack<>();
        Node node = root;
        while (node != null) {
            stk.push(node);
            node = getNextNode(node, key);
        }
        resolveStack(stk);
    }

    private void resolveStack(Stack<Node> stk) {
        Node node;
        while (!stk.empty()) {
            node = stk.peek();
            stk.pop();
            rebalanceNode(node);
        }
    }

    private void rebalanceNode(Node node) {
        node.refreshHeight();
        if (node.bf == 2) {
            if (node.left.bf == -1)
                rotateLeftRight(node);
            else
                rotateRight(node);
        } else if (node.bf == -2) {
            if (node.right.bf == 1)
                rotateRightLeft(node);
            else
                rotateLeft(node);
        }
    }

    private void rotateRight(Node node) {
        Node S = Node.clone(node);
        Node X = Node.clone(node.left);
        Node B = Node.clone(node.left.right);
        Node C = Node.clone(node.right);

        node.assignNode(X);
        node.right = S;
        node.right.left = B;
        node.right.right = C;

        node.right.refreshHeight();
        node.refreshHeight();
    }

    private void rotateLeft(Node node) {
        Node S = Node.clone(node);
        Node X = Node.clone(node.right);
        Node A = Node.clone(node.left);
        Node B = Node.clone(node.right.left);

        node.assignNode(X);
        node.left = S;
        node.left.left = A;
        node.left.right = B;

        node.left.refreshHeight();
        node.refreshHeight();
    }

    private void rotateLeftRight(Node node) {
        rotateLeft(node.left);
        rotateRight(node);
    }

    private void rotateRightLeft(Node node) {
        rotateRight(node.right);
        rotateLeft(node);
    }

}
