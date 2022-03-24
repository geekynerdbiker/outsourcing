package comp2402w22a4;
// Thanks to Pat Morin for the skeleton of this file!

// NOTE(Students): Do not change anything in this file.


import java.util.Arrays;
import java.util.Comparator;
import java.util.Queue;
import java.util.Random;
import java.util.Stack;
import java.util.LinkedList;
import java.util.List;
import java.util.ArrayList;

public class Algorithms {
	protected static Random rand = new Random();
	
	public static <T extends Comparable<T>> void mergeSort(T[] a) {
		mergeSort(a, new DefaultComparator<T>());
	}
	
	public static <T> void mergeSort(T[] a, Comparator<T> c) {
		if (a.length <= 1) return;
		T[] a0 = Arrays.copyOfRange(a, 0, a.length/2);
		T[] a1 = Arrays.copyOfRange(a, a.length/2, a.length);
		mergeSort(a0, c);
		mergeSort(a1, c);
		merge(a0, a1, a, c);
	}
	
	/**
	 * Perform a bread-first search of g starting at vertex i
	 * @param g
	 * @param i
	 */
	public static void bfs(Graph g, int r) {
		boolean[] seen = new boolean[g.nVertices()];
		Queue<Integer> q = new LinkedList<Integer>();
		q.add(r);
		seen[r] = true;
		while (!q.isEmpty()) {
			int i = q.remove();
			for (Integer j : g.outEdges(i)) {
				if (!seen[j]) {
					q.add(j);
					seen[j] = true;
				}
			}
		}
	}

  // bfs but also prints out the "edge" formed in the BFS tree.
	public static void bfsZ(Graph g, int r) {
		boolean[] seen = new boolean[g.nVertices()];
		Queue<Integer> q = new LinkedList<Integer>();
		q.add(r);
		seen[r] = true;
		while (!q.isEmpty()) {
			int i = q.remove();
			for (Integer j : g.outEdges(i)) {
				if (!seen[j]) {
					System.out.println(i + " => " + j);
					q.add(j);
					seen[j] = true;
				}
			}
		}
	}

	/**
	 * Perform a bread-first search of g starting at vertex s, ending at t
   * Return the minimum distance between s and t, found via bfs.
	 * @param g
	 * @param s
	 * @param t 
	 */
	public static int bfs(Graph g, int s, int t) {
    if( s == t )  return 0; 

		boolean[] seen = new boolean[g.nVertices()];
		Queue<Integer> q = new LinkedList<Integer>();
    Queue<Integer> d = new LinkedList<Integer>();
		q.add(s);
    d.add(0);
		seen[s] = true;
		while (!q.isEmpty()) {
			int i = q.remove();
      int dist = d.remove();
			for (Integer j : g.outEdges(i)) {
        if( j == t ) { // we found t!
          return dist+1;
        }
				if (!seen[j]) {
					q.add(j);
          d.add(dist+1);
					seen[j] = true;
				}
			}
		}
    return -1;
	}

	/**
	 * Perform a bread-first search of g starting at vertex s, ending at t
   * Return an array of "predecessors" along the path, that is, for a
   * vertex i, if pred[i]=j then bfs travelled along the edge (j,i).
	 * @param g
	 * @param s
	 */
	public static int[] bfsPred(Graph g, int s) {
		boolean[] seen = new boolean[g.nVertices()];
		Queue<Integer> q = new LinkedList<Integer>();
    int[] pred = new int[g.nVertices()];
    for( int i=0; i < g.nVertices(); i++ ) {
      pred[i] = -1;
    }
		q.add(s);
    pred[s] = -1;
		seen[s] = true;
		while (!q.isEmpty()) {
			int i = q.remove();
			for (Integer j : g.outEdges(i)) {
				if (!seen[j]) {
          pred[j]=i;
					q.add(j);
					seen[j] = true;
				}
			}
		}
    return pred;
	}


	protected static byte white = 0, grey = 1, black = 2;

	/** 
	 * Recursive implementation of DFS
	 * @param g
	 * @param i
	 */
	public static void dfs(Graph g, int r) {
		byte[] c = new byte[g.nVertices()];
		dfs(g, r, c);
	}

	public static void dfs(Graph g, int i, byte[] c) {
		c[i] = grey;  // currently visiting i
		for (Integer j : g.outEdges(i)) {
			if (c[j] == white) {
				c[j] = grey;
				dfs(g, j, c);
			} 
		}
		c[i] = black; // done visiting i
	}

