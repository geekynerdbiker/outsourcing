package geekynerdbiker;
// Thank you Pat Morin for the basic skeleton of this file.

// Students: No need to change anything in this file.

import java.util.Comparator;

public class DefaultComparator<T> implements Comparator<T> {
	@SuppressWarnings("unchecked")
	public int compare(T a, T b) {
		return ((Comparable<T>)a).compareTo(b);
	}
}
