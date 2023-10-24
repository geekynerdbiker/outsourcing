#ifndef TIME_H
#define TIME_H

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

class Time
{
	friend ostream& operator<< (ostream&, const Time&);
public:
	Time();
	Time(int h, int m, int s);
    Time& operator+(int s);
	int elasedSec() const;
	Time getTime();
	bool operator<(const Time& t) const;
	bool operator<=(const Time& t) const;
	bool operator>(const Time& t) const;
	bool operator>=(const Time& t) const;
	bool operator==(const Time& t) const;
private:
	bool isValidTime(int, int, int);
	int hour;
	int min;
	int sec;
};

#endif // !TIME_H

