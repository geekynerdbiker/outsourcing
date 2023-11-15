/**
 * Represents a generically-typed binary tree node. Each binary node contains
 * data, a reference to the left child, and a reference to the right child.
 *
 * @author Habtamu M. and ??
 * @version March 12, 2022
 */



#pragma once

#include <iostream>
#include <string>

class Node
{
    
    std::string data;
    
    Node* leftChild;
    
    Node* rightChild;
    
public:
    Node(std::string data, Node* leftChild, Node* rightChild)
    {
        this->data = data;
        this->leftChild = leftChild;
        this->rightChild = rightChild;
    }
    
    Node(std::string data)
    {
        this->data = data;
        this->leftChild = nullptr;
        this->rightChild = nullptr;
    }
    
    /**
     * @return the node data
     */
    std::string getData()
    {
        return data;
    }
    
    /**
     * @param data - the node data to be set
     */
    void setData(std::string data) {
        this->data = data;
    }
    
    /**
     * @return reference to the left child node
     */
    Node* getLeftChild()
    {
        return leftChild;
    }
    
    /**
     * @param leftChild - reference of the left child node to be set
     */
    void setLeftChild(Node* leftChild)
    {
        this->leftChild = leftChild;
    }
    
    /**
     * @return reference to the right child node
     */
    Node* getRightChild()
    {
        return rightChild;
    }
    
    /**
     * @param rightChild - reference of the right child node to be set
     */
    void setRightChild(Node* rightChild) {
        this->rightChild = rightChild;
    }
    
};

class BinarySearchTree
{
private:
    // Pointer to root of the tree
    Node* root=nullptr;
public:
    
    // Adds a word to the tree
    void insert(std::string word);
    // Removes a word from the tree
    void remove(std::string word);
    // Checks if a word is in the tree
    bool exists(std::string word) const;
    // Creates a string representing the tree in alphabetical order
    std::string inorder() const;
    // Creates a string representing the tree in pre-order
    std::string preorder() const;
    // Creates a string representing the tree in post-order
    std::string postorder() const;
    // Checks if two trees are equal
    bool operator==(const BinarySearchTree& other) const;
    // Checks if two trees are not equal
    bool operator!=(const BinarySearchTree& other) const;
    // Reads in words from an input stream into the tree
    friend std::istream& operator>>(std::istream& in, BinarySearchTree& tree);
};
