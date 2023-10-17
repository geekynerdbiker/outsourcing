//
//  main.c
//  c-comparearrlg
//
//  Created by Jacob arrn on 2022/03/27.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int max(int a, int b) {
    return a > b ? a : b;
}

// 완전 탐색: O(N^3)
int alg1(int arr[], int n) {
    int mSum = 0, sum = 0;
    
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            sum = 0;
            for (int k = i; k <= j; k++)
                sum = sum + arr[k];
            mSum = max(mSum, sum);
        }
    }
    
    return mSum;
}

// 중복 제거: O(N^2)
int alg2(int arr[], int n) {
    int mSum = 0, sum = 0;
    
    for (int i = 0; i < n; i++) {
        sum = 0;
        for (int j = i; j < n; j++) {
            sum = sum + arr[j];
            mSum = max(mSum, sum);
        }
    }
    
    return mSum;
}

// 분할 정복: O(N log N)
int alg3(int arr[], int left, int right) {
    int mSum, mLeft, mRight, mCen;
    int cLeft, cRight, sum;
    
    if (left == right) {
        if (arr[left] > 0)
            return arr[left];
        else return 0;
    }
    
    int cen = (left + right) / 2;
    
    mLeft = alg3(arr, left, cen);
    mRight = alg3(arr, cen + 1, right);
    cLeft = 0;
    sum = 0;
    
    for (int i = cen; i >= left; i--) {
        sum = sum + arr[i];
        cLeft = max(cLeft, sum);
    }
    
    cRight = 0;
    sum = 0;
    
    for (int i = cen + 1; i <= right; i++) {
        sum = sum + arr[i];
        cRight = max(cRight, sum);
    }
    
    mCen = cLeft + cRight;
    mSum = max(max(mLeft, mRight), mCen);
    
    return mSum;
}

// 동적 계획법: O(N)
int alg4(int arr[], int n) {
    int mSum = 0, sum = 0;
    
    for (int i = 0; i < n; i++) {
        sum = max(sum + arr[i], 0);
        mSum = max(mSum, sum);
    }
    
    return mSum;
}

int *getArray(int n) {
    printf("Generating array...\n");
    int *arr = (int *)malloc(sizeof(int) * n);
    
    for (int i = 0; i < n; i++)
        arr[i] = rand() % 100;
    
    return arr;
}

int main(int argc, const char * argv[]) {
    FILE *fp = fopen("result.txt", "w");
    srand((unsigned int)time(NULL));
    
    clock_t s1, s2, s3, s4;
    clock_t e1, e2, e3, e4;
    printf("Compare times of each algorithm\n");
    fprintf(fp, "Compare times of each algorithm\n");
    
    for (int n = 1000; n <= 5000; n += 1000) {
        int *arr = getArray(n);
        
        printf("Starting brute force algorithm...\n");
        s1 = clock();
        alg1(arr, n);
        e1 = clock();
        
        printf("Starting remove dups algorithm...\n");
        s2 = clock();
        alg2(arr, n);
        e2 = clock();
        
        printf("Starting DC algorithm...\n");
        s3 = clock();
        alg3(arr, 0, n);
        e3 = clock();
        
        printf("Starting DP algorithm...\n");
        s4 = clock();
        alg4(arr, n);
        e4 = clock();
        
        printf("\2t%f\2t%f\2t%f\2t%f\n", (float)(e1-s1)/CLOCKS_PER_SEC, (float)(e2-s2)/CLOCKS_PER_SEC, (float)(e3-s3)/CLOCKS_PER_SEC, (float)(e4-s4)/CLOCKS_PER_SEC);
        fprintf(fp, "\2t%f\2t%f\2t%f\2t%f\n", (float)(e1-s1)/CLOCKS_PER_SEC, (float)(e2-s2)/CLOCKS_PER_SEC, (float)(e3-s3)/CLOCKS_PER_SEC, (float)(e4-s4)/CLOCKS_PER_SEC);
    }
    fclose(fp);
    return 0;
}

