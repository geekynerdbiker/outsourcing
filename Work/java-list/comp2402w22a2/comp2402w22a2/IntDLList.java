package comp2402w22a2;
// Thank you Pat Morin for the basic skeleton of this file.


import java.util.AbstractList;
import java.util.Collection;
import java.util.ListIterator;

/**
 * This class implements the MyList interface as a single array a.
 * Elements are stored at positions a[0],...,a[size()-1].
 * Doubling/halving is used to resize the array a when necessary.
 *
 * @param <T> the type of objects stored in the List
 * @author morin
 * @author sharp
 */
public class IntDLList extends DLList<Integer> {

    /**
     * Constructor
     */
    @SuppressWarnings("unchecked")
    public IntDLList() {
        super();
    }


    public void sum(IntDLList other) {
    }


    public void intervalInsert(IntDLList other) {

    }




    // This main method is provided for you for testing purposes.
    // You will want to add to this for local testing.
    public static void main(String[] args) {
        // These tests are not at all sufficient. They are just examples.
        testSum(10, 10);
        testSum(10, 3);
        testSum(10, 5);
        testIntervalInsert(10, 2);
        testIntervalInsert(10, 4);
        testIntervalInsert(10, 9);
        testIntervalInsert(10, 11);

    }

    // Creates a IntDLList of size n and one of size k.
    // Then it calls sum on the first, passing in the second.
    public static void testSum(int n, int k) {
        System.out.println("Test Sum------");
        IntDLList mal = new IntDLList();
        for (int i = 0; i < n; i++) {
            mal.add(i, mal.size());
        }
        System.out.println(mal);
        IntDLList other = new IntDLList();
        for (int i = 0; i < k; i++) {
            other.add(i, other.size());
        }
        System.out.println(other);
        mal.sum(other);
        System.out.println(mal);
        System.out.println("Done Test Sum------");
    }

    // Creates a MyIntArrayStack of size n and of size k.
    // Calls intervalInsert on the first, passing in the second.
    public static void testIntervalInsert(int n, int k) {
        System.out.println("Test IntervalInsert------");
        IntDLList mal = new IntDLList();
        for (int i = 0; i < n; i++) {
            mal.add(i, mal.size());
        }
        System.out.println(mal);
        IntDLList other = new IntDLList();
        for (int i = 0; i < k; i++) {
            other.add(i, other.size()+1);
        }
        System.out.println(other);
        mal.intervalInsert(other);
        System.out.println(mal);
        System.out.println("Done Test IntervalInsert------");
    }


}
