//
//  main.c
//  c-basic
//
//  Created by Jacob An on 2022/03/24.
//

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)

int main() {
    srand((unsigned int)time(NULL));
    int r = rand() % 6;
    
    int arr[] = { 1, 4, 7, 10, 13, 16};
    printf("The random number is %d\n", arr[r]);
    
    return 0;
}
