#include <iostream>
#include <fstream>
#include <string>
#include "T_Array.h"
#include "Student.h"

using namespace std;

Student* fget_students(istream& fin, int& num_student);
template<typename T> void printVector(vector<T>&v);

int main()
{
    ifstream fin;
    const string fin_name = "student_records.txt";
    fin.open(fin_name);
    if (fin.fail()) {
        cout << "Fail to open an input file " << fin_name << endl;
        exit;
    }
    int num_student;
    Student* students = fget_students(fin, num_student);
    fin.close();
    
    vector<Student> v_students(students, students + num_student);
    cout << "Initial v_students :" << endl;
    printVector(v_students);
    
    v_students[0].set_KeyAttr(REG_ID); sort(v_students.begin(), v_students.end());
    cout << "\nv_students after sorting by reg_id :" << endl; printVector(v_students);
    v_students[0].set_KeyAttr(NAME); sort(v_students.begin(), v_students.end());
    cout << "\nv_students after sorting by name :" << endl; printVector(v_students);
    v_students[0].set_KeyAttr(ST_ID); sort(v_students.begin(), v_students.end());
    cout << "\nv_students after sorting by st_id :" << endl; printVector(v_students);
    v_students[0].set_KeyAttr(NATION); sort(v_students.begin(), v_students.end());
    cout << "\nv_students after sorting by Nation :" << endl; printVector(v_students);
    v_students[0].set_KeyAttr(DOB); sort(v_students.begin(), v_students.end());
    cout << "\nv_students after sorting by Date_of_Birth (DoB) :" << endl; printVector(v_students);
    v_students[0].set_KeyAttr(ARRV_TIME); sort(v_students.begin(), v_students.end());
    cout << "\nv_students after sorting by Arrival Time :" << endl; printVector(v_students);
    v_students[0].set_KeyAttr(GPA); sort(v_students.rbegin(), v_students.rend());
    cout << "\nv_students after sorting by GPA (decreasing order):" << endl; printVector(v_students);
    
    Student* pSt;
    T_Array<Student, int> stArray(num_student, "T_Array<Student>");
    for (int i = 0; i < num_student; i++)
    {
        stArray.insert(i, students[i]);
    }
    
    cout << "T_Array<Student> at initialization :" << endl; stArray.print(1);
    
    stArray[0].set_KeyAttr(REG_ID); stArray.insertion_sort(INCREASING);
    cout << "\nT_Array<Student> after insertion_sort(increasing order) by REG_ID : " << endl; stArray.print(1);
    
    stArray[0].set_KeyAttr(NAME); stArray.insertion_sort(INCREASING);
    cout << "\nT_Array<Student> after insertion_sort(increasing order) by NAME : " << endl; stArray.print(1);
    
    stArray[0].set_KeyAttr(ST_ID); stArray.insertion_sort(INCREASING);
    cout << "\nT_Array<Student> after insertion_sort(increasing order) by ST_ID : " << endl; stArray.print(1);
    
    stArray[0].set_KeyAttr(NATION); stArray.insertion_sort(INCREASING);
    cout << "\nT_Array<Student> after insertion_sort(increasing order) by NATION : " << endl; stArray.print(1);
    
    stArray[0].set_KeyAttr(DOB); stArray.insertion_sort(INCREASING);
    cout << "\nT_Array<Student> after insertion_sort(increasing order) by DoB : " << endl; stArray.print(1);
    
    stArray[0].set_KeyAttr(ARRV_TIME); stArray.insertion_sort(INCREASING);
    cout << "\nT_Array<Student> after insertion_sort(increasing order) by arrival_time : " << endl; stArray.print(1);
    
    stArray[0].set_KeyAttr(GPA); stArray.insertion_sort(DECREASING);
    cout << "\nT_Array<Student> after insertion_sort(decreasing order) by GPA : " << endl; stArray.print(1);
    
    return 0;
}

Student* fget_students(istream& fin, int& num_student) {
    fin >> num_student;
    Student* students = new Student[num_student];
    int reg_id, st_id;
    int yr, mn, dy;
    int hh, mm, ss;
    string name, nation;
    double gpa;
    for (int i = 0; i < num_student; i++) {
        fin >> reg_id >> name >> st_id >> nation;
        fin >> yr >> mn >> dy >> hh >> mm >> ss >> gpa;
        students[i].set_regID(reg_id);
        students[i].set_name(name);
        students[i].set_StID(st_id);
        students[i].set_nation(nation);
        students[i].set_DoB(Date(yr, mn, dy));
        students[i].set_ArrivalTime(Time(hh, mm, ss));
        students[i].set_GPA(gpa);
    }
    
    return students;
}

template<typename T>
void printVector(vector<T>& v) {
    string typeName = typeid(T).name();
    cout << "Vector size(" << v.size() << "), elements : \n";
    typename vector<T>::iterator p;
    for (p = v.begin(); p != v.end(); p++)
    {
        cout << *p << " ";
    }
    cout << endl;
};
