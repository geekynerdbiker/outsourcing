/*
 MIT License - see LICENSE file for full details
 
 Copyright (c) 2023 KimDongHyun
 
 Permission is hereby granted, free of charge, to any person obtaining a copy of
 this software and associated documentation files, to deal in the Software
 without restriction, including without limitation the rights to use, copy,
 modify, merge, publish, distribute, sublicense, and/or sell copies of the
 Software.
 
 Written by KimDongHyun on 2023-11-10
 */

#include <iostream>
#include <sstream>
#include <string>

#include "AVLTree.h"

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    int T;
    cin >> T;
    
    for (int i = 0; i < T; i++) {
        int Q;
        cin >> Q;
        
        AVLTree<int> avl;
        for (int j = 0; j < Q; j++) {
            string input;
            cin >> input;
            
            stringstream ss(input);
            string command, param;
            ss >> command >> param;
            
            if (command == "insert") {
                avl.insert(stoi(param));
            } else if (command == "find") {
                avl.find(stoi(param));
            } else if (command == "size") {
                avl.size();
            } else if (command == "empty") {
                avl.empty();
            } else if (command == "minimum") {
                avl.minimum(stoi(param));
            } else if (command == "maximum") {
                avl.maximum(stoi(param));
            }
        }
    }
    
    return 0;
}
