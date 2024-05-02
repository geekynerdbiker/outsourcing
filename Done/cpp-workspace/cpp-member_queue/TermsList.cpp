#include "TermsList.h"

// constructor
TermsLIST::TermsLIST(): head(nullptr) {
    this->size = 0;
    this->status = false;
}

// destroyer
TermsLIST::~TermsLIST() {

}

// insert node to list
void TermsLIST::insert(MemberQueueNode* memberQueueNode, NameBST* nameBST) {
    string name = memberQueueNode->getName();
    string date = memberQueueNode->getDate();
    int age = memberQueueNode->getAge();
    char term = memberQueueNode->getTerm();
    
    TermsListNode* termsListNode = this->getHead();
    bool added = false;

    // check head is null
    if (!termsListNode)
        added = true;
    else {
        added = true;
        while (termsListNode) {
            if (termsListNode->getTerm() == term) {
                added = false;
                break;
            }
            termsListNode = termsListNode->getNext();
        }
    }

    TermsBSTNode* termsBSTNode = new TermsBSTNode(name, date, age);
    termsBSTNode->setTermDate(term);
    
    NameBSTNode* newNameBSTNode = new NameBSTNode(name, date, termsBSTNode->getTermDate(), age, term);
    nameBST->insert(newNameBSTNode);
    
    if (added) {
        TermsListNode* newTermsLIstNode = new TermsListNode(term);

        TermsBST* TB = new TermsBST(termsBSTNode);
        newTermsLIstNode->setRoot(TB);

        if (!this->size)
            this->setHead(newTermsLIstNode);
        else {
            termsListNode = this->getHead();
            for (int i = 1; i < size; i++)
                termsListNode = termsListNode->getNext();
            termsListNode->setNext(newTermsLIstNode);
        }
    } else {
        termsListNode->increase();
        termsListNode->getRoot()->insert(termsBSTNode);
        termsListNode->getRoot()->increase();
    }
    
    this->size++;
}

// print tree
TermsBST* TermsLIST::PrintTermsBST(char c) {
    TermsListNode* termsListNode = getHead();

    while (termsListNode) {
        if (termsListNode->getTerm() == c)
            return termsListNode->getRoot();
        else
            termsListNode = termsListNode->getNext();
    }

    return NULL;
}

// delete list node by name
void TermsLIST::deleteName(string name, string date, char term) {
    TermsListNode* termsListNode = this->getHead();
    TermsBST* termsBST = NULL;

    while (true) {
        if (termsListNode->getTerm() == term) {
            termsBST = termsListNode->getRoot();
            break;
        } else
            termsListNode = termsListNode->getNext();
    }
    termsListNode->decrease();

    int isEmpty = termsBST->remove(date);
    
    if (isEmpty) {
        TermsListNode* prevNode = this->getHead();
        while (!(prevNode->getNext() == termsListNode))
            prevNode = prevNode->getNext();
        prevNode->setNext(NULL);
        delete termsListNode;
    }
}

// delete list node by date
void TermsLIST::deleteDate(NameBST* nameBST, string date) {
    this->status = false;
    TermsListNode* termsListNode = this->getHead();

    while (termsListNode) {
        TermsBST* termsBST = termsListNode->getRoot();
        TermsListNode* targetNode = termsListNode;
        int isEmpty = termsBST->deleteDate(nameBST, date);
        
        if (!isEmpty)
            this->status = true;
        
        for (int i = 0; i < isEmpty; i++) {
            termsListNode->decrease();
            this->size--;
        }
        termsListNode = termsListNode->getNext();

        // check root is not null
        if (!termsBST->getRoot()) {
            delete termsBST;
            int count = 0;
            TermsListNode* tempNode = this->getHead();
            while (tempNode) {
                count++;
                tempNode->getNext();
                if (count > 1) break;
            }

            if (count == 1) {
                delete targetNode;
                delete this;
            } else {
                if (this->getHead() == targetNode) {
                    this->setHead(targetNode->getNext());
                } else {
                    TermsListNode* termsListNode = this->getHead();
                    while (!(termsListNode->getNext() == targetNode))
                        termsListNode = termsListNode->getNext();
                    termsListNode->setNext(targetNode->getNext());
                }
                delete targetNode;
            }
        }
    }
}
