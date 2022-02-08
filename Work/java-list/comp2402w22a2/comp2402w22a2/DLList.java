package comp2402w22a2;
// Thank you Pat Morin for the basic skeleton of this file.

import java.util.ListIterator;

/**
 * An implementation of the List interface as a doubly-linked circular list. A
 * dummy node is used to simplify the code.
 *
 * @param <T> the type of elements stored in the list
 * @author morin
 */
public class DLList<T> implements MyList<T> {
    class Node {
        T x;
        Node prev, next;
    }

    /**
     * Number of nodes in the list
     */
    int n;

    /**
     * The dummy node. We use the convention that dummy.next = first and
     * dummy.prev = last
     */
    protected Node dummy;

    public DLList() {
        dummy = new Node();
        dummy.next = dummy;
        dummy.prev = dummy;
        n = 0;
    }

    /**
     * Add a new node containing x before the node p
     *
     * @param w the node to insert the new node before
     * @param x the value to store in the new node
     * @return the newly created and inserted node
     */
    protected Node addBefore(Node w, T x) {
        Node u = new Node();
        u.x = x;
        u.prev = w.prev;
        u.next = w;
        u.next.prev = u;
        u.prev.next = u;
        n++;
        return u;
    }

    /**
     * Remove the node p from the list
     *
     * @param w the node to remove
     */
    protected void remove(Node w) {
        w.prev.next = w.next;
        w.next.prev = w.prev;
        n--;
    }

    /**
     * Get the i'th node in the list
     *
     * @param i the index of the node to get
     * @return the node with index i
     */
    protected Node getNode(int i) {
        Node p = null;
        if (i < n / 2) {
            p = dummy.next;
            for (int j = 0; j < i; j++)
                p = p.next;
        } else {
            p = dummy;
            for (int j = n; j > i; j--)
                p = p.prev;
        }
        return p;
    }

    public int size() {
        return n;
    }

    public boolean add(T x) {
        addBefore(dummy, x);
        return true;
    }

    public T remove(int i) {
        if (i < 0 || i > n - 1) throw new IndexOutOfBoundsException();
        Node w = getNode(i);
        remove(w);
        return w.x;
    }

    public void add(int i, T x) {
        if (i < 0 || i > n) throw new IndexOutOfBoundsException();
        addBefore(getNode(i), x);
    }

    public T get(int i) {
        if (i < 0 || i > n - 1) throw new IndexOutOfBoundsException();
        return getNode(i).x;
    }

    public T set(int i, T x) {
        if (i < 0 || i > n - 1) throw new IndexOutOfBoundsException();
        Node u = getNode(i);
        T y = u.x;
        u.x = x;
        return y;
    }

    public void clear() {
        dummy.next = dummy;
        dummy.prev = dummy;
        n = 0;
    }

    public void insertSingleBlock(int i, DLList<T> other) {
        // TODO: Your code goes here!
    }


	// Note: DO NOT CHANGE THIS FUNCTION.
	// otherwise the server tests might fail.
    public DLList<T> removeFirst() {
		if( this.size() == 0 ) return new DLList<T>();

        DLList<T> other = new DLList<T>();
        T first = remove(0);
        other.n = this.n;
        other.dummy = this.dummy;

        this.dummy = new Node();
        this.dummy.next = dummy;
        this.dummy.prev = dummy;
        this.n = 0;
        this.add(0, first);
        return other;
    }


    public String toString() {
        StringBuilder retStr = new StringBuilder();
        retStr.append("[");
        Node u = dummy.next;
        while (u != dummy) {
            retStr.append(u.x);
            u = u.next;
            if (u != dummy) {
                retStr.append(", ");
            }
        }
        retStr.append("]");
        return retStr.toString();
    }

    public ListIterator<T> iterator() {
        return new Iterator(this, 0);
    }

    class Iterator implements ListIterator<T> {
        /**
         * The list we are iterating over
         */
        DLList<T> l;

        /**
         * The node whose value is returned by next()
         */
        Node p;

        /**
         * The last node whose value was returned by next() or previous()
         */
        Node last;

        /**
         * The index of p
         */
        int i;

        Iterator(DLList<T> il, int ii) {
            l = il;
            i = ii;
            p = l.getNode(i);
        }

        public boolean hasNext() {
            return p != l.dummy;
        }

        public T next() {
            T x = p.x;
            last = p;
            p = p.next;
            i++;
            return x;
        }

        public int nextIndex() {
            return i;
        }

        public boolean hasPrevious() {
            return p.prev != dummy;
        }

        public T previous() {
            p = p.prev;
            last = p;
            i--;
            return p.x;
        }

        public int previousIndex() {
            return i - 1;
        }

        public void add(T x) {
            DLList.this.addBefore(p, x);
        }

        public void set(T x) {
            last.x = x;
        }

        public void remove() {
            if (p == last) {
                p = p.next;
            }
            DLList.this.remove(last);
        }

    }

    public static void main(String[] args) {
        int n = 8;
        testInsertSingleBlock(n);
//    testInsertSingleBlock(0);
//    testInsertSingleBlock(100);
    }


    // Creates a MyList of n elements, then calls
    // blockify on that list. Prints out the blocks that
    // are returned.
    public static void testInsertSingleBlock(int n) {
        System.out.println("Test InsertSingleBlock------");
        DLList<Integer> ml = new DLList<Integer>();

        // Create a DLLIst with n elements 0, 1, 2, ..., n-1.
        for (int i = 0; i < n; i++) {
            ml.add(i, ml.size());
        }
        System.out.println("ml: " + ml);

        // Create various "other" DLList with 2 elements
        DLList<Integer> other0 = new DLList<Integer>();
        DLList<Integer> other1 = new DLList<Integer>();
        DLList<Integer> other2 = new DLList<Integer>();

        for (int i = 0; i < 2; i++) {
            other0.add(i, -1);
            other1.add(i, -2);
            other2.add(i, -3);
        }
        System.out.println("other: " + other0);

        // Call insertSingleBlock on it. Print out the results.
        ml.insertSingleBlock(n / 2, other0);
        System.out.println(ml);
        ml.insertSingleBlock(0, other1);
        System.out.println(ml);
        ml.insertSingleBlock(n, other2);
        System.out.println(ml);

        other0 = ml.removeFirst();
        System.out.println(ml);
        System.out.println(other0);
        ml.insertSingleBlock(1, other0);
        System.out.println(ml);

        System.out.println("Done Test InsertSingleBlock------");
    }
}
