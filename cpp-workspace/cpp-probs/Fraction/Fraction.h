#pragma once
#include <iostream>

using namespace std;

class Fraction {
public:
	Fraction();
	Fraction(int, int);
	
    const int getNumer() const;
    void setNumer(int);
    
    const int getDenom() const;
	 int setDenom(int);
	
    const int getGcd(int, int) const;
	const Fraction operator +(const Fraction&) const;
private:
	int denom, numer;
};

ostream& operator <<(ostream& oStream, const Fraction& fraction);
