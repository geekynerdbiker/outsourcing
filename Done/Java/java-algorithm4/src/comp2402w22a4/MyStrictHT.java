package comp2402w22a4;
// Thank you Pat Morin for the basic skeleton of this file.

import java.util.*;

/**
 * This class implements hashing with chaining using multiplicative hashing
 * with a hashtable that does not grow its dimension / number of buckets.
 * @author morin
 * @author sharp
 *
 * @param <T>
 */
public class MyStrictHT<T> extends StrictHT<T> {

	/**
	 * Create a new empty hash table
	 */
	public MyStrictHT() {
		super();
	}

	// TODO(Student): override any (non-final) methods from StrictHT as you
	// see fit in order to improve the runtime of the add, remove, and find
	// methods.
	// You can override by copying the code over here and then making
	// appropriate modifications.
	// Do not change the StrictHT file at all -- make all of your modifications
	// in this file!


	public static void main(String[] args) {
		// If you want to run the program with assertions on,
		// use the -ea runtime parameter, e.g.
		// java -ea comp2402w22a4.MyStrictHT
		int n = 10;
		MyStrictHT<Integer> t = new MyStrictHT<Integer>();
		System.out.println("Adding " + n + " integers to MyStrictHT...");
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
		System.out.println("Adding " + n + " integers to MyStrictHT...");
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
