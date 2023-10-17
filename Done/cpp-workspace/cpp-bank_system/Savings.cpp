#include "BankAccount.h"
#include "Savings.h"
#include <iostream>

Savings::Savings(int num, float bal, float rate) : BankAccount(num, bal) {
    this->intrate = rate;
}

void Savings::interest() {
    this->bal += this->bal * this->intrate / 1200.;
}

int Savings::withdraw(float amount) {
    if (amount > this->bal) {
        cout << "Cannot withdraw " << amount << " on account " << this->acctnum << " because the balance is low." << endl;
        return 0;
    } else {
        this->bal -= amount;
        return 1;
    }
}

void Savings::print() {
    cout << "Savings Account: " << this->acctnum << " BankName: " << this->bank_name << " Credit: " << this->credit << endl;
    cout << "\tBalance: " << this->bal << endl;
    cout << "\tInterest: " << this->intrate << endl << endl;
}
