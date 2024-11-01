

public class Main {
    // Part 1c, 1d, 1e
    public static void main(String[] args) {
	// write your code here
        PublicTester pt = new PublicTester();

        // Part 1c
        pt.setup();
        pt.testInsert();

        pt.setup();
        pt.testSearch();

        pt.setup();
        pt.testRemove();

        pt.setup();
        pt.testInorder();

        // Part 1d
        pt.setup();
        pt.testIteratorProperFunctionality();

        // Part 1e
        pt.setup();
        pt.testCalender();

    }
}
