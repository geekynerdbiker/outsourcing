#include <iostream>
#include <string>

#include "student.hpp"
#include "list.hpp"
#include "node.hpp"

using namespace std;

// 함수 선언
void save_node(list &l, node *n);
void delete_node(list &l, node *n);
void print_list(list &l);
void pivot(list &l);
void print_pivot_dept(list &l, int function);
void print_pivot_gender(list &l, int function);
void print_pivot_both(list &l, int function);

// 메인 함수
int main(void) {
    list l;
    node *n;
    student s;
    
    while (true) {
        // 메뉴 출력
        int selection;
        cout << "----------MENU----------" << endl;
        cout << "1. Add a student" << endl;
        cout << "2. Delete a student" << endl;
        cout << "3. Print the student's list" << endl;
        cout << "4. Pivot table" << endl;
        cout << "5. Exit" << endl;
        cout << "------------------------" << endl;
        
        cout << "Selection: ";
        cin >> selection;
        
        // 메뉴에 따른 함수 호출
        switch (selection) {
            case 1:
                s.input_info();
                
                n = new node(s);
                save_node(l, n);
                break;
                
            case 2:
                s.input_info();
                n = new node(s);
                delete_node(l, n);
                break;
                
            case 3:
                print_list(l);
                break;
                
            case 4:
                pivot(l);
                break;
                
            case 5:
                cout << "Exit!" << endl;
                return 0;
                
            default:
                break;
        }
    }
}

// 노드 저장 함수
void save_node(list &l, node *n) {
    node *p = l.head;
    
    // 헤드가 비어있으면 헤드에 저장
    if (!p)
        l.head = n;
    else {
        while (p) {
            // 같은 데이터가 존재하는지 확인
            if (!p->data.dept.compare(n->data.dept) && !p->data.name.compare(n->data.name) && !p->data.gender.compare(n->data.gender) && p->data.age == n->data.age) {
                cout << "The student already exists." << endl;
                return;
            }
            if (!p->next) {
                p->next = n;
                break;
            }
            p = p->next;
        }
        // 같은 데이터가 없으면 저장
    }
    
    // 총 학생수 증가
    l.count++;
    
    // 학과가 이미 존재하는지 검사
    for (int i = 0; i < l.dept_cnt; i++)
        if (!l.dept[i].compare(n->data.dept))
            return;
    
    // 존재하지 않으면 추가 및 총 학과 수 증가
    l.dept[l.dept_cnt++] = n->data.dept;
}

// 노드 삭제 함수
void delete_node(list &l, node *n) {
    node *p = l.head;
    node *q = NULL;
    
    // 헤드가 비어있으면 아무 것도 하지 않음
    while (p) {
        // 모든 데이터가 동일한지 검사
        if (!p->data.dept.compare(n->data.dept) && !p->data.name.compare(n->data.name) && !p->data.gender.compare(n->data.gender) && p->data.age == n->data.age) {
            
            // 삭제할 노드가 헤드일 때
            if (p == l.head) {
                // 헤드의 다음 노드가 존재할 때
                if (l.head->next)
                    l.head = l.head->next;
                // 헤드만 존재할 때
                else
                    l.head = NULL;
            // 삭제할 노드가 헤드가 아닐 때
            } else {
                // 삭제할 노드의 다음 노드가 존재할 때
                if (p->next)
                    q->next = p->next;
                // 삭제할 노드가 맨 마지막 노드일 때
                else
                    q->next = NULL;
            }
            
            
            cout << "Deleted!" << endl;
            // 삭제를 성공하면 총 학생수 감소
            l.count--;
            
            // 삭제할 노드와 같은 학과의 다른 노드가 존재하는지 검사
            node *k = l.head;
            
            while (k) {
                if (!k->data.dept.compare(n->data.dept))
                    return;
                k = k->next;
            }
            
            // 존재하지 않으면 삭제 및 총 학과 수 감소
            for (int i = 0; i < l.dept_cnt; i++)
                if (!l.dept[i].compare(n->data.dept))
                    l.dept[i] = l.dept[l.dept_cnt--];
            
            // 파괴자
            delete p;
            return;
        }
        q = p;
        p = p->next;
    }
                
    
    cout << "Can't Delete it" << endl;
}

