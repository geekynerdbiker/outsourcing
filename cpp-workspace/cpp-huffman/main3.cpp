#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>

using namespace std;

string decode(const string& encoded, const unordered_map<string, char>& huffmanTable) {
    string decoded = "";
    string currentCode = "";

    for (char bit : encoded) {
        currentCode += bit;
        if (huffmanTable.find(currentCode) != huffmanTable.end()) {
            decoded += huffmanTable.at(currentCode);
            currentCode = "";
        }
    }

    if (!currentCode.empty()) {
        cerr << "Decoding error: remaining bits do not match any code." << endl;
    }

    return decoded;
}

int main() {
    ifstream tableFile("table.txt");
    if (!tableFile) {
        cerr << "Error: Could not open table.txt" << endl;
        return 1;
    }

    unordered_map<string, char> huffmanTable;
    string line;
    while (getline(tableFile, line)) {
        if (line.empty()) continue;
        char ch = line[0];
        string code = line.substr(2);
        huffmanTable[code] = ch;
    }
    tableFile.close();

    ifstream codeFile("code.txt");
    if (!codeFile) {
        cerr << "Error: Could not open code.txt" << endl;
        return 1;
    }

    string encoded;
    codeFile >> encoded;
    codeFile.close();

    string decoded = decode(encoded, huffmanTable);

    cout << decoded << endl;

    return 0;
}
