#include "BankAccount.h"
#include "Checking.h"
#include "InterestChecking.h"
#include <iostream>

InterestChecking::InterestChecking(int num, float bal, float cmin, float imin, float chg, float rate, float monchg) : Checking(num, bal, cmin, chg) {
    this->minint = imin;
    this->intrate = rate;
    this->moncharge = monchg;
}

void InterestChecking::interest() {
    if (this->bal < this->minint) {
        this->bal -= this->moncharge;
    } else {
        this->bal += this->bal * this->intrate / 1200.;
    }
}

void InterestChecking::print() {
    cout << "Checking Account: " << this->acctnum << " BankName: " << this->bank_name << " Credit: " << this->credit << endl;
    cout << "\tBalance: " << this->bal << endl;
    cout << "\tMinimum to Avoid Charges: " << this->minimum << endl;
    cout << "\tCharge per Check: " << this->charge << endl;
    cout << "\tMinimum balance for getting interest and No Monthly Fee: " << this->minint << endl;
    cout << "\tInterest: " << this->intrate << "%" << endl;
    cout << "\tMonthly Fee: " << this->moncharge << endl << endl;
}