// 학생 리스트 출력 함수
void print_list(list &l) {
    node *p = l.head;
    
    if (l.head == NULL) {
        cout << "No student added." << endl;
        return;
    }
    
//    l.sort("Dept");
    l.sort_all();
    
    cout.width(8);
    cout << left << "Dept";
    cout.width(8);
    cout << left << "Gender";
    cout.width(8);
    cout << left << "Name";
    cout.width(8);
    cout << left << "Age";
    cout << endl;
    
    while (p) {
        cout.width(8);
        cout << left << p->data.dept;
        cout.width(8);
        cout << left << p->data.gender;
        cout.width(8);
        cout << left << p->data.name;
        cout.width(8);
        cout << left << p->data.age;
        cout << endl;
        
        p = p->next;
    }
}

// 피봇 테이블 생성 함수
void pivot(list &l) {
    int category, function;
    cout << "----------Category----------" << endl;
    cout << "1. Dept" << endl;
    cout << "2. Gender" << endl;
    cout << "3. Dept and Gender" << endl;
    cout << "----------------------------" << endl;
    
    cout << "Selection: ";
    cin >> category;
    
    cout << "----------Function----------" << endl;
    cout << "1. Average" << endl;
    cout << "2. Max" << endl;
    cout << "3. Min" << endl;
    cout << "----------------------------" << endl;
    
    cout << "Selection: ";
    cin >> function;
    
    switch (category) {
        case 1:
            // 학과 기준
            print_pivot_dept(l, function);
            break;
        case 2:
            // 성별 기준
            print_pivot_gender(l, function);
            break;
        case 3:
            // 학과 + 성별 기준
            print_pivot_both(l, function);
            break;
        
        default:
            break;
    }
}

void print_pivot_dept(list &l, int function) {
    if (l.head == NULL)
        return;

    string dept;
    int cnt, sum, max, min;
    switch (function) {
        case 1:
            cout.width(8);
            cout << left << "Dept";
            cout.width(8);
            cout << left << "Average";
            cout << endl;
            
            // 각각의 학과에 대해서 순회
            for (int i = 0; i < l.dept_cnt; i++) {
                node *p = l.head;
                cnt = 0;
                sum = 0;
                
                dept = l.dept[i];
                while (p) {
                    // 같은 학과이면 나이 합계에 더하고, 총 학생수 증가
                    if (!dept.compare(p->data.dept)) {
                        sum += p->data.age;
                        cnt++;
                    }
                    p = p->next;
                }
                // 한 학과에 대해 순회가 끝나면 출력
                if (cnt) {
                    cout << fixed;
                    cout.width(8);
                    cout << left << dept;
                    cout.width(8);
                    float avg = sum / (float)cnt;
                    cout.precision(1);
                    cout << left << avg;
                    cout << endl;
                }
            }
            break;
            
        case 2:
            cout.width(8);
            cout << left << "Dept";
            cout.width(8);
            cout << left << "Max";
            cout << endl;
            
            for (int i = 0; i < l.dept_cnt; i++) {
                node *p = l.head;
                max = 0;
                dept = l.dept[i];
                while (p) {
                    // 최댓값 갱신
                    if (!dept.compare(p->data.dept))
                        max = max > p->data.age ? max : p->data.age;
                    p = p->next;
                }
                if (max) {
                    cout.width(8);
                    cout << left << dept;
                    cout.width(8);
                    cout << left << max;
                    cout << endl;
                }
            }
            break;
        
        case 3:
            cout.width(8);
            cout << left << "Dept";
            cout.width(8);
            cout << left << "Min";
            cout << endl;
            
            for (int i = 0; i < l.dept_cnt; i++) {
                node *p = l.head;
                min = 0;
                dept = l.dept[i];
                while (p) {
                    // 최솟값 갱신
                    if (!dept.compare(p->data.dept)) {
                        if (min == 0)
                            min = p->data.age;
                        else
                            min = min < p->data.age ? min : p->data.age;
                    }
                    p = p->next;
                }
                if (min) {
                    cout.width(8);
                    cout << left << dept;
                    cout.width(8);
                    cout << left << min;
                    cout << endl;
                }
            }
            break;
            
        default:
            break;
    }
}

