#include <stdio.h>

int getDay(int y) {
    int days[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int month = 0, year = 0, lunar = 1;
    
    for (lunar = 1; lunar < y; lunar++) {
        if (lunar % 4 == 0 || (lunar % 100 != 0 && lunar % 400 == 0))
            year += 366;
        else
            year += 365;
    }
    
    if (lunar % 4 == 0 || (lunar % 100 != 0 && lunar % 400 == 0))
        days[1] = 29;
    
    return (year + month) % 7;
}

int main(int argc, char *argv[]) {
    int year;
    
    printf("연도를 입력하세요: ");
    scanf("%d", &year);
    
    int count = 1;
    int array[42] = { 0 };
    for (int i = getDay(year); i < getDay(year)+31; i++)
        array[i] = count++;
    
    for (int i = 0; i < 42; i++) {
        if (i % 7 == 0)
            printf("\n");
        printf("%3d ", array[i]);
    }
    printf("\n");
    
    return 0;
}
