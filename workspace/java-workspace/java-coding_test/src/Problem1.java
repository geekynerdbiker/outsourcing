public class Problem1 {
    /**
     * 생성자 (예제 실행)
     */
    public Problem1() {
        int[] result1 = solve(new int[]{1, 13, 15, 12, 3, 1, 10}, 4);
        int[] result2 = solve(new int[]{0, 10, 0, 8, 0, 12}, 1);
        int[] result3 = solve(new int[]{11, 3, 1, 6, 20, 7, 1, 0, 0}, 6);

        printResult("Problem 1 - ex1: ", result1);
        printResult("Problem 1 - ex2: ", result2);
        printResult("Problem 1 - ex3: ", result3);
    }

    public static int[] solve(int[] predict, int k) {
        // 결과 배열 초기화
        int[] result = new int[predict.length];

        // 예측 값 보다 큰 가장 작은 k의 배수로 초기화
        for (int i = 0; i < result.length; i++)
            result[i] = ((predict[i] + k - 1) / k) * k;

        // 조건을 만족할 때까지 수정
        while (!isValid(result, k))
            correction(result, k);

        return result;
    }

    /**
     * 문제 조건에 맞도록 배열 수정
     * @param arr 현재 배열
     * @param k k
     */
    private static void correction(int[] arr, int k) {
        for (int i = 1; i < arr.length; i++) {
            // 앞의 값이 현재 값보다 작으면서 k이상 차이날 경우 앞의 값 k만큼 증가
            while (arr[i - 1] < arr[i] && arr[i] - arr[i - 1] > k)
                arr[i - 1] += k;
            // 앞의 값이 현재 값보다 크면서 k이상 차이날 경우 현재 값 k만큼 증가
            while (arr[i - 1] > arr[i] && arr[i - 1] - arr[i] > k)
                arr[i] += k;
        }
    }

    /**
     * 현재 배열이 조건을 만족하는지 확인 -
     * @param arr 검사할 배열
     * @param k k
     * @return 조건을 만족하면 참
     */
    private static boolean isValid(int[] arr, int k) {
        for (int i = 1; i < arr.length; i++)
            if (Math.abs(arr[i] - arr[i - 1]) > k)
                return false;
        return true;
    }

    /**
     * 배열 출력 (결과 확인용)
     * @param header 말머리
     * @param arr 배열
     */
    private static void printResult(String header, int[] arr) {
        System.out.print(header);
        for (int j : arr)
            System.out.print(j + " ");
        System.out.println();
    }
}
