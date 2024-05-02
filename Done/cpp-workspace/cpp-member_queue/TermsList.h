#pragma once
#include "TermsListNode.h"
#include "MemberQueue.h"
#include "NameBST.h"

class TermsLIST {
private:
    TermsListNode* head;
    int size;
    bool status;

public:
    TermsLIST();
    ~TermsLIST();

    TermsListNode* getHead() { return this->head; }
    bool getDelete() { return this->status; }
    
    void setHead(TermsListNode * termsListNode) {
        this->head = termsListNode;
    }
    void insert(MemberQueueNode *, NameBST *);
    TermsBST* PrintTermsBST(char c);
    void deleteName(string, string, char);
    void deleteDate(NameBST *, string);
    void decrease() { this->size--; }
};
