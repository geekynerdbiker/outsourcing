package comp2402w22a4;
// Thank you Pat Morin for the basic skeleton of this file.

// Students: No need to change anything in this file.
// NOTE(Students): Do not change anything in this file.
// Needed for Algorithms.java

import java.util.Comparator;

public class DefaultComparator<T> implements Comparator<T> {
	@SuppressWarnings("unchecked")
	public int compare(T a, T b) {
		return ((Comparable<T>)a).compareTo(b);
	}
}
