#include <stdio.h>

int main(int argc, const char * argv[]) {
    int month, days;
    
    printf("달을 입력하시오: ");
    scanf("%d", &month);
    
    switch (month){
        case 2:
            days = 28;
            break;
        case 4:
            days = 30;
            break;
        case 6:
            days = 30;
            break;
        case 9:
            days = 30;
            break;
        case 11:
            days = 30;
            break;
        case 1:
            days = 31;
            break;
        case 3:
            days = 31;
            break;
        case 5:
            days = 31;
            break;
        case 7:
            days = 31;
            break;
        case 8:
            days = 31;
            break;
        case 10:
            days = 31;
            break;
        case 12:
            days = 31;
            break;
        default:
            days = 0;
            printf("%d는 없는 달 입니다.\n", month);
    }
    printf("%d월의 일수는 %d일입니다.\n", month, days);
    
    return 0;
}
