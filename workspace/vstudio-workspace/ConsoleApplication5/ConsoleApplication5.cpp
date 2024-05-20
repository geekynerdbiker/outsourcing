#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <queue>

using namespace std;

int compare(pair<int, int> p1, pair<int, int> p2) {
    return p1.first > p2.first;
}

int compare2(pair<int, int> p1, pair<int, int> p2) {
    return p1.second < p2.second;
}

void method1(int n, int k, vector<pair<int, int>> scores) {
    vector<pair<int, int>> differences;
    for (int i = 0; i < n - 1; i++) {
        pair<int, int> item;

        item.first = scores[i].first - scores[i + 1].first;
        item.second = i;

        differences.push_back(item);
    }

    sort(differences.begin(), differences.end(), compare);

    int ans = 0;
    vector<int> group_index;
    for (int i = 0; i < k - 1; i++) {
        ans += differences[i].first;
        group_index.push_back(differences[i].second);
    }

    cout << ans << endl;

    sort(group_index.begin(), group_index.end());

    vector<vector<pair<int, int>>> groups;

    int start = 0, end = 0;
    for (int i = 0; i < k - 1; i++) {
        end = group_index[i];
        vector<pair<int, int>> group;
        for (int j = start; j <= end; j++) {
            pair<int, int> item;

            item = scores[j];
            group.push_back(item);
        }
        groups.push_back(group);
        start = end + 1;
    }

    vector<pair<int, int>> group;
    for (int i = end + 1; i < n; i++) {
        pair<int, int> item;

        item = scores[i];
        group.push_back(item);
    }
    groups.push_back(group);
    for (int i = 0; i < groups.size(); i++) {
        sort(groups[i].begin(), groups[i].end(), compare2);
    }

    ofstream fout("Partition1.txt");
    if (fout.is_open()) {
        for (int i = 0; i < groups.size(); i++) {
            for (int j = 0; j < groups[i].size() - 1; j++) {
                fout << groups[i][j].second << "(" << groups[i][j].first << ") ";
            }
            fout << groups[i][groups[i].size() - 1].second << "(" << groups[i][groups[i].size() - 1].first << ")" << endl;

        }
    }
    else {
        cout << "Error: Cannot write file." << endl;
    }
}



void method2(int n, int k, vector<pair<int, int>> scores) {
   vector<priority_queue<double, vector<double>, greater<double>>> groups(k);
   vector<priority_queue<double, vector<double>, greater<double>>> index_groups(k);

   for (pair<int, int> item : scores) {
       double min_variance = numeric_limits<double>::max();
       int index = 0;

       for (int i = 0; i < k; ++i) {
           double variance = groups[i].empty() ? 0 : groups[i].top() - item.first;
           if (variance < min_variance) {
               min_variance = variance;
               index = i;
           }
       }
       groups[index].push(item.first);
       index_groups[index].push(item.second);
   }

   vector<vector<int>> result(k);
   vector<vector<int>> index_result(k);
   vector<double> variances(k);

   for (int i = 0; i < k; ++i) {
       while (!groups[i].empty()) {
           result[i].push_back(groups[i].top());
           index_result[i].push_back(index_groups[i].top());
           groups[i].pop();
           index_groups[i].pop();

           // 분산 계산
           if (result[i].size() == 1) {
               variances[i] = 0;
           }
           else {
               double mean = 0;
               for (int num : result[i]) {
                   mean += num;
               }
               mean /= result[i].size();

               double variance = 0;
               for (int num : result[i]) {
                   variance += pow(num - mean, 2);
               }
               variance /= result[i].size();

               variances[i] = variance;
           }
       }
   }
   
   vector<vector<pair<int, int>>> results;

   for (int i = 0; i < result.size(); i++) {
       vector<pair<int, int>> group;
       for (int j = 0; j < result[i].size(); j++) {
           pair<int, int> item;
           item.first = result[i][j];
           item.second = index_result[i][j];
           group.push_back(item);
       }
       results.push_back(group);
   }
      
   double sum = 0;
   for (double variance : variances) {
       sum += variance;
   }

   cout << sum << endl;

    for (int i = 0; i < results.size(); i++) {
        sort(results[i].begin(), results[i].end(), compare2);
    }

    ofstream fout("Partition2.txt");
    if (fout.is_open()) {
        for (int i = 0; i < results.size(); i++) {
            for (int j = 0; j < results[i].size() - 1; j++) {
                fout << results[i][j].second << "(" << results[i][j].first << ") ";
            }
            fout << results[i][results[i].size() - 1].second << "(" << results[i][results[i].size() - 1].first << ")" << endl;

       }
    }
    else {
        cout << "Error: Cannot write file." << endl;
    }
}

int main() {
    int n, k;
    cin >> n >> k;

    vector<pair<int, int>> scores;
    for (int i = 0; i < n; ++i) {
        int score;
        cin >> score;

        pair<int, int> item;

        item.first = score;
        item.second = i+1;

        scores.push_back(item);
    }

    sort(scores.begin(), scores.end(), compare); 

    method1(n, k, scores);
    method2(n, k, scores);

    return 0;
}
