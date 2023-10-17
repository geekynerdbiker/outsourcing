//
//  BST.cpp
//  cpp-cube
//
//  Created by Jacob An on 2022/06/10.
//

#include <stdio.h>
#include <string.h>
#include "BST.h"


BST::BST(char input[50]) {
    strcpy(n, input);
    right = NULL;
    left = NULL;
}
