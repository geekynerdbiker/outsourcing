#ifndef BANKACCOUNT_H
#define BANKACCOUNT_H
#include <string>
using namespace std;

class BankAccount{
    public:
        BankAccount(int num,float bal);
        void deposit(float amount); //money getting into account
        void loan(float amount); 
        virtual int withdraw(float amount) = 0; // money getting out of account
        int getAcctnum(); // getter function
        float getBalance();// getter function
        int getcredit(); // getter function
        string getBankname(); // getter function
        virtual void print() = 0;
    protected:
        int acctnum; // account number(계좌번호)
        float bal; //current balance of account(현재 잔고)
        string bank_name;
        int credit;
};

#endif
