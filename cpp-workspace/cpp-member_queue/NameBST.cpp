#include "NameBST.h"

// constructor
NameBST::NameBST() : root(nullptr) {
    this->size = 0;
}

// destroyer
NameBST::~NameBST() {

}

// insert node
void NameBST::insert(NameBSTNode* newNode) {
    NameBSTNode* nameBSTNode = this->getRoot();
    
    // check root is not null
    if (nameBSTNode) {
        while (1) {
            // check name to insert ASC
            if (nameBSTNode->getName().compare(newNode->getName()) > 0) {
                if (nameBSTNode->getLeft())
                    nameBSTNode = nameBSTNode->getLeft();
                else {
                    newNode->setParent(nameBSTNode);
                    nameBSTNode->setLeft(newNode);
                    this->size++;
                    break;
                }
            } else {
                if (nameBSTNode->getRight())
                    nameBSTNode = nameBSTNode->getRight();
                else {
                    newNode->setParent(nameBSTNode);
                    nameBSTNode->setRight(newNode);
                    this->size++;
                    break;
                }
            }
        }
    } else {
        root = newNode;
        this->size++;
    }
}

// search node
NameBSTNode *NameBST::search(string name) {
    NameBSTNode* nameBSTNode = getRoot();

    while (true) {
        // check root is not null
        if (!nameBSTNode)
            return nameBSTNode;

        if (name.compare(nameBSTNode->getName()) == 0)
            return nameBSTNode;
        else if (name.compare(nameBSTNode->getName()) < 0)
            nameBSTNode = nameBSTNode->getLeft();
        else nameBSTNode = nameBSTNode->getRight();
    }
}

// remove node
char NameBST::remove(string name) {
    NameBSTNode *destination = search(name);

    // check node is exist
    if (!destination)
        return 0;
    else {
        char term = destination->getTerm();
        NameBSTNode *parentNode = destination->getParent();
        
        // children are null
        if (destination->getLeft() == NULL && destination->getRight() == NULL) {
            if (!parentNode)
                this->root = NULL;
            if (parentNode->getLeft() == destination)
                parentNode->setLeft(NULL);
            else
                parentNode->setRight(NULL);
        } else if (destination->getLeft() && destination->getRight()) {
            NameBSTNode* left = destination->getLeft();
            NameBSTNode* right = destination->getRight();
            NameBSTNode* replaceNode = right;

            // go to left leaf node
            while (replaceNode->getLeft())
                replaceNode = replaceNode->getLeft();
            replaceNode->getParent()->setLeft(NULL);
            
            if (replaceNode->getRight() && (replaceNode != right)) {
                replaceNode->getParent()->setLeft(replaceNode->getRight());
                replaceNode->getRight()->setParent(replaceNode->getParent());
            }

            if (parentNode) {

                if (parentNode->getLeft() == destination)
                    parentNode->setLeft(replaceNode);
                else
                    parentNode->setRight(replaceNode);
                replaceNode->setParent(parentNode);

                replaceNode->setLeft(left);
                left->setParent(replaceNode);

                if (replaceNode != right) {
                    replaceNode->setRight(right);
                    right->setParent(replaceNode);
                }
            } else {
                if (replaceNode->getParent()->getLeft() == replaceNode)
                    replaceNode->getParent()->setLeft(NULL);

                this->root = replaceNode;
                replaceNode->setParent(NULL);
                replaceNode->setLeft(left);
                left->setParent(replaceNode);
                replaceNode->setRight(right);
                right->setParent(replaceNode);

            }
        } else {
            NameBSTNode* childNode = destination->getLeft();
            if (!childNode) childNode = destination->getRight();

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
        }

        delete destination;
        this->size--;

        return term;
    }
}
