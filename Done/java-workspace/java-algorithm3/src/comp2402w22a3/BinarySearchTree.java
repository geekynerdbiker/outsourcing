package comp2402w22a3;
// Thank you Pat Morin for the basic skeleton of this file.

import java.util.Comparator;
import java.util.Iterator;
import java.util.Random;

public class BinarySearchTree<Node extends BinarySearchTree.BSTNode<Node, T>, T> extends
        BinaryTree<Node> implements SSet<T> {

    protected Comparator<T> c;

    public static class BSTNode<Node extends BSTNode<Node, T>, T>
            extends BinaryTree.BTNode<Node> {
        // Usually these would not be public, but for server tests it's necessary.
        public T x;       // Holds the data value of this node.
    }

    /**
     * The number of nodes (elements) currently in the tree
     */
    protected int n;


    /**
     * An extension of BSTNode that you can actually instantiate.
     */
    public static class BSTEndNode<T> extends BSTNode<BSTEndNode<T>, T> {
        public BSTEndNode() {
            this.parent = this.left = this.right = null;
            this.x = null;
        }
    }

    protected Node newNode(T x) {
        Node u = super.newNode();
        u.x = x;
        return u;
    }

    public BinarySearchTree(Node sampleNode, Node nil, Comparator<T> c) {
        super(sampleNode, nil);
        this.c = c;
    }

    public BinarySearchTree(Node sampleNode, Comparator<T> c) {
        super(sampleNode);
        this.c = c;
    }

    public BinarySearchTree(Node sampleNode) {
        this(sampleNode, new DefaultComparator<T>());
    }


    public void insertSingleBlock(BinarySearchTree<Node, T> other) {
        //TODO(student): Your code goes here.

        Node sNode = this.firstNode();
        Node otherNode = other.firstNode();

        if (otherNode == null)
            return;

        T otherFirst = otherNode.x, otherLast;

        while (other.nextNode(otherNode) != null)
            otherNode = other.nextNode(otherNode);

        otherLast = otherNode.x;

        boolean isValid = false;
        while (sNode != null) {
            if (c.compare(otherFirst, sNode.x) < 0) {
                if (c.compare(otherLast, sNode.x) < 0) {
                    isValid = true;
                    break;
                }
            } else if (c.compare(otherFirst, sNode.x) >= 0) {
                if (c.compare(otherLast, sNode.x) >= 0) {
                    isValid = true;
                    break;
                }
            } else {
                sNode = this.nextNode(sNode);
            }
        }

        if (isValid) {
            this.add(other.r);
        }
    }


    /**
     * Search for a value in the tree
     *
     * @return the last node on the search path for x
     */
    protected Node findLast(T x) {
        Node w = r, prev = nil;
        while (w != nil) {
            prev = w;
            int comp = c.compare(x, w.x);
            if (comp < 0) {
                w = w.left;
            } else if (comp > 0) {
                w = w.right;
            } else {
                return w;
            }
        }
        return prev;
    }

    /**
     * Search for a value in the tree
     *
     * @return the last "left turn" node on the search path for x
     */
    protected Node findGENode(T x) {
        Node w = r, z = nil;
        while (w != nil) {
            int comp = c.compare(x, w.x);
            if (comp < 0) {
                z = w;        // We're turning left! Save z.
                w = w.left;
            } else if (comp > 0) {
                w = w.right;
            } else {
                return w;
            }
        }
        return z;
    }

    /**
     * Search for a value in the tree
     *
     * @return the min value y >= x; null if x is larger than everything in tree
     */
    public T find(T x) {
        Node w = r, z = nil;
        while (w != nil) {
            int comp = c.compare(x, w.x);
            if (comp < 0) {
                z = w;
                w = w.left;
            } else if (comp > 0) {
                w = w.right;
            } else {
                return w.x;
            }
        }
        return z == nil ? null : z.x;
    }

    /**
     * Search for a value in the tree
     *
     * @return the last "right turn" node on the search path for x
     */
    protected Node findLTNode(T x) {
        Node u = r, z = nil;
        while (u != nil) {
            int comp = c.compare(x, u.x);
            if (comp < 0) {
                u = u.left;
            } else if (comp > 0) {
                z = u;      // We're turning right! Save z.
                u = u.right;
            } else {
                return u;
            }
        }
        return z;
    }


    /**
     * Add the node u as a child of node p -- ASSUMES p has no child
     * where u should be added
     *
     * @param p
     * @param u
     * @return true if the child was added, false otherwise
     */
    protected boolean addChild(Node p, Node u) {
        if (p == nil) {
            r = u;              // inserting into empty tree
        } else {
            int comp = c.compare(u.x, p.x);
            if (comp < 0) {
                p.left = u;
            } else if (comp > 0) {
                p.right = u;
            } else {
                return false;   // u.x is already in the tree
            }
            u.parent = p;
            // Update all ancestors of u to have one bigger size
            while (p != nil) {
                p = p.parent;
            }
        }
        n++;
        return true;
    }

    /**
     * Add a new value
     *
     * @param x
     * @return
     */
    public boolean add(T x) {
        Node p = findLast(x);
        return addChild(p, newNode(x));
    }

    /**
     * Add a new value
     *
     * @param x
     * @return
     */
    public boolean add(Node u) {
        Node p = findLast(u.x);
        return addChild(p, u);
    }

    /**
     * Remove the node u --- ASSUMING u has at most one child
     *
     * @param u
     */
    protected void splice(Node u) {
        Node s, p; // s is the child of u, p is the parent.
        if (u.left != nil) {
            s = u.left;
        } else {
            s = u.right;
        }
        if (u == r) { // There is no parent, just replace r with s.
            r = s;
            p = nil;
        } else {
            p = u.parent;
            if (p.left == u) {
                p.left = s; // splice out u
            } else {
                p.right = s;  // splice out u
            }
        }
        if (s != nil) {
            s.parent = p;
        }
        while (p != nil) {
            p = p.parent;
        }
        n--;
    }

    /**
     * Remove the node u from the binary search tree
     *
     * @param u
     */
    protected void remove(Node u) {
        if (u.left == nil || u.right == nil) {
            splice(u);
        } else {
            Node w = u.right;
            while (w.left != nil)
                w = w.left;
            u.x = w.x;
            splice(w);
        }
    }


    /**
     * Remove a node
     *
     * @param x
     * @return
     */
    public boolean remove(T x) {
        Node u = findLast(x);
        if (u != nil && c.compare(x, u.x) == 0) {
            remove(u);
            return true;
        }
        return false;
    }

    public String toString() {
        String s = "[";
        Iterator<T> it = iterator();
        while (it.hasNext()) {
            s += it.next().toString() + (it.hasNext() ? "," : "");
        }
        s += "]";
        return s;
    }

    // Why do I need this method, shouldn't inheritance and polymorphism
    // take care of this?
    public Node firstNode() {
        return super.firstNode();
    }

    // Why do I need this method, shouldn't inheritance and polymorphism
    // take care of this?
    public Node nextNode(Node u) {
        return super.nextNode(u);
    }


    public Iterator<T> iterator(Node u) {
        class BTI implements Iterator<T> {
            protected Node w, prev;

            public BTI(Node iw) {
                w = iw;
            }

            public boolean hasNext() {
                return w != nil;
            }

            public T next() {
                T x = w.x;
                prev = w;
                w = nextNode(w);
                return x;
            }

            public void remove() {
                // NOTE: This is a bug.  remove() methods have to be changed
                // DON'T USE REMOVE ON THE ITERATOR
                BinarySearchTree.this.remove(prev);
            }
        }
        return new BTI(u);
    }

    public Iterator<T> iterator() {
        return iterator(firstNode());
    }

    public Iterator<T> iterator(T x) {
        return iterator(findGENode(x));
    }

    public int size() {
        return n;
    }

    public void clear() {
        super.clear();
        n = 0;
    }

    public Comparator<? super T> comparator() {
        return c;
    }


    public static BinarySearchTree<BSTEndNode<Integer>, Integer> emptyBST() {
        return randomBST(0);
    }

    public static BinarySearchTree<BSTEndNode<Integer>, Integer> randomBST(int n) {
        BSTEndNode<Integer> sample = new BSTEndNode<Integer>();
        BinarySearchTree<BSTEndNode<Integer>, Integer> t = new
                BinarySearchTree<BSTEndNode<Integer>, Integer>(sample);
        Random rand = new Random();
        for (int i = 0; i < n; i++) {
            int value = rand.nextInt(3 * n);
            t.add(value);
        }

        return t;
    }

    // THIS IS JUST FOR TESTING PURPOSES
    // It removes the left child and returns it, if a left child exists.
    // If there's no left child, it tries to remove and return the right child.
    // If there is no child, it returns an empty tree.
    // You can use this to test, but don't use it in your code.
    // The size of this and other are not updated properly for this to work
    // elsewhere, but it's good enough to use in tests if you don't care about size.
    public BinarySearchTree<Node, T> removeChild() {

        Node sample = super.newNode();
        BinarySearchTree<Node, T> other = new
                BinarySearchTree<Node, T>(sample);

        if ((this.r.left == nil) && (this.r.right == nil)) { // neither child exists do nothing
            return other;
        }
        if (this.r.left != nil) { // There is a left child
            other.r = this.r.left;
            this.r.left = nil;
            other.r.parent = nil;
            other.n = 1; // this isn't correct, but it's a lower bound that isn't 0.
            this.n--;     // this isn't correct, but it is an upper bound
            return other;
        } else {
            other.r = this.r.right;
            this.r.right = nil;
            other.r.parent = nil;
            other.n = 1; // this isn't correct, but it's a lower bound that isn't 0.
            this.n--;    // this isn't correct but it's an upper bound
            return other;
        }
    }

    // Returns BST made from n random multiples of n.
    public static BinarySearchTree<BSTEndNode<Integer>, Integer> randomSpacedBST(int n) {
        BSTEndNode<Integer> sample = new BSTEndNode<Integer>();
        BinarySearchTree<BSTEndNode<Integer>, Integer> t = new
                BinarySearchTree<BSTEndNode<Integer>, Integer>(sample);
        Random rand = new Random();
        for (int i = 0; i < n; i++) {
            int value = rand.nextInt(3 * n);
            t.add(n * value);
        }

        return t;
    }

    // Random BST of <= n elements in range [start, start+n)
    public static BinarySearchTree<BSTEndNode<Integer>, Integer> randomIntBST(int start, int n) {
        BSTEndNode<Integer> sample = new BSTEndNode<Integer>();
        BinarySearchTree<BSTEndNode<Integer>, Integer> t = new
                BinarySearchTree<BSTEndNode<Integer>, Integer>(sample);
        Random rand = new Random();
        for (int i = 0; i < n; i++) {
            int value = rand.nextInt(n);
            t.add(start + value);
        }

        return t;
    }

    public static void main(String[] args) {
        // These tests are not at all sufficient. They are just examples.

        int n = 10;
        BinarySearchTree<BinarySearchTree.BSTEndNode<Integer>, Integer> bst =
                BinarySearchTree.randomSpacedBST(n);
        System.out.println(bst);


        BinarySearchTree<BinarySearchTree.BSTEndNode<Integer>, Integer> other =
                BinarySearchTree.randomIntBST(n + 1, n - 1);
        System.out.println(other);


        bst.insertSingleBlock(other);
        System.out.println(bst);

        for (int i = 0; i < n; i++) {
            other = bst.removeChild();
            bst.insertSingleBlock(other);
        }
    }

}
