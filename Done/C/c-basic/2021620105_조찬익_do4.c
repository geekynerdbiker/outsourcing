#include <stdio.h>

int main(int argc, const char * argv[]) {
    int n, sum = 0;
    
    do {
        printf("정수를 입력하시오(5의 배수이면 종료) : ");
        scanf("%d", &n);
    
        sum += n;
    } while ( n % 5 != 0);

    printf("입력된 정수들의 총합계 : %d\n", sum);
    
    return 0;
}
