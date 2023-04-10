import java.io.*;
import java.util.StringTokenizer;

public class fcfs {

    static void print_FCFS(int n, int WT[], FileWriter output) throws IOException {
        BufferedWriter bw = new BufferedWriter(output);

        int result = 0;
        for (int i = 0; i < n; i++) {
            bw.write(Integer.toString(WT[i]) + "\n");
        }

        bw.flush();
        bw.close();
    }

    static void FCFS(int n, int AT[], int BT[], int WT[]) {
        int time = 0, turn = 0, temp = 0;
        for (int i = 0; i < n; i++) {
            time = time + BT[i];
            if (temp - AT[i] > 0) {
                turn = time - AT[i];
                WT[i] = turn - BT[i];
            } else if (temp - AT[i] < 0) {
                time = time + (AT[i] - temp);
                WT[i] = 0;
            }
            temp = time;
        }
    }

    static void bubble_sort(int n, int PN[], int AT[], int BT[]) {
        int temp, temp2, temp3;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n - 1; j++) {
                if (AT[j] > AT[j + 1]) {
                    temp = AT[j];
                    AT[j] = AT[j + 1];
                    AT[j + 1] = temp;

                    temp2 = BT[j];
                    BT[j] = BT[j + 1];
                    BT[j + 1] = temp2;

                    temp3 = PN[j];
                    PN[j] = PN[j + 1];
                    PN[j + 1] = temp3;
                } else if (PN[j] > PN[j + 1] && AT[j] == AT[j + 1]) {
                    temp = AT[j];
                    AT[j] = AT[j + 1];
                    AT[j + 1] = temp;

                    temp2 = BT[j];
                    BT[j] = BT[j + 1];
                    BT[j + 1] = temp2;

                    temp3 = PN[j];
                    PN[j] = PN[j + 1];
                    PN[j + 1] = temp3;
                }
            }
        }
    }

    public static void main(String[] args) throws IOException {
        File input_fp = new File("fcfs.inp");
        File output_fp = new File("fcfs.out");

        FileReader input;
        FileWriter output;

        BufferedReader br;

        try {
            input = new FileReader(input_fp);
            output = new FileWriter(output_fp);

            br = new BufferedReader(input);
            String line = "";

            int n = Integer.parseInt(br.readLine());
            int P_num = 0;
            int at = 0, bt = 0;
            int[] PN = new int[n];
            int[] AT = new int[100];
            int[] BT = new int[100];
            int[] WT = new int[100];

            while ((line = br.readLine()) != null) {
                StringTokenizer st = new StringTokenizer(line, " ");

                while (st.hasMoreTokens()) {
                    P_num = Integer.parseInt(st.nextToken());
                    PN[P_num] = P_num;
                    AT[P_num] = Integer.parseInt(st.nextToken());
                    BT[P_num] = Integer.parseInt(st.nextToken());
                }
            }

            bubble_sort(n, PN, AT, BT);
            FCFS(n, AT, BT, WT);
            print_FCFS(n, WT, output);

            br.close();
            input.close();
            output.close();

        } catch (
                FileNotFoundException e) {
            throw new RuntimeException(e);
        }
    }
}

