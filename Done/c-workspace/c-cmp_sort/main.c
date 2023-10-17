#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int *getArrayAsc(int n) {
    int *arr = (int *)malloc(sizeof(int) * n);
    
    for (int i = 0; i < n; i++)
        arr[i] = i + 1;
    
    return arr;
}

int *getArrayDesc(int n) {
    int *arr = (int *)malloc(sizeof(int) * n);
    
    for (int i = 0; i < n; i++)
        arr[i] = n - i;
    
    return arr;
}

int *getArrayRand(int n) {
    int *arr = getArrayAsc(n);
    
    for (int i = 0; i < 2/n; i++) {
        int k1 = rand() % n;
        int k2 = rand() % n;
        
        int temp = arr[k1];
        arr[k1] = arr[k2];
        arr[k2] = temp;
    }
    
    return arr;
}


void insertionSort(int *arr, int n) {
    int j, temp;
    for (int i = 1; i < n; i++) {
        temp = arr[i];
        for (j = i; j > 0 && arr[j-1] > temp; j--)
            arr[j] = arr[j-1];
        arr[j] = temp;
    }
}

void shellSort(int *arr, int n)
{
    int i, j, k, h, v;
    for (h = n/2; h > 0; h /= 2) {
        for (i = 0; i < h; i++) {
            for (j = i+h; j < n; j += h) {
                v = arr[j];
                k = j;
                while (k > h-1 && arr[k-h] > v) {
                    arr[k] = arr[k-h];
                    k -= h;
                }
                arr[k] = v;
            }
        }
    }
}

void swap(int *arr, int a, int b) {
    int temp = arr[a];
    arr[a] = arr[b];
    arr[b] = temp;
}

int partition(int *arr, int left, int right) {
    int pivot = arr[left], low = left+1, high = right, temp;
    while(low <= high) {
        while(low <= right && pivot >= arr[low]) low++;
        while(high >= (left+1) && pivot <= arr[high]) high--;
        if(low <= high) swap(arr, low, high);
    }
    swap(arr, left, high);
    return high;
}

void quickSort(int *arr, int left, int right) {
    if(left <= right) {
        int pivot = partition(arr, left, right);
        quickSort(arr, left, pivot-1);
        quickSort(arr, pivot+1, right);
    }
}

void heapify(int *arr, int n) {
    for (int i = 1; i < n; ++i) {
        int child = i;
        do {
            int root = (child - 1) / 2;
            if (arr[root] < arr[child]) {
                int temp = arr[root];
                arr[root] = arr[child];
                arr[child] = temp;
            }
            child = root;
        } while (child != 0);
    }
}

void heap(int *arr, int *n) {
    int temp = arr[0];
    arr[0] = arr[*n-1];
    arr[*n-1] = temp;
    --(*n);
}

void heapSort(int *arr, int n) {
    int k = n;
    for (int i = 0; i < n; ++i) {
        heapify(arr, n);
        heap(arr, &k);
    }
}


void ASC(int N) {
    clock_t s1, s2, s3, s4;
    clock_t e1, e2, e3, e4;
    printf("\t\tCompare times of each algorithm (A)\n");
    
    printf("Insertion Sort");
    
    int *arr = getArrayAsc(N);
    
    s1 = clock();
    insertionSort(arr, N);
    e1 = clock();
    
    printf("%18.2f", (float)(e1-s1));
    
    
    printf("\nShell Sort\t");
    arr = getArrayAsc(N);
    s2 = clock();
    shellSort(arr, N);
    e2 = clock();
    
    printf("%20.2f", (float)(e2-s2));
    
    printf("\nQuick Sort\t");
    arr = getArrayAsc(N);
    s3 = clock();
    quickSort(arr, 0, N-1);
    e3 = clock();
    
    printf("%20.2f", (float)(e3-s3));
    
    printf("\nHeap Sort\t");
    arr = getArrayAsc(N);
    s4 = clock();
    heapSort(arr, N);
    e4 = clock();
    
    printf("%20.2f", (float)(e4-s4));
    
    
    printf("\n\n");
}

void DESC(int N) {
    clock_t s1, s2, s3, s4;
    clock_t e1, e2, e3, e4;
    printf("\t\tCompare times of each algorithm (D)\n");
    
    printf("Insertion Sort");
    
    int *arr = getArrayDesc(N);
    
    s1 = clock();
    insertionSort(arr, N);
    e1 = clock();
    
    printf("%18.2f", (float)(e1-s1));
    
    
    printf("\nShell Sort\t");
    arr = getArrayDesc(N);
    s2 = clock();
    shellSort(arr, N);
    e2 = clock();
    
    printf("%20.2f", (float)(e2-s2));
    
    printf("\nQuick Sort\t");
    arr = getArrayDesc(N);
    s3 = clock();
    quickSort(arr, 0, N-1);
    e3 = clock();
    
    printf("%20.2f", (float)(e3-s3));
    
    printf("\nHeap Sort\t");
    arr = getArrayDesc(N);
    s4 = clock();
    heapSort(arr, N);
    e4 = clock();
    
    printf("%20.2f", (float)(e4-s4));
    
    
    printf("\n\n");
}
void RAND(int N) {
    clock_t s1, s2, s3, s4;
    clock_t e1, e2, e3, e4;
    printf("\t\tCompare times of each algorithm (A)\n");
    
    printf("Insertion Sort");
    
    int *arr = getArrayRand(N);
    
    s1 = clock();
    insertionSort(arr, N);
    e1 = clock();
    
    printf("%18.2f", (float)(e1-s1));
    
    
    printf("\nShell Sort\t");
    arr = getArrayRand(N);
    s2 = clock();
    shellSort(arr, N);
    e2 = clock();
    
    printf("%20.2f", (float)(e2-s2));
    
    printf("\nQuick Sort\t");
    arr = getArrayRand(N);
    s3 = clock();
    quickSort(arr, 0, N-1);
    e3 = clock();
    
    printf("%20.2f", (float)(e3-s3));
    
    printf("\nHeap Sort\t");
    arr = getArrayRand(N);
    s4 = clock();
    heapSort(arr, N);
    e4 = clock();
    
    printf("%20.2f", (float)(e4-s4));
    
    
    printf("\n\n");
}

int main(int argc, const char * argv[]) {
    srand((unsigned int)time(NULL));
    
    int n;
    printf("Input N: ");
    scanf("%d", &n);
    
    ASC(n);
    DESC(n);
    RAND(n);
    
    return 0;
}

