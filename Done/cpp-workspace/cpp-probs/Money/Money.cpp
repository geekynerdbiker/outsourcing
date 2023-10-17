#include <iostream>
#include "Money.h"

Money::Money() {
	dollars = 0;
	cents = 0;
}
Money::Money(int dollar, int cent) {
	setDollars(dollar);
    setCents(cent);
}

int Money::getDollars() const { return dollars; }
void Money::setDollars(int dollar) { dollars = dollar; }

int Money::getCents() const { return cents; }
void Money::setCents(int cent) { cents = cent; }

Money Money::inputNreturn() {
    int dollar, cent;
	
    cout << "Input dollars and cents : ";
	cin >> dollar >> cent;
    
    if (cent >= 100) {
        setDollars(dollar + (cent / 100));
        setCents(cent % 100);
    } else {
        setDollars(dollar);
        setCents(cent);
    }
    if (dollar != 0 || cent != 0)
        cout << "Input amount is " << toString() << endl;

    return Money(dollars, cents);
}
string Money::toString() const {
	string str = "$" + to_string(dollars) + '.' + to_string(cents);
	
    return str;
}

const Money Money::operator +(const Money& secondMoney) const {
	return Money(dollars + secondMoney.getDollars(), cents + secondMoney.getCents());
}
const Money Money::operator -(const Money& secondMoney) const {
	int resultCents = dollars * 100 + cents - secondMoney.getDollars() * 100 + secondMoney.getCents();
    
	return Money(resultCents / 100, resultCents % 100);
}
const bool Money::operator ==(const Money& secondMoney) const {
	return (dollars * 100 + cents == secondMoney.getDollars() * 100 + secondMoney.getCents());
}
const bool Money::operator !=(const Money& secondMoney) const {
	return (dollars * 100 + cents != secondMoney.getDollars() * 100 + secondMoney.getCents());
}
const bool Money::operator >=(const Money& secondMoney) const {
	return (dollars * 100 + cents >= secondMoney.getDollars() * 100 + secondMoney.getCents());
}
const bool Money::operator <=(const Money& secondMoney) const {
	return (dollars * 100 + cents <= secondMoney.getDollars() * 100 + secondMoney.getCents());
}
const bool Money::operator >(const Money& secondMoney) const {
	return (dollars * 100 + cents > secondMoney.getDollars() * 100 + secondMoney.getCents());
}
const bool Money::operator <(const Money& secondMoney) const {
	return (dollars * 100 + cents < secondMoney.getDollars() * 100 + secondMoney.getCents());
}
