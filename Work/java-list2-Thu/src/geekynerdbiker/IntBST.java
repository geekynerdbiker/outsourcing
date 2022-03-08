package geekynerdbiker;
// Thank you Pat Morin for the basic skeleton of this file.


import java.util.*;

/**
 * This class implements the MyList interface as a single array a.
 * Elements are stored at positions a[0],...,a[size()-1].
 * Doubling/halving is used to resize the array a when necessary.
 *
 * @param <T> the type of objects stored in the List
 * @author morin
 * @author sharp
 */
public class IntBST extends BinarySearchTree<BinarySearchTree.BSTEndNode<Integer>,Integer> {

    /**
     * Constructor
     */
    public IntBST(BinarySearchTree.BSTEndNode<Integer> sampleNode, BinarySearchTree.BSTEndNode<Integer> nil) {
        super(sampleNode);
        this.c = new DefaultComparator<Integer>();
    }

    public IntBST(BinarySearchTree.BSTEndNode<Integer> sampleNode) {
        super(sampleNode);
        this.c = new DefaultComparator<Integer>();
    }

    public int numDescendantsMod(int y) {
        // TODO(students): Your code goes here.
        int count = 0;

        BSTEndNode<Integer> sNode = this.firstNode();

        while (sNode != null) {
            if(Math.floorMod(sNode.x, y) == 0 )
                count++;
            sNode = this.nextNode(sNode);
        }

        return count;
    }


    public void sum(IntBST other) {
        // TODO(student): Your solution goes here.
        IntBST rst = emptyBST();

        BSTEndNode<Integer> sNode = this.firstNode();
        BSTEndNode<Integer> otherNode = other.firstNode();

        while (sNode != null) {
            rst.add(sNode.x + otherNode.x);
            int k = sNode.x;
            sNode = this.nextNode(sNode);
            this.remove(k);
            otherNode = other.nextNode(otherNode);
            if(otherNode == null)
                otherNode = other.firstNode();
        }

        BSTEndNode<Integer> curr = rst.firstNode();
        while( curr != null) {
            this.add(curr.x);
            curr = rst.nextNode(curr);
        }
    }


    public static IntBST emptyBST() {
        return randomBST(0);
    }


    // Constructs and returns a random BST on <= n elements, by
    // randomly generating n values between 0 and 3n, and inserting
    // them into the tree. If there are duplicate random values
    // then there will be < n elements in the tree.
    public static IntBST randomBST(int n) {
        BSTEndNode<Integer> sample = new BSTEndNode<Integer>();
        IntBST t = new IntBST(sample);
        Random rand = new Random();
        for( int i=0; i < n; i++ ) {
            int value = rand.nextInt(3*n);
            t.add(value);
        }

        return t;
    }



    // This main method is provided for you for testing purposes.
    // You will want to add to this for local testing.
    public static void main(String[] args) {
        // These are just examples of local tests, they are not sufficient.
        // One of your tasks is to add and modify these tests to test
        // your code more thoroughly here before submitting to the server.
        int n = 10;
        IntBST bst = randomBST(n);

        // Tests for numDescendantsMod
        // This is just one example of a test for numDescendantsMod. Add more!
        System.out.println( bst );
        int t = bst.numDescendantsMod(2);
        System.out.println( t );

       // Tests for Sum
        bst = emptyBST();
        bst.add(1);
        bst.add(3);
        bst.add(6);


        IntBST other = emptyBST();
        other.add(1);
        other.add(3);

        System.out.println( bst );
        System.out.println( other );
        bst.sum(other);
        System.out.println( bst );
        System.out.println(bst.numDescendantsMod(3));

        testSum(10, 10);
        testSum(10, 3);
        testSum(10, 5);
    }

    // Creates a BST of size <= n and one of size <=k.
    // Then it calls sum on the first, passing in the second.
    public static void testSum(int n, int k) {
        System.out.println("Test Sum------");
        IntBST bst = IntBST.randomBST(n);
        IntBST other = IntBST.randomBST(k);

        bst.sum(other);

        System.out.println("Done Test Sum------");
    }
}
