#include <iostream>
#include <fstream>
#include <sstream>
#include <random>

using namespace std;

int comparisonCount = 0;

void insertionSort(int A[], int n) {
    int i, j, tmp;

    for (i = 1; i < n; i++) {
        tmp = A[i];
        for (j = i; A[j-1] > tmp &&  j > 0; j--) {
            A[j] = A[j - 1];
            comparisonCount++;
        } A[j] = tmp;
    }
}

void swap(int *a, int *b) {
  int tmp;

  tmp = *a;
  *a = *b;
  *b = tmp;
}

int partition(int A[], int p, int r) {
    int pivot = A[p];
    int h = p;

    for (int k = p + 1; k <= r; k++) {
        if (A[k] < pivot) {
            h = h + 1;
            swap(&A[h], &A[k]);
            comparisonCount++;
        }
    }
    swap(&A[p], &A[h]);
    
    return h;
}

int randomizedPartition(int A[], int p, int r) {
    int pivot = rand() % (r - p + 1) + p;
    swap(&A[r], &A[pivot]);
    
    return partition(A, p, r);
}

void quickSort(int A[], int p, int r) {
    if (p < r) {
        int q = partition(A, p, r);
        quickSort(A, p, q - 1);
        quickSort(A, q + 1, r);
    }
}

void randomizedQuickSort(int A[], int p, int r) {
    if (p < r) {
        int q = randomizedPartition(A, p, r);
        randomizedQuickSort(A, p, q - 1);
        randomizedQuickSort(A, q + 1, r);
    }
}

void readFile(string fname, int A[]) {
    ifstream file(fname);
    string line;
    
    int index = 0;
    while (!file.eof()) {
        getline(file, line);
        
        stringstream ss(line);
        string num;
        while (getline(ss, num, '\t'))
            A[index++] = stoi(num);
    }
}

int main() {
    string fname;
    cin >> fname;

    int A[50];
    
    readFile(fname, A);
    insertionSort(A, 50);
    cout << "InsertSort: " << comparisonCount << endl;
    
    comparisonCount = 0;
    readFile(fname, A);
    quickSort(A, 0, 50);
    cout << "QuickSort: " << comparisonCount << endl;
    
    comparisonCount = 0;
    readFile(fname, A);
    randomizedQuickSort(A, 0, 50);
    cout << "Randomized QuickSort: " << comparisonCount << endl;
    
    cout << endl;
}


