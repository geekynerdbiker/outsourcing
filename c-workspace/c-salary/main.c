//
//  main.c
//  c-payment
//
//  Created by Jacob An on 2022/04/17.
//

#include <time.h>
#include <stdio.h>
#include <stdlib.h>

double getTax(double salary) {
    double tax;
    
    if (salary < 10000000) {
        return salary * 0.08;
    } else if (salary < 40000000) {
        return 10000000 * 0.08 + (salary - 10000000) * 0.17;
    } else if (salary < 80000000) {
        return 10000000 * 0.08 + (salary - 10000000) * 0.17 + (salary - 30000000) * 0.26;
    }
    return 10000000 * 0.08 + (salary - 10000000) * 0.17 + (salary - 30000000) * 0.26 + (salary-40000000) * 0.35;
    
}

int main(int argc, const char * argv[]) {
    srand((unsigned int)time(NULL));
    
    double salary, inflation = 0;
    
    
    printf("연봉: ");
    scanf("%lf",&salary);
    
    for (int year = 1; year <=30; year++) {
        if (year >= 2)
            inflation = rand() % 4 + 1;
            salary += salary * ((inflation + 1) / 100);
        double tax = getTax(salary);
        
        printf("%d년차 연봉인상률: %.lf%%, 연봉액: %.lf원, 근로세액: %.lf원, 실질소득액: %.lf원\n", year, (inflation), salary, tax, salary-tax);
    }
    return 0;
}
