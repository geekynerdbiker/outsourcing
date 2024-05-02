#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <regex>

using namespace std;


void generateRandomSentence(const unordered_map<string, int>& hm1, const unordered_map<string, string>& hm2) {
    string key;
    srand((unsigned)time(NULL));
    int val = rand() % hm1.size();
    
    for (pair<string,int> elem : hm1) {
        if (elem.second == val)
            key = elem.first;
    }

    cout << key << " ";
    while (hm2.find(key) != hm2.end()) {
        string val = hm2.find(key)->second;
        
        int idx = 0;
        for (int i = 0; i < val.length(); i++)
            if (val[i] == ' ') {
                idx = i;
                break;
            }
        cout << val.substr(idx, val.length()-1) << " ";
        key = val;
    }

}

void run(const unordered_map<string, int>& hm1, const unordered_map<string, string>& hm2) {
    int command;
    do {
        cout << "\nChoose options below.\n1) Generate a sentence.\n2) Finish.\n" << endl;
        cin >> command;
        
        switch (command) {
            case 1:
                generateRandomSentence(hm1, hm2);
                cout << "\n";
                break;

            default:
                break;
        }
    } while (command != 2);
}

int main() {
    string filename("war_peace_plain.txt");
    unordered_map<string, int> hm1(1024);
    unordered_map<string, string> hm2(1024);
    
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Could not open the file - '" << filename << "'" << endl;
        return EXIT_FAILURE;
    }
    
    stringstream ss;
    ss << file.rdbuf();
    
    string full_text = ss.str();
    size_t pos = 0;
    std::string token;
    
    while (true) {
        pos = full_text.find("\r\n");
        if (pos < 0 || pos >= full_text.length())
            break;
        full_text.erase(pos+1, 1);
        if (full_text[pos] == '\r') {
            if (pos == 0)
                full_text.erase(pos, 1);
            else
                full_text[pos] = ' ';
        }
    }
    
    while (true) {
        pos = full_text.find(",");
        if (pos < 0 || pos >= full_text.length())
            break;
        full_text.erase(pos, 1);
    }
    
    while (true) {
        pos = full_text.find("?");
        if (pos < 0 || pos >= full_text.length())
        break;
        full_text.replace(pos, 1,  ".");
    }
    
    while (true) {
        pos = full_text.find("!");
        if (pos < 0 || pos >= full_text.length())
            break;
        full_text.replace(pos, 1,  ".");
    }
    
    while (true) {
        pos = full_text.find("“");
        if (pos < 0 || pos >= full_text.length())
            break;
        full_text.replace(pos, 1,  "");
    }
    while (true) {
        pos = full_text.find("”");
        if (pos < 0 || pos >= full_text.length())
            break;
        full_text.replace(pos, 1,  "");
    }
    
    istringstream is(full_text);
    string line;
    vector<string> lines;
    
    while (getline(is, line, '.'))
        lines.push_back(line);
    
    int hash_index = 0;
    for (auto &token : lines) {
        int index = 0;
        bool isSpace = false;
        
        while (token[0] == ' ')
            token.erase(0, 1);
        for (int i = 0; i< token.length(); i++) {
            if (!isSpace && token[i] == ' ') {
                isSpace = true;
                continue;
            } if (isSpace && token[i] == ' ') {
                index = i;
                break;
            }
        }
        
        std::string key = token.substr(0, index);
        if (key.compare("") == 0)
            continue;
        hm1.insert(make_pair(key, hash_index++));
        
        string buf2;
        vector<string> words;
        
        istringstream is2(token);
        while (getline(is2, buf2, ' '))
            words.push_back(buf2);
        if (words.size() > 2) {
            for (int i = 0; i < words.size() - 2; i++) {
                std::string curr = words[i];
                std::string next = words[i+1];
                std::string nextnext = words[i+2];
                
                std::string key = curr + " " + next;
                std::string val = next + " " + nextnext;
                hm2.insert(make_pair(key, val));
            }
        }
    }
    
    
    run(hm1, hm2);
    
    cout << "Thank you!" <<endl;
    file.close();
    return 0;
}
