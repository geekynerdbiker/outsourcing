import java.util.*;
import static org.junit.Assert.*;
import org.junit.*;


public class PublicTester {

    MyBST<Integer, Integer> completeTree;

    // 
    /**
     * The setup method create a complete tree with height three
     * The tree has following structure and will be used as testing purpose
     *           4
     *         /  \
     *       2     6
     *     /  |   /
     *    1   3  5
     */
    @Before
    public void setup(){

        MyBST.MyBSTNode<Integer, Integer> root = 
            new MyBST.MyBSTNode(4, 1, null);
        MyBST.MyBSTNode<Integer, Integer> two = 
            new MyBST.MyBSTNode(2, 1, root);
        MyBST.MyBSTNode<Integer, Integer> six = 
            new MyBST.MyBSTNode(6, 1, root);
        MyBST.MyBSTNode<Integer, Integer> one = 
            new MyBST.MyBSTNode(1, 2, two);
        MyBST.MyBSTNode<Integer, Integer> three = 
            new MyBST.MyBSTNode(3, 30, two);
        MyBST.MyBSTNode<Integer, Integer> five = 
            new MyBST.MyBSTNode(5, 50, six);

        this.completeTree = new MyBST();
        this.completeTree.root = root;
        root.setLeft(two);
        root.setRight(six);
        two.setLeft(one);
        two.setRight(three);
        six.setLeft(five);
        this.completeTree.size = 6;
    }

    // ====== MyBSTNode class ======

    // Test predecessor() on a non-leaf node
    @Test
    public void testNodePredecessorNonLeafNode() {
        MyBST.MyBSTNode<Integer, Integer> root = completeTree.root;
        assertSame(root.getLeft().getRight(), root.predecessor());

    }
    // Test predecessor() on a leaf node
    @Test
    public void testNodePredecessorLeafNode() {
        MyBST.MyBSTNode<Integer, Integer> root = completeTree.root; 
        assertSame(root, root.getRight().getLeft().predecessor());
    }

    // ====== MyBST class ======

    // Test insert method
    @Test
    public void testInsert(){
        MyBST.MyBSTNode<Integer, Integer> root = completeTree.root; 
        completeTree.insert(10, 1);
        assertEquals((Integer)10, root.getRight().getRight().getKey());
    }

    // Test search method
    @Test
    public void testSearch(){
        assertEquals((Integer)30, completeTree.search(3));
        assertEquals(null, completeTree.search(10));
    }

    // Test remove method
    @Test
    public void testRemove(){
        MyBST.MyBSTNode<Integer, Integer> root = completeTree.root; 
        assertEquals((Integer)30, completeTree.remove(3));
        assertNull(root.getLeft().getRight());
        assertEquals((Integer)1, completeTree.remove(6));
        assertEquals((Integer)5, root.getRight().getKey());
    }

    // Test inorder method
    @Test
    public void testInorder(){
        MyBST.MyBSTNode<Integer, Integer> root = completeTree.root; 
        ArrayList<MyBST.MyBSTNode<Integer, Integer>> expectedRes 
            = new ArrayList<>();
        expectedRes.add(root.getLeft().getLeft());
        expectedRes.add(root.getLeft());
        expectedRes.add(root.getLeft().getRight());
        expectedRes.add(root);
        expectedRes.add(root.getRight().getLeft());
        expectedRes.add(root.getRight());
        ArrayList<MyBST.MyBSTNode<Integer, Integer>> actualRes 
            = completeTree.inorder();
        for (int i=0; i<expectedRes.size(); i++){
            assertSame(expectedRes.get(i), actualRes.get(i));
        }
    }

    // ====== MyBSTIterator class ======

    // Test the initial state of iterator and the function of 
    // properly move to the next node
    @Test
    public void testIteratorProperFunctionality(){
        // because MyBSTIterator extends MyBST, so it has the root instance
        // variable. Assign this variable from completeTree to the iterator
        MyBSTIterator<Integer, Integer> iterTree = new MyBSTIterator();
        iterTree.root = completeTree.root;

        // Initialize the BST value iterator that start from root
        MyBSTIterator<Integer, Integer>.MyBSTValueIterator vi = 
            iterTree.new MyBSTValueIterator(iterTree.root);

        // next should points to the root
        assertSame(iterTree.root, vi.next);
        //lastVisited should be null
        assertNull(vi.lastVisited);
        // Moving forward, nextNode should return root
        assertSame(completeTree.root, vi.nextNode());
        // next should be forwarded to the successor of root
        assertSame(completeTree.root.successor(), vi.next);
        // root become the last visited node
        assertSame(completeTree.root, vi.lastVisited);
    }

    // ====== Calender class ======

    // Test the basic functionality of MyCalendar calss
    @Test
    public void testCalender(){
        MyCalendar cal = new MyCalendar();
        // check MyTreeMap is initialized
        assertNotNull(cal.getCalendar());
        // Book an event on a calender with no event
        assertTrue(cal.book(10, 20));
        // Book a conflicting event
        assertFalse(cal.book(5, 15));
        assertFalse(cal.book(15, 25));
        //events can be consecutive
        assertTrue(cal.book(0, 10));
        assertTrue(cal.book(20, 30));
    }
}
