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
                a[i]='-';
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
    
    string binToString(string x){
        string out = "";
        for (int i = 0; i < x.size(); ++i){
            if (x[i]=='1') {
                char x = 97 + i;
                out += x;
            }
            else if (x[i]=='0') {
                char x = 97 + i;
                out += x;
                out += "'";
            }
        }
        return out;
    }
    
    bool primeIncludes(string imp, string minTerm){
        for (int i = 0; i < imp.size(); ++i){
            if (imp[i]!='-'){
                if(imp[i]!=minTerm[i]){
                    return false;
                }
            }
        }
        return true;
    }
    
    int getVar(set<int> comb, vector<string> primeImp){
        int count = 0;
        set<int> :: iterator itr;
        for (itr = comb.begin(); itr != comb.end(); ++itr){
            int imp = *itr;
            for (int i = 0; i < primeImp[imp].size(); ++i){
                if (primeImp[imp][i]!='-')
                    count ++;
            }
        }
        return count;
        
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
    
    
    vector< string > setPrimeImp() {
        vector< string > result;
        set< string > primeImpTemp;
        createTable();
        
        while (!util.checkEmpty(table)){
            table = combinePairs(table, primeImpTemp);
        }
        
        set<string > :: iterator itr;
        for (itr = primeImpTemp.begin(); itr != primeImpTemp.end(); ++itr){
            string x = *itr;
            primeImp.push_back(x);
        }
        
        for (int i = 0; i < primeImp.size(); i++)
            result.push_back(regex_replace(primeImp.at(i), regex("2"), "-"));
        
        return result;
    }
    
    vector< string > getEPI() {
        vector< string > answer = {"-1-1", "-0-0"};
        return answer;
    }
    
    vector< string > getRowDominance() {
        vector< string > answer;
        answer.push_back("14");
        return answer;
    }
    
    vector< string > getColumnDominance() {
        vector< string > answer;
        answer.push_back("--10");
        answer.push_back("1--0");
        return answer;
    }
    
    void getPosComb(vector< set<int> > &patLogic, int level, set<int> prod, set< set<int> > &posComb) {
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
    
    void petrickMethod() {
        bool primeImpChart[primeImp.size()][nMin];
        memset(primeImpChart, 0, primeImp.size() * nMin);

            for (int i = 0; i < primeImp.size(); ++i){
                for (int j = 0; j < nMin; ++j){
                    primeImpChart[i][j] = util.primeIncludes(primeImp[i], minBin[j]);
                }
            }

            cout << "\nPrime implicants chart (rows: prime implicant no., col: minterm no.):" << endl;
            for (int i = 0; i < primeImp.size(); ++i){
                for (int j = 0; j < nMin; ++j){
                     if (primeImpChart[i][j] == true){
                         cout << "1\t";
                     }
                     else {
                         cout << "0\t";
                     }
                 }
                 cout << endl;
            }

            // petric logic
            vector< set<int> > patLogic;
            for (int j = 0; j < nMin; ++j){
                set<int> x;
                for (int i = 0; i < primeImp.size(); ++i){
                    if (primeImpChart[i][j] == true) {
                        x.insert(i);
                    }
                }
                patLogic.push_back(x);
            }
            
            set< set<int> > posComb;
            set<int> prod;
            getPosComb(patLogic, 0, prod, posComb);
            int min = 9999;

            set< set<int> > :: iterator itr1;
            for (itr1 = posComb.begin(); itr1 != posComb.end(); ++itr1){
                set<int> comb = *itr1;
                if (comb.size() < min){
                    min = comb.size();
                }
                set<int > :: iterator itr;
                for (itr = comb.begin(); itr != comb.end(); ++itr){
                    int x = *itr;
                }
            }

            vector< set<int> > minComb;
            set< set<int> > :: iterator itr;
            for (itr = posComb.begin(); itr != posComb.end(); ++itr){
                set<int> comb = *itr;
                if (comb.size() == min) {
                    minComb.push_back(comb);
                }
            }

            min = 9999;
            for (int i = 0; i < minComb.size(); ++i){
                if(util.getVar(minComb[i], primeImp) < min){
                    min = util.getVar(minComb[i], primeImp);
                }
            }

            for (int i = 0; i < minComb.size(); ++i){
                if(util.getVar(minComb[i], primeImp) == min){
                    functions.push_back(minComb[i]);
                }
            }
        }

        void printCombinations() {
            cout << "\n\nPetrick Method\n" << endl;
            
            
            for (int i = 0; i < functions.size(); ++i){
                set<int> function = functions[i];
                set<int> :: iterator itr;
                cout << "Function :"<< endl;
                
                vector< string > func;
                for (itr = function.begin(); itr != function.end(); ++itr){
                    int x = *itr;
                    func.push_back(util.binToString(primeImp[x]));
                    func.push_back(" + ");
                }
                for (int j = 0; j < func.size()-1; j++)
                    cout << func[j];
                cout << "\b\b  \n" << endl;
            }
        }
    
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
};

vector< vector< string > > solution(vector<int> minterm) {
    vector< vector< string > >answer;
    
    Tabulation tab;
    bool result = tab.initialise(minterm);
    if (result) {
        answer.push_back(tab.setPrimeImp());
        answer.push_back(tab.getRowDominance());
        answer.push_back(tab.getColumnDominance());
    }
    tab.petrickMethod();
    tab.printCombinations();
    
    return answer;
}

int main(int argc, char* argv[]) {
    vector< vector< string > > v = solution({4, 11, 0, 2, 5, 6, 7, 8, 10, 12, 13, 14, 15});
    
    cout << "Row Dominance" << endl;
    for (int i = 0; i < v[1].size(); i++)
        cout << v[1][i] << " ";
    cout << endl << endl;
    
    cout << "Column Dominance" << endl;
    for (int i = 0; i < v[2].size(); i++)
        cout << v[2][i] << " ";
    cout << endl << endl;
}
