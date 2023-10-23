import java.util.LinkedList;
import java.util.Queue;
import java.util.Stack;
// (Nearly) Optimal Binary Search Tree

public class BST { // Binary Search Tree implementation

    protected Node root;
    protected int size, freq, probe;

    protected boolean NOBSTified = false;
    protected boolean OBSTified = false;

    public BST() {
        this.root = null;
        this.size = 0;
        this.freq = 0;
        this.probe = 0;
    }

    public void insert(String key) {
        if (this.root == null) {
            this.size += 1;
            this.freq += 1;

            this.root = new Node(key);
            return;
        }

        Node n = this.root;
        Stack<Node> stack = new Stack<>();
        while (n != null) {
            stack.push(n);
            n = getNext(n, key);
        }

        while (!stack.empty()) {
            n = stack.peek();
            stack.pop();
            n.refresh();
        }
    }


    public boolean find(String key) {
        Node n = this.root;

        while (n != null) {
            probe(n);

            if (key.compareTo(n.getKey()) < 0) n = n.getLeftSub();
            else if (key.compareTo(n.getKey()) > 0) n = n.getRightSub();
            else return true;
        }
        return false;
    }

    public int sumFreq() {
        return this.freq;
    }

    public int sumWeightedPath() {
        Queue<Node> nodeQueue = new LinkedList<>();
        Queue<Integer> depthQueue = new LinkedList<>();

        nodeQueue.add(root);
        depthQueue.add(1);

        int weight = 0;
        while (!nodeQueue.isEmpty() && !depthQueue.isEmpty()) {
            Node node = nodeQueue.poll();
            int depth = depthQueue.poll();

            weight += depth * node.getFreq();

            if (node.getLeftSub() != null) {
                nodeQueue.add(node.getLeftSub());
                depthQueue.add(depth + 1);
            }
            if (node.getRightSub() != null) {
                nodeQueue.add(node.getRightSub());
                depthQueue.add(depth + 1);
            }
        }
        return weight;
    }

    public int size() {
        return size;
    }

    public void nobst() {
        this.NOBSTified = true;

        Node[] nodes = new Node[this.size() + 1];
        listing(this.root, nodes, 1);

        int[] weightSum = getWeightSum(nodes);
        this.root = nobst(weightSum, nodes, 1, size);
    }


    public void obst() {
        OBSTified = true;

        Node[] nodes = new Node[this.size() + 1];
        listing(this.root, nodes, 1);

        int[] weightSum = getWeightSum(nodes);
        int[][] rootTable = getTable(this, weightSum);

        this.root = obst(nodes, rootTable, 1, size);
    }


    // additional function
    protected Node getNext(Node n, String key) {
        if (key.compareTo(n.getKey()) < 0) {
            if (n.getLeftSub() == null) {
                this.size += 1;
                this.freq += 1;
                n.setLeftSub(new Node(key));
                return null;
            }
            return n.getLeftSub();
        } else if (key.compareTo(n.getKey()) > 0) {
            if (n.getRightSub() == null) {
                this.size += 1;
                this.freq += 1;
                n.setRightSub(new Node(key));
                return null;
            }
            return n.getRightSub();
        } else {
            this.freq += 1;
            n.setFreq(n.getFreq() + 1);
            return null;
        }
    }

    protected void probe(Node n) {
        this.probe += 1;
        n.setProbe(n.getProbe() + 1);
    }

    public void reset() {
        this.freq = 0;
        this.probe = 0;

        Queue<Node> queue = new LinkedList<>();
        queue.add(root);

        while (!queue.isEmpty()) {
            Node node = queue.poll();

            node.setFreq(0);
            node.setProbe(0);

            if (node.getLeftSub() != null) queue.add(node.getLeftSub());
            if (node.getRightSub() != null) queue.add(node.getRightSub());
        }
    }


    private static int listing(Node n, Node[] nodes, int index) {
        if (n == null)
            return index;

        index = listing(n.getLeftSub(), nodes, index);
        nodes[index++] = n;
        index = listing(n.getRightSub(), nodes, index);

        return index;
    }

    private static int[] getWeightSum(Node[] nodes) {
        int[] weightSum = new int[nodes.length];

        for (int i = 1; i < nodes.length; i++)
            weightSum[i] = weightSum[i - 1] + nodes[i].getFreq();

        return weightSum;
    }

    private static Node nobst(int[] weights, Node[] nodes, int left, int right) {
        if (left > right)
            return null;

        int root = left;
        int last = weights[right] - weights[left];

        int s = left + 1;
        int e = right;

        while (s < e) {
            int m = (s + e + 1) / 2;
            if (weights[right] - weights[m] >= weights[m - 1] - weights[left - 1]) {
                s = m;
            } else {
                e = m - 1;
            }
        }

        for (int i = s; i <= Math.min(right, s + 1); i++) {
            int diff = Math.abs((weights[i - 1] - weights[left - 1]) - (weights[right] - weights[i]));
            if (diff < last) {
                root = i;
                last = diff;
            }
        }

        Node n = new Node("");
        n.assignNode(nodes[root]);
        n.setLeftSub(nobst(weights, nodes, left, root - 1));
        n.setRightSub(nobst(weights, nodes, root + 1, right));
        n.refresh();
        return n;
    }

    private static int[][] getTable(BST bst, int[] weights) {
        int n = bst.size();

        int[][] costs = new int[n + 2][n + 1];
        int[][] roots = new int[n + 2][n + 1];

        for (int i = 1; i <= n; i++) {
            roots[i][i] = i;
            costs[i][i] = weights[i] - weights[i - 1];
        }
        for (int i = 1; i < n; i++) {
            if (costs[i][i] >= costs[i + 1][i + 1]) {
                roots[i][i + 1] = i;
                costs[i][i + 1] = costs[i + 1][i + 1] + weights[i + 1] - weights[i - 1];
            } else {
                roots[i][i + 1] = i + 1;
                costs[i][i + 1] = costs[i][i] + weights[i + 1] - weights[i - 1];
            }
        }

        for (int i = n; i >= 1; i--) {
            for (int j = i + 2; j <= n; j++) {
                int root = roots[i][j - 1];
                int min = costs[i][root - 1] + costs[root + 1][j];
                for (int k = roots[i][j - 1]; k <= roots[i + 1][j]; k++) {
                    if (costs[i][k - 1] + costs[k + 1][j] < min) {
                        min = costs[i][k - 1] + costs[k + 1][j];
                        root = k;
                    }
                }
                roots[i][j] = root;
                costs[i][j] = min + weights[j] - weights[i - 1];
            }
        }

        return roots;
    }

    private static Node obst(Node[] nodes, int[][] roots, int left, int right) {
        if (left > right)
            return null;
        int root = roots[left][right];

        Node n = new Node("");

        n.assignNode(nodes[root]);
        n.setLeftSub(obst(nodes, roots, left, root - 1));
        n.setRightSub(obst(nodes, roots, root + 1, right));
        n.refresh();

        return n;
    }

    public void print() {
        Node[] nodes = new Node[this.size() + 1];
        listing(this.root, nodes, 1);
        for (int i = 1; i <= size; i++) {
            System.out.println(nodes[i]);
        }
    }
}