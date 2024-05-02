#include <stdio.h>

int main() {
    while (1) {
        long long a1 = 0, a2 = 0, b1 = 0, b2 = 0;
        int aLen1 = 0, aLen2 = 0, bLen1 = 0, bLen2 = 0;
        char turn = 'a';
        
        char input = 0, continueRun = 0;
        int opError = 0;
        printf("수식 : ");
        while (1) {
            input = getchar();
            
            if (input >= '0' && input <= '9') {
                if (turn == 'a') {
                    if (aLen1 < 15) {
                        a1 *= 10;
                        a1 += input - '0';
                        aLen1++;
                    } else if (aLen2 < 15) {
                        a2 *= 10;
                        a2 += input - '0';
                        aLen2++;
                    }
                } else if (turn == 'b') {
                    if (bLen1 < 15) {
                        b1 *= 10;
                        b1 += input - '0';
                        bLen1++;
                    } else if (bLen2 < 15) {
                        b2 *= 10;
                        b2 += input - '0';
                        bLen2++;
                    }
                }
            } else if (input == '+') {
                turn = 'b';
            } else if (input == ' ') {
                continue;
            } else if (input == '\n') {
                break;
            } else {
                printf("결과 : 잘못된 연산자입니다.");
                opError = 1;
                break;
            }
        }
        if (opError) {
            printf("\n");
            getchar();
        } else {
            long long sum1 = 0;
            long long sum2 = 0;
            
            if (aLen2 == 0 && bLen2 == 0) {
                sum1 = a1 + b1;
            } else {
                for (int i = 0; i < 15 - aLen2; i++) {
                    unsigned long long k = a1 % 10;
                    for (int j = aLen2; j < i + aLen2; j++)
                        k *= 10;
                    a2 += k;
                    aLen2++;
                    a1 /= 10;
                    aLen1--;
                }
                for (int i = 0; i < 15 - bLen2; i++) {
                    unsigned long long k = b1 % 10;
                    for (int j = bLen2; j < i + bLen2; j++)
                        k *= 10;
                    b2 += k;
                    bLen2++;
                    b1 /= 10;
                    bLen1--;
                }
                sum1 = a1 + b1;
                sum2 = a2 + b2;
            }
            
            int sumLen1 = 0, sumLen2 = 0;
            
            unsigned long long sum1Tmp = sum1;
            unsigned long long sum2Tmp = sum2;
            
            while (sum1Tmp > 0) {
                sum1Tmp /= 10;
                sumLen1++;
            }
            
            while (sum2Tmp > 0) {
                sum2Tmp /= 10;
                sumLen2++;
            }
            
            sum1Tmp = sum1;
            sum2Tmp = sum2;
            
            int i;
            if (sumLen1 > 15) {
                printf("결과 : 오버플로우가 발생했습니다.\n");
            } else {
                printf("결과 : ");
                if (sumLen2 == 0) {
                    printf("000,000,000,000,000,");
                    for (i = 0; i < 15 - sumLen1; i++) {
                        if ((i + 1) % 3 == 0)
                            printf("0,");
                        else
                            printf("0");
                    }
                    for (int j = i; j < i + sumLen1; j++) {
                        sum1Tmp = sum1;
                        unsigned long long k;
                        
                        for (int l = 0; l < sumLen1 - (j - i + 1); l++) {
                            sum1Tmp /= 10;
                        }
                        k = sum1Tmp % 10;
                        if ((j + 1) % 3 == 0 && j != i + sumLen1 - 1)
                            printf("%lld,", k);
                        else
                            printf("%lld", k);
                    }
                } else {
                    for (i = 0; i < 15 - sumLen1; i++) {
                        if ((i + 1) % 3 == 0)
                            printf("0,");
                        else
                            printf("0");
                    }
                    for (int j = i; j < i + sumLen1; j++) {
                        sum1Tmp = sum1;
                        unsigned long long k;
                        
                        for (int l = 0; l < sumLen1 - (j - i + 1); l++) {
                            sum1Tmp /= 10;
                        }
                        k = sum1Tmp % 10;
                        if ((j + 1) % 3 == 0 && j != i + sumLen2 - 1)
                            printf("%lld,", k);
                        else
                            printf("%lld", k);
                    }
                    
                    for (int j = 0; j < sumLen2; j++) {
                        sum2Tmp = sum2;
                        unsigned long long k;
                        
                        for (int l = 0; l < sumLen1 - (j - i + 1); l++) {
                            sum2Tmp /= 10;
                        }
                        k = sum2Tmp % 10;
                        if ((j + 1) % 3 == 0 && j != i + sumLen2 - 1)
                            printf("%lld,", k);
                        else
                            printf("%lld", k);
                    }
                }
                printf("\n");
            }
        }
        
        while (continueRun != 'n' && continueRun != 'y') {
            printf("계속 하시겠습니까? ");
            scanf(" %c", &continueRun);
        }
        
        if (continueRun == 'n')
            break;
        else if (continueRun == 'y') {
            continueRun = 0;
            printf("\n");
            getchar();
            continue;
        }
        
    }
    return 0;
}
