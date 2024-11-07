#include <iostream>
using namespace std;

/*header call here*/
#include <vector>
#include <algorithm>

/*global variable declare here*/

/*function declare here*/
void function(int* arr, int size) {
    vector<int> dp(size, -1);
    vector<int> stones(arr, arr + size);

    dp[0] = stones[0];
    for (int i = 0; i < size; i++) {
        int k = i == 0 ? 1 : dp[i] - stones[i-1];

        for (int jump : {k - 3, k, k + 1, k + 2}) {
            if (jump <= 0 || (i == 0 && jump != 1))
                continue;

            int next_pos = stones[i] + jump;
            auto it = lower_bound(stones.begin() + i + 1, stones.end(), next_pos);

            if (it != stones.end() && *it == next_pos) {
                int next_idx = distance(stones.begin(), it);
                dp[next_idx] = max(dp[next_idx], stones[next_idx]);
            }
        }
    }

    cout << *max_element(dp.begin(), dp.end()) << endl;
}

int main() {
    int size;
    cin >> size;

    int* input = new int[size];
    for (int idx = 0; idx < size; idx++) {
        cin >> input[idx];
    }

    /*local variable declare here*/

    /*function call here*/
    function(input, size);

    delete[] input;
    return 0;
}