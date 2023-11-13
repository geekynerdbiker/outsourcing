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

#ifndef AVLNODE_H
#define AVLNODE_H

template <typename T>
class AVLNode {
public:
    T key;
    AVLNode *left;
    AVLNode *right;
    int height;
    int size;  // 이 노드를 루트로 하는 서브트리의 크기
    
    AVLNode(T val, AVLNode *l = nullptr, AVLNode *r = nullptr)
    : key(val), left(l), right(r), height(1), size(1) {}
};

#endif  // AVLNODE_H
