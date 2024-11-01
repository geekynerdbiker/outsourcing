//
//  Node.cpp
//  cpp-cube
//
//  Created by Jacob An on 2022/06/10.
//

#include <stdio.h>
#include "Node.h"

Node::Node(int zz, int yy, int xx) {
    left = NULL;
    right = NULL;
    up = NULL;
    down = NULL;
    front = NULL;
    behind = NULL;
    
    word = NULL;
    
    x = xx;
    y = yy;
    z = zz;
    
    count = 0;
}

Node::Node(Node& n) {
    this->left = n.left;
    this->right = n.right;
    this->up = n.up;
    this->down = n.down;
    this->front = n.front;
    this->behind = n.behind;
    
    this->x = n.x;
    this->y = n.y;
    this->z = n.z;
    
    this->word = n.word;
    
}
