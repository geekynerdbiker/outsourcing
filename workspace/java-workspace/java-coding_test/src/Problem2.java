import java.util.ArrayList;
import java.util.Arrays;

/*
1,1 일때
 */
public class Problem2 {
    /**
     * 생성자 (예제 실행)
     */
    public Problem2() {
        int[][] result1 = solve(new int[]{1, 0, 0, 0, 1}, new int[][]{{1, 0, 0, 2, 2, 2, 2}, {2, 2, 1, 2, 1, 0, 2}, {2, 0, 1, 2, 2, 2, 2}, {2, 2, 2, 2, 1, 2, 2}, {2, 1, 0, 0, 1, 2, 2}});
        int[][] result2 = solve(new int[]{1, 1, 1, 1, 1}, new int[][]{{2, 2, 2}, {2, 1, 2}, {2, 2, 2}});
        int[][] result3 = solve(new int[]{0, 1}, new int[][]{{0, 2, 2, 2, 0}, {2, 1, 2, 1, 2}, {2, 2, 2, 2, 2}});
        int[][] result4 = solve(new int[]{0, 1, 1}, new int[][]{{0, 1, 0, 2}, {0, 2, 1, 2}, {1, 0, 1, 2}});

        printResult("Problem 2 - ex1: ", result1);
        printResult("Problem 2 - ex2: ", result2);
        printResult("Problem 2 - ex3: ", result3);
        printResult("Problem 2 - ex4: ", result4);
    }

    public static int[][] solve(int[] msg, int[][] maze) {
        // 결과 배열 초기화. 정답 갯수를 모르기 때문에 ArrayList 사용
        ArrayList<ArrayList<Integer>> result = new ArrayList<>();

        // 모든 빈칸 좌표에서 출발
        for (int i = 0; i < maze.length; i++)
            for (int j = 0; j < maze[i].length; j++) {
                // 현재 칸이 벽이거나 사방에 벽이 없으면 다음 칸 탐색
                if (isWall(i, j, maze) || !anyWalls(i, j, maze))
                    continue;

                // 메세지 출력이 가능한 칸인지 확인하여 가능한 칸이라면 결과에 좌표 추가
                ArrayList<ArrayList<Integer>> coordinateRight = match(maze, msg, i, j, true);
                ArrayList<ArrayList<Integer>> coordinateLeft = match(maze, msg, i, j, false);

                if (!coordinateRight.isEmpty())
                    result.addAll(coordinateRight);
                if (!coordinateLeft.isEmpty())
                    result.addAll(coordinateLeft);

            }
        return convertTo2DArray(result);
    }

    /**
     * 현재 좌표에서 msg를 찾으면 도착좌표 반환
     *
     * @param msg 메세지
     * @param x   현재 x좌표
     * @param y   현재 y좌표
     * @return 결과 ArrayList
     */
    private static ArrayList<ArrayList<Integer>> match(int[][] maze, int[] msg, int x, int y, boolean isRightHand) {
        // 정답을 저장할 리스트
        ArrayList<ArrayList<Integer>> coordinates = new ArrayList<>();
        // 현재까지 이동 경로를 저장할 리스트
        ArrayList<ArrayList<Integer>> path = new ArrayList<>();
        // 현재까지 작성한 메세지를 저장할 리스트
        ArrayList<Integer> currMsg = new ArrayList<>();
        // 방문을 기록할 배열
        boolean[][] visited = new boolean[maze.length][maze[0].length];

        dfs(maze, x, y, visited, path, coordinates, currMsg, msg, isRightHand);

        return coordinates;
    }

