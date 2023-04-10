#ifndef List_hpp
#define List_hpp

#include "node.hpp"

using namespace std;

// 리스트 클래스
class list {
public:
    int count, dept_cnt;
    string dept[9];
    node *head;
    
    // 생성자
    list() {
        this->count = 0;
        this->dept_cnt = 0;
        
        for (int i = 0; i < 9; i++)
            this->dept[i] = "";
        this->head = NULL;
    }
    
    // 솔직히 왜 필요한지 모르겠음.
    void sort(string metric);
};

#endif
