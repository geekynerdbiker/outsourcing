package geekynerdbiker;
// Thank you Pat Morin for the basic skeleton of this file.

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

/**
 * @author morin
 * @author sharp
 */
public class Part2 {

    /**
     * @param x an integer parameter
     * @param r the reader to read from
     * @param w the writer to write to
     * @throws IOException, NumberFormatException
     */
    public static void doIt(int x, BufferedReader r, PrintWriter w)
            throws IOException, NumberFormatException {

        List<Integer> l = new ArrayList<>();

        for (String line = r.readLine(); line != null; line = r.readLine()) {
            if (l.size() == 0) {
                l.add(Integer.parseInt(line));
            } else {
                if (l.contains(Integer.parseInt(line))) {
                    continue;
                }
                l.add(Integer.parseInt(line));
            }
        }

        Collections.sort(l);

        List<Integer> list = new ArrayList<>();

        int sum = 0, result = 0;
        for (int i = 0; i < l.size(); i++) {
            if (Math.floorMod(i, x) == 0) {
                list.add(l.get(i));
                sum += l.get(i);
            }
        }
        int a = 24022022 / list.size(), b = Math.floorMod(24022022, list.size());
        result = Math.floorMod(a * sum, 2402);

        for (int i = 0; i < b; i++)
            result += list.get(i);

        w.println(Math.floorMod(result, 2402));
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
