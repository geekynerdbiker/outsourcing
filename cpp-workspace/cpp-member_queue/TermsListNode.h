#pragma once
#include <string>
#include "TermsBST.h"

using namespace std;

class TermsListNode {
private:
    TermsBST* root;
    TermsListNode* next;
    
    char term;
    int count;

public:
    TermsListNode(char term) {
        this->root = NULL;
        this->next = NULL;
        
        this->term = term;
        this->count = 1;
    }
    ~TermsListNode() {}

    TermsBST* getRoot() { return this->root; }
    TermsListNode* getNext() { return next; }
    char getTerm() { return this->term; }
    int getCount() { return this->count; }
    
    void setRoot(TermsBST* root) { this->root = root; }
    void setNext(TermsListNode* next) { this->next = next; }
    void setTerm(char t) { this->term = t; }
    
    void increase() { this->count++; }
    void decrease() { this->count--; }
    
    
};
