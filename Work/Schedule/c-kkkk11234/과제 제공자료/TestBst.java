import java.io.*;
import java.lang.management.*;

class TestBst {
    public static ThreadMXBean TMB;

    public static void main(String[] args) {
        long cputime;
        TMB = ManagementFactory.getThreadMXBean();
        if (!TMB.isThreadCpuTimeSupported()) {
            System.out.println("ThreadCpuTime is not supported.");
            System.exit(0);
        }

        String path =  "./program2/public/";//"";//
        String fileName = "1000words.txt";
        String keyFileName = "2000words.txt";

        // construct bsts
        BST nobst = new BST();
        buildBST(nobst, path + fileName);
        BST obst = new BST();
        buildBST(obst, path + fileName);
        AVL avl = new AVL();
        buildBST(avl, path + fileName);

        // (2) AVL test
        System.out.println("Sum of Weighted Path Lengths (AVL): " + avl.sumWeightedPath());
        avl.resetCounters();
        probeBST(avl, path + keyFileName);

        // (3) Transform another plain BST into an NOBST and repeat probing.
        cputime = TMB.getCurrentThreadCpuTime();
        nobst.nobst();
        cputime = TMB.getCurrentThreadCpuTime() - cputime;
        System.out.println("CPU time to convert to an NOBST: " + (cputime / 1000000) + " millisec");
        System.out.println("Sum of Weighted Path Lengths (NOBST): " + nobst.sumWeightedPath());

        nobst.resetCounters();
        probeBST(nobst, path + keyFileName);

        // (3) Transform another plain BST into an NOBST and repeat probing.
        cputime = TMB.getCurrentThreadCpuTime();
        obst.obst();
        cputime = TMB.getCurrentThreadCpuTime() - cputime;
        System.out.println("CPU time to convert to an OBST: " + (cputime / 1000000) + " millisec");
        System.out.println("Sum of Weighted Path Lengths (OBST): " + obst.sumWeightedPath());

        obst.resetCounters();
        probeBST(obst, path + keyFileName);
    }

    public static void buildBST(BST bst, String input) {
        TextInputStream sfs = new TextInputStream(input);

        long cputime = TMB.getCurrentThreadCpuTime();
        while (sfs.ready())
            bst.insert(sfs.readWord());
        cputime = TMB.getCurrentThreadCpuTime() - cputime;

        // bst.print();
        String bstType = (bst instanceof AVL) ? "AVL" : "BST";
        System.out.println("CPU time to build a(n) " + bstType + ": " + (cputime / 1000000) + " millisec");
    }

    public static void probeBST(BST bst, String keys) {
        TextInputStream qfs = new TextInputStream(keys);
        int notfound = 0;

        long cputime = TMB.getCurrentThreadCpuTime();
        while (qfs.ready()) {
            String queryWord = qfs.readWord();
            if (bst.find(queryWord) == false) {
                System.out.println("The word `" + queryWord + "' not found.");
                notfound++;
            }
        }
        cputime = TMB.getCurrentThreadCpuTime() - cputime;

        // bst.print();
        String bstType = "BST";
        if (bst instanceof AVL)
            bstType = "AVL";
        else if (bst.NOBSTified == true)
            bstType = "NOBST";
        else if (bst.OBSTified == true)
            bstType = "OBST";

        System.out.println("Total number of node accesses (" + bstType + "): " + bst.sumProbes() + " (failed searches: "
                + notfound + ")");
        System.out.println("CPU time for searching keys (" + bstType + "): " + (cputime / 1000000) + " millisec");
    }
}