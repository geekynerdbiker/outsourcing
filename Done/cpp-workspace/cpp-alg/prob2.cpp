#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <limits>
#include <cstring>
#include <cmath>
using namespace std;

vector<vector<bool>> subsetSum(vector<int> set, int n, int L) {
    vector<vector<bool>> subset;
    
    for (int i = 0; i <= n; i++) {
        vector<bool> v;
        v.push_back(true);
        for (int j = 1; j <= L; j++) {
            v.push_back(false);
        }
        subset.push_back(v);
    }
    
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= L; j++) {
            if (j < set[i - 1])
                subset[i][j] = subset[i - 1][j];
            if (j >= set[i - 1])
                subset[i][j] = subset[i - 1][j] || subset[i - 1][j - set[i - 1]];
        }
    }
    
    return subset;
}

void backTrack(vector<int> set, vector<vector<bool>> memo, vector<int> *result, int n, int L) {
    if (n == 0)
        return;
    
    if (memo[n][L]) {
        if (memo[n-1][L] == 0) {
            result->push_back(n-1);
            backTrack(set, memo, result, n - 1, L - set[n - 1]);
        } else {
            backTrack(set, memo, result, n - 1, L);
        }
    } else {
        backTrack(set, memo, result, n, L - 1);
    }
}

int prob2(string inputFile, string outputFile) {
    vector<int> set;
    
    string line;
    ifstream ifile(inputFile);
    ofstream ofile(outputFile);
    
    if (!ifile.is_open()) {
        cerr << "Could not open input file" << endl;
        return EXIT_FAILURE;
    }
    
    if (!ofile.is_open()) {
        cerr << "Could not open output file" << endl;
        return EXIT_FAILURE;
    }
    
    int n = 0, iter = 0, L = 0;
    while (getline(ifile, line)) {
        if (n == 0) {
            n = atoi(line.c_str());
        } else if (iter < n) {
            int k = atof(line.c_str());
            set.push_back(k);
            
            iter++;
        } else {
            L = atoi(line.c_str());
        }
    }
    
    vector<vector<bool>> memoization;
    vector<int> result;
    memoization = subsetSum(set, n, L);
    if (memoization[n][L]) {
        ofile << 1 << endl;
        backTrack(set, memoization, &result, n, L);
        ofile << result.size() << endl;
        for (int i = result.size() - 1; i >= 0; i--)
            ofile << result[i] << endl;
    } else
        cout << 0 << endl;
    
    ifile.close();
    ofile.close();
    return 0;
}

int main(int argc, char** argv) {
    string line;
    ifstream ifile("SS_test_command.txt");
    
    if (!ifile.is_open()) {
        cerr << "Could not open input file" << endl;
        return EXIT_FAILURE;
    }
    
    int n = 0;
    while (getline(ifile, line)) {
        if (n == 0) {
            n = atoi(line.c_str());
        } else {
            stringstream sstream(line);
            string token;
            
            getline(sstream, token, ' ');
            string inputFile = token;
            
            getline(sstream, token, '\r');
            string outputFile = token;
            prob2(inputFile, outputFile);
        }
    }
    ifile.close();
}
