import java.util.Queue;
import java.util.Stack;
import java.util.LinkedList;
// (Nearly) Optimal Binary Search Tree
// Bongki Moon (bkmoon@snu.ac.kr)

public class BST { // Binary Search Tree implementation

    protected boolean NOBSTified = false;
    protected boolean OBSTified = false;
    protected Node root;
    protected int totSize, totFreq, totProbe;

    public BST() {
        root = null;
        totSize = 0;
        totFreq = 0;
    }

    // Tree node operation
    protected Node makeNewNode(String key) {
        totSize += 1;
        totFreq += 1;
        return new Node(key);
    }

    protected void increaseFrequency(Node node) {
        totFreq += 1;
        node.frequency += 1;
    }

    protected void increaseProbe(Node node){
        totProbe += 1;
        node.probe += 1;
    }

    // return nextNode
    // if there are no nextNode, make node or increase frequency
    protected Node getNextNode(Node node, String key) {
        int flag = key.compareTo(node.key);
        if (flag < 0) {
            if (node.left == null) {
                node.left = makeNewNode(key);
                return null;
            }
            return node.left;
        } else if (flag > 0) {
            if (node.right == null) {
                node.right = makeNewNode(key);
                return null;
            }
            return node.right;
        } else {
            increaseFrequency(node);
            return null;
        }
    }

    // inserting key
    public void insert(String key) {
        if (root == null) {
            root = makeNewNode(key);
            return;
        }

        Node node = root;
        Stack<Node> stk = new Stack<>();
        while (node != null) {
            stk.push(node);
            node = getNextNode(node, key);
        }
        resolveStack(stk);
    }

    private void resolveStack(Stack<Node> stk){
        Node node;
        while(!stk.empty()){
          node = stk.peek(); stk.pop();
          node.refreshHeight();;
        }
      }

    // find key
    public boolean find(String key) {
        Node node = root;
        while (node != null) {
            increaseProbe(node);
            int flag = key.compareTo(node.key);
            if (flag < 0)
                node = node.left;
            else if (flag > 0)
                node = node.right;
            else
                return true;
        }
        return false;
    }

    public int size() {
        return totSize;
    }

    public int sumFreq() {
        return totFreq;
    }

    public int sumProbes() {
        return totProbe;
    }

    public int sumWeightedPath() {
        Queue<Node> que = new LinkedList<>();
        Queue<Integer> depthQue = new LinkedList<>();
        que.add(root);
        depthQue.add(1);
        int ret = 0;
        while(!que.isEmpty()){
            Node node = que.poll(); 
            int depth = depthQue.poll();
            ret += depth * node.frequency;
            if(node.left != null){
                que.add(node.left);
                depthQue.add(depth+1);
            }
            if(node.right != null){
                que.add(node.right);
                depthQue.add(depth+1);
            }
        }
        return ret;
    }

    public void resetCounters() {
        totFreq = 0;
        totProbe = 0;
        Queue<Node> que = new LinkedList<>();
        que.add(root);
        while(!que.isEmpty()){
            Node node = que.poll(); 
            node.frequency = 0;
            node.probe = 0;
            if(node.left != null) que.add(node.left);
            if(node.right != null) que.add(node.right);
        }
    }

    private static Node[] getNodesList(BST bst) {
        Node[] nodes = new Node[bst.size() + 1];
        fillNodesList(bst.root, nodes, 1);
        return nodes;
    }

    private static int fillNodesList(Node node, Node[] nodes, int index) {
        if (node == null)
            return index;
        index = fillNodesList(node.left, nodes, index);
        nodes[index++] = node;
        index = fillNodesList(node.right, nodes, index);
        return index;
    }

    private static int[] getWeightSum(Node[] nodes) {
        int sz = nodes.length;
        int[] weightSum = new int[sz];
        for (int i = 1; i < sz; i++) {
            weightSum[i] = weightSum[i - 1] + nodes[i].frequency;
        }
        return weightSum;
    }

    public void nobst() {
        NOBSTified = true;
        Node[] nodes = getNodesList(this);
        int[] weightSum = getWeightSum(nodes);
        root = nobst(weightSum, nodes, 1, totSize);
    } // Set NOBSTified to true.

    private static Node nobst(int[] weightSum, Node[] nodes, int l, int r) {
        if (l > r)
            return null;

        int root = l, lastMin = weightSum[r] - weightSum[l];
        
        int s = l+1, e = r;
        while(s < e){
            int m = (s+e+1)/2;
            if(weightSum[m-1] - weightSum[l-1] <= weightSum[r] - weightSum[m]){
                s = m;
            }else{
                e = m-1;
            }
        }
        
        for (int i = s; i <= Math.min(r, s+1); i++) {
            int difference = Math.abs((weightSum[i - 1] - weightSum[l - 1]) - (weightSum[r] - weightSum[i]));
            if (difference < lastMin) { // until right is heavier
                root = i;
                lastMin = difference;
            }
        }

        Node ret = new Node("");
        ret.assignNode(nodes[root]);
        ret.left = nobst(weightSum, nodes, l, root - 1);
        ret.right = nobst(weightSum, nodes, root + 1, r);
        ret.refreshHeight();
        return ret;
    }

    public void obst() {
        OBSTified = true;
        Node[] nodes = getNodesList(this);
        int[] weightSum = getWeightSum(nodes);
        int[][] rootTable = getRootTable(this, nodes, weightSum);
        root = obst(nodes, rootTable, 1, totSize);
    }

    private static int[][] getRootTable(BST bst, Node[] nodes, int[] weightSum) { // TODO. reduce time!!!!!!!!!
        int n = bst.size();
        int[][] costTable = new int[n + 2][n + 1];
        int[][] rootTable = new int[n + 2][n + 1];

        for (int i = 1; i <= n; i++) { // j == i
            rootTable[i][i] = i;
            costTable[i][i] = weightSum[i] - weightSum[i - 1];
        }
        for (int i = 1; i < n; i++) { // j == i+1
            if (costTable[i][i] >= costTable[i + 1][i + 1]) {
                rootTable[i][i + 1] = i;
                costTable[i][i + 1] = costTable[i + 1][i + 1] + weightSum[i + 1] - weightSum[i - 1];
            } else {
                rootTable[i][i + 1] = i + 1;
                costTable[i][i + 1] = costTable[i][i] + weightSum[i + 1] - weightSum[i - 1];
            }
        }

        for(int low = n; low >= 1; low--){
            for(int high=low+2; high <=n; high++){
                int root = rootTable[low][high - 1];
                int minCost = costTable[low][root - 1] + costTable[root + 1][high];
                for(int r = rootTable[low][high-1]; r <= rootTable[low+1][high]; r++){
                    if (costTable[low][r - 1] + costTable[r + 1][high] < minCost) {
                        minCost = costTable[low][r - 1] + costTable[r + 1][high];
                        root = r;
                    }
                }
                rootTable[low][high] = root;
                costTable[low][high] = minCost + weightSum[high] - weightSum[low - 1];
            }
        }
        return rootTable;
    }

    private static Node obst(Node[] nodes, int[][] rootTable, int l, int r) {
        if (l > r)
            return null;
        Node ret = new Node("");
        int root = rootTable[l][r];
        ret.assignNode(nodes[root]);
        ret.left = obst(nodes, rootTable, l, root - 1);
        ret.right = obst(nodes, rootTable, root + 1, r);
        ret.refreshHeight();
        return ret;
    }
    public void print() {
        Node[] nodes = getNodesList(this);
        for(int i=1; i<=totSize; i++){
            System.out.println(nodes[i]);    
        }
    }



}