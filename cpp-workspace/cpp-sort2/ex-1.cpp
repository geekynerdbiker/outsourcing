#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

void insertionSort(int A[], int n) {
    int i, j, tmp;

    for (i = 1; i < n; i++) {
        tmp = A[i];
        for (j = i; A[j-1] > tmp &&  j > 0; j--)
            A[j] = A[j - 1];
        A[j] = tmp;
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
    
    for (int i = 0; i < 50; i++)
        cout << A[i] << " ";
    cout << endl;
}

