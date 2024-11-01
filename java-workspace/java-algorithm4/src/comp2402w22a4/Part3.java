package comp2402w22a4;
// Thank you Pat Morin for the basic skeleton of this file.

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.util.*;
import java.util.stream.Collectors;

/**
 * @author morin
 * @author sharp
 */
public class Part3 {

    /**
     * @param x an integer parameter
     * @param r the reader to read from
     * @param w the writer to write to
     * @throws IOException, NumberFormatException
     */
    public static void doIt(int x, BufferedReader r, PrintWriter w)
            throws IOException, NumberFormatException {

        if (x == 0) {
            w.println(0);
            return;
        }

        List<Integer> l = new ArrayList<>();
        SortedSet<Integer> s = new TreeSet<>();

        int i = 0;

        for (String line = r.readLine(); line != null; line = r.readLine()) {
            l.add(Integer.parseInt(line));

            if (Math.floorMod(l.get(i), x) == 0)
                s.add(l.get(i));
            i++;
        }

        int start = 0, len = 0, max = 0;
        SortedSet<Integer> headSet = s;
        while (!headSet.isEmpty()) {
            if (len == 0) {
                start = headSet.last() / x;
                len++;
            } else {
                if (headSet.last() / x == start -1) {
                    len++;
                    start--;
                } else {
                    if (max < len) max = len;
                    len = 1;
                    start = headSet.last() / x;
                }
            }
            headSet = headSet.headSet(headSet.last());
        }
        if (max < len) max = len;
        w.println(max);
    }


    /**
     * The driver.  Open a BufferedReader and a PrintWriter, either from System.in
     * and System.out or from filenames specified on the command line, then call doIt.
     *
     * @param args
     */
    public static void main(String[] args) {
        try {
            BufferedReader r;
            PrintWriter w;
            int x;
            if (args.length == 0) {
                x = 2402;
                r = new BufferedReader(new InputStreamReader(System.in));
                w = new PrintWriter(System.out);
            } else if (args.length == 1) {
                x = Integer.parseInt(args[0]);
                r = new BufferedReader(new InputStreamReader(System.in));
                w = new PrintWriter(System.out);
            } else if (args.length == 2) {
                x = Integer.parseInt(args[0]);
                r = new BufferedReader(new FileReader(args[1]));
                w = new PrintWriter(System.out);
            } else {
                x = Integer.parseInt(args[0]);
                r = new BufferedReader(new FileReader(args[1]));
                w = new PrintWriter(new FileWriter(args[2]));
            }
            long start = System.nanoTime();
            try {
                doIt(x, r, w);
            } catch (NumberFormatException e) {
                System.out.println("Your input must be integer only");
                System.out.println(e);
            }
            w.flush();
            long stop = System.nanoTime();
            System.out.println("Execution time: " + 1e-9 * (stop - start));
        } catch (IOException e) {
            System.err.println(e);
            System.exit(-1);
        }
    }
}
