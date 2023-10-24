#ifndef PERSON_H
#define PERSON_H

#include <iostream>
#include <iomanip>
#include "Date.h"

using namespace std;

class Person
{
    friend ostream& operator<<(ostream& fout, const Person& p);
public:
    Person() { name = "nobody"; }
    Person(string n) { name = n; }
    void set_name(string n) { name = n; }
    const string get_name() const { return name; }
    void set_nation(string country) { nation = country; }
    const string get_nation() const { return nation; }
    void set_regID(int rgID) { regID = rgID; }
    const int get_regID() const { return regID; }
    void set_DoB(Date dob) { DoB = dob; }
    Date get_DoB() const { return DoB; }
protected:
    string name;
    int regID;
    string nation;
    Date DoB;
};

#endif // !PERSON_H
