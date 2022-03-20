//
//  main.cpp
//  cpp-cpu-arr
//
//  Created by Jacob An on 2022/03/21.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

vector<pair<int, int>> cpu;
int main(int argc, const char * argv[]) {
    ifstream ifs("multi2.in");
    ofstream ofs("multi2.out");
    
    bool isFirstLine = true;
    int CPURest = 0, workTime = 0;
    while (ifs.peek() != EOF) {
        string line;
        getline(ifs, line);
        
        vector<string> words;
        stringstream sstream(line);
        string word;
        
        if (isFirstLine) {
            isFirstLine = false;
            continue;
        }
        
        bool isOdd = false;
        while(getline(sstream, word, ' ')) {
            int k = 0;
            if (word > "0" && word < "9")
                k = stoi(word);
            if (k == -1) {
                isOdd = false;
                continue;
            }
            if (isOdd) CPURest += k;
            else workTime += k;
            isOdd = !isOdd;
        }
    }
    ofs << CPURest << " " << workTime << endl;
    ofs.close();
    
    return 0;
}
