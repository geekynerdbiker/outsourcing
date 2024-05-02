#include <iostream>
#include <sstream>
#include "PriorityQueue.hpp"

using namespace std;
int main(int argc, char *argv[]) {
    Printer p;
    Document d("","",-1);
    string input;
    
    int T, N, M;
    cin >> T;
    cin.ignore();
    
    for (int t = 0; t < T; t++) {
        cin >> N;
        cin.ignore();
        for (int n = 0; n < N; n++) {
            getline(cin, input);
            stringstream ss(input);
            string command, id, title, priority;
            ss >> command >> id >> title >> priority;
            
            if (command.compare("I") == 0)
                p.insertDoc(id, title, stoi(priority));
            else if (command.compare("P") == 0) {
                if (p.emptyPrinter())
                    cout << "Empty printer." << endl;
                else {
                    d = p.popDoc();
                    cout << d.getId() << " " << d.getTitle() << endl;
                }
            } else if (command.compare("T") == 0) {
                if (p.emptyPrinter())
                    cout << "Empty printer." << endl;
                else {
                    d = p.topDoc();
                    cout << d.getId() << " " << d.getTitle() << endl;
                }
            } else if (command.compare("S") == 0) {
                if (p.emptyPrinter())
                    cout << "Empty printer." << endl;
                else {
                    cout << p.sizePrinter() << endl;
                }
            } else if (command.compare("E") == 0) {
                if (p.emptyPrinter())
                    cout << "1" << endl;
                else
                    cout << "0" << endl;
            }
        }
        cin >> M;
        cin.ignore();
        
        if (M > p.sizePrinter()) {
            cout << "M > printer.size()" << endl;
        } else {
            for (int m = 0; m < M; m++)
                d = p.popDoc();
            cout << d.getId() << " " << d.getTitle() << endl;
        }
        
        while (!p.emptyPrinter())
            p.popDoc();
    }
    
    return 0;
}

/*
[ TEST INPUT ]

3
10
I AAA DS 1
T
I BBB DCN 3
I CCC LinearAlgebra 2
I DDD Energy 4
E
S
I EEE Circuits 5
P
P
2
7
I abcd Attendance 13
I bbdie FinalExam 6
I urgg FirstQuiz 5
I dbwo4B FirstPR 1
I go5G SecondQuiz 9
I back SecondPR 7
I ffci11 QnA 2
5
1
I ABC EmptyDoc 6
2
 */
