#include <stdio.h>

int main(int argc, const char * argv[]) {
    int i, goods, price;
    int min = 100000, max = -100000;
    int sum, avg ;
    
    sum = 0;
    do {
        printf("제품개수를 입력하시오: ");
        scanf("%d", &goods);
    } while (goods < 1 || goods>3);
    
    for (i = 0; i < goods; i++){
        do {
            printf("%d번째 제품의 가격을 입력하시오: ", i+1);
            scanf("%d", &price);
        } while (price < 1000 || price>10000);
        
        if (price < min)
            min = price;
        if (price > max)
            max = price;
        sum = sum + price;
    }
    avg = sum / goods;
    printf("최대값:  %d 최소값:  %d 평균값: %d\n", max, min, avg);
    
    return 0;
}
