#include "TermsBST.h"
#include "NameBST.h"

// constructor
TermsBST::TermsBST(TermsBSTNode *root) {
    this->root = root;
    this->count = 0;
    this->size = 0;
}

// destroyer
TermsBST::~TermsBST() {
    
}

// return root
TermsBSTNode *TermsBST::getRoot() {
    return root;
}

// insert node. same algorithm with NameBST
void TermsBST::insert(TermsBSTNode *termsBSTNode) {
    TermsBSTNode *curTBNode = this->getRoot();

    while (true) {
        if (curTBNode->getKey() > termsBSTNode->getKey()) {
            if (curTBNode->getLeft())
                curTBNode = curTBNode->getLeft();
            else {
                curTBNode->setLeft(termsBSTNode);
                termsBSTNode->setParent(curTBNode);
                break;
            }
        } else {
            if (curTBNode->getRight())
                curTBNode = curTBNode->getRight();
            else {
                curTBNode->setRight(termsBSTNode);
                termsBSTNode->setParent(curTBNode);
                break;
            }
        }
    }
}

// search node. same algorithm with NameBST
TermsBSTNode *TermsBST::search(string date) {
    TermsBSTNode *rootNode = getRoot();

    while (1) {
        if (!rootNode)
            return rootNode;

        int res = date.compare(rootNode->getTermDate());
        if (res == 0)
            return rootNode;
        else if (res < 0)
            rootNode = rootNode->getLeft();
        else
            rootNode = rootNode->getRight();
    }
}

// remove node. same algorithm with NameBST
bool TermsBST::remove(string date) {
    TermsBSTNode *destination = search(date);
    TermsBSTNode *parentNode = destination->getParent();
    
    if (destination->getLeft() == NULL && destination->getRight() == NULL) {
        if (!parentNode)
            this->root = NULL;

        delete destination;
        delete this;
        
        return 1;
    } else if (destination->getLeft() && destination->getRight()) {
        TermsBSTNode *left = destination->getLeft();
        TermsBSTNode *right = destination->getRight();
        TermsBSTNode *targetNode = right;
        
        while (targetNode->getLeft())
            targetNode = targetNode->getLeft();
        targetNode->getParent()->setLeft(NULL);

        if (targetNode->getRight() && (targetNode != right)) {
            targetNode->getParent()->setLeft(targetNode->getRight());
            targetNode->getRight()->setParent(targetNode->getParent());
        }

        if (parentNode) {
            if (parentNode->getLeft() == destination)
                parentNode->setLeft(targetNode);
            else
                parentNode->setRight(targetNode);
            
            targetNode->setParent(parentNode);
            targetNode->setLeft(left);
            left->setParent(targetNode);
            
            if (targetNode != right) {
                targetNode->setRight(right);
                right->setParent(targetNode);
            }
        } else {
            if (targetNode->getParent()->getLeft() == targetNode)
                targetNode->getParent()->setLeft(NULL);

            this->root = targetNode;
            targetNode->setParent(NULL);
            targetNode->setLeft(left);
            left->setParent(targetNode);
            targetNode->setRight(right);
            right->setParent(targetNode);
        }
    } else {
        TermsBSTNode *childNode = destination->getLeft();
        
        if (!childNode)
            childNode = destination->getRight();

        if (parentNode) {
            if (parentNode->getLeft() == destination)
                parentNode->setLeft(childNode);
            else
                parentNode->setRight(childNode);

            childNode->setParent(parentNode);
        } else {
            this->root = childNode;
            childNode->setParent(NULL);
        }

        delete destination;
    }

    return 0;
}

// delete from right leaf -> left leaf using date
TermsBSTNode *TermsBST::deletePostorder(NameBST *nameBST, TermsBSTNode *termsBSTNode, string date) {
    if (!termsBSTNode)
        return nullptr;

    // traverse post-order
    TermsBSTNode *left = deletePostorder(nameBST, termsBSTNode->getLeft(), date);
    TermsBSTNode *right = deletePostorder(nameBST, termsBSTNode->getRight(), date);

    // compare date
    if (termsBSTNode->getTermDate() < date) {
        if (termsBSTNode == this->root)
            this->root = NULL;

        nameBST->remove(termsBSTNode->getName());

        delete termsBSTNode;
        this->count++;
        return nullptr;
    }

    termsBSTNode->setLeft(left);
    termsBSTNode->setRight(right);

    return termsBSTNode;
}

// delete with date
int TermsBST::deleteDate(NameBST *nameBST, string date) {
    this->count = 0;
    deletePostorder(nameBST, this->root, date);
    
    return this->count;
}
