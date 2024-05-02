class Node {
    private String key;
    private Node leftSub, rightSub;
    private int freq, probe, height, balance;

    public Node(String key) {
        this.key = key;

        this.leftSub = null;
        this.rightSub = null;

        this.freq = 1;
        this.probe = 0;
        this.height = 1;
        this.balance = 0;
    }

    public String getKey() {
        return this.key;
    }

    public Node getLeftSub() {
        return this.leftSub;
    }

    public void setLeftSub(Node leftSub) {
        this.leftSub = leftSub;
    }

    public Node getRightSub() {
        return this.rightSub;
    }

    public void setRightSub(Node rightSub) {
        this.rightSub = rightSub;
    }

    public int getFreq() {
        return this.freq;
    }

    public void setFreq(int freq) {
        this.freq = freq;
    }

    public int getProbe() {
        return this.probe;
    }

    public void setProbe(int probe) {
        this.probe = probe;
    }

    public int getHeight() {
        return this.height;
    }

    public int getBalance() {
        return this.balance;
    }

    public static Node clone(Node node) {
        if (node == null)
            return null;
        Node n = new Node("");
        n.assignNode(node);

        return n;
    }

    public void assignNode(Node node) {
        this.key = node.key;

        this.leftSub = node.leftSub;
        this.rightSub = node.rightSub;

        this.freq = node.freq;
        this.probe = node.probe;
        this.height = node.height;
        this.balance = node.balance;
    }

    public void refresh() {
        int left = 0, right = 0;

        if (leftSub != null)
            left = leftSub.getHeight();
        if (rightSub != null)
            right = rightSub.getHeight();

        height = 1 + Math.max(left, right);
        balance = left - right;
    }

    public String toString() {
        return String.format("[%s:%d:%d]", key, freq, probe);
    }
}