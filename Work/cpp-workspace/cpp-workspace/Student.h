#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <iomanip>
#include "Person.h"
#include "Time.h"

using namespace std;

enum STUDENT_ATTR {REG_ID, NAME, ST_ID, NATION, DOB, ARRV_TIME, GPA };
class Student : public Person
{
	friend ostream& operator<< (ostream&, Student&);
public:
	Student();
	Student(int reg_id, string n, int st_id, string country, double gpa);
    void set_StID(int st_id) { this->st_id = st_id; }
    int get_StID() const { return this->st_id; }
    void set_GPA(double gpa) { this->gpa = gpa; }
    double get_GPA() const { return this->gpa; }
    void set_ArrivalTime(Time arvTime) { arrivalTime = arvTime; }
    Time get_ArrivalTime() const { return arrivalTime; }
    static void set_KeyAttr(STUDENT_ATTR keyAttr) { keyAttr = keyAttr; }
    static STUDENT_ATTR get_KeyAttr() { return keyAttr; }
    static STUDENT_ATTR keyAttr;
    bool operator<(const Student& other) const;
    bool operator<=(const Student& other) const;
    bool operator>(const Student& other) const;
    bool operator>=(const Student& other) const;
    bool operator==(const Student& other) const;

private:
	int st_id;
	double gpa;
	Time arrivalTime;
};

#endif // !STUDENT_H
