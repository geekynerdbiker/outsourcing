//
//  main.cpp
//  cpp-set
//
//  Created by Jacob An on 2022/10/17.
//

#include <iostream>
#include "Set.h"

int main(int argc, const char * argv[]) {
    Set s1, s2, resultSet;
    
    cout << "Input 2 sets of integers(Each set should end with negative value)." << endl;
    cin >> s1 >> s2;
    resultSet = s1 | s2;
    cout << "Union is " << resultSet << endl;
    resultSet = s1 & s2;
    cout << "Intersection is " << resultSet << endl;
    return 0;
}
