package geekynerdbiker;

import java.util.Scanner;
import java.util.StringTokenizer;

public class Main {
    public static void main(String[] args) {
        Scanner s = new Scanner(System.in);

        StringTokenizer st;
        int p = Integer.parseInt(s.nextLine());
        int CPURest = 0, endTime = 0;
        for (int i = 0; i < p; i++) {
            int k = 0;
            st = new StringTokenizer(s.nextLine(), " ");
            while (st.hasMoreTokens()) {
                int n = Integer.parseInt(st.nextToken());
                if (n == -1) {
                    k = 0;
                    continue;
                }
                if (k % 2 == 1) CPURest += n;
                endTime += n;
                k++;
            }
        }
        System.out.print(CPURest + " " + endTime);
    }
}
