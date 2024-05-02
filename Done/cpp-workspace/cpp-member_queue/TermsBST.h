#pragma once
#include "TermsBSTNode.h"
#include "MemberQueue.h"
#include "NameBST.h"

class TermsBST {
private:
    TermsBSTNode* root;
    int count;
    int size;

public:
    TermsBST(TermsBSTNode* root);
    ~TermsBST();

    TermsBSTNode* getRoot();
    int getSize() { return this->size; }
    int increase() { return this->size++; }

    void insert(TermsBSTNode *);
    TermsBSTNode* search(string);
    bool remove(string);
    TermsBSTNode* deletePostorder(NameBST*, TermsBSTNode*, string);
    int deleteDate(NameBST* nb, string termDate);
};
