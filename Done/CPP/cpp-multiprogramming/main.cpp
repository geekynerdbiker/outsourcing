#include <iostream>
#include <fstream>

using namespace std;

int getMinimumRest();
int getMaximumRest();
void process(int, int);
int getRest();
int getLastRest();
bool isRest();
bool isDone();

void getLog();

int n = 0, totalRest = 0;
int rest = 0, total = 0;
int idx[1000] = { 0 };
int cpuSize[1000] = { 0 };
int cpu[1000][100] = { 0 };

int main(int argc, const char * argv[]) {
    ifstream ifs("t1.in");
    ofstream ofs("multi.out");
    
    bool isFirstLine = true;
    
    int number = 0, cpuNumber = 0, t = 0, state = 0; // 0: work, 1: rest
    

    // Input & Parsing process
    while (ifs >> number) {
        if (isFirstLine) {
            n = number;
            isFirstLine = false;
            continue;
        } else {
            cpu[cpuNumber][t++] = number;
            if (number == -1) {
                cpuSize[cpuNumber] = t;
                t = 0;
                cpuNumber++;
            }
        }
    }
    
    // Scheduling process
    while (true) {
//        getLog(); // Not nessecsery
        if (isDone()) break;
        if (isRest()) {
            rest = getRest();
            totalRest += rest;
            total += rest;
            if (isDone()) {
                state = 1;
                break;
            }
        }
        
        for (int i = 0; i < n; i++) {
            if (idx[i] == cpuSize[i] - 1) continue;
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
    if (state) totalRest -= rest;

    cout << totalRest << " " << total << endl;
//    ofs << totalRest << " " << total << endl;
//    ofs.close();
    
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

int getMaximumRest() {
    int max = 0;
    
    for (int j = 0; j < n; j++)
        if (cpu[j][idx[j]] > 0 && cpu[j][idx[j]] > max)
            max = cpu[j][idx[j]];
    
    return max;
}

// Process CPU Works
void process(int i, int min) {
    for (int j = 0; j < n; j++)
        if (j != i && idx[j] % 2 == 1) {
            if (cpu[j][idx[j]] > min) cpu[j][idx[j]] -= min;
            else if (cpu[j][idx[j]] == -1) continue;
            else {
                cpu[j][idx[j]] = 0;
                idx[j]++;
            }
        }
}

// Process Rest
int getRest() {
    int rest = getMinimumRest();
    
    for (int i = 0; i < n; i++)
        if (idx[i] != cpuSize[i] - 1) {
            cpu[i][idx[i]] -= rest;
            if (cpu[i][idx[i]] == 0) idx[i]++;
        }
    return rest;
}

int getLastRest() {
    int rest = getMaximumRest();
    
    for (int i = 0; i < n; i++)
        if (idx[i] != cpuSize[i] - 1) {
            if (cpu[i][idx[i]] >= rest)
                cpu[i][idx[i]] -= rest;
            else cpu[i][idx[i]] = 0;
            if (cpu[i][idx[i]] == 0) idx[i]++;
        }
    return rest;
}


// Check CPU is resting
bool isRest() {
    bool isLastWork = false;
    
    for (int i = 0; i < n; i++) {
        if (idx[i] == cpuSize[i] - 2) {
            isLastWork = true;
        } else if (idx[i] == cpuSize[i] - 1) {
            continue;
        } else {
            isLastWork = false;
            break;
        }
    }
    
    for (int i = 0; i < n; i++)
        if (idx[i] < cpuSize[i] - 1) {
            if (idx[i] % 2 == 0)
                return false;
        }
    if (isLastWork) {
        getLastRest();
        return false;
    }
    return true;
}

// Check CPU has done working
bool isDone() {
    for (int i = 0; i < n; i++)
        if (idx[i] != cpuSize[i] - 1)
            return false;
    return true;
}

void getLog() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < cpuSize[i]; j++)
            printf("%d ", cpu[i][j]);
        printf("\n");
    }
    printf("\n");
}
