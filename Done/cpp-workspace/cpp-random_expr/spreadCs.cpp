#include <iostream>
#include <vector>
#include <stack>
#include <random>
#include "spreadCs.hpp"

#include <ctime>
#include <cstring>

using namespace std;

SpreadCs::SpreadCs() {
    // Implement Here!
    for (int i = 0; i < 20; ++i) {
        inserted[i] = false;
    }
    N = 0;
    maximum = -2147483647;
}

vector<char> SpreadCs::randomExprGenerate() {
    srand(time(NULL));
    // randomly generated odd number which is less than 20
    N = rand() % 10 * 2 + 1;
    cout << "N: " << N << endl;
    // Number in 0 ~ 9 operator in +, -, *
    for (int i = 0; i < N; i++) {
        if (i % 2 == 0) {
            // generate random number in 1 ~ 9
            expr.push_back(rand() % 9 + 1 + '0');
        }
        else {
            expr.push_back(rand() % 3 == 0 ? '+' : rand() % 3 == 1 ? '-' : '*');
        }
    }
    return expr;
}


bool SpreadCs::answerCheck(vector<char> expr, int answer) {
    int trueAnswer = getTrueAnswer(expr);
    cout << "True answer: " << trueAnswer << endl;
    return trueAnswer == answer;
}


int SpreadCs::getTrueAnswer(vector<char> expr) {
    // Implement Here!
    this->expr = expr;
    N = expr.size();

    insertParentheses(0);

    return maximum;
}



vector<char> SpreadCs::mid2post(vector<char> expr) {
    //implement here!
    stack<char> s;
    vector<char> postfix;
    bool paren = false;

    for (int i = 0; i < expr.size(); i++) {
        if (isdigit(expr[i])) {
            postfix.push_back(expr[i]);
        }

        if (inserted[i] && !paren) {
            s.push('(');
            paren = true;
        }
        else if (inserted[i] && paren) {
            while (!s.empty() && s.top() != '(') {
                postfix.push_back(s.top());
                s.pop();
            }
            s.pop();
            paren = false;
        }
        else {
            if (isdigit(expr[i]))
                continue;
            if (expr[i] == '+' || expr[i] == '-') {
                while (!s.empty() && (s.top() == '*' || s.top() == '+' || s.top() == '-')) {
                    postfix.push_back(s.top());
                    s.pop();
                }
            }
            else if (expr[i] == '*') {
                while (!s.empty() && (s.top() == '*')) {
                    postfix.push_back(s.top());
                    s.pop();
                }
            }
            s.push(expr[i]);
        }
    }
    while (!s.empty()) {
        postfix.push_back(s.top());
        s.pop();
    }
    return postfix;
}


int SpreadCs::evalPostfix(vector<char> postfix) {
    // Implement Here!
    stack<int> s;

    for (char& i : postfix) {
        if (isdigit(i)) {
            s.push(i - '0');
        }
        else {
            int a = s.top();
            s.pop();
            int b = s.top();
            s.pop();
            if (i == '+') {
                s.push(a + b);
            }
            else if (i == '-') {
                s.push(b - a);
            }
            else if (i == '*') {
                s.push(a * b);
            }
        }
    }
    if (!s.empty()) {
        return s.top();
    }
    else {
        return -1;
    }
}

int SpreadCs::evalExpr() {
    vector<char> postfix = mid2post(expr);
    return evalPostfix(postfix);
}


void SpreadCs::insertParentheses(int i) {
    if (i >= N) {
        vector<char> postfix = mid2post(expr);
        int result = evalPostfix(postfix);
        if (result > maximum) {
            maximum = result;
        }
        return;
    }
    for (int j = i; j < N; j += 2)
    {
        if (j + 2 >= N)
        {
            insertParentheses(j + 1);
            continue;
        }
        if (inserted[j] == false && inserted[j + 2] == false) {
                inserted[j] = true;
                inserted[j + 2] = true;
                insertParentheses(j + 2);
                inserted[j] = false;
                inserted[j + 2] = false;
        }
    }
}


bool SpreadCs::run() {
    cout << "Calculate the maximum value of the expression by inserting parentheses." << endl;
    cout << "No nested parentheses are allowed." << endl;
    cout << "Expr: ";
    randomExprGenerate();
    for (int i = 0; i < N; i++) {
        cout << expr[i];
    }
    cout << endl;
    cout << "Type the answer: ";
    int answer;
    cin >> answer;
    bool isCorrect = answerCheck(expr, answer);
    if (isCorrect) {
        cout << "Correct!" << endl;
    }
    else {
        cout << "Wrong!" << endl;
    }
    return isCorrect;
}

///////////////////////////////////////////////////
int main() {
}

/*
2*8*3*4+(5+8)*(1+8)*(5+6) => 1479

(2*8)*3*4+(5+8)*(1+8)*(5+6)

2*6*1-2*8*3+6*6-7+2 => 866

2*(5-2)*5*(1+1)-7 => 53
*/