void print_pivot_gender(list &l, int function) {
    if (l.head == NULL)
        return;

    // 순회를 위한 성별 지정
    string gender[] = {"F", "M"};
    int cnt, sum, max, min;
    switch (function) {
        case 1:
            cout.width(8);
            cout << left << "Gender";
            cout.width(8);
            cout << left << "Average";
            cout << endl;
            
            for (int i = 0; i < 2; i++) {
                node *p = l.head;
                cnt = 0;
                sum = 0;
                
                while (p) {
                    // 같은 성별일 때
                    if (!gender[i].compare(p->data.gender)) {
                        sum += p->data.age;
                        cnt++;
                    }
                    p = p->next;
                }
                if (cnt) {
                    cout << fixed;
                    cout.width(8);
                    cout << left << gender[i];
                    cout.width(8);
                    float avg = sum / (float)cnt;
                    cout.precision(1);
                    cout << left << avg;
                    cout << endl;
                }
            }
            break;
            
        case 2:
            cout.width(8);
            cout << left << "Gender";
            cout.width(8);
            cout << left << "Max";
            cout << endl;
            
            for (int i = 0; i < 2; i++) {
                node *p = l.head;
                max = 0;
                
                while (p) {
                    if (!gender[i].compare(p->data.gender))
                        max = max > p->data.age ? max : p->data.age;
                    p = p->next;
                }
                if (max) {
                    cout.width(8);
                    cout << left << gender[i];
                    cout.width(8);
                    cout << left << max;
                    cout << endl;
                }
            }
            break;
        
        case 3:
            cout.width(8);
            cout << left << "Gender";
            cout.width(8);
            cout << left << "Min";
            cout << endl;
            
            for (int i = 0; i < 2; i++) {
                node *p = l.head;
                min = 0;
                
                while (p) {
                    if (!gender[i].compare(p->data.gender)) {
                        if (min == 0)
                            min = p->data.age;
                        else
                            min = min < p->data.age ? min : p->data.age;
                    }
                    p = p->next;
                }
                if (min) {
                    cout.width(8);
                    cout << left << gender[i];
                    cout.width(8);
                    cout << left << min;
                    cout << endl;
                }
            }
            break;
            
        default:
            break;
    }
}

void print_pivot_both(list &l, int function) {
    if (l.head == NULL)
        return;

    string dept, gender[] = {"F", "M"};
    int cnt, sum, max, min;
    switch (function) {
        case 1:
            cout.width(8);
            cout << left << "Dept";
            cout.width(8);
            cout << left << "Gender";
            cout.width(8);
            cout << left << "Average";
            cout << endl;
            
            // 각각의 학과에 대해 순회
            for (int i = 0; i < l.dept_cnt; i++) {
                node *p = l.head;
                cnt = 0;
                sum = 0;
                
                dept = l.dept[i];
                // 각각의 성별에 대해 순회
                for (int j = 0; j < 2; j++) {
                    while (p) {
                        // 같은 학과이면서 같은 성별일 때
                        if (!dept.compare(p->data.dept) && !gender[j].compare(p->data.gender)) {
                            sum += p->data.age;
                            cnt++;
                        }
                        p = p->next;
                    }
                    if (cnt) {
                        cout.width(8);
                        cout << left << dept;
                        cout.width(8);
                        cout << left << gender[j];
                        cout.width(8);
                        float avg = sum / (float)cnt;
                        cout.precision(1);
                        cout << left << avg;
                        cout << endl;
                    }
                }
            }
                
            break;
            
        case 2:
            cout.width(8);
            cout << left << "Dept";
            cout.width(8);
            cout << left << "Gender";
            cout.width(8);
            cout << left << "Max";
            cout << endl;
            
            for (int i = 0; i < l.dept_cnt; i++) {
                node *p = l.head;
                max = 0;
                
                dept = l.dept[i];
                for (int j = 0; j < 2; j++) {
                    while (p) {
                        if (!dept.compare(p->data.dept) && !gender[j].compare(p->data.gender))
                            max = max > p->data.age ? max : p->data.age;
                        p = p->next;
                    }
                    if (max) {
                        cout.width(8);
                        cout << left << dept;
                        cout.width(8);
                        cout << left << gender[j];
                        cout.width(8);
                        cout << left << max;
                        cout << endl;
                    }
                }
            }
            break;
        
        case 3:
            cout.width(8);
            cout << left << "Dept";
            cout.width(8);
            cout << left << "Gender";
            cout.width(8);
            cout << left << "Min";
            cout << endl;
            
            for (int i = 0; i < l.dept_cnt; i++) {
                node *p = l.head;
                min = 0;
                
                dept = l.dept[i];
                for (int j = 0; j < 2; j++) {
                    while (p) {
                        if (!dept.compare(p->data.dept) && !gender[j].compare(p->data.gender))
                            min = min > p->data.age ? min : p->data.age;
                        p = p->next;
                    }
                    if (min) {
                        cout.width(8);
                        cout << left << dept;
                        cout.width(8);
                        cout << left << gender[j];
                        cout.width(8);
                        cout << left << min;
                        cout << endl;
                    }
                }
            }
            break;
            
        default:
            break;
    }
}
