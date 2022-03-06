package comp2402w22a3;
// Thank you Pat Morin for the basic skeleton of this file.

// Students: No need to change anything in this file.

import java.util.LinkedList;
import java.util.Queue;
import java.io.PrintWriter;
import java.util.Random;

/**
 * An implementation of binary trees
 *
 * @param <Node>
 * @author morin
 */
public class BinaryTree<Node extends BinaryTree.BTNode<Node>> {

    // A BTNode has a left & right child and a parent BTNode.
    public static class BTNode<Node extends BTNode<Node>> {
        public Node left;
        public Node right;
        public Node parent;
    }

    /**
     * The root of this tree
     */
    protected Node r;

    /**
     * This tree's "null" node
     */
    protected Node nil;


    /**
     * An extension of BTNode that you can actually instantiate.
     * You don't need to worry about what this is for.
     */
    protected static class EndNode extends BTNode<EndNode> {
        public EndNode() {
            this.parent = this.left = this.right = null;
        }
    }

    /**
     * Used to make a mini-factory
     * You don't need to worry about what this is for.
     */
    protected Node sampleNode;

    /**
     * Create a new instance of this class
     *
     * @param sampleNode - a sample of a node that can be used
     *                   to create a new node in newNode()
     * @param nil        - a node that will be used in place of null
     */
    public BinaryTree(Node sampleNode, Node nil) {
        this.sampleNode = sampleNode;
        this.nil = nil;
        r = nil;
    }

    /**
     * Create a new instance of this class
     *
     * @param sampleNode - a sample of a node that can be used
     *                   to create a new node in newNode()
     */
    public BinaryTree(Node sampleNode) {
        this.sampleNode = sampleNode;
    }


    /**
     * Allocate a new node for use in this tree
     *
     * @return
     */
    @SuppressWarnings({"unchecked"})
    protected Node newNode() {
        try {
            Node u = (Node) sampleNode.getClass().getDeclaredConstructor().newInstance();
            u.parent = u.left = u.right = nil;
            return u;
        } catch (Exception e) {
            return null;
        }
    }

    /**
     * Compute the size (number of nodes) of this tree
     *
     * @return the number of nodes in this tree
     * @warning uses recursion so could cause a stack overflow
     */
    public int size() {
        return size(r);
    }

    /**
     * Compute the size (number of nodes) of the tree rooted at u
     *
     * @return the size of the subtree rooted at u
     * @warning uses recursion so could cause a stack overflow
     */
    protected int size(Node u) {
        if (u == nil) return 0;
        return 1 + size(u.left) + size(u.right);
    }

    /**
     * Compute the number of nodes in this tree iteratively
     * (i.e. without recursion)
     *
     * @return the size of the tree (rooted at r)
     */
    public int size2() {
        Node u = r, prev = nil, next;
        int n = 0;
        while (u != nil) {
            if (prev == u.parent) {
                n++;
                if (u.left != nil) next = u.left;
                else if (u.right != nil) next = u.right;
                else next = u.parent;
            } else if (prev == u.left) {
                if (u.right != nil) next = u.right;
                else next = u.parent;
            } else {
                next = u.parent;
            }
            prev = u;
            u = next;
        }
        return n;
    }

    /**
     * Compute the height of this tree (equivalent to the maximum depth
     * of any node in this tree)
     *
     * @return the height of this tree
     * @warning uses recursion so could cause a stack overflow
     */
    public int height() {
        return height(r);
    }

    /**
     * Compute the height of the subtree rooted at u
     *
     * @return the height of the subtree rooted at u
     * @warning uses recursion so could cause a stack overflow
     */
    protected int height(Node u) {
        if (u == nil) return -1;
        return 1 + Math.max(height(u.left), height(u.right));
    }


    public String toString() {
        StringBuilder sb = new StringBuilder();
        toStringHelper(sb, r);
        return sb.toString();
    }

    protected void toStringHelper(StringBuilder sb, Node u) {
        if (u == null) {
            return;
        }
        sb.append('(');
        toStringHelper(sb, u.left);
        toStringHelper(sb, u.right);
        sb.append(')');
    }


    /**
     * @return
     */
    public boolean isEmpty() {
        return r == nil;
    }

    /**
     * Make this tree into the empty tree
     */
    public void clear() {
        r = nil;
    }

    /**
     * Demonstration of a recursive traversal
     *
     * @param u
     */
    public void traverse(Node u) {
        if (u == nil) return;
        traverse(u.left);
        traverse(u.right);
    }

    /**
     * Demonstration of a non-recursive traversal
     */
    public void traverse2() {
        Node u = r, prev = nil, next;
        while (u != nil) {
            if (prev == u.parent) {
                if (u.left != nil) {
                    next = u.left;
                } else if (u.right != nil) {
                    next = u.right;
                } else {
                    next = u.parent;
                }
            } else if (prev == u.left) {
                if (u.right != nil) {
                    next = u.right;
                } else {
                    next = u.parent;
                }
            } else {
                next = u.parent;
            }
            prev = u;
            u = next;
        }
    }

    /**
     * Find the first node in an in-order traversal
     *
     * @return the first node reported in an in-order traversal
     */
    public Node firstNode() {
        Node w = r;
        if (w == nil) return nil;
        while (w.left != nil)
            w = w.left;
        return w;
    }

    /**
     * Find the node that follows w in an in-order traversal
     *
     * @param w
     * @return the node that follows w in an in-order traversal
     */
    public Node nextNode(Node w) {
        if (w.right != nil) {
            w = w.right;
            while (w.left != nil)
                w = w.left;
        } else {
            while (w.parent != nil && w.parent.left != w)
                w = w.parent;
            w = w.parent;
        }
        return w;
    }

    /**
     * @ return an n-node BinaryTree that has the shape of a random
     * binary search tree.
     */
    public static BinaryTree<EndNode> randomTree(int n) {
        Random rand = new Random();
        EndNode sample = new EndNode();
        BinaryTree<EndNode> t = new BinaryTree<EndNode>(sample);
        t.r = randomTreeHelper(n, rand);
        return t;
    }

    protected static EndNode randomTreeHelper(int n, Random rand) {
        if (n == 0) {
            return null;
        }
        EndNode r = new EndNode();
        int ml = rand.nextInt(n);
        int mr = n - ml - 1;
        if (ml > 0) {
            r.left = randomTreeHelper(ml, rand);
            r.left.parent = r;
        }
        if (mr > 0) {
            r.right = randomTreeHelper(mr, rand);
            r.right.parent = r;
        }
        return r;
    }

    public static void main(String[] args) {
        System.out.println(randomTree(30));
    }

}
