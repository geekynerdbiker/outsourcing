package geekynerdbiker;
// Thank you Pat Morin for the basic skeleton of this file.

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.List;


public class Part4 {

    /**
     * Your code goes here - see Part0 for an example
     *
     * @param x an integer parameter
     * @param r the reader to read from
     * @param w the writer to write to
     * @throws IOException, NumberFormatException
     */
    public static void doIt(int x, BufferedReader r, PrintWriter w) throws IOException {
        //TODO(student): Your code goes here.
        List<Integer> l = new ArrayList<>();

        int sum = 0;

        for (String line = r.readLine(); line != null; line = r.readLine()) {
            l.add(Integer.parseInt(line));
        }

        int k = 0;
        List<Integer> chain = new ArrayList<>();
        for (int i = 0; i < x; i++) {
            if (i == 0) k = l.get(0);
            else k = l.get(Math.floorMod(k, l.size()));

            int min = Integer.MAX_VALUE;
            for (int j = 0; j < chain.size(); j++) {
                if (chain.get(j) < min) {
                    min = chain.get(j);
                }
            }

            if (Math.floorMod(k, 5) == 0)
                chain.add(k);

            if (min != Integer.MAX_VALUE) {
                sum += min;

                if (Math.floorMod(k, 24) == 0) {
                    int minChain = Integer.MAX_VALUE;
                    int minChainIndex = 0;
                    for (int j = 0; j < chain.size(); j++) {
                        if (minChain > chain.get(j)) {
                            minChain = chain.get(j);
                            minChainIndex = j;
                        }
                    }
                    chain.remove(minChainIndex);
                }
            }
        }

        w.println(Math.floorMod(sum, 2402));
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
