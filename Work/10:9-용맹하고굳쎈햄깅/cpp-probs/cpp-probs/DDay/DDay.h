#include <iostream>
#pragma once

using namespace std;

/* Day */
class Day {
public:
    Day();
    Day(int, int, int);
    
    const int getYear() const;
    void setYear(int);
    
    const int getMonth() const;
    void setMonth(int);
    
    const int getDay() const;
    void setDay(int);
    
    
    const Day operator ++();
    const Day operator --();
    const Day operator +(int) const;
    const Day operator -(int) const;
private:
    int year;
    int month;
    int day;
};
ostream& operator <<(ostream& oStream, const Day& day);

/* D-Day */
class DDay {
public:
	DDay();
    
	Day getToday() const;
    void setToday(char[9]);
    void setToday(Day);
    
    Day getDDate() const;
    void setDDate(int);
    
    int getDDay() const;
private:
	Day today;
	Day dDate;
	int dDay;
};
ostream& operator <<(ostream&, const DDay&);
