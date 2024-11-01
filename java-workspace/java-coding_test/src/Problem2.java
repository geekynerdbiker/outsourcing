import java.util.*;

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
        HashSet<ArrayList<Integer>> result = new HashSet<>();

        // 모든 빈칸 좌표에서 출발
        for (int i = 0; i < maze.length; i++) {
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
        }

        ArrayList<ArrayList<Integer>> sortedResult = new ArrayList<>(result);
        sortedResult.sort(Comparator.comparingInt(o -> o.get(0)));

        return convertTo2DArray(sortedResult);
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
        ArrayList<ArrayList<Integer>> path;
        // 현재까지 작성한 메세지를 저장할 리스트
        ArrayList<Integer> currMsg;
        // 방문을 기록할 배열
        boolean[][] visited;

        // 모든 방향에 대해 초기화 진행 후 출발
        for (int dir = 0; dir < 4; dir++) {
            path = new ArrayList<>();
            currMsg = new ArrayList<>();
            visited = new boolean[maze.length][maze[0].length];

            if (isRightHand)
                dfsRightHand(maze, x, y, dir, false, visited, path, coordinates, currMsg, msg);
            else
                dfsLeftHand(maze, x, y, dir, false, visited, path, coordinates, currMsg, msg);
        }

        return coordinates;
    }

    /**
     * 깊이 우선 탐색 - 오른쪽
     *
     * @param maze        미로
     * @param x           현재 x좌표
     * @param y           현재 y좌표
     * @param visited     방문 확인용
     * @param path        현재까지 이동한 좌표
     * @param coordinates 동일한 메세지를 보낸 좌표
     * @param currMsg     현재까지 얻은 메세지
     * @param msg         조난 메세지
     */
    private static void dfsRightHand(int[][] maze, int x, int y, int direction, boolean isCorner, boolean[][] visited, ArrayList<ArrayList<Integer>> path, ArrayList<ArrayList<Integer>> coordinates, ArrayList<Integer> currMsg, int[] msg) {
        // 필요 이상의 이동시 종료
        if (currMsg.size() > msg.length)
            return;

        // 위, 오른쪽, 아래, 왼쪽 순서 -> 오른손으로 벽을 짚으며 탐색
        int[] dx = {-1, 0, 1, 0};
        int[] dy = {0, 1, 0, -1};

        // 내 오른쪽 방향
        int rightDirection = (direction + 1) % 4;
        int myRightX = x + dx[rightDirection];
        int myRightY = y + dy[rightDirection];

        if (!isWall(myRightX, myRightY, maze) && currMsg.isEmpty())
            return;

        if (!currMsg.isEmpty())
            visited[x][y] = true;

        if (maze[myRightX][myRightY] != 2) {
            currMsg.add(maze[myRightX][myRightY]);
            path.add(new ArrayList<>(Arrays.asList(x, y)));
        }

        // 현재까지 경로와 메세지가 다르면 종료
        for (int i = 0; i < currMsg.size(); i++)
            if (currMsg.get(i) != msg[i])
                return;

        // 메세지와 일치하는 위치에 도달했으면
        if (msg.length == currMsg.size()) {
            coordinates.add(path.get(path.size() - 1));
        } else {
            for (int dir = 0; dir < 4; dir++) {
                // 다음 이동할 좌표
                int nextDirection = (direction + dir) % 4;
                int newRightDirection = (direction + dir + 1) % 4;

                int nx = x + dx[nextDirection];
                int ny = y + dy[nextDirection];

                if (dir == 0 && isWall(nx, ny, maze)) {
                    int dirCount = 0;
                    while (isWall(nx, ny, maze)) {
                        if (dirCount == 4)
                            break;
                        nextDirection = (nextDirection + 3) % 4;
                        newRightDirection = (newRightDirection + 3) % 4;

                        nx = x + dx[nextDirection];
                        ny = y + dy[nextDirection];

                        myRightX = x + dx[newRightDirection];
                        myRightY = y + dy[newRightDirection];

                        currMsg.add(maze[myRightX][myRightY]);
                        path.add(new ArrayList<>(Arrays.asList(x, y)));

                        for (int i = 0; i < currMsg.size(); i++)
                            if (currMsg.get(i) != msg[i])
                                return;

                        if (msg.length == currMsg.size()) {
                            coordinates.add(path.get(path.size() - 1));

                            if (!path.isEmpty())
                                path.removeLast();
                            if (!currMsg.isEmpty())
                                currMsg.removeLast();
                            visited[x][y] = false;

                            return;
                        }
                        dirCount++;
                    }
                }
                myRightX = x + dx[newRightDirection];
                myRightY = y + dy[newRightDirection];

                // 현재 좌표의 오른쪽이 올바른 좌표이면서 오른쪽이 벽일때만 해당 방향으로 이동 가능
                if (isWall(myRightX, myRightY, maze) || isCorner) {
                    // 다음 이동할 방향의 오른쪽이 벽인지 검사
                    int nextRightDirection = (direction + dir + 1) % 4;
                    int myNextRightX = nx + dx[nextRightDirection];
                    int myNextRightY = ny + dy[nextRightDirection];

                    if (isValid(nx, ny, maze, visited) && isWall(myNextRightX, myNextRightY, maze)) {
                        dfsRightHand(maze, nx, ny, nextDirection, false, visited, path, coordinates, currMsg, msg);
                    } else if (isValid(nx, ny, maze, visited) && !isWall(myNextRightX, myNextRightY, maze)) {
                        dfsRightHand(maze, nx, ny, nextRightDirection, true, visited, path, coordinates, currMsg, msg);
                    }
                }
            }
        }

        // 백트래킹 사용하여 현재 위치 경로에서 제거
        if (!path.isEmpty())
            path.removeLast();
        if (!currMsg.isEmpty())
            currMsg.removeLast();
        visited[x][y] = false;
    }

    /**
     * 깊이 우선 탐색 - 왼쪽
     *
     * @param maze        미로
     * @param x           현재 x좌표
     * @param y           현재 y좌표
     * @param visited     방문 확인용
     * @param path        현재까지 이동한 좌표
     * @param coordinates 동일한 메세지를 보낸 좌표
     * @param currMsg     현재까지 얻은 메세지
     * @param msg         조난 메세지
     */
    private static void dfsLeftHand(int[][] maze, int x, int y, int direction, boolean isCorner, boolean[][] visited, ArrayList<ArrayList<Integer>> path, ArrayList<ArrayList<Integer>> coordinates, ArrayList<Integer> currMsg, int[] msg) {
        // 필요 이상의 이동시 종료
        if (currMsg.size() > msg.length)
            return;

        // 위, 왼쪽, 아래, 오른쪽 순서 -> 오른손으로 벽을 짚으며 탐색
        int[] dx = {-1, 0, 1, 0};
        int[] dy = {0, -1, 0, 1};

        int leftDirection = (direction + 1) % 4;
        int myLeftX = x + dx[leftDirection];
        int myLeftY = y + dy[leftDirection];

        if (!isWall(myLeftX, myLeftY, maze) && currMsg.isEmpty())
            return;

        if (!currMsg.isEmpty())
            visited[x][y] = true;
        if (maze[myLeftX][myLeftY] != 2) {
            currMsg.add(maze[myLeftX][myLeftY]);
            path.add(new ArrayList<>(Arrays.asList(x, y)));
        }

        // 현재까지 경로와 메세지가 다르면 종료
        for (int i = 0; i < currMsg.size(); i++)
            if (currMsg.get(i) != msg[i])
                return;

        // 메세지와 일치하는 위치에 도달했으면
        if (msg.length == currMsg.size()) {
            coordinates.add(path.get(path.size() - 1));
        } else {
            for (int dir = 0; dir < 4; dir++) {
                // 다음 이동할 좌표
                int nextDirection = (direction + dir) % 4;
                int newLeftDirection = (direction + dir + 1) % 4;

                int nx = x + dx[nextDirection];
                int ny = y + dy[nextDirection];

                boolean rotate = false;
                if (dir == 0 && isWall(nx, ny, maze)) {
                    int dirCount = 0;
                    while (isWall(nx, ny, maze)) {
                        if (dirCount == 4)
                            break;
                        nextDirection = (nextDirection + 3) % 4;
                        newLeftDirection = (newLeftDirection + 3) % 4;

                        nx = x + dx[nextDirection];
                        ny = y + dy[nextDirection];

                        myLeftX = x + dx[newLeftDirection];
                        myLeftY = y + dy[newLeftDirection];

                        currMsg.add(maze[myLeftX][myLeftY]);
                        path.add(new ArrayList<>(Arrays.asList(x, y)));

                        for (int i = 0; i < currMsg.size(); i++)
                            if (currMsg.get(i) != msg[i])
                                return;

                        if (msg.length == currMsg.size()) {
                            coordinates.add(path.get(path.size() - 1));

                            if (!path.isEmpty())
                                path.removeLast();
                            if (!currMsg.isEmpty())
                                currMsg.removeLast();
                            visited[x][y] = false;

                            return;
                        }

                        if (isValid(nx, ny, maze, visited)) {
                            rotate = true;
                            break;
                        }

                        dirCount++;
                    }
                }

                myLeftX = x + dx[newLeftDirection];
                myLeftY = y + dy[newLeftDirection];

                // 현재 좌표의 오른쪽이 올바른 좌표이면서 왼쪽이 벽일때만 해당 방향으로 이동 가능
                if (isWall(myLeftX, myLeftY, maze) || isCorner) {
                    // 다음 이동할 방향의 왼쪽이 벽인지 검사
                    if (!rotate)
                        newLeftDirection = (direction + dir + 1) % 4;
                    int myNextLeftX = nx + dx[newLeftDirection];
                    int myNextLeftY = ny + dy[newLeftDirection];

                    if (isValid(nx, ny, maze, visited) && isWall(myNextLeftX, myNextLeftY, maze)) {
                        dfsLeftHand(maze, nx, ny, nextDirection, false, visited, path, coordinates, currMsg, msg);
                    } else if (isValid(nx, ny, maze, visited) && !isWall(myNextLeftX, myNextLeftY, maze)) {
                        dfsLeftHand(maze, nx, ny, newLeftDirection, true, visited, path, coordinates, currMsg, msg);
                    }
                }
            }
        }

        // 백트래킹 사용하여 현재 위치 경로에서 제거
        if (!path.isEmpty())
            path.removeLast();
        if (!currMsg.isEmpty())
            currMsg.removeLast();
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

        return x >= 0 && x < n && y >= 0 && y < m && maze[x][y] != 2;
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
        if (al.isEmpty())
            return new int[0][0];
        int rows = al.size();
        int cols = al.get(0).size();

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
