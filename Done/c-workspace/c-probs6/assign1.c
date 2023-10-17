#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int partition(int A[], int low, int high, int *count) {
    int pivot = A[low];
    int i = low + 1;
    int j = high;
    
    while (i <= j) {
        while (i <= j && A[i] <= pivot) {
            i++;
            (*count)++;
        }
        
        while (i <= j && A[j] > pivot) {
            j--;
            (*count)++;
        }
        
        if (i <= j) {
            int temp = A[i];
            A[i] = A[j];
            A[j] = temp;
        }
    }
    
    int temp = A[low];
    A[low] = A[j];
    A[j] = temp;
    
    return j;
}


void quicksort_a(int A[], int low, int high, int *count) {
    if (low < high) {
        
        int pivot_idx = partition(A, low, high, count);
        quicksort_a(A, low, pivot_idx - 1, count);
        quicksort_a(A, pivot_idx + 1, high, count);
    }
}


int main() {
    srand(time(NULL));
    int A[100];
    
    for (int i = 0; i < 100; i++) {
        A[i] = rand() % 1000;
        for (int j = 0; j < i; j++)
            if (A[i] == A[j]) {
                i--;
                break;
            }
    }
    
    printf("Before sorting:\n");
    for (int i = 0; i < 100; i++)
        printf("%d ", A[i]);
    printf("\n");
    
    int count = 0;
    quicksort_a(A, 0, 99, &count);
    printf("After sorting:\n");
    for (int i = 0; i < 100; i++)
        printf("%d ", A[i]);

    printf("\nNumber of comparisons: %d\n", count);
    
    for (int i = 0; i < 100; i++) {
        A[i] = i;
        for (int j = 0; j < i; j++)
            if (A[i] == A[j]) {
                i--;
                break;
            }
    }
    
    printf("Before sorting:\n");
    for (int i = 0; i < 100; i++)
        printf("%d ", A[i]);
    printf("\n");
    
    count = 0;
    quicksort_a(A, 0, 99, &count);
    printf("After sorting:\n");
    for (int i = 0; i < 100; i++)
        printf("%d ", A[i]);

    printf("\nNumber of comparisons: %d\n", count);
    
    for (int i = 0; i < 100; i++) {
        A[i] = 100 - i;
        for (int j = 0; j < i; j++)
            if (A[i] == A[j]) {
                i--;
                break;
            }
    }
    
    printf("Before sorting:\n");
    for (int i = 0; i < 100; i++)
        printf("%d ", A[i]);
    printf("\n");
    
    count = 0;
    quicksort_a(A, 0, 99, &count);
    printf("After sorting:\n");
    for (int i = 0; i < 100; i++)
        printf("%d ", A[i]);

    printf("\nNumber of comparisons: %d\n", count);
    return 0;
}
