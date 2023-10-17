#include <iostream>
#include <queue>

using namespace std;

int N, W, H;
int center[101][2];

int map[101][101];
int check[101][101];
int visited[101][101];

int start_x, start_y;
int centers;
int start_hp;

int atk[101];
int dx[4] = { 1, 0, -1, 0 };
int dy[4] = { 0, 1, 0, -1 };

void init() {
    start_x = 0;
    start_y = 0;
    start_hp = 0;
    centers = 0;
    
    for (int i = 0; i < W; i++) {
        for (int j = 0; j < 1; j++)
            center[i][j] = 0;
        for (int j = 0; j < H; j++) {
            map[i][j] = 0;
            check[i][j] = 0;
            visited[i][j] = 0;
        }
    }
}

void BFS(int x, int y) {
    visited[x][y] = 1;
    
    queue<pair<int, int>> q;
    queue<int> hp;
    
    q.push(make_pair(x, y));
    hp.push(start_hp);

    while (!q.empty()) {
        int x = q.front().first;
        int y = q.front().second;
        int curr = hp.front();

        q.pop();
        hp.pop();

        for (int i = 0; i < 4; i++) {
            int next_x = x + dx[i];
            int next_y = y + dy[i];
            int next_hp = curr;

            if (0 <= next_x && next_x < W && 0 <= next_y && next_y < H) {
                if (map[next_x][next_y] != 1 && visited[next_x][next_y] == 0) {
                    if (map[next_x][next_y] == 3) {
                        check[next_x][next_y] = check[x][y] + 1;
                        visited[next_x][next_y] = 1;
                    } else if (map[next_x][next_y] < 0)
                        next_hp += map[next_x][next_y];
                    
                    if (next_hp > 0) {
                        check[next_x][next_y] = check[x][y] + 1;
                        visited[next_x][next_y] = 1;
                        q.push(make_pair(next_x, next_y));
                        hp.push(next_hp);
                    }
                }
            }
        }
    }
}

int main(void) {
    cin >> N;
    
    for (int T = 0; T < N; T++) {
        cin >> W >> H;
        init();
        
        centers = 0;
        int index = 0, monsters = 0;
        for (int i = 0; i < W; i++) {
            for (int j = 0; j < H; j++) {
                cin >> map[i][j];
                if (map[i][j] == 4)
                    monsters++;
                else if (map[i][j] == 2) {
                    start_x = i;
                    start_y = j;
                } else if (map[i][j] == 3) {
                    center[index][0] = i;
                    center[index++][1] = j;
                    centers++;
                }
            }
        }
        
        cin >> start_hp;
        for (int i = 0; i < monsters; i++)
            cin >> atk[i];
        
        index = 0;
        for (int i = 0; i < W; i++) {
            for (int j = 0; j < H; j++) {
                if (map[i][j] == 4)
                    map[i][j] = atk[index++] * -1;
            }
        }
        
        BFS(start_x, start_y);
        
        int min = 1000000;
        for (int i = 0; i < centers; i++)
            if (check[center[i][0]][center[i][1]] < min)
                if (check[center[i][0]][center[i][1]] != 0)
                    min = check[center[i][0]][center[i][1]];
        if (min != 1000000)
            cout << min << endl;
        else
            cout << "NO" << endl;
    }
}
/*
[ INPUT ]
3
3 3
2 4 4
1 4 4
3 4 3
15
4 5 13 4 9
5 5
0 0 0 0 2
4 1 1 4 1
0 4 0 0 0
1 1 4 1 4
3 0 0 0 0
15
4 9 2 6 3
5 5
0 0 0 0 2
4 1 1 4 1
0 4 0 0 0
1 1 4 1 4
3 1 0 0 0
15
4 9 2 6 3

[ OUTPUT ]
4
10
NO
 */
