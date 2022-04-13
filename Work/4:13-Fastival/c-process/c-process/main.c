//
//  main.c
//  c-process
//
//  Created by Jacob An on 2022/04/13.
//

#include <time.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char * argv[]) {
    int buffer, equation;
    srand((unsigned int)time(NULL));
    
    printf("Enter Bounded buffer size: ");
    scanf("%d", &buffer);
    printf("Equation frequency: ");
    scanf("%d", &equation);
    
    
    return 0;
}

void producer() {
    int a, b, op;
    
    a = rand() % 100;
    b = rand() % 100;
    
}

void consumer() {
    
}
