#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

int getMinimumRest();
void process(int, int);
int getRest();
bool isRest();
bool isDone();
bool isLastIO();

int n = 0, isIOLast;
vector<int> idx;
vector<vector<int>> cpu;

int main(int argc, const char * argv[]) {
    ifstream ifs("multi2.in");
    ofstream ofs("multi2.out");
    
    bool isFirstLine = true;
    int processor = 0, rest = 0, total = 0, totalRest = 0;
    
    // Input & Parsing process
    while (ifs.peek() != EOF) {
        string line;
        getline(ifs, line);
        
        vector<string> words;
        stringstream sstream(line);
        string word;
        
        if (isFirstLine) {
            n = stoi(line);
            
            for (int i = 0; i < n; i++) {
                vector<int> processor;
                cpu.push_back(processor);
                idx.push_back(0);
            }
            
            isFirstLine = false;
            continue;
        }
        
        while(getline(sstream, word, ' ')) {
            int k = stoi(word);
            cpu[processor].push_back(k);
            if (k == -1) processor++;
        }
    }
    
    // Scheduling process
    while (true) {
        if (isDone()) break;
        if (isRest()) {
            rest = getRest();
            totalRest += rest;
            total += rest;
        }
        
        for (int i = 0; i < n; i++) {
            if (idx[i] == cpu[i].size() - 1) continue;
            if (idx[i] % 2 == 1) continue;
            
            int curr = cpu[i][idx[i]];
            int min = cpu[i][idx[i]];
            
            total += curr;
            cpu[i][idx[i]] = 0;
            idx[i]++;
            
            process(i, min);
            break;
        }
    }
    
    // Output process
    if (isLastIO()) totalRest -= rest;
    
    ofs << totalRest << " " << total << endl;
    ofs.close();
    
    return 0;
}

// Get rest value
int getMinimumRest() {
    int min = INT_MAX;
    
    for (int j = 0; j < n; j++)
        if (cpu[j][idx[j]] > 0 && cpu[j][idx[j]] < min)
            min = cpu[j][idx[j]];
    
    return min;
}

// Process CPU Works
void process(int i, int min) {
    for (int j = 0; j < n; j++)
        if (j != i && idx[j] % 2 == 1) {
            if (cpu[j][idx[j]] > min) cpu[j][idx[j]] -= min;
            else if (cpu[j][idx[j]] == -1) continue;
            else {
                if (cpu[j].size() - 1 > idx[j] + 1)
                    min = cpu[j][idx[j]];
                cpu[j][idx[j]] = 0;
                idx[j]++;
            }
        }
}

// Process Rest
int getRest() {
    int rest = getMinimumRest();
    
    for (int i = 0; i < n; i++)
        if (idx[i] != cpu[i].size() - 1) {
            cpu[i][idx[i]] -= rest;
            if (cpu[i][idx[i]] == 0) idx[i]++;
        }
    return rest;
}

// Check CPU is resting
bool isRest() {
    for (int i = 0; i < n; i++)
        if (idx[i] != cpu[i].size() - 1)
            if (idx[i] % 2 == 0)
                return false;
    
    return true;
}

// Check CPU has done working
bool isDone() {
    for (int i = 0; i < n; i++)
        if (idx[i] != cpu[i].size()-1)
            return false;
    return true;
}

// Check CPU works on last I/O
bool isLastIO() {
    int sum = 0;
    
    for (int i = 0; i < n; i++)
        sum += cpu[i].size() - 1;
    
    if (sum % 2 == 0) return true;
    else return false;
}
