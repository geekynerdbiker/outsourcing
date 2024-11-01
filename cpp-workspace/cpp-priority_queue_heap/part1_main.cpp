//#include <iostream>
//#include <sstream>
//#include "PriorityQueue.hpp"
//
//using namespace std;
//int main(int argc, char *argv[]) {
//    PriorityQueue pq(1);
//    string input;
//    
//    while (true) {
//        getline(cin, input);
//        stringstream ss(input);
//        string command, argument;
//        ss >> command >> argument;
//        
//        if (command.compare("I") == 0)
//            pq.insertHeap(stoi(argument));
//        else if (command.compare("P") == 0) {
//            if (pq.emptyHeap())
//                cout << "Empty queue." << endl;
//            else
//                cout << pq.popHeap() << endl;
//        } else if (command.compare("T") == 0) {
//            if (pq.emptyHeap())
//                cout << "Empty queue." << endl;
//            else
//                cout << pq.topHeap() << endl;
//        } else if (command.compare("S") == 0) {
//            if (pq.emptyHeap())
//                cout << "Empty queue." << endl;
//            else
//                cout << pq.sizeHeap() << endl;
//        } else if (command.compare("E") == 0) {
//            if (pq.emptyHeap())
//                cout << "1" << endl;
//            else
//                cout << "0" << endl;
//        }
//        
//    }
//    return 0;
//}
//
///*
//[ TEST INPUT ]
// 
//-1
//20
//E
//I 3
//I 7
//I 11
//T
//I 2
//I 15
//I 5
//T
//S
//I 8
//P
//P
//S
//P
//P
//P
//P
//P
//P
// */
