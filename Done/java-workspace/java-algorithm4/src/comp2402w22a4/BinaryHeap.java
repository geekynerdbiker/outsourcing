package comp2402w22a4;
// Thank you Pat Morin for the basic skeleton of this file.

// NOTE(Students): Do not change anything in this file.
// Needed for Algorithms.java


import java.util.AbstractQueue;
import java.util.Arrays;
import java.util.Collections;
import java.util.Comparator;
import java.util.Iterator;
import java.util.Random;

/**
 * This class implements a priority queue as a class binary heap
 * stored implicitly in an array
 *
 * @param <T>
 * @author morin
 */
public class BinaryHeap<T> extends AbstractQueue<T> {

    Comparator<T> c;

    /**
     * Our backing array
     */
    protected T[] a;

    /**
     * The number of elements in the priority queue
     */
    protected int n;

    /**
     * Create a new empty binary heap
     */
    public BinaryHeap() {
        this(new DefaultComparator<T>());
    }


    @SuppressWarnings("unchecked")
    public BinaryHeap(Comparator<T> c0) {
        c = c0;
        a = (T[]) new Object[1];
        n = 0;
    }

    @SuppressWarnings("unchecked")
    public void clear() {
        a = (T[]) new Object[1];
        n = 0;
    }

    /**
     * Create a new binary heap by heapifying a
     *
     * @param a
     */
    public BinaryHeap(T[] a) {
        this(a, new DefaultComparator<T>());
    }

    /**
     * Create a new binary heap by heapifying a
     *
     * @param ia
     */
    public BinaryHeap(T[] a, Comparator<T> c) {
        this.c = c;
        this.a = a;
        n = a.length;
        for (int i = n / 2 - 1; i >= 0; i--) {
            trickleDown(i);
        }
    }


    protected void resize() {
        @SuppressWarnings("unchecked")
        T[] b = (T[]) new Object[Math.max(n * 2, 1)];
        System.arraycopy(a, 0, b, 0, n);
        a = b;
    }

    /**
     * @param i
     * @return the index of the left child of the value at index i
     */
    protected int left(int i) {
        return 2 * i + 1;
    }

    /**
     * @param i
     * @return the index of the left child of the value at index i
     */
    protected int right(int i) {
        return 2 * i + 2;
    }

    /**
     * @param i
     * @return the index of the parent of the value at index i
     */
    protected int parent(int i) {
        return (i - 1) / 2;
    }


    public int size() {
        return n;
    }

    /**
     * Swap the two values a[i] and a[j]
     *
     * @param i
     * @param j
     */
    final protected void swap(int i, int j) {
        T x = a[i];
        a[i] = a[j];
        a[j] = x;
    }


    public boolean offer(T x) {
        return add(x);
    }

    public boolean add(T x) {
        if (n + 1 > a.length) resize();
        a[n++] = x;
        bubbleUp(n - 1);
        return true;
    }

    /**
     * Run the bubbleUp routine at position i
     *
     * @param i
     */
    protected void bubbleUp(int i) {
        int p = parent(i);
        while (i > 0 && c.compare(a[i], a[p]) < 0) {
            swap(i, p);
            i = p;
            p = parent(i);
        }
    }


    public T smallest(int k) {
        // TODO(student): Your code goes here.
        // While not required, I've included a Pair and PairComparator class
        // that you can use if you like. Don't worry about it unless you think
        // you want something like that.
        return null;
    }

    // Pair is an internal class that allows you to store an
    // (index, element) pair. There is an associated Comparator
    // PairComparator.
    class Pair {
        int index;
        T data;

        public Pair(int index, T data) {
            this.index = index;
            this.data = data;
        }

        public String toString() {
            return "[" + index + ": " + data + "]";
        }
    }

    // This is a Comparator for the (index, element) pairs.
    // Together, these two classes allow you go store elements
    // in a data structure while keeping the index around.
    // That is, you can store (index, element) pairs, and then
    // use this PairComparator to compare the pairs just on the
    // value of their element.
    class PairComparator implements Comparator<Pair> {
        public int compare(Pair a, Pair b) {
            return c.compare(a.data, b.data);
        }
    }


    public T peek() {
        return a[0];
    }

    public T poll() {
        return remove();
    }

    public T remove() {
        T x = a[0];
        a[0] = a[--n];
        trickleDown(0);
        if (3 * n < a.length) resize();
        return x;
    }

    /**
     * Move element i down in the heap until the heap
     * property is restored
     *
     * @param i
     */
    protected void trickleDown(int i) {
        do {
            int j = -1;
            int r = right(i);
            if (r < n && c.compare(a[r], a[i]) < 0) {
                int l = left(i);
                if (c.compare(a[l], a[r]) < 0) {
                    j = l;
                } else {
                    j = r;
                }
            } else {
                int l = left(i);
                if (l < n && c.compare(a[l], a[i]) < 0) {
                    j = l;
                }
            }
            if (j >= 0) swap(i, j);
            i = j;
        } while (i >= 0);
    }

    public Iterator<T> iterator() {
        class PQI implements Iterator<T> {
            int i;

            public PQI() {
                i = 0;
            }

            public boolean hasNext() {
                return i < n;
            }

            public T next() {
                return a[i++];
            }

            public void remove() {
                throw new UnsupportedOperationException();
            }
        }
        return new PQI();
    }

    /**
     * An implementation of the heapsort algorithm
     *
     * @param <T>
     * @param a
     */

    public static <T> void sort(T[] a, Comparator<T> c) {
        BinaryHeap<T> h = new BinaryHeap<T>(a, c);
        while (h.n > 1) {
            h.swap(--h.n, 0);
            h.trickleDown(0);
        }
        Collections.reverse(Arrays.asList(a));
    }

    public static <T extends Comparable<T>> void sort(T[] a) {
        sort(a, new DefaultComparator<T>());
    }

    /**
     * @param args
     */
    public static void main(String[] args) {
        BinaryHeap<Integer> h = new BinaryHeap<Integer>();
        Random r = new Random();

        // These are just limited examples of local tests.
        // Please modify as you see fit in order to test
        // your programs more thoroughly before submitting to server.
        int n = 10;
        for (int i = 0; i < n; i++) {
            h.add(r.nextInt(2500));
        }

        long start, stop;
        double elapsed;
        System.out.print("performing " + n + " smallest(i) for i=1...n...");
        start = System.nanoTime();
        //System.out.println(h);
        for (int i = 0; i < n; i++) {
            System.out.println(h.smallest(i + 1));
        }

        stop = System.nanoTime();
        elapsed = 1e-9 * (stop - start);
        System.out.println("(" + elapsed + "s ["
                + (int) (((double) n) / elapsed) + "ops/sec])");

    }


}
