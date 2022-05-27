#include <string>
#include <vector>
#include <iostream>
#include <regex>
#include <set>
#include <bitset>
#include <algorithm>

using namespace std;

class Util{
public:
    string intToBinString(int size, int val){
        string bin;
        bin = bitset<100>(val).to_string();
        bin = bin.substr(100-size);
        return bin;
    }

    int get1s(string x) {
        // returns the number of 1s in a binary string
        int count = 0;
        for (int i = 0; i < x.size(); ++i){
            if (x[i] == '1')
                count++;
        }
        return count;
    }

    bool compare(string a, string b) {
        int count = 0;
        for(int i = 0; i < a.length(); i++) {
            if (a[i]!=b[i])
                count++;
        }

        if(count == 1)
            return true;

        return false;
    }

    string getDiff(string a, string b) {
        for(int i = 0; i < a.length(); i++) {
            if (a[i]!=b[i])
                a[i]='2';
        }

        return a;
    }

    bool checkEmpty(vector< vector< string> > table){
        for (int i = 0; i < table.size(); ++i){
            if (table[i].size()!=0) {
                return false;
            }
        }
        return true;
    }
};

class Tabulation{
private:
    Util util;
    vector< int > minInt;
    vector< string > minBin;
    int nBits;
    int nMin;
    vector< vector< string> > table;
    vector< string > primeImp;
//    vector< string > essentialPrimeImp;
    vector< set<int> > functions;



public:
    bool initialise(vector<int> input) {
        if (input.empty())
            return false;

        nBits = input.at(0);
        nMin = input.at(1);

        for (int i = 0; i < nMin; ++i){
            minInt.push_back(input.at(i+2));
            minBin.push_back(util.intToBinString(nBits, input.at(i+2)));
        }

        table = vector< vector< string> >(nBits+1);

        return true;
    }

    vector< string > setPrimeImp(vector<int> input) {
        vector< string > result;
        set< string > primeImpTemp;
        createTable();

        while (!util.checkEmpty(table)){
            table = combinePairs(table, primeImpTemp);
        }

        set< string > :: iterator itr;
        for (itr = primeImpTemp.begin(); itr != primeImpTemp.end(); ++itr){
            string x = *itr;
            primeImp.push_back(x);
        }

//        set< string > essentialPrimeImpTemp;
//        for (int i = 0; i < primeImp.size(); i++) {
//            int count = 0;
//            for (int j = 0; j < essentialPrimeImp.size(); j++) {
//                if (primeImp.at(i) == essentialPrimeImp.at(j)) count++;
//            }
//            if(count>1)
//                essentialPrimeImpTemp.insert(primeImp.at(i));
//            result.push_back(regex_replace(primeImp.at(i), regex("2"), "-"));
//        }

        return result;
//        result.push_back("EPI");
//
//        vector< string > binInput;
//        for (int i = 0; i < input.size()-2; i++)
//            binInput.push_back(util.intToBinString(input.at(0), input[i+2]));
//
//        for (int i = 0; i < primeImp.size(); i++) {
//            if (isEssential(binInput[i], primeImp) != "")
//                result.push_back(regex_replace(isEssential(binInput[i], primeImp), regex("2"), "-"));
//        }
//
//        return result;
    }

//    string isEssential(string input, vector< string > pi) {
//        int count = 0;
//        char source[20], target[20];
//        string epi = "";
//
//        strcpy(source, input.c_str());
//        for (int i = 0; i < pi.size(); i++) {
//            bool isPI = true;
//            epi = "";
//            strcpy(target, pi[i].c_str());
//            for (int j = 0; j < pi[i].length(); j++) {
//                if (target[j] != '2' && source[j] != target[j]) {
//                    isPI = false;
//                    break;
//                }
//                epi = pi[i];
//                isPI = true;
//            }
//            if (isPI) count++;
//        }
//
//        return count == 1 ? epi : "";
//    }

    vector< vector< string> > combinePairs(vector< vector< string> > table, set<string>& primeImpTemp) {
        bool checked[table.size()][nMin];
        memset(checked, 0, table.size()*nMin);
        vector< vector< string> > newTable(table.size()-1);


        for (int i = 0; i < table.size() -1; ++i){
            for (int j = 0; j < table[i].size(); ++j){
                for (int k = 0; k < table[i+1].size(); k++){
                    if (util.compare(table[i][j], table[i+1][k])){
                        newTable[i].push_back(util.getDiff(table[i][j], table[i+1][k]));
                        checked[i][j] = true;
                        checked[i+1][k] = true;
                    }
                }
            }
        }

        for (int i = 0; i < table.size(); ++i){
            for (int j = 0; j < table[i].size(); ++j){
                if (!checked[i][j]) {
                    primeImpTemp.insert(table[i][j]);
//                    essentialPrimeImp.push_back(table[i][j]);
                }
            }
        }

        return newTable;
    }

    void createTable() {
        for (int i = 0; i < nMin; ++i){
            int num1s = util.get1s(minBin[i]);
            table[num1s].push_back(minBin[i]);
        }
    }

    void printTable() {
        for (int i = 0; i < nMin; i++) {
            for (int j = 0; j < table.size(); j++)
                cout << table.at(i).at(j) << " ";
            cout << endl;
        }
    }
    
    void getPosComb(vector< set<int> > &patLogic, int level, set<int> prod, set< set<int> > &posComb) {
        // a recursive function to multiple elements of set patLogic and store it in set posComb
        if (level == patLogic.size()){
            set<int> x = prod;
            posComb.insert(x);
            return;
        }
        else{
            set<int > :: iterator itr;
            for (itr = patLogic[level].begin(); itr != patLogic[level].end(); ++itr){

                int x = *itr;
                bool inserted = prod.insert(x).second;
                getPosComb(patLogic, level+1, prod, posComb);
                if (inserted){
                    prod.erase(x);
                }
            }
        }
    }
};

vector<string> solution(vector<int> minterm) {
    vector<string> answer;

    Tabulation tab;
    bool result = tab.initialise(minterm);
    if (result)
        answer = tab.setPrimeImp(minterm);
    tab.printTable();
    
    return answer;
}

int main(int argc, char* argv[]) {
    vector< string > v = solution({3, 6, 0, 1, 2, 3, 4, 5});
}
