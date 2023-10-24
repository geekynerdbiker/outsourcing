#include "Time.h"

ostream& operator<<(ostream& ostr, const Time& t) {
    ostr << "(";
    ostr << setw(2) << t.hour << ":"
        << setw(2) << t.min << ":"
        << setw(2) << t.sec << ")";

    return ostr;
}

Time::Time()
{
	hour = 0; min = 0; sec = 0;
}

Time::Time(int h, int m, int s)
{
	if (isValidTime(h, m, s))
	{
		hour = h; min = m; sec = s;
	}
	else
	{
		cout << "illegal time!!" << endl;
		exit(-1);
	}
}

Time& Time::operator+(int s)
{
    this->sec += s;

    if (sec >= 60)
    {
        for (int i = 0; i < sec / 60; i++)
            min++;
        sec = sec % 60;
    }

    if (min >= 60)
    {
        for (int i = 0; i < min / 60; i++)
            hour++;
        min = min % 60;
    }

    if (hour >= 24)
    {
        hour = hour % 24;
    }

    return *this;
}

int Time::elasedSec() const {
	int e_sec = 0;
    
	e_sec += this->sec;
	e_sec += this->min * 60;
	e_sec += this->hour * 60 * 60;

	return e_sec;
}

Time Time::getTime() {
	Time get(*this);

	return get;
}

bool Time::operator<(const Time& t) const {
	if (this->elasedSec() < t.elasedSec())
		return true;
	return false;
}

bool Time::operator<=(const Time& t) const {
	if (this->elasedSec() <= t.elasedSec())
		return true;
	return false;
}

bool Time::operator>(const Time& t) const {
	if (this->elasedSec() > t.elasedSec())
		return true;
	return false;
}

bool Time::operator>=(const Time& t) const {
	if (this->elasedSec() >= t.elasedSec())
		return true;
	return false;
}

bool Time::operator==(const Time& t) const {
	if (this->elasedSec() == t.elasedSec())
		return true;
	return false;
}


bool Time::isValidTime(int h, int m, int s) {
    if (h < 24 && m < 60 && s < 60)
        return true;
    return false;
}
