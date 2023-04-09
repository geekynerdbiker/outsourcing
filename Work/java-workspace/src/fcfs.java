import java.io.*;
import java.util.*;

public class fcfs {
    public static void main(String[] args) throws IOException {
        File input_fp = new File("1.inp");
        File output_fp = new File("1.out");

        FileReader input;
        FileWriter output;

        BufferedReader br;
        BufferedWriter bw;


        try {
            input = new FileReader(input_fp);
            output = new FileWriter(output_fp);

            br = new BufferedReader(input);
            String line = "";

            int n = Integer.parseInt(br.readLine());
            int[][] data = new int[n][100];
            int[] turnaround = new int[n];
            int[] io = new int[n];

            Vector<Integer> sorter = new Vector<>();
            Queue<Integer> pq = new LinkedList<>();

            int[] result = new int[n];


            for (int i = 0; i < n; i++) {
                for (int j = 0; j < 100; j++)
                    data[i][j] = -1;
                io[i] = 0;
            }


            int v_idx = 0;
            while ((line = br.readLine()) != null) {
                StringTokenizer st = new StringTokenizer(line, " ");

                while (st.hasMoreTokens()) {
                    int idx = 0;

                    while (true) {
                        int k = Integer.parseInt(st.nextToken());
                        data[v_idx][idx++] = k;
                        if (k == -1) {
                            result[v_idx++] = idx;
                            break;
                        }

                    }
                }
            }

            int iter = 0;
            for (int i = 0; i < n; i++) {
                for (int j = 0; data[i][j] != -1; j += 2) {
                    iter++;
                }
            }

            int curr = 0, cpu = 0, tmp = 0, idle = 0;

            for (int i = 0; i < n; i++) {
                if (curr == data[i][0]) {
                    pq.add(i);
                    data[i][0] = -1;
                }
            }

            while (pq.isEmpty()) {
                curr++;
                idle++;
                for (int i = 0; i < n; i++) {
                    if (curr == data[i][0]) {
                        pq.add(i);
                        data[i][0] = -1;
                    }
                }

            }

            while (iter != 0) {
                while (true) {
                    if (!pq.isEmpty()) {
                        tmp = pq.poll();
                        break;
                    } else {
                        curr++;
                        idle++;
                        for (int i = 0; i < n; i++) {
                            io[i]--;
                            if (io[i] == 0) {
                                for (int j = 0; j < 100; j++) {
                                    if (data[i][j] != -1) {
                                        sorter.add(i);
                                        break;
                                    }
                                }
                            }
                            if (curr == data[i][0]) {
                                sorter.add(i);
                                data[i][0] = -1;
                            }
                        }
                        if (sorter.size() > 1) {
                            Collections.sort(sorter);
                        }
                        for (Integer integer : sorter) {
                            pq.add(integer);
                        }
                        sorter.clear();
                    }
                }
                int i = 0;
                for (i = 1; ; i += 2) {
                    if (data[tmp][i] != -1) {
                        cpu = data[tmp][i];
                        data[tmp][i] = -1;
                        if (result[tmp] % 2 == 0) {
                            turnaround[tmp] = curr + cpu;
                        }
                        break;
                    }
                }

                while (true) {
                    if (cpu == 0) {
                        io[tmp] = data[tmp][i + 1];
                        data[tmp][i + 1] = -1;
                        if (result[tmp] % 2 != 0) {
                            turnaround[tmp] = curr + io[tmp] + 1;
                        } else
                            turnaround[tmp] += io[tmp];
                        break;
                    }

                    cpu--;
                    curr++;
                    for (int j = 0; j < n; j++) {
                        io[j]--;
                        if (curr == data[j][0]) {
                            pq.add(j);
                            data[j][0] = -1;
                        } else if (io[j] == 0) {
                            for (int k = 0; k < 100; k++) {
                                if (data[j][k] != -1) {
                                    pq.add(j);
                                    break;
                                }
                            }

                        }
                    }
                }
                iter--;
            }

            bw = new BufferedWriter(output);

            bw.write(idle + "\n");
            for (int i = 0; i < n; i++) {
                bw.write(turnaround[i] + "\n");
            }

            bw.flush();
            br.close();
            bw.close();
            input.close();
            output.close();

        } catch (FileNotFoundException e) {
            throw new RuntimeException(e);
        }
    }
}

