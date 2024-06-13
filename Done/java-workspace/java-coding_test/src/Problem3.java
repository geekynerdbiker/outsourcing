public class Problem3 {
    /**
     * 생성자 (예제 실행)
     */
    public Problem3() {
        int[] result1 = solve(4, 3, new int[][]{{1, 1, 2, 4, 3}, {3, 2, 1, 2, 3}, {4, 1, 1, 4, 3}, {2, 2, 1, 3, 3}});
        int[] result2 = solve(2, 4, new int[][]{{3, 1, 2, 2, 4}, {3, 1, 2, 2, 4}, {4, 2, 1, 2, 3}, {1, 1, 1, 2, 3}});
        int[] result3 = solve(2, 2, new int[][]{{3, 1, 1, 1, 2}, {1, 1, 2, 2, 2}, {4, 2, 1, 2, 2}, {2, 1, 1, 2, 1}});

        printResult("Problem 3 - ex1: ", result1);
        printResult("Problem 3 - ex2: ", result2);
        printResult("Problem 3 - ex3: ", result3);
    }

    public static int[] solve(int rows, int columns, int[][] swipes) {
        // 결과 배열 초기화
        int[] result = new int[swipes.length];
        int[][] arr = new int[rows][columns];

        int num = 0;
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < columns; j++)
                arr[i][j] = ++num;

        for (int i = 0; i < swipes.length; i++)
            result[i] = swipe(swipes[i], arr);

        return result;
    }

    private static int swipe(int[] cmd, int[][] arr) {
        int dir = cmd[0];
        int x1 = cmd[1] - 1; // 입력받은 좌표는 양의 정수로 나타내어져서 1 빼줌
        int y1 = cmd[2] - 1;
        int x2 = cmd[3] - 1;
        int y2 = cmd[4] - 1;

        switch (dir) {
            case 1: // 아래
                return swipeDown(x1, y1, x2, y2, arr);
            case 2: // 위
                return swipeUp(x1, y1, x2, y2, arr);
            case 3: // 오른쪽
                return swipeRight(x1, y1, x2, y2, arr);
            case 4: // 왼쪽
                return swipeLeft(x1, y1, x2, y2, arr);
            default:
                return 0;
        }
    }

    public static int swipeUp(int x1, int y1, int x2, int y2, int[][] array) {
        int n = array.length;
        int m = array[0].length;
        int[][] result = new int[n][m];

        int sum = 0;
        for (int i = x1; i < x2; i++) // 마지막 줄 제외 밀면서 복사
            for (int j = y1; j <= y2; j++)
                result[i][j] = array[i + 1][j];

        for (int j = y1; j <= y2; j++) { // 마지막 줄 복사하면서 원소 합 구함
            result[x2][j] = array[x1][j];
            sum += result[x2][j];
        }

        for (int i = x1; i <= x2; i++) // 원래 배열 업데이트
            for (int j = y1; j <= y2; j++)
                array[i][j] = result[i][j];

        return sum; // 합 반환
    }

    public static int swipeDown(int x1, int y1, int x2, int y2, int[][] array) {
        int n = array.length;
        int m = array[0].length;
        int[][] result = new int[n][m];

        int sum = 0;
        for (int i = x1 + 1; i <= x2; i++)
            for (int j = y1; j <= y2; j++)
                result[i][j] = array[i - 1][j];

        for (int j = y1; j <= y2; j++) {
            result[x1][j] = array[x2][j];
            sum += result[0][j];
        }

        for (int i = x1; i <= x2; i++)
            for (int j = y1; j <= y2; j++)
                array[i][j] = result[i][j];

        return sum;
    }

    public static int swipeLeft(int x1, int y1, int x2, int y2, int[][] array) {
        int n = array.length;
        int m = array[0].length;
        int[][] result = new int[n][m];

        int sum = 0;
        for (int i = x1; i <= x2; i++) {
            for (int j = y1; j < y2; j++)
                result[i][j] = array[i][j + 1];
            result[i][y2] = array[i][y1];
            sum += result[i][y2];
        }


        for (int i = x1; i <= x2; i++)
            for (int j = y1; j <= y2; j++)
                array[i][j] = result[i][j];

        return sum;
    }

    public static int swipeRight(int x1, int y1, int x2, int y2, int[][] array) {
        int n = array.length;
        int m = array[0].length;
        int[][] result = new int[n][m];

        int sum = 0;
        for (int i = x1; i <= x2; i++) {
            for (int j = y1 + 1; j <= y2; j++) {
                result[i][j] = array[i][j - 1];
            }
            result[i][y1] = array[i][y2];
            sum += result[i][y1];
        }

        for (int i = x1; i <= x2; i++)
            for (int j = y1; j <= y2; j++)
                array[i][j] = result[i][j];

        return sum;
    }

    /**
     * 배열 출력 (결과 확인용)
     *
     * @param header 말머리
     * @param arr    배열
     */
    private static void printResult(String header, int[] arr) {
        System.out.print(header);
        for (int j : arr)
            System.out.print(j + " ");
        System.out.println();
    }
}
