//
//  main.cpp
//  untitled2
//
//  Created by Jacob An on 2021/12/09.
//

#include <iostream>

// Q7
const ComplexNumber z1(3.0, 4.0);
const ComplexNumber z2(2.0, -5.2);
const ComplexNumber z3(-1.5, 6.0);
const ComplexNumber z4(2.0, 3.0);

ComplexNumber z5 = subtract(multiply(add(z2, z3.conjugate()), z4), z1);
ComplexNumber z6 = add(multiply(ComplexNumber(3, 0), z2),ComplexNumber(z1.norm(), 0));


// Q8
vector<double> remove_negative (vector<double> &vec) {
vector<double> negative_part, positive_part;

for(int i=0 ; i < vec.size(); i++){
double k = vec.front();

if (k < 0) negative_part.push_back(k);
else positive_part.push_back(k);
}

vec = positive_part;
return negative_part;
}

// Q9
char* merge (char str1[], char str2[]) {
char* merged = (char*)malloc(sizeof(char)*(strlen(str1)+strlen(str2)));

int len1 = strlen(str1);
int len2 = strlen(str2);

for (int i=0; i < (len1 < len2 ? len1 : len2); i++) {
merged[2*i] = str1[i];
merged[2*i+1] = str2[i];
}

for (int i=(len1 < len2 ? len1 : len2); i < (len1 > len2 ? len1 : len2); i++){ //4 5 6
char c = len1 > len2 ? str1[i] : str2[i];
merged[i+(len1 < len2 ? len1 : len2)] = c;
}

return merged;
}


// Q10-1
vector<BankAccount> ba;

for (int i=0; i < 100; i) {
double balance = (rand % 30 + 11) * 100
ba.push_back(BankAccount(i, balance));
}


// Q10-2
BankAccount merge2Accounts(BankAccount& acc1, BankAccount& acc2, string new_name) {
double balance = acc1.getBalance() + acc2.getBalance();

acc1.setName(&quot;inactive account&quot;);
acc1.setBalance(0);
acc2.setName(&quot;inactive account&quot;);
acc2.setBalance(0);

return BankAccount(new_name, balance);

}

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}
