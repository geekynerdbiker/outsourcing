#include "Date.h"
#include <iostream>
#include <iomanip>
#include <string>
 
enum WEEKDAY { SUN, MON, TUE, WED, THR, FRI, SAT };
enum MONTHS { JAN = 1, FEB, MAR, APR, MAY, JUN, JUL, AUG, SEP, OCT, NOV, DEC };
const char* WeekDayName[DAYS_P_WEEK] = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };
const char* MonthName[13] = { "", "January", "February", "March", "April",
	"May", "June", "July", "August", "September", "October", "November", "December" };


ostream& operator<<(ostream& output, const Date& D) {
	output << "(" << setw(4) << D.year << "."
		<< setw(2) << right << D.month << "."
		<< setw(2) << right << D.day << ")";

	return output;
}


Date::Date() {
	year = 0; month = 0; day = 0;
}

Date::Date(int y, int m, int d) {
    year = y;
    month = m;
    day = d;
}

Date::~Date() {
    
}

int Date::getWeekDay() {
    int weekDay_AD010101 = MON;
    int weekDay;
    int elapsedDays = 0;

    elapsedDays = getElapsedDaysFromAD010101();
    weekDay = (weekDay_AD010101 + elapsedDays) % 7;
    
    return weekDay;
}

int Date::getElapsedDaysFromAD010101() const {
    int yearDay;
    int elpsDay = 0;
    
    for (int y = 2; y < year; y++) {
        if (isLeapYear(y))
            elpsDay += 366;
        else
            elpsDay += 365;
    }

    yearDay = getYearDay(year, month, day);
    elpsDay += (yearDay - 1);
    
    return elpsDay;
}

int Date::getElapsedDaysFromAD010101(Date D) const {
    int yearDay;
    int elpsDay = 0;

    for (int y = 2; y < D.year; y++) {
        if (isLeapYear(y))
            elpsDay += 366;
        else
            elpsDay += 365;
    }

    yearDay = getYearDay(year, month, day);
    elpsDay += (yearDay - 1);

    return elpsDay;
}

bool Date::operator<(const Date& D) const {
    if (this->getElapsedDaysFromAD010101() < D.getElapsedDaysFromAD010101())
        return true;
    else
        return false;
}
bool Date::operator<=(const Date& D) const {
    if (this->getElapsedDaysFromAD010101() <= D.getElapsedDaysFromAD010101())
        return true;
    else
        return false;
}

bool Date::operator>(const Date& D) const {
	if (this->getElapsedDaysFromAD010101() > D.getElapsedDaysFromAD010101())
		return true;
	else
		return false;
}

bool Date::operator>=(const Date& D) const {
    if (this->getElapsedDaysFromAD010101() >= D.getElapsedDaysFromAD010101())
        return true;
    else
        return false;
}


bool Date::operator==(const Date& D) const {
	if (this->getElapsedDaysFromAD010101() == D.getElapsedDaysFromAD010101())
		return true;
	else
		return false;
}

bool Date::isValidDate(int y, int m, int d) {
	int days_month[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

	if (isLeapYear(y))
		days_month[FEB] = 29;

	if ((y >= 1) && ((m >= 1) && (m <= 12)) && ((d >= 1) && (d <= days_month[m])))
		return true;
	else
		return false;
}

bool isLeapYear(int y) {
    if ((y % 100 == 0) && (y % 4) == 0 && (y % 400 != 0))
        return true;
    else
        return false;
}

int getYearDay(int year, int month, int day) {
    int days_month[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    int yearDay = 0;

    if (isLeapYear(year))
        days_month[FEB] = 29;
    for (int months = JAN; months < month; months++)
        yearDay += days_month[months];
    yearDay += day;

    return yearDay;
}
