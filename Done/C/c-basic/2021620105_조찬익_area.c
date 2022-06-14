#include <stdio.h>
#define PI 3.14

int main(int argc, const char * argv[]) {
    double r;
    
    printf("원의 반지름을 실수로 입력하시오. 예<10.3> : ");
    scanf("%lf", &r);
    printf("원의 둘레: %.2f\n", r*2*PI);
    printf("원의 면적: %.4f\n", r*r*PI);
    
    return 0;
}
