#ifndef Student_hpp
#define Student_hpp

#include <iostream>

using namespace std;

// 학생 클래스
class student {
public:
    string dept, name, gender;
    int age;
    
    // 생성자
    student() {
        this->dept = "";
        this->name = "";
        this->gender = "";
        this->age = 0;
    }
    
    void input_info() {
        string dept, gender, name;
        int age;
        
        cout << "Dept: ";
        cin >> dept;
        
        // 학과가 대문자가 아니면 종료
        for (int i = 0; i < dept.length(); i++)
            if (dept[i] > 'Z' || dept[i] < 'A') {
                cout << "Dept can be only capital letter." << endl;
                return;
            }
        
        cout << "Gender: ";
        cin >> gender;
        
        // 성별이 F 또는 M이 아니면 종료
        if (gender.length() > 1 || !(gender[0] == 'M' || gender[0] == 'F')) {
            cout << "Only M and F can be a gender." << endl;
            return;
        }
        
        
        cout << "Name: ";
        cin >> name;
        
        cout << "Age: ";
        cin >> age;
        
        // 나이가 18세 미만, 30세 이상이면 종료
        if (age < 18 || age > 30) {
            cout << "Age must be bigger or equal than 18 and smaller or equal than 30." << endl;
            return;
        }
        
        this->dept = dept;
        this->gender = gender;
        this->name = name;
        this->age = age;
    }
};
#endif /* Student_hpp */
