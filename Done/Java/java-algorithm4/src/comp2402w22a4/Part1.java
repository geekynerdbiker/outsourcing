package comp2402w22a4;
// Thank you Pat Morin for the basic skeleton of this file.

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.List;
import java.util.SortedSet;
import java.util.TreeSet;

/**
 * @author morin
 * @author sharp
 */
public class Part1 {

    /**
     * @param x an integer parameter
     * @param r the reader to read from
     * @param w the writer to write to
     * @throws IOException, NumberFormatException
     */
    public static void doIt(int x, BufferedReader r, PrintWriter w)
            throws IOException, NumberFormatException {

        List<Integer> l = new ArrayList<>();
        SortedSet<Integer> s = new TreeSet<>();

        int i = 0, j = 0;
        int curr = 0, sum = 0;

        for (String line = r.readLine(); line != null; line = r.readLine()) {
            l.add(Integer.parseInt(line));

            if (j == 0 && x == 1) {
                w.println(Math.floorMod(l.get(0), 2402));
                return;
            } else if (j == curr) {
                while ((i < x) && (curr < l.size())) {
                    curr = l.get(curr);
                    if (s.isEmpty()) {
                        s.add(curr);
                        sum = Math.floorMod(sum + curr, 2402);
                    }
                    else {
                        int beforeAdd = s.size();
                        s.add(curr);
                        int afterAdd = s.size();
                        if(beforeAdd < afterAdd)
                            sum = Math.floorMod(sum + curr, 2402);
                    }
                    i++;
                }
                if (i == x) {
                    w.println(sum);
                    return;
                }
            }
            j++;
        }

        for(; i < x; i++ ) {
            curr = l.get(curr % l.size() );
            if (s.isEmpty()) {
                s.add(curr);
                sum = Math.floorMod(sum + curr, 2402);
            }
            else {
                int beforeAdd = s.size();
                s.add(curr);
                int afterAdd = s.size();
                if(beforeAdd != afterAdd)
                    sum = Math.floorMod(sum + curr, 2402);
            }
        }
        w.println(sum);
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
