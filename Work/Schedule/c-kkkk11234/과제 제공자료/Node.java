class Node {
    public String key;
    public int frequency, probe;
    public Node left, right;
    public int h, bf;

    public Node(String key) {
        this.key = key;
        frequency = 1;
        probe = 0;
        left = null;
        right = null;
        h = 1;
        bf = 0;
    }

    public static Node clone(Node node) {
        if (node == null)
            return node;
        Node ret = new Node("");
        ret.assignNode(node);
        return ret;
    }

    public void assignNode(Node node) {
        this.key = node.key;
        this.frequency = node.frequency;
        this.probe = node.probe;
        this.left = node.left;
        this.right = node.right;
        this.h = node.h;
        this.bf = node.bf;
    }

    public void refreshHeight() {
        int lh = 0, rh = 0;
        if (left != null)
            lh = left.h;
        if (right != null)
            rh = right.h;
        h = 1 + Math.max(lh, rh);
        bf = lh - rh;
    }

    public String toString() {
        return String.format("[%s:%d:%d]", key, frequency, probe);
    }
}