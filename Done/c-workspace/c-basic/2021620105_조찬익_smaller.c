#include <stdio.h>

int main(int argc, const char * argv[]) {
    int x, y, z, min;
    
    printf("첫번째 정수: ");
    scanf("%d", &x);
    printf("두번째 정수: ");
    scanf("%d", &y);
    printf("세번째 정수: ");
    scanf("%d", &z);
    
    if (x < y) {
        if (x < z) min = x;
        else min = z;
    }
    else {
        if (y < z) min = y;
        else min = z;
    }
    printf("입력한 %d, %d, %d 중 가장 작은 수는 %d 입니다.\n", x, y, z, min);
    
    return 0;
}
