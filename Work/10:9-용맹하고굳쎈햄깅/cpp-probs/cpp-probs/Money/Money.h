#include <string>
#pragma once

using namespace std;

class Money {
public:
	Money();
	Money(int, int);
    
	int getDollars() const;
    void setDollars(int);
    
    int getCents() const;
	void setCents(int);
    
	Money inputNreturn();
	string toString() const;
	
    const Money operator +(const Money&) const;
	const Money operator -(const Money&) const;
	const bool operator ==(const Money&) const;
	const bool operator !=(const Money&) const;
	const bool operator >=(const Money&) const;
	const bool operator <=(const Money&) const;
	const bool operator >(const Money&) const;
	const bool operator <(const Money&) const;
private:
	int dollars = 0;
	int cents = 0;
    
	void setSum(int, int);
};
