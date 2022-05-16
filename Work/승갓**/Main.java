import java.io.*;
import java.util.*;

public class Main {
//    private static BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
//    private static BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));

    public static void main(String[] args) {
//        //p1
//        int result = solution(new int[]{4, 4, 3}, 2, 1);
//        //p3
//        result = solution(new int[][]{{3200, 4}, {2300, 2}, {1100, 1}, {4200, 6}}, new String[]{"2022/05/02", "2022/05/01", "2022/05/07", "2022/05/05", "2022/05/08", "2022/05/13~2022/05/15", "2022/05/14~2022/05/17", "2022/05/01~2022/05/02", "2022/05/16"});
//        System.out.print(result);

//        String[] result = solution(new String[]{"0001 3 95", "0001 5 90", "0001 5 100", "0002 3 95", "0001 7 80", "0001 8 80", "0001 10 90", "0002 10 90", "0002 7 80", "0002 8 80", "0002 5 100", "0003 99 90"});
        String[] result = solution(new String[]{"1901 1 100", "1901 2 100", "1901 4 100", "1901 7 100", "1901 8 100", "1902 2 100", "1902 1 100", "1902 7 100", "1902 4 100", "1902 8 100", "1903 8 100", "1903 7 100", "1903 4 100", "1903 2 100", "1903 1 100", "1101 1 95", "1101 2 100", "1101 4 100", "1101 7 100", "1101 9 100", "1102 1 95", "1102 2 100", "1102 4 100", "1102 7 100", "1102 9 100"});
        for (int i = 0; i < result.length; i++)
            System.out.print(result[i]);
        //        String[] result = solution(new int[][]{{1, 1}, {2, 1}, {1, 2}, {3, 3}, {6, 4}, {3, 1}, {3, 3}, {3, 3}, {3, 4}, {2, 1}});
    }

//     1
    public static int solution(int[] v, int a, int b) {
        int answer = 0;

        while (true) {
            Arrays.sort(v);
            if (v[0] <= 0) break;
            for (int i = 0; i < v.length - 1; i++)
                v[i] -= b;
            v[v.length - 1] -= a;
            answer++;
        }
        return v[0] == 0 ? answer : answer - 1;
    }

    //    2
    static class Status implements Comparable<Status> {
        String person;
        int number;
        int score;

        Status(String a, int b, int c) {
            person = a;
            number = b;
            score = c;
        }

        @Override
        public int compareTo(Status o) {
            if (person.compareTo(o.person) > 0) return 1;
            else if (person.compareTo(o.person) == 0) return 0;
            else return -1;
        }
    }

    public static String[] solution(String[] logs) {
        String[] answer;
        StringTokenizer st;
        List<Status> data = new ArrayList<>();

        List<String> result = new ArrayList<>();
        for (int i = 0; i < logs.length; i++) {
            st = new StringTokenizer(logs[i]);
            data.add(new Status((st.nextToken(" ")), Integer.parseInt(st.nextToken(" ")), Integer.parseInt(st.nextToken(" "))));
        }

        int count = 0;

        Collections.sort(data);

        String p1 = null, p2;
        for (int i = 0; i < data.size() - 1; i++) {
            if (p1 != null && p1.compareTo(data.get(i).person) != 0)
                count = 0;
            p1 = data.get(i).person;
            for (int j = i; j < data.size(); j++) {
                while (data.get(i).person.compareTo(data.get(j).person) == 0 && j < data.size() - 1) j++;

                p2 = data.get(j).person;
                if (data.get(i).number == data.get(j).number && data.get(i).score == data.get(j).score)
                    count++;
                if (count >= 5) {
                    result.add(p1);
                    result.add(p2);
                    break;
                }
                if (j + 1 < data.size())
                    if (p2.compareTo(data.get(j + 1).person) != 0)
                        break;
            }
        }


        answer = new String[result.size()];
        for (int i = 0; i < result.size(); i++) {
            if (result.get(i) == result.get(i)+1) continue;
            answer[i] = result.get(i);
        }

        if (result.size() == 0) {
            answer = new String[1];
            answer[0] = "None";
        }

        return answer;
    }

