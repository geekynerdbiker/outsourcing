#include "BankAccount.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

BankAccount::BankAccount(int num, float bal) {
    int r = rand() % 3;
    
    this->acctnum = num;
    this->bal = bal;
    
    if (r == 0)
        this->bank_name = "하나";
    else if (r == 1)
        this->bank_name = "우리";
    else if (r == 2)
        this->bank_name = "신한";
    
    if (bal < 1000)
        this->credit = 1;
    else if (bal < 2000)
        this->credit = 2;
    else
        this->credit = 3;
    
}
void BankAccount::deposit(float amount) {
    this->bal += amount;
}

void BankAccount::loan(float amount) {
    if (this->credit == 1) {
        cout << "The amount cannot be loaned" << endl;
    } else if (this->credit == 2) {
        if (amount < 100 || amount > 500)
            cout << "The amount cannot be loaned" << endl;
        else
            this->bal += amount * 0.9;
    } else if (this->credit == 3) {
        if (amount < 100 || amount > 1000)
            cout << "The amount cannot be loaned" << endl;
        else
            this->bal += amount * 0.95;
    }
    
}

int BankAccount::getAcctnum() {
    return this->acctnum;
    
}

float BankAccount::getBalance() {
    return this->bal;
}

int BankAccount::getcredit() {
    return this->credit;
}

string BankAccount::getBankname() {
    return this->bank_name;
}
