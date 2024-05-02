#include "BinarySearchTree.h"

void BinarySearchTree::insert(std::string word) {
    Node* n = new Node(word);
    
    if (root == nullptr)
        root = n;
    else {
        Node *p = root;
        
        while (p != nullptr) {
            if (word.compare(p->getData()) < 0) {
                if (p->getLeftChild() == nullptr) {
                    p->setLeftChild(n);
                    return;
                } p = p->getLeftChild();
            } else if (word.compare(p->getData()) > 0) {
                if (p->getRightChild() == nullptr) {
                    p->setRightChild(n);
                    return;
                } p = p->getRightChild();
            } else return;
        }
    }
}

void BinarySearchTree::remove(std::string word) {
    Node *parent = nullptr;
    Node *p = root;
    
    while (p != nullptr && word.compare(p->getData()) != 0) {
        parent = p;
        if (word.compare(p->getData()) < 0) {
            p = p->getLeftChild();
        } else {
            p = p->getRightChild();
        }
    }
    
    if (p == nullptr)
        return;
    
    if (p->getLeftChild() == nullptr && p->getRightChild() == nullptr) {
        if (p != root) {
            if (parent->getLeftChild() == p) {
                parent->setLeftChild(nullptr);
            } else {
                parent->setRightChild(nullptr);
            }
        } else {
            root = nullptr;
        }
    } else if (p->getLeftChild() != nullptr && p->getRightChild() != nullptr) {
        Node *temp = p->getRightChild();
        while (temp->getLeftChild() != nullptr)
            temp = temp->getLeftChild();
        
        std::string tempValue = temp->getData();
        
        remove(temp->getData());
        p->getData() = tempValue;
    } else {
        Node *child = (p->getLeftChild() != nullptr) ? p->getLeftChild() : p->getRightChild();
        
        if (p != root) {
            if (p == parent->getLeftChild()) {
                parent->setLeftChild(child);
            } else {
                parent->setRightChild(child);
            }
        } else {
            root = child;
        }
    }
}

bool BinarySearchTree::exists(std::string word) const {
    Node *p = root;
    
    if (root == nullptr)
        return false;
    else {
        while (p != nullptr) {
            if (word.compare(p->getData()) == 0)
                return true;
            else {
                if (word.compare(p->getData()) < 0)
                    p = p->getLeftChild();
                else
                    p = p->getRightChild();
            }
        }
    }
    
    return false;
}

void inorder(Node* node, std::string& value) {
    if (node != nullptr) {
        if (node->getLeftChild() != nullptr)
            inorder(node->getLeftChild(), value);
        if (node->getData() != "")
            value += node->getData() + " ";
        if (node->getRightChild() != nullptr)
            inorder(node->getRightChild(), value);
    }
}

std::string BinarySearchTree::inorder() const {
    std::string value = "";
    ::inorder(root, value);
    
    if (value != "") {
        value.erase(prev(value.end()));
        return value;
    } else
        return std::string("");
}

void preorder(Node* node, std::string& value) {
    if (node != nullptr) {
        if (node->getData() != "")
            value += node->getData() + " ";
        if (node->getLeftChild() != nullptr)
            preorder(node->getLeftChild(), value);
        if (node->getRightChild() != nullptr)
            preorder(node->getRightChild(), value);
    }
}

std::string BinarySearchTree::preorder() const {
    std::string value = "";
    ::preorder(root, value);
    
    if (value != "") {
        value.erase(prev(value.end()));
        return value;
    } else
        return std::string("");
}

void postorder(Node* node, std::string& value) {
    if (node != nullptr) {
        if (node->getLeftChild() != nullptr)
            postorder(node->getLeftChild(), value);
        if (node->getRightChild() != nullptr)
            postorder(node->getRightChild(), value);
        if (node->getData() != "")
            value += node->getData() + " ";
        
    }
}

std::string BinarySearchTree::postorder() const {
    std::string value = "";
    ::postorder(root, value);
    
    if (value != "") {
        value.erase(prev(value.end()));
        return value;
    } else
        return std::string("");
}

bool equal(Node* left, Node* right) {
    if (left != nullptr && right != nullptr) {
        if (left->getData().compare(right->getData()) == 0) {
            equal(left->getLeftChild(), right->getLeftChild());
            equal(left->getRightChild(), right->getRightChild());
            return true;
        } else
            return false;
    } else
        return false;
}

bool BinarySearchTree::operator==(const BinarySearchTree& other) const {
    return (equal(this->root, other.root));
}

bool BinarySearchTree::operator!=(const BinarySearchTree& other) const {
    return (!equal(this->root, other.root));
}

std::istream& operator>>(std::istream& in, BinarySearchTree& tree) {
    std::string input;
    
    in >> input;
    tree.insert(input);
    
    return in;
}
