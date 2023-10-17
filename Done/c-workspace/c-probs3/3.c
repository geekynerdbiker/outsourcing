//
//  main.c
//  dknsd
//
//  Created by Jacob An on 2021/12/13.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int main(int argc, const char * argv[]) {
    srand((unsigned) time(NULL));
    
    int r[15];
    int under5 = 0, over5 = 0;
    
    int i;
    for (i=0;i<15;i++) {
        r[i] = rand() % 10 + 1;
        printf("%d번째 저장된 난수는 %d다.\n", i, r[i]);
        if (r[i] <= 5) under5++;
        else over5++;
    }
    
    double e = (-1*(double)under5/15.0*log((double)under5/15.0))+(-1*(double)over5/15.0*log((double)over5/15.0));
    
    printf("5이하의 숫자 개수: %d\n", under5);
    printf("5를 초과하는 숫자 개수: %d\n", over5);
    printf("배열의 엔트로피는 %.6lf다.\n", e);
    
}
