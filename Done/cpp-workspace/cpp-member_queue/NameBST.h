#pragma once
#include "NameBSTNode.h"

class NameBST {
private:
    NameBSTNode *root;
    int size;

public:
    NameBST();
    ~NameBST();

    NameBSTNode *getRoot() { return this->root; };

    void insert(NameBSTNode *);
    NameBSTNode *search(string);
    char remove(string);
};
