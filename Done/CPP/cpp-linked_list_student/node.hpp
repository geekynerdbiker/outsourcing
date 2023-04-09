#ifndef node_hpp
#define node_hpp

#include "student.hpp"

// 노드 클래스
class node {
public:
    student data;
    node *next;
    
    // 생성자
    node(student data) {
        this->data = data;
        this->next = NULL;
    }
};

#endif
