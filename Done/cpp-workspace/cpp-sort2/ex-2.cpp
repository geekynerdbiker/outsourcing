#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

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
        }
    }
    swap(&A[p], &A[h]);
    
    return h;
}

void quickSort(int A[], int p, int r) {
    if (p < r) {
        int q = partition(A, p, r);
        quickSort(A, p, q - 1);
        quickSort(A, q + 1, r);
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
    quickSort(A, 0, 50);
    
    for (int i = 0; i < 50; i++)
        cout << A[i] << " ";
    cout << endl;
}

