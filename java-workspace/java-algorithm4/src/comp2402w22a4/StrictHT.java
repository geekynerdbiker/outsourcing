package comp2402w22a4;
// Thank you Pat Morin for the basic skeleton of this file.

// NOTE(Students): Do not change anything in this file.

import java.util.*;

/**
 * This class implements hashing with chaining using multiplicative hashing
 * with a hashtable that does not grow its dimension / number of buckets.
 * @author morin
 * @author sharp
 *
 * @param <T>
 */
public class StrictHT<T> extends AbstractCollection<T> {

	/**
	 * The hash table
	 */
	Collection<T>[] t; // Do not change this.

	/**
	 * The "dimension" of the table (table.length = 2^d)
	 * In the "strict" HT this cannot change. In a normal
	 * HT this would increase as n increases.
	 * You should not change d for assignment 4. If you do,
	 * tests will fail.
	 */
	static final int d=12; // Do not change this.

	/**
	 * The number of elements in the hash table
	 */
	int n;
		
	/**
	 * The multiplier
	 */
	int z;

	/**
	 * The number of bits in an int
	 */
	protected static final int w = 32;
	
	/**
	 * Create a new empty hash table
	 */
	public StrictHT() {
		t = allocTable(1<<d);
		Random r = new Random();
		z = r.nextInt() | 1;     // is a random odd integer
	}
	
	/**
	 * Allocate and initialize a new empty table
	 * @param s
	 * @return
	 */
	@SuppressWarnings({"unchecked"})
	protected Collection<T>[] allocTable(int s) {
		Collection<T>[] tab = new ArrayList[s];
		for (int i = 0; i < s; i++) {
			tab[i] = new ArrayList<T>();
		}
		return tab;
	}

	/**
	 * Return the number of elements stored in this hash table
	 */
	public final int size() {
		return n;
	}

	/**
	 * This is not usually a public method, but it's public for
	 * testing purposes.
	 * @return the number of buckets in our hashtable.
	 */
	public final int numBuckets() {
		return t.length;
	}

	/**
	 * Compute the table location for object x
	 * @param x
	 * @return ((x.hashCode() * z) mod 2^w) div 2^(w-d)
	 */
	protected final int hash(Object x) {
		return (z * x.hashCode()) >>> (w-d);
	}
	
	/**
	 * Add the element x to the hashtable if it is not
	 * already present
	 */
	public boolean add(T x) {
		if( t[hash(x)].contains(x) ) {
			return false;
		}
		t[hash(x)].add(x);
		n++;
		return true;
	}

	/**
	 *
	 * @param x The element to remove
	 * @return  The element x if it was removed.
	 */
	@SuppressWarnings({"unchecked"})
	public T removeOne(Object x) {
		if( t[hash(x)].remove(x) ) {
			n--;
			return (T)x;
		}
		return null;
	}

	public boolean remove(Object x) {
		return removeOne(x) != null;
	}

	/**
	 * Get the copy of x stored in this table.
	 * @param x - the item to get 
	 * @return - the element x if x is in the HT.
	 *
	 * Note that this is slightly different than our usual HT implementation
	 * which *usually* returns the y in the HT s.t. y.equals(x).
	 */
	@SuppressWarnings({"unchecked"})
	public T find(Object x) {
		if( t[hash(x)].contains(x) ) {
			return (T)x;
		}
		return null;
	}

	public Iterator<T> iterator() {
		class IT implements Iterator<T> {
			int i;
			Iterator<T> it;
			int ilast;
			Iterator<T> itLast;
			IT() {
				i = 0;
				it = t[i].iterator();
				itLast = t[i].iterator();
				while (i < t.length && !it.hasNext()) {
					i++;
					if (i < t.length) {
						it = t[i].iterator();
					}
				}
			}
			protected void jumpToNext() {
				while (i < t.length && !it.hasNext()) {
					i++;
					if( i < t.length ) {
						it = t[i].iterator();
					}
				}
			}
			public boolean hasNext() {
				return i < t.length;
			}
			public T next() {
				ilast = i;
				itLast = it;
				T x =  it.next();
				jumpToNext();
				return x;
			}
			public void remove() {
				itLast.remove();
				n--;
			}		
		}
		return new IT();
	}

	public final boolean checkT() {
		// Check that t (and not some other structure) contains n elements.
		int total = 0;
		for( Collection c : t) {
			total += c.size();
		}
		return (total == n);
	}
	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// If you want to run the program with assertions on,
		// use the -ea runtime parameter, e.g.
		// java -ea comp2402w22a4.StrictHT
		int n = 10;
		StrictHT<Integer> t = new StrictHT<Integer>();
		System.out.println("Adding " + n + " integers to StrictHT...");
		long start = System.nanoTime();
		for (int i = 0; i < n; i++) {
			t.add(i*2);
			assert(t.numBuckets() == 4096);
		}
		System.out.println( "Iterating through " + n + " elements...");
		int numIt = 0;
		for( Integer el : t ) {
			numIt++;
		}
		assert(numIt == n);
		System.out.println( "Iterating and removing all " + n + " elements..." );
		Iterator<Integer> it = t.iterator();
		while( it.hasNext() ) {
			it.next();
			it.remove();
			assert(t.numBuckets() == 4096);
		}
		assert(t.size() == 0);
		assert(t.numBuckets() == 4096);
		n = 3000000;
		System.out.println("Adding " + n + " integers to StrictHT...");
		for (int i = 0; i < n; i++) {
			t.add(i*2);
			assert(t.numBuckets() == 4096);
		}
		assert(t.size()==n);
		System.out.println( "finding the " + n + " elements..." );
		for (int i = 0; i < 2*n; i++) {
			Integer x = t.find(i);
			if (i % 2 == 0) {
				assert(x.intValue() == i);
			} else {
				assert(x == null);
			}
		}
		long stop = System.nanoTime();
		System.out.println("done (" + (stop-start)*1e-9 + "s)");
		assert(t.checkT());
		assert(t.numBuckets() == 4096);
	}

}
