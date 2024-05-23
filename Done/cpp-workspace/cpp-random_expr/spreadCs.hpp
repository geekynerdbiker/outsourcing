#include <vector>
using namespace std;

class SpreadCs {
public:
    SpreadCs();
    bool run();
    vector<char> randomExprGenerate();
    bool answerCheck(vector<char>, int);
    int getTrueAnswer(vector<char>);
    vector<char> mid2post(vector<char>);
    int evalPostfix(vector<char>);
    int evalExpr();
    void insertParentheses(int); // Maybe useful if you use DFS

private:
    bool inserted[20]; // Maybe useful if you use DFS
    int maximum = -2147483647;
    int N;
    vector<char> expr;
};