	public static void dfsZ(Graph g, int r) {
		byte[] c = new byte[g.nVertices()];
		dfsZ(g, r, c);
	}

	public static void dfsZ(Graph g, int i, byte[] c) {
		c[i] = grey;  // currently visiting i
		for (Integer j : g.outEdges(i)) {
			if (c[j] == white) {
				System.out.println(i + " => " + j);
				c[j] = grey;
				dfsZ(g, j, c);
			} 
		}
		c[i] = black; // done visiting i
	}

	/**
	 * A non-recursive implementation of dfs
	 * Note, this doesn't give exactly the same traversal as dfs(g,r)
	 * @param g
	 * @param r
	 */
	public static void dfs2(Graph g, int r) {
		byte[] c = new byte[g.nVertices()];
		Stack<Integer> s = new Stack<Integer>();
		s.push(r);
		while (!s.isEmpty()) {
			int i = s.pop();
			if (c[i] == white) {
				c[i] = grey;
				for (int j : g.outEdges(i))
					s.push(j);
			}
		}
	}

	public static void dfs2Z(Graph g, int r) {
		byte[] c = new byte[g.nVertices()];
		Stack<Integer> s = new Stack<Integer>();
		s.push(r);
		while (!s.isEmpty()) {
			int i = s.pop();
			if (c[i] == white) {
				c[i] = grey;
				System.out.println(i);
				for (int j : g.outEdges(i))
					s.push(j);
			}
		}
	}

	public static int[] dfs2Pred(Graph g, int r) {
		byte[] c = new byte[g.nVertices()];
    int[] pred = new int[g.nVertices()];
    for( int i=0; i < g.nVertices(); i++ ) {
      pred[i] = -1;
    }
		Stack<Integer> s = new Stack<Integer>();
		s.push(r);
		while (!s.isEmpty()) {
			int i = s.pop();
			if (c[i] == white) {
				c[i] = grey;
				for (int j : g.outEdges(i)) {
          pred[j] = i;
					s.push(j);
        }
			}
		}
    return pred;
	}

  public static List<Integer> topologicalSort(Graph g) {
    List<Integer> l = new ArrayList<>();
    Queue<Integer> q = new LinkedList<Integer>();
    int[] inDegrees = new int[g.nVertices()];
    for( int i=0; i < inDegrees.length; i++ ) {
      inDegrees[i] = g.inDegree(i);
      if( inDegrees[i] == 0 ) 
        q.add(i);
    }


		boolean[] seen = new boolean[g.nVertices()];
		while (!q.isEmpty()) {
			int i = q.remove();
		  seen[i] = true;
      l.add(i);
			for (Integer j : g.outEdges(i)) {
        inDegrees[j]--;
				if (!seen[j]) {
					q.add(j);
					seen[j] = true;
				}
			}
		}
    if( l.size() != g.nVertices() )
      return null;

    return l;
  }


	protected static <T> void merge(T[] a0, T[] a1, T[] a, Comparator<T> c) {
		int i0 = 0, i1 = 0;
		for (int i = 0; i < a.length; i++) {
			if (i0 == a0.length)
				a[i] = a1[i1++];
			else if (i1 == a1.length)
				a[i] = a0[i0++];
			else if (c.compare(a0[i0], a1[i1]) < 0)
				a[i] = a0[i0++];
			else 
				a[i] = a1[i1++];
		}
	}

	/**
	 * Sort an array a whose entries contain integers in {0,...,k-1}
	 * @param a the array to sort
	 * @param k 
	 * @return an array b that contains a sorted version of a
	 */
	public static int[] countingSort(int[] a, int k) {
		int c[] = new int[k];
		for (int i = 0; i < a.length; i++)
			c[a[i]]++;
		for (int i = 1; i < k; i++)
			c[i] += c[i-1];
		int b[] = new int[a.length];
		for (int i = a.length-1; i >= 0; i--)
			b[--c[a[i]]] = a[i];
		return b;
	}

	/**
	 * Sort an array a of non-negative integers
	 * @param a
	 * @param k
	 * @return
	 */
	protected static int d = 8;
	protected static int w = 32;
	public static int[] radixSort(int[] a) {
		int[] b = null;
		for (int p = 0; p < w/d; p++) {
			int c[] = new int[1<<d];
			// the next three for loops implement counting-sort
			b = new int[a.length];
			for (int i = 0; i < a.length; i++)
				c[(a[i] >> d*p)&((1<<d)-1)]++;
			for (int i = 1; i < 1<<d; i++)
				c[i] += c[i-1];
			for (int i = a.length-1; i >= 0; i--)
				b[--c[(a[i] >> d*p)&((1<<d)-1)]] = a[i];
			a = b;
		}
		return b;
	}


