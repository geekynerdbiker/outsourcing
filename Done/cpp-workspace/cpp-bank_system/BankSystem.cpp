#include "BankAccount.h"
#include "BankSystem.h"
#include <cstring>

void BankSystem::transaction(BankAccount* from, BankAccount* to, float amount) {
    float fee = 5;
    
    if (!from->getBankname().compare(to->getBankname())) {
        if (from->withdraw(amount+fee) == 1) {
            to->deposit(amount);
        }
    } else {
        if (from->withdraw(amount) == 1) {
            to->deposit(amount);
        }
    }
}

void BankSystem::deposit(BankAccount* b, float amount) {
    b->deposit(amount);
}

void BankSystem::withdraw(BankAccount* b, float amount) {
    b->withdraw(amount);
}
void BankSystem::loan(BankAccount* b, float amount) {
    b->loan(amount);
}
