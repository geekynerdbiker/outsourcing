//
//  main.c
//  c-basic
//
//  Created by Jacob An on 2022/03/24.
//

#include <stdio.h>
#pragma warning(disable:4996)

int main() {
    float a, b;
    printf("First num : ");
    scanf("%f", &a);
    
    printf("Second num : ");
    scanf("%f", &b);
    
    printf("Add : %.0f\n", a+b);
    printf("Sub : %.0f\n", a-b);
    printf("Mul : %.0f\n", a*b);
    printf("Div : %f\n", a/b);
    
    return 0;
}
