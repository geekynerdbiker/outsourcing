//
//  BST.h
//  cpp-cube
//
//  Created by Jacob An on 2022/06/10.
//

#ifndef BST_h
#define BST_h

class BST {
public:
    char n[50] = {'\0', };
    BST* right;
    BST* left;
    
    BST(char input[50]);
};

#endif /* BST_h */
