#include "BankAccount.h"
#include "Checking.h"
#include <iostream>

Checking::Checking(int num, float bal, float min, float chg) : BankAccount(num, bal) {
    this->minimum = min;
    this->charge = chg;
}

int Checking::withdraw(float amount) {
    if (amount > this->bal) {
        cout << "Cannot withdraw " << amount << " on account " << this->acctnum << " because the balance is low." << endl;
        return 0;
    } else {
        if (this->bal < this->minimum) {
            this->bal -= amount + this->charge;
        } else {
            this->bal -= amount;
        }
        
        return 1;
    }
}

void Checking::print() {
    cout << "Checking Account: " << this->acctnum << " BankName: " << this->bank_name << " Credit: " << this->credit << endl;
    cout << "\tBalance: " << this->bal << endl;
    cout << "\tMinimum to Avoid Charges: " << this->minimum << endl;
    cout << "\tCharge per Check: " << this->charge << endl << endl;
}
