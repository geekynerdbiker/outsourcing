#pragma once
#include "MemberQueue.h"
#include "TermsList.h"
#include "TermsBST.h"
#include "NameBST.h"
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

class Manager
{
private:
    ifstream fcmd;
    ofstream flog;

public:
    Manager();
    ~Manager();

    void run(const char *command);

    void PrintSuccess(const char *cmd);
    void PrintErrorCode(int num);
    template<typename T>
    void inorderPrint(T* curNode);

    // LOAD
    void LOAD(MemberQueue *);
    // ADD
    void ADD(MemberQueue *);
    // QPOP
    void QPOP(TermsLIST *, MemberQueue *, NameBST *);
    // SEARCH
    void SEARCH(NameBST *);
    // PRINT
    void PRINT(TermsLIST *, NameBST *);
    // DELETE
    void DELETE(TermsLIST *, NameBST *);
};
