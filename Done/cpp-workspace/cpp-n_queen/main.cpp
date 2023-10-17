#include <iostream>

using namespace std;

int map[10][10] = {0};
int visited[10][10] = {0};

int check(int selected, int i) {
    for (int x = 0; x < 10; x++) {
        if (map[x][i] == 1)
            return 0;
        if (selected-x >= 0 && i-x >= 0 && map[selected-x][i-x] == 1)
            return 0;
        if (selected+x < 10 && i-x >= 0 && map[selected+x][i-x] == 1)
            return 0;
        if (selected-x >= 0 && i+x < 10 && map[selected-x][i+x] == 1)
            return 0;
        if (selected+x < 10 && i+x < 10 && map[selected+x][i+x] == 1)
            return 0;
    }
    return 1;
}

void search(int selected) {
    int i;
    
    i = 0;
    if (selected == 10) {
        for (int x = 0; x < 10; x++)
            for (int y = 0; y < 10; y++)
                if (map[x][y] == 1)
                    cout << y;
        cout << endl;
        
        return;
    } else {
        while (i++ < 10) {
            if (check(selected, i-1)) {
                map[selected][i-1] = 1;
                search(selected+1);
                map[selected][i-1] = 0;
            }
        }
    }
}

int main() {
    search(0);
    
    return 0;
}
