#include <stdio.h>

int prime(int);
int get_number();

int main(int argc, const char * argv[]) {
    int n, result;
    
    n = get_number();
    result = prime(n);
    printf("%d의 약수들의 합은 %d입니다.\n", n, result);
    
    return 0;
}

int get_number() {
    int n;
    
    printf("정수를 입력하시오: ");
    scanf("%d", &n);
    
    return n;
}

int prime(int n) {
    int i, sum=0;
    
    for (i = 1; i <= n; i++) {
        if (n % i == 0) {
            printf("%d는 약수입니다.\n", i);
            sum += i;
        }
        else
            printf("%d는 약수가 아닙니다.\n", i);
    }
    return sum;
}
