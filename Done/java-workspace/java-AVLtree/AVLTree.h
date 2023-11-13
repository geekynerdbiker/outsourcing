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

#ifndef AVLTree_H
#define AVLTree_H

#include "AVLNode.h"

template <typename T>
class AVLTree {
public:
    AVLTree();
    
    ~AVLTree();  // 소멸자는 정의해야 할 수도 있습니다.
    
    void insert(T key);
    bool find(T key);
    bool empty() const;
    int size() const;
    void minimum(T key);
    void maximum(T key);
    
private:
    AVLNode<T> *root;
    
    // 기본적인 AVL 트리 연산
    AVLNode<T> *insert(AVLNode<T> *node, T key);
    AVLNode<T> *find(AVLNode<T> *node, T key);
    int height(AVLNode<T> *node);
    int getBalance(AVLNode<T> *node);
    AVLNode<T> *rotateLeft(AVLNode<T> *node);
    AVLNode<T> *rotateRight(AVLNode<T> *node);
    AVLNode<T> *rebalance(AVLNode<T> *node);
    void updateHeightAndSize(AVLNode<T> *node);
};

#endif  // AVLTree_H
