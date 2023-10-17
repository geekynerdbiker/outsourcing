#include "Fraction.h"

Fraction::Fraction() {
	numer = 1;
	denom = 1;
}

Fraction::Fraction(int num, int den) {
	numer = num;
    if (den == 0) cout << "Denom cannot be 0." << endl;
    else setDenom(den);
};

const int Fraction::getDenom() const { return denom; }
int Fraction::setDenom(int den) {
    denom = den;

    int gcd = getGcd(numer, denom);
    
    numer /= gcd;
    denom /= gcd;
    
    return 1;
};

const int Fraction::getNumer() const { return numer; }
void Fraction::setNumer(int num) {
    numer = num;
    setDenom(denom);
};

const int Fraction::getGcd(int n1, int n2) const {
    int smaller = 0, gcd = 1;
    
    smaller = abs(n2) > abs(n1) ? abs(n1) : abs(n2);
    
    for (int i = 2; i <= smaller; i++)
        if (n1 % i == 0 && n2 % i == 0)
            gcd = i;
    
    return gcd;
}

const Fraction Fraction::operator +(const Fraction& fraction) const {
	
	return Fraction((numer * fraction.denom) + (fraction.numer * denom), denom * fraction.denom);
};

ostream& operator <<(ostream& outputStream, const Fraction& fraction) {
	if (fraction.getNumer() * fraction.getDenom() < 0)
		return outputStream << "-" << abs(fraction.getNumer()) << "/" << abs(fraction.getDenom());
	else return outputStream << abs(fraction.getNumer()) << "/" << abs(fraction.getDenom());
}
