//
//  Node.h
//  cpp-cube
//
//  Created by Jacob An on 2022/06/10.
//

#ifndef Node_h
#define Node_h

#include "BST.h"

class Node {
public:
    Node* left;
    Node* right;
    Node* up;
    Node* down;
    Node* front;
    Node* behind;
    
    BST* word;
    
    int z;
    int y;
    int x;
    
    int count;
    
    Node(int zz, int yy, int xx);
    Node(Node& n);
};

#endif /* Node_h */
