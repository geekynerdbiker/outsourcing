//
//  Cube.h
//  cpp-cube
//
//  Created by Jacob An on 2022/06/10.
//

#ifndef Cube_h
#define Cube_h

#include <iostream>
#include "Node.h"

using namespace std;

class Block {
private:
    Node* head;
public:
    Block();
    void insertBlock(int z, int y);
    Node* getHead();
    void print();
};

class Surface {
private:
    Node* head;
public:
    Block a;
    Block b;
    Block c;
    
    Node* getHead();
    void insertSurface(int z);
};

class Cube {
private:
    Node* head;
public:
    Surface a;
    Surface b;
    Surface c;
    
    Node* getHead();
    BST* getMin(BST* target);
    
    void initCube();
    void insert(int x, int y, int z, char name[50]);
    
    void remove(int x, int y, int z, char name[50]);
    BST* removeBSTNode(Node* N, BST* bst, BST* par, char name[50]);
    
    void find(char name[50]);
    BST* fineName(BST* p, char name[50]);
    Node* findNode(int x, int y, int z);
    
    void print(int x, int y, int z);
    void postorder(BST* p);
    void inorder(BST* p);
    void preorder(BST* p);
    
    void printAll();
    
    void exchange(int x1, int y1, int z1, int x2, int y2, int z2);
    void turn(int place, int clock, int spin);
};

#endif /* Cube_h */