    // 3
    public static int solution(int[][] masks, String[] dates) {
        int answer = 0;
        Set<Integer> set = new HashSet<>();

        for (int i = 0; i < dates.length; i++) {
            dates[i] = dates[i].replace("/", "");
            if (dates[i].length() > 8) {
                StringTokenizer st = new StringTokenizer(dates[i]);
                int dt1 = Integer.parseInt(st.nextToken("~"));
                int dt2 = Integer.parseInt(st.nextToken("~"));

                for (int j = dt1; j <= dt2; j++) {
                    int jm = j % 10000 / 100;
                    int jd = j % 100;

                    if (jm == 1 || jm == 3 || jm == 5 || jm == 7 || jm == 8 || jm == 10) {
                        if (jd == 31) j += 70;
                    } else if (jm == 2 || jm == 4 || jm == 6 || jm == 9 || jm == 11) {
                        if (jd == 30) j += 71;
                    } else if (jm == 12) {
                        if (jd == 31) j += 8770;
                    }
                    set.add(j);
                }
            } else
                set.add(Integer.parseInt(dates[i]));
        }

        List<Integer> list = new ArrayList<>(set);
        Collections.sort(list);
        Arrays.sort(masks, new Comparator<int[]>() {
            @Override
            public int compare(int[] o1, int[] o2) {
                if (o1[1] == o2[1]) {
                    return o2[0] - o1[0];
                } else {
                    return o2[1] - o1[1];
                }
            }
        });

        int continous = 1;
        for (int k = 0; k < list.size() - 1; k++) {
            int today = list.get(k);
            int tomorrow = list.get(k + 1);

            int ty = list.get(k) / 10000;
            int tm = list.get(k) % 10000 / 100;
            int td = list.get(k) % 100;

            int tmy = list.get(k + 1) / 10000;
            int tmm = list.get(k + 1) % 10000 / 100;
            int tmd = list.get(k + 1) % 100;

            if (ty == tmy && tm == tmm && td == tmd - 1) {
                continous++;
            } else if ((tm == 1 || tm == 3 || tm == 5 || tm == 7 || tm == 8 || tm == 10) && (td == 31 && tmm == tm + 1 && tmd == 1)) {
                continous++;
            } else if ((tm == 2 || tm == 4 || tm == 6 || tm == 9 || tm == 11) && (td == 30 && tmm == tm + 1 && tmd == 1)) {
                continous++;
            } else if (tm == 12 && td == 31 && tmy == ty + 1 && tmm == 1 && tmd == 1) {
                continous++;
            } else {
                while (continous > 0) {
                    for (int m = 0; m < masks.length; m++) {
                        if (masks[m][1] <= continous) {
                            answer += masks[m][0];
                            continous -= masks[m][1];
                            break;
                        }
                    }
                }
                continous = 1;
            }
        }
        return answer;
    }

    // 4
    public static int[][] map = new int[8][8];
    public static boolean[][] visited = new boolean[7][7];
    public static int[][] remove = new int[8][8];

    public static String[] solution(int[][] macaron) {
        String[] answer = new String[6];


        for (int i = 0; i < macaron.length; i++) {
            int index = 0;
            while (map[index + 1][macaron[i][0]] == 0 && index < 6)
                index++;
            map[index][macaron[i][0]] = macaron[i][1];
        }


        for (int i = 1; i <= 6; i++) {
            for (int j = 1; j <= 6; j++) {
                visited[i][j] = true;
                dfs(i, j, 1);
                visited[i][j] = false;
            }
        }
        StringBuilder sb = new StringBuilder();

        for (int i = 1; i <= 6; i++) {
            for (int j = 1; j <= 6; j++) {
                sb.append(map[i][j]);
            }
            answer[i - 1] = sb.toString();
        }

        return answer;
    }

    static void dfs(int x, int y, int count) {
        int[][] dir = {{1, 1}, {1, -1}, {-1, 1}, {-1, -1}};

        int curr = map[x][y];
        if (curr == 0)
            return;
        for (int d = 0; d < 4; d++) {
            if (curr == map[x + dir[d][0]][y + dir[d][1]])
                if (!visited[x + dir[d][0]][y + dir[d][1]]) {
                    visited[x + dir[d][0]][y + dir[d][1]] = true;
                    dfs(x + dir[d][0], y + dir[d][1], count + 1);
                    visited[x + dir[d][0]][y + dir[d][1]] = false;
                }
        }
        if (count >= 3) map[x][y] = 0;
    }
}
