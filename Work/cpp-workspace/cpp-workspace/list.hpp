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
    
    
    // 정렬 함수
    void sort(string metric) {
        node *p, *q;
        
        // 학과에 대해 정렬
        if (!metric.compare("Dept")) {
            for (p = this->head; p; p = p->next) {
                for (q = p; q; q = q->next) {
                    if (q->data.dept.compare(p->data.dept) > 0) {
                        student s = q->data;
                        q->data = p->data;
                        p->data = s;
                    }
                }
            }
        }
        // 성별에 대해 정렬
        else if (!metric.compare("Gender")) {
            for (p = this->head; p; p = p->next) {
                for (q = p; q; q = q->next) {
                    if (q->data.gender.compare(p->data.gender) > 0) {
                        student s = q->data;
                        q->data = p->data;
                        p->data = s;
                    }
                }
            }
        }
        // 이름에 대해 정렬
        else if (!metric.compare("Name")) {
            for (p = this->head; p; p = p->next) {
                for (q = p; q; q = q->next) {
                    if (q->data.name.compare(p->data.name) > 0) {
                        student s = q->data;
                        q->data = p->data;
                        p->data = s;
                    }
                }
            }
        }
        // 나이에 대해 정렬
        else if (!metric.compare("Age")) {
            for (p = this->head; p; p = p->next) {
                for (q = p; q; q = q->next) {
                    if (q->data.age> p->data.age) {
                        student s = q->data;
                        q->data = p->data;
                        p->data = s;
                    }
                }
            }
        }
    }
    
    // 전체 성분에 대해 정렬 학과 -> 성별 -> 이름 -> 나이 순서의 비교 및 오름차순
    void sort_all() {
        node *p, *q;
        
        for (p = this->head; p; p = p->next) {
            for (q = p; q; q = q->next) {
                if (q->data.dept.compare(p->data.dept) < 0) {
                    student s = q->data;
                    q->data = p->data;
                    p->data = s;
                } else if (!q->data.dept.compare(p->data.dept)) {
                    if (q->data.gender.compare(p->data.gender) < 0) {
                        student s = q->data;
                        q->data = p->data;
                        p->data = s;
                    } else if (!q->data.gender.compare(p->data.gender)) {
                        if (q->data.name.compare(p->data.name) < 0) {
                            student s = q->data;
                            q->data = p->data;
                            p->data = s;
                        } else if (!q->data.name.compare(p->data.name)) {
                            if (q->data.age < p->data.age) {
                                student s = q->data;
                                q->data = p->data;
                                p->data = s;
                            }
                        }
                    }
                }
            }
        }
    }
};

#endif
