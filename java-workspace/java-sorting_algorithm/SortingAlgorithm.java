public class SortingAlgorithm {

    //Q1
    // Time O(N logN) | Space O(1)
    private static int[] hybridSort(int[] array) {//Do not edit
        //Your Answer
        if (array.length <= 1)
            return array;
        for (int i = array.length - 1; i > 0; i--) {
            int min = -1, pivot = i;
            for (int j = array.length - i - 1; j < i; j++) {
                if (array[j] > array[j + 1])
                    swap(array, j, j + 1);
                if (pivot == i || min > array[j]) {
                    pivot = j;
                    min = array[j];
                }
            }
            if (pivot != i)
                swap(array, array.length - i - 1, pivot);
        }
        return array;
    }

    //Q2
    // Time O(N*M) | Space O(1)
    private static int[] organiserSort(int[] array, int[] order) {//Do not edit
        //Your Answer
        if (array.length <= 1)
            return array;
        int count = 0;
        for (int i = 0; i < order.length; i++) {
            for (int j = count; j < array.length; j++) {
                if (array[j] == order[i]) {
                    if (count != j)
                        swap(array, count, j);
                    count++;
                }
            }
        }

        return array;
    }

    //Q3
    //Time O(N) | Space O(N)
    private static int[] modifiedCountingSort(int[] array) {//Do not edit
        //Your Answer

        // If available
//        int max = Arrays.stream(array).max().getAsInt();
//        int min = Arrays.stream(array).max().getAsInt();

        // If not
        if (array.length <= 1)
            return array;

        int max = Integer.MIN_VALUE;
        int min = Integer.MAX_VALUE;
        for (int i = 0; i < array.length; i++) {
            if (array[i] < min)
                min = array[i];
            if (array[i] > max)
                max = array[i];
        }

        int[] count = new int[max - min + 1];
        for (int value : array)
            count[value - min]++;

        int i = 0;
        for (int j = min; j <= max; j++)
            for (int k = 0; k < count[j - min]; k++)
                array[i++] = j;

        return array;
    }

    //Q4
    // Time O(N+k) | Space O(1)
    private static int[] mountainSort(int[] array) {//Do not edit
        //Your Answer
        if (array.length <= 1)
            return array;

        int k = (array.length + 1) / 2;

        modifiedCountingSort(array);

        for (int i = 0; i < k / 2; i++)
            swap(array, k + i, array.length - i - 1);
        return array;
    }

    private static void swap(int[] array, int i, int j) {//Do not edit
        int temp = array[j];
        array[j] = array[i];
        array[i] = temp;
    }

    public static void main(String[] args) {
        //You can edit here for your own testing
        // Q1
        int[] array = {9, 8, 7, 6, 5, 4, 3, 2, 1};
//        array = new int[]{1, 1, 1, 1, 1, 1, 1};
        hybridSort(array);

        for (int i : array)
            System.out.print(i + " ");
        System.out.println();

        // Q2
        array = new int[]{0, 2, -1, 0, 2, -1, -1, 0, -1, -1, 0, 0, 2, -1};
        int[] order = {0, 2, -1};
//        array = new int[]{1, 1, 1, 1, 1, 1, 1};
//        order = new int[]{1};
        organiserSort(array, order);

        for (int i : array)
            System.out.print(i + " ");
        System.out.println();

        // Q3
        array = new int[]{0, 4, -1, 0, 2, -5, -1, 0, -1, -1, 0, 0, -2, -1};
//        array = new int[]{1, 1, 1, 1, 1, 1, 1};
        modifiedCountingSort(array);

        for (int i : array)
            System.out.print(i + " ");
        System.out.println();

        //Q4
        array = new int[]{34, 12, 7, 43, 55, 97, 41, 28, 2, 62};
//        array = new int[]{1, 1, 1, 1, 1};
        mountainSort(array);

        for (int i : array)
            System.out.print(i + " ");
        System.out.println();
    }

}