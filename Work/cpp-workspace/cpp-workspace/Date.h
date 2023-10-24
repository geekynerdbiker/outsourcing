#ifndef DATE_H
#define DATE_H

#include <iostream>
#include <cstdlib>
#include <fstream>

using namespace std;

#define WEEKDATY_AD01JAN01 MON
#define DAYS_P_WEEK 7

class Date
{
	friend ostream& operator<<(ostream& output, const Date&);

public:
	Date();
	Date(int y, int m, int d);
    ~Date();
	int getWeekDay();
	int getElapsedDaysFromAD010101() const;
    int getElapsedDaysFromAD010101(Date) const;
    bool operator<(const Date&) const;
    bool operator<=(const Date&) const;
    bool operator>(const Date&) const;
    bool operator>=(const Date&) const;
	bool operator==(const Date&) const;
	

private:
	bool isValidDate(int y, int m, int d);
	int year;
	int month;
	int day;
};
bool isLeapYear(int y);
int getYearDay(int year, int month, int day);


#endif // !DATE_H
