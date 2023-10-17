#include <iostream>
#include "Fraction.h"

int main() {
    Fraction f1(2,3), f2(-2,5), f3;
    f3 = f1 + f2;
    cout << f1 << " + " << f2;
    cout << " = " << f3 << endl;
    return 0;
}
