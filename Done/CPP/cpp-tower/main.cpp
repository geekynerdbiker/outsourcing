#include <iostream>
#include <cmath>

using namespace std;

char **arr;
char tower[][6] = { "  $  ", " $ $ ", "$$$$$" };

void solve(int n, int x, int y) {
    if (n == 1) {
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 5; j++)
                arr[y + i][x + j] = tower[i][j];
        return;
    }
    
    solve(n / 2, x + 3 * n / 2, y);
    solve(n / 2, x, y + 3 * n / 2);
    solve(n / 2, x + 3 * n, y + 3 * n / 2);
}

int main(int argc, const char * argv[]) {
    int n;
    
    cout << "Input: ";
    cin >> n;
    
    n = 3 * pow(2, n-1);
    
    arr = new char*[n];
    for (int i = 0; i < n; i++)
        arr[i]= new char[n*2];
    
    solve(n/3, 0, 0);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 2 * n - 1; j++) {
            char c = arr[i][j] == '$' ? '$' : ' ';
            cout << c;
        }
        cout << endl;
    }
    
    return 0;
}

