#pragma once

#include <fstream>
#include <iostream>
#include <string>

#pragma once

template <class T>
int insertionsort(
                  T arr[],
                  int len) {  // 이건 제가 작성한건데 int형으로는 작동했고 반환값도 정답인거 같아요!
    int operations = 0;
    int temp;
    for (int i = 1; i < len; i++) {
        temp = arr[i];
        int pos = i;
        while (pos > 0 && arr[pos - 1] > temp) {
            arr[pos] = arr[pos - 1];
            pos--;
            operations++;
        }
        operations++;
        arr[pos] = temp;
    }
    return operations;
}

template< class T >
void swap( T& a, T& b ) {
    T temp = a;
    a = b;
    b = temp;
}

template <class T>
int partition(T arr[], int start, int end, int & operations)
{
    int pivot = arr[start];
    
    int count = 0;
    for (int i = start + 1; i <= end; i++)
        if (arr[i] <= pivot) count++;
    
    int pivotIndex = start + count;
    swap(arr[pivotIndex], arr[start]);
    
    int i = start, j = end;
    
    while (i < pivotIndex && j > pivotIndex) {
        operations++;
        while (arr[i] <= pivot) i++;
        while (arr[j] > pivot) j--;
        if (i < pivotIndex && j > pivotIndex)
            swap(arr[i++], arr[j--]);
    }
    
    return pivotIndex;
}

template <class T>
int quicksort(T arr[], int len)
{
    int operations = 0;
    int start = 0, end = len, p = 0;
    
    while (start < end) {
        p = partition(arr, start, end, operations);
        end = p-1;
        p = partition(arr, start, end, operations);
        start = p+1;
    }
    
    return operations;
}

template <class T>
int merge(T arr[], int left, int mid, int right, int & operations)
{
    int k;
    int n1 = mid - left + 1;
    int n2 =  right - mid;
    
    T L[n1], R[n2];
    
    for(int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for(int j = 0; j < n2; j++)
        R[j] = arr[mid + 1+ j];
    
    int i = 0;
    int j = 0;
    k = left;
    
    while (i < n1 && j < n2)
    {
        operations++;
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    
    while (i < n1)
    {
        operations++;
        arr[k] = L[i];
        i++;
        k++;
    }
    
    while (j < n2)
    {
        operations++;
        arr[k] = R[j];
        j++;
        k++;
    }
    
    return operations;
}

template <class T>
int mergesort(T array[], int len)
{
    int operations = 0;
    int start = 0, end = len;
    int mid = start + (end - start) / 2;
    
    while (start < end) {
        end = mid;
        merge(array, start, mid, end, operations);
        start = mid+1;
        merge(array, start, mid, end, operations);
    
    }
    return operations;
}

template <class T>
int shellsort(T arr[], int n)
{
    int operations = 0;
    for (int gap = n/2; gap > 0; gap /= 2)
    {
        for (int i = gap; i < n; i += 1)
        {
            operations++;
            T temp = arr[i];
            
            int j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap)
                arr[j] = arr[j - gap];
            
            arr[j] = temp;
        }
    }
    return operations;
}