    /**
     * 깊이 우선 탐색 -
     *
     * @param maze        미로
     * @param x           현재 x좌표
     * @param y           현재 y좌표
     * @param visited     방문 확인용
     * @param path        현재까지 이동한 좌표
     * @param coordinates 동일한 메세지를 보낸 좌표
     * @param currMsg     현재까지 얻은 메세지
     * @param msg         조난 메세지
     * @param isRightHand 오른손을 짚고 가면 참, 왼손이면 거짓
     */
    private static void dfs(int[][] maze, int x, int y, boolean[][] visited, ArrayList<ArrayList<Integer>> path, ArrayList<ArrayList<Integer>> coordinates, ArrayList<Integer> currMsg, int[] msg,boolean isRightHand) {
        // 필요 이상의 이동시 종료
        if (currMsg.size() > msg.length)
            return;

        // 이동중 코너를 돌아야하는 경우
        boolean isCorner = false;

        if (!anyWalls(x, y, maze))
            isCorner = true;

        // 위, 오른쪽, 아래, 왼쪽 순서 -> 오른손으로 벽을 짚으며 탐색
        int[] dx = {-1, 0, 1, 0};
        int[] dy = {0, 1, 0, -1};

        visited[x][y] = true;

        // 현재까지 경로와 메세지가 다르면 종료
        for (int i = 0; i < currMsg.size(); i++)
            if (currMsg.get(i) != msg[i])
                return;

        // 메세지와 일치하는 위치에 도달했으면
        if (msg.length == currMsg.size()) {
            coordinates.add(path.getLast());
        } else {
            for (int dir = 0; dir < 4; dir++) {
                // 다음 이동할 방향
                int nx = x + dx[dir];
                int ny = y + dy[dir];

                // 다다음 이동할 방향 (오른손을 짚고 전진 하려면 현재 진행방향의 오른쪽이 벽이어야 함)
                int nnx, nny;
                if (isRightHand) {
                    if (isCorner) {
                        nnx = nx + dx[(dir + 1) % 4];
                        nny = ny + dy[(dir + 1) % 4];
                    } else {
                        nnx = x + dx[(dir + 1) % 4];
                        nny = y + dy[(dir + 1) % 4];
                    }
                } else {
                    if (isCorner) {
                        nnx = nx + dx[((4 + dir) - 1) % 4];
                        nny = ny + dy[((4 + dir) - 1) % 4];
                    } else {
                        nnx = x + dx[((4 + dir) - 1) % 4];
                        nny = y + dy[((4 + dir) - 1) % 4];
                    }
                }

                if (isValid(nx, ny, maze, visited) && isWall(nnx, nny, maze)) {
                    // 코너를 돌때는 메세지 경로를 추가하지 않음
                    if (!isCorner)
                        currMsg.add(maze[nnx][nny]);
                    path.add(new ArrayList<>(Arrays.asList(x, y)));
                    dfs(maze, nx, ny, visited, path, coordinates, currMsg, msg, isRightHand);
                }
            }
        }

        // 백트래킹 사용하여 현재 위치 경로에서 제거
        if (!path.isEmpty())
            path.removeLast();
        visited[x][y] = false;
    }

    /**
     * 올바른 좌표의 벽인지 확인
     *
     * @param x    현재 x좌표
     * @param y    현재 y좌표
     * @param maze 미로
     * @return 올바른 좌표의 벽일 때 참 반환
     */
    private static boolean isWall(int x, int y, int[][] maze) {
        int n = maze.length;
        int m = maze[0].length;

        if (x >= 0 && x < n && y >= 0 && y < m)
            if (maze[x][y] != 2)
                return true;

        return false;
    }

    /**
     * 현재 좌표를 기준으로 사방에 벽이 있는지 확인
     *
     * @param x    현재 x좌표
     * @param y    현재 y좌표
     * @param maze 미로
     * @return 사방에 벽이 존재할 때 참 반환
     */

    private static boolean anyWalls(int x, int y, int[][] maze) {
        int[] dx = {-1, 0, 1, 0};
        int[] dy = {0, 1, 0, -1};


        // 네갈래 방향에 대해 탐색
        for (int dir = 0; dir < 4; dir++) {
            // 이동할 좌표
            int nx = x + dx[dir];
            int ny = y + dy[dir];

            // 이동할 좌표가 미로 안의 좌표이면서 벽이면 참
            if (isWall(nx, ny, maze))
                return true;
        }

        // 사방 모두 벽이 아닌 경우
        return false;
    }

    private static boolean isValid(int x, int y, int[][] maze, boolean[][] visited) {
        int n = maze.length;
        int m = maze[0].length;
        return x >= 0 && x < n && y >= 0 && y < m && maze[x][y] == 2 && !visited[x][y];
    }

    /**
     * 2중 ArrayList를 int [][] 배열로 변환
     *
     * @param al 변환할 리스트
     * @return 변환된 배열
     */
    public static int[][] convertTo2DArray(ArrayList<ArrayList<Integer>> al) {
        int rows = al.size();
        int cols = al.getFirst().size();

        int[][] arr = new int[rows][cols];

        for (int i = 0; i < rows; i++)
            for (int j = 0; j < cols; j++)
                arr[i][j] = al.get(i).get(j);

        return arr;
    }

    /**
     * 배열 출력 (결과 확인용)
     *
     * @param header 말머리
     * @param arr    배열
     */
    private static void printResult(String header, int[][] arr) {
        System.out.print(header);
        for (int[] a : arr) {
            System.out.print("(" + a[0] + ", " + a[1] + ") ");
        }
        System.out.println();
    }
}
