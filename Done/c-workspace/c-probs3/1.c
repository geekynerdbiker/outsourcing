//
//  main.c
//  dknsd
//
//  Created by Jacob An on 2021/12/13.
//

#include <stdio.h>

int main(int argc, const char * argv[]) {
    int n;
    int fib[20];
    
    printf("1000이하의 자연수를 입력하시오: ");
    scanf("%d", &n);
    
    fib[0] = 1;
    fib[1] = 1;
    
    for (int i=2; i < 19; i++) {
        fib[i] = fib[i-1]+fib[i-2];
        if (fib[i] % n == 0 && fib[i] < 1000)
            printf("피보나치 수중 사용자가 입력한 수의 배수: %d\n", fib[i]);
    }
    
    
    return 0;
}
