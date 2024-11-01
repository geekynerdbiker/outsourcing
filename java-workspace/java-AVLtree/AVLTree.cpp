/*
 MIT License - see LICENSE file for full details
 
 Copyright (c) 2023 KimDongHyun
 
 Permission is hereby granted, free of charge, to any person obtaining a copy of
 this software and associated documentation files, to deal in the Software
 without restriction, including without limitation the rights to use, copy,
 modify, merge, publish, distribute, sublicense, and/or sell copies of the
 Software.
 
 Written by KimDongHyun on 2023-11-10
 */
#include "AVLTree.h"

#include <math.h>

#include <iostream>
#include <string>

#include "AVLNode.h"

template <typename T>
int AVLTree<T>::height(AVLNode<T> *node) {
    return node ? node->height : 0;
    
};

template <typename T>
int AVLTree<T>::getBalance(AVLNode<T> *node) {
    return node ? height(node->left) : height(node->right);
};

template <typename T>
AVLNode<T> *AVLTree<T>::rotateLeft(AVLNode<T> *node) {
    AVLNode<T> *newRoot = node->right;
    node->right = newRoot->left;
    newRoot->left = node;
    
    updateHeightAndSize(node);
    updateHeightAndSize(newRoot);
    
    return newRoot;
};

template <typename T>
AVLNode<T> *AVLTree<T>::rotateRight(AVLNode<T> *node) {
    AVLNode<T> *newRoot = node->left;
    node->left = newRoot->right;
    newRoot->right = node;
    
    updateHeightAndSize(node);
    updateHeightAndSize(newRoot);
    
    return newRoot;
};

template <typename T>
AVLNode<T> *AVLTree<T>::rebalance(AVLNode<T> *node) {
    updateHeightAndSize(node);
    
    int balance = getBalance(node);
    
    // Left Heavy
    if (balance > 1) {
        // Left-Right Case
        if (getBalance(node->left) < 0) {
            node->left = rotateLeft(node->left);
        }
        return rotateRight(node);
    }
    // Right Heavy
    else if (balance < -1) {
        // Right-Left Case
        if (getBalance(node->right) > 0) {
            node->right = rotateRight(node->right);
        }
        return rotateLeft(node);
    }
    
    return node;
};

template <typename T>
void AVLTree<T>::updateHeightAndSize(AVLNode<T> *node) {
    if (node) {
        node->height = 1 + (height(node->left) > height(node->right) ? height(node->left) : height(node->right));
        node->size = 1 + (node->left ? node->left->size : 0) +
        (node->right ? node->right->size : 0);
    }
};

template <typename T> 
AVLNode<T> *AVLTree<T>::insert(AVLNode<T> *node, T key) {
    if (node == nullptr) {
        return new AVLNode<T>(key);
    }
    
    if (key < node->key) {
        node->left = insert(node->left, key);
    } else if (key > node->key) {
        node->right = insert(node->right, key);
    } else {
        return node;  // 중복된 키는 허용되지 않음
    }
    
    return rebalance(node);
};

template <typename T>
AVLNode<T> *AVLTree<T>::find(AVLNode<T> *node, T key) {
    AVLNode<T>* curr = node;
    
    while (curr != nullptr && curr->key!= key) {
        if (key < curr->key)
            curr = curr->left;
        else if (key > curr->key)
            curr = curr->right;
    }

    return curr;
}

template <typename T>
void AVLTree<T>::insert(T key) {
    root = insert(root, key);
}

template <typename T>
bool AVLTree<T>::find(T key) {
    AVLNode<T>* node = find(root, key);
    if (node)
        std::cout << node->height << std::endl;
}

template <typename T>
bool AVLTree<T>::empty() const {
    if (root->size == 1) {
        std::cout << "1" << std::endl;
        return true;
    } else {
        std::cout << "0" << std::endl;
        return false;
    }
}

template <typename T>
int AVLTree<T>::size() const {
    return root->size;
}

template <typename T>
void AVLTree<T>::minimum(T key) {
    AVLNode<T>** curr = &find(root, key);
    
    while ((*curr)->left) {
        curr = &((*curr)->left);
    }
    
    std::cout << (*curr)->key << " " << (*curr)->getHeight() << std::endl;
}

template <typename T>
void AVLTree<T>::maximum(T key) {
    AVLNode<T>** curr = &find(root, key);
    
    while ((*curr)->right) {
        curr = &((*curr)->right);
    }
    
    std::cout << (*curr)->key << " " << (*curr)->getHeight() << std::endl;
    
}