	public static <T extends Comparable<T>> void quickSort(T[] a) {
		quickSort(a, new DefaultComparator<T>());
	}

	public static <T> void quickSort(T[] a, Comparator<T> c) {
		quickSort(a, 0, a.length, c);
	}

	
	public static <T extends Comparable<T>> void heapSort(T[] a) {
		BinaryHeap.sort(a, new DefaultComparator<T>());
	}

	public static <T> void heapSort(T[] a, Comparator<T> c) {
		BinaryHeap.sort(a, c);
	}

	
	protected final static <T> void  swap(T[] a, int i, int j) {
		T t = a[i];
		a[i] = a[j];
		a[j] = t;
	}
	
	/**
	 * Run quicksort on the subarray a[i],...,a[i+n-1]
	 * @param <T>
	 * @param a
	 * @param i
	 * @param n
	 * @param c
	 */
	public static <T> void quickSort(T[] a, int i, int n, Comparator<T> c) {
		if (n <= 1) return;
		T x = a[i + rand.nextInt(n)];
		int p = i-1, j = i, q = i+n;
		// a[i..p]<x,  a[p+1..q-1]??x, a[q..i+n-1]>x 
		while (j < q) {
			int comp = c.compare(a[j], x);
			if (comp < 0) {       // move to beginning of array
				swap(a, j++, ++p);
			} else if (comp > 0) {
				swap(a, j, --q);  // move to end of array
			} else {
				j++;              // keep in the middle
			}
		}
		// a[i..p]<x,  a[p+1..q-1]=x, a[q..i+n-1]>x 
		quickSort(a, i, p-i+1, c);
		quickSort(a, q, n-(q-i), c);
	}

	public static void main(String[] args) {
		long start, stop;
		int n = 1000000;
		Random rand = new Random();
		Integer[] a = new Integer[1000000];
		for (int i = 0; i < a.length; i++) 
			a[i] = rand.nextInt();
		System.out.print("Sorting " + n + " integers using quickSort...");
		start = System.nanoTime();
		quickSort(a);
		stop = System.nanoTime();
		System.out.println("done (" + (stop-start)*1e-9 + "s)");

		for (int i = 0; i < a.length; i++) 
			a[i] = rand.nextInt();
		System.out.print("Sorting " + n + " integers using mergeSort...");
		start = System.nanoTime();
		mergeSort(a);
		stop = System.nanoTime();
		System.out.println("done (" + (stop-start)*1e-9 + "s)");

		/*for (int i = 0; i < a.length; i++) 
			a[i] = rand.nextInt();
		System.out.print("Sorting " + n + " integers using heapSort...");
		start = System.nanoTime();
		heapSort(a);
		stop = System.nanoTime();
		System.out.println("done (" + (stop-start)*1e-9 + "s)"); */

		a = null;
		int[] b = new int[n];
		for (int i = 0; i < b.length; i++) 
			b[i] = rand.nextInt(1<<30);
		System.out.print("Sorting " + n + " integers using radixSort...");
		start = System.nanoTime();
		radixSort(b);
		stop = System.nanoTime();
		System.out.println("done (" + (stop-start)*1e-9 + "s)");

//		int n = 100;
//		int a[] = new int[n];
//		for (int i = 0; i < n; i++)
//			a[i] = rand.nextInt(1<<30);
//		int[] b = radixSort(a);
//		for (int x : b) {
//			System.out.print(x + ",");
//		}
//		System.out.println();
//		Arrays.sort(a);
//		for (int x : a) {
//			System.out.print(x + ",");
//		}
//		Integer[] a = new Integer[n];
//		for (int i = 0; i < n; i++)
//			a[i] = rand.nextInt(10*n);
//		Integer[] b = Arrays.copyOfRange(a, 0, n);
//		Integer[] c = Arrays.copyOfRange(b, 0, n);
//		heapSort(a);
//		mergeSort(b);
//		quickSort(c);
//		for (int i = 0; i < n; i++)
//			Utils.myassert(a[i].equals(b[i]) && b[i].equals(c[i]));
//		if (n <= 100) {
//			System.out.println(Arrays.asList(a));
//			System.out.println(Arrays.asList(b));
//			System.out.println(Arrays.asList(c));
//		}
	}
}
