#include <string>
#include <vector>
#include <sstream>
#include <queue>
#include <iostream>

using namespace std;

int solution1(vector<long long> arr) {
    int answer = 0;
    long long tolerance = 0;

    for (int i = 0; i < arr.size(); i++) {
        int len = 1;

        for (int j = i; j < arr.size() - 1; j++) {
            if (i == j) {
                tolerance = arr[j] - arr[j+1];
                len++;
                continue;
            } if (arr[j] - arr[j+1] == tolerance) len++;
            else {
                i = j-1;
                break;
            }
        }
        if (len > answer)
            answer = len;
    }
    return answer;
}

vector<int> solution2(vector<vector<string>> folders, vector<vector<string>> files, vector<string> selected, vector<string>excepted) {
    vector<int> answer;
    vector<string> sizes;

    int count = 0;
    for (int i = 0; i < files.size(); i++) {
        bool ex = false;
        for (int j = 0; j < excepted.size(); j++)
            if (!files[i][0].compare(excepted[j])){
                ex = true;
                continue;
            }
        if (ex) continue;

        for (int j = 0; j < selected.size(); j++)
            if (!selected[j].compare("root") || !files[i][2].compare(selected[j])) {
                cout << files[i][0];
                sizes.push_back(files[i][1]);
                count++;
                break;
            }
    }

    for (int i = 0; i < sizes.size(); i++) {
        int size;
        char unit;

        stringstream ss;
        cout << sizes[i] << endl;
        ss << sizes[i];
        ss >> size >> unit;
        cout << size << unit;
    }

    return answer;
}

bool isMovable(int N, int x1, int x2, int y1, int y2) {
    if (x2 < 0 || x2 >= N || y2 < 0 || y2 >= N)
        return false;
    return max(abs(x1-N/2), abs(y1-N/2)) <= max(abs(x2-N/2), abs(y2-N/2));
}

int solution3(int N, vector<int> board) {
    int answer = 0;

    int cost = 0;
    vector<vector<int>> matrix;
    vector<vector<bool>> visited;

    int idx = 0;
    for (int i = 0; i < N; i++) {
        vector<int> matrix_v;
        vector<bool> visited_v;
        for (int j = 0; j < N; j++) {
            matrix_v.push_back(board[idx++]);
            visited_v.push_back(false);
        }
        matrix.push_back(matrix_v);
        visited.push_back(visited_v);
    }

    int dir[4][2] = {{0,1},{1,0},{0,-1},{-1,0}};
    int curr_x = N / 2, curr_y = N / 2;

    queue<pair<int, int>> q;
    cost += matrix[curr_x][curr_y];
    visited[curr_x][curr_y] = true;
    q.push(make_pair(curr_x, curr_y));

    while (!q.empty()) {
        curr_x = q.front().first;
        curr_y = q.front().second;
        q.pop();

        int next_x = -1, next_y = -1, min = -1;
        for (int i = 0; i < 4; i++) {
            int temp_cost = matrix[curr_x + dir[i][0]][curr_y + dir[i][1]];
            if (!isMovable(N, curr_x, curr_x + dir[i][0], curr_y, curr_y + dir[i][1]))
                continue;
            if (visited[curr_x + dir[i][0]][curr_y + dir[i][1]])
                continue;
            if (min == -1 || min > temp_cost) {
                min = temp_cost;
                next_x = curr_x + dir[i][0];
                next_y = curr_y + dir[i][1];
            }
        }

        cost += min;
        if (next_x == 0 || next_y == 0 || next_x == N-1 || next_y == N-1)
            break;

        visited[next_x][next_y] = true;
        q.push(make_pair(next_x, next_y));
    }

    return cost;
}

int solution4(vector<vector<int>> board) {
    int answer = -1;

    int dir[4][2] = {{0,1},{1,0},{0,-1},{-1,0}};
    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board.size(); j++) {
            if (!board[i][j]) {
                for (int k = 0; k < board.size() / 2; k++) {
                    bool isDiamond = false;
                    for (int l = 0; l < 4; l++) {
                        if (board[i+dir[l][0] * k][j+dir[l][1] * k]) {

                        }
                    }
                }
            }
        }
    }

    return answer;
}

int main() {
    printf("Prob 1: \n");
    //    printf("%d\n", solution1({2, 3, 4, -1, -6, -11, 1}));
    //    printf("%d\n", solution1({0, 0, 0, 0, 0}));
    //
    //    printf("Prob 2: \n");
    //    vector<int> rst = solution2({{"food", "root"}, {"meat", "root"}, {"fruit", "root"}, {"animal", "root"}}, {{"cat", "1B", "animal"}, {"dog", "2B", "animal"}, {"fork", "1KB", "meat"}, {"beef", "8B", "meat"}, {"apple", "4B", "fruit"}, {"fire", "83B", "root"}}, {"root", "meat"}, {"fork", "apple"});
    //    printf("%d\n", rst[1]);
    //    printf("Prob 3: \n");
    //    printf("%d\n", solution3(5, {9,3,9,9,9, 5, 2, 7, 8, 9, 8, 1, 5, 8, 9, 6, 1, 8, 7, 9, 9, 9, 9, 9, 9}));
    //    printf("Prob 4: \n");
    printf("%d\n", solution4({{0, 0, 1, 0, 0}, {0, 1, 0, 1, 0},{1, 0, 0, 0, 1},{0, 1, 0, 1, 0},{0, 0, 1, 0, 0}}));

    return 0;
}
