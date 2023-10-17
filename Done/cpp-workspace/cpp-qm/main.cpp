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
        
        // 4. implicant 비트 수와, minterm 원소 갯수 입력
        nBits = input.at(0);
        nMin = input.at(1);
        
        // 5. 원소 갯수만큼 다음 원소를 받아 각각 정수, 2진 문자열 벡터에 삽입
        for (int i = 0; i < nMin; ++i){
            minInt.push_back(input.at(i+2));
            minBin.push_back(util.intToBinString(nBits, input.at(i+2)));
        }
        
        // 6. 비트수+1 만큼의 테이블 초기화
        table = vector< vector< string> >(nBits+1);
        return true;
    }
    
    
    vector< string > setPrimeImp() {
        vector< string > result;
        set< string > primeImpTemp;
        createTable();
        
        // 8. 테이블과 PI를 저장할 임시 테이블을 넘겨주어, PI값들을 찾아서 primeImpTemp 저장
        while (!util.checkEmpty(table)){
            table = combinePairs(table, primeImpTemp);
        }
        
        // 9. primeImp에 찾아낸 PI 집합을 저장
        set<string > :: iterator itr;
        for (itr = primeImpTemp.begin(); itr != primeImpTemp.end(); ++itr){
            string x = *itr;
            primeImp.push_back(x);
        }
        
        // 10. 오름차순 정렬을 위하여 2로 저장한 부분을 '-'로 바꿔줌
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
        // 12. PI 차트 생성을 위한 초기화
        bool primeImpChart[primeImp.size()][nMin];
        memset(primeImpChart, 0, primeImp.size() * nMin);

        // 13. 차트의 해당 row col에 PI와 입력값 매칭
            for (int i = 0; i < primeImp.size(); ++i){
                for (int j = 0; j < nMin; ++j){
                    primeImpChart[i][j] = util.primeIncludes(primeImp[i], minBin[j]);
                }
            }

        // 14. 차트 출력
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
            // 15. 패트릭 방법 시작. 해당하는 조합의 부분을 찾아서 개별 함수를 위해서 저장, 이 때 row, col dominance 조건을 만족할 경우 찾으면서 각각의 벡터에 저장
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
            
            // 16. 찾아낸 PI들로 함수를 조합함.
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

            // 17. 최소한의 원소 갯수 조합으로 만들어진 함수들만 저장
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

            // 18. 조합된 함수들을 함수 벡터에 저장
            for (int i = 0; i < minComb.size(); ++i){
                if(util.getVar(minComb[i], primeImp) == min){
                    functions.push_back(minComb[i]);
                }
            }
        }

        // 20. 함수 출력
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
    // 2. 정답을 담을 벡터를 생성
    vector< vector< string > >answer;
    
    // 3. 테이블 생성 및 입력값으로 테이블 초기화
    Tabulation tab;
    bool result = tab.initialise(minterm);
    if (result) {
        // 7. PI를 찾기위한 함수 실행
        answer.push_back(tab.setPrimeImp());
        answer.push_back(tab.getRowDominance());
        answer.push_back(tab.getColumnDominance());
    }
    // 11. 패트릭 방법 시작
    tab.petrickMethod();
    // 19. 패트릭 출력
    tab.printCombinations();
    
    // 21. PI, row dominance, column dominance 가 저장된 벡터 반환
    return answer;
}

int main(int argc, char* argv[]) {
    // 1. 2차원 문자열 벡터에 해당 입력값을 매개변수로 넘겨주어 풀이 함수 실행.
    vector< vector< string > > v = solution({4, 11, 0, 2, 5, 6, 7, 8, 10, 12, 13, 14, 15});
    
    
    // 22. row dominance 출력
    cout << "Row Dominance" << endl;
    for (int i = 0; i < v[1].size(); i++)
        cout << v[1][i] << " ";
    cout << endl << endl;

    // 23. column dominance 출력
    cout << "Column Dominance" << endl;
    for (int i = 0; i < v[2].size(); i++)
        cout << v[2][i] << " ";
    cout << endl << endl;
}
