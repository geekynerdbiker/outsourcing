#include "DDay.h"
#include <iomanip>

using namespace std;

const int MONTHS = 12;
const int DAYS[MONTHS + 1] = { 31, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

bool isLeap(int yy) {
    return ((yy % 4 == 0 && yy % 100 != 0) || yy % 400 == 0);
}

/* Day */
Day::Day() {
    year = 2022;
    month = 9;
    day = 29;
}
Day::Day(int yy, int mm, int dd) {
    year = yy;
    month = mm;
    day = dd;
}

const int Day::getYear() const { return year; }
void Day::setYear(int yy) { year = yy; }

const int Day::getMonth() const { return month; }
void Day::setMonth(int mm) { month = mm; }

const int Day::getDay() const { return day; }
void Day::setDay(int dd) { day = dd; }

const Day Day::operator ++() {
    day++;
    
    if (day > DAYS[month] + (month == 2 && isLeap(year))) {
        day -= DAYS[month] + (month == 2 && isLeap(year));
        month++;
    }
    
    if (month > 12) {
        year++;
        month = 1;
    }

    return Day(year, month, day);
}
const Day Day::operator --() {
    day--;
    if (day < 1) {
        month--;
        if (month < 1) {
            year--;
            month = 12;
        }
        day = DAYS[month] + (month == 2 && isLeap(year));
    }
    
    return Day(year, month, day);
}
const Day Day::operator +(int dd) const {
    int tmpYY = year;
    int tmpMM = month;
    int tmpDD;
    
    dd -= 1;
    while (dd >= 365 + isLeap(tmpYY + 1) ) {
        dd -= 365 + isLeap(tmpYY + 1);
        tmpYY++;
    }
    
    tmpDD = day + dd;
    while (tmpDD > DAYS[tmpMM]) {
        if (tmpDD > DAYS[tmpMM] + (month == 2 && isLeap(tmpYY))) {
            tmpDD -= DAYS[tmpMM] + (month == 2 && isLeap(tmpYY));
            tmpMM++;
        }
        if (tmpMM > 12) {
            tmpYY++;
            tmpMM = 1;
        }
    }
    return Day(tmpYY, tmpMM, tmpDD);
}
const Day Day::operator -(int dd) const {
    int tmpYY = year;
    int tmpMM = month;
    int tmpDD;
    
    dd *= -1;
    while (abs(dd) >= 365 + (month == 2 && isLeap(tmpYY))) {
        if (!isLeap(tmpYY - 1)) {
            if (dd <= -365) {
                dd += 365;
                tmpYY--;
            }
        } else {
            if (dd <= -366) {
                dd += 366;
                tmpYY--;
            }
        }
    }
    
    tmpDD = day + dd;
    while (tmpDD < 0) {
        if (isLeap(tmpYY))
            tmpMM--;
            if (tmpMM < 1) {
                tmpYY--;
                tmpMM = 12;
            }
        else
            while (tmpDD <= 0) {
                tmpDD += DAYS[tmpMM];
                if (tmpDD <= 0) tmpMM--;
                if (tmpMM < 1) {
                    tmpYY--;
                    tmpMM = 12;
                    tmpDD = 31 - abs(tmpDD);
                }
            }
    }
    
    return Day(tmpYY, tmpMM, tmpDD);
}

ostream& operator <<(ostream& oStream, const Day& day) {
    oStream << day.getYear() << "/";
    oStream << setfill('0') << setw(2) << right << day.getMonth() << "/";
    return oStream << setfill('0') << setw(2) << right << day.getDay();;
}

/* D-Day */
DDay::DDay() {
	today = Day();
	dDate = Day(0, 0, 0);
	dDay = 0;
}
Day DDay::getToday() const { return today; }
void DDay::setToday(char input[9]) {
    int yy = (input[0] - '0') * 1000 + (input[1] - '0') * 100 + (input[2] - '0') * 10 + (input[3] - '0') * 1;
    int mm = (input[4] - '0') * 10 + (input[5] - '0') * 1;
    int dd = (input[6] - '0') * 10 + (input[7] - '0') * 1;
    
    if (mm >12) {
        cout << "*** Error!! Set month as 1" << endl;
        mm = 1;
    }
    if (dd > DAYS[mm]) {
        cout << "*** Error!! Set day as 1" << endl;
        dd = 1;
    }
    
    today = Day(yy, mm, dd);
    if (dDay != 0) {
        setDDate(dDay);
    }
}
void DDay::setToday(Day dd) { today = dd; }

Day DDay::getDDate() const { return dDate; }
void DDay::setDDate(int dday) {
    if (dday > 0) {
        dDate = today + dday;
        dDay = dday;
    }
    else {
        dDate = today - (-1 * dday);
        dDay = dday;
    }
}

int DDay::getDDay() const { return dDay; }

ostream& operator <<(ostream& oStream, const DDay& dday) {
	oStream << "[Date] " << dday.getToday();
	oStream << " [D-day : " << dday.getDDay() << "] ";
	if (dday.getDDay() == 0) oStream << "NONE";
	else oStream << dday.getDDate();
        
	return oStream;
}
