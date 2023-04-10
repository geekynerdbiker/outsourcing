#include <iostream>
#pragma warning(disable: 4996)

int solve(unsigned long long S, int L) {
    int sum = 0, len = 0, max = 0;
    
    int k = 1;
    if (S % 2 == 0) {
        while (sum < S/2) {
            sum += k;
            max = k;
            k++;
            len++;
        }
        
        while (--k != L) {
            sum += k;
            len++;
        }
        
        while (sum < S) {
            sum += max;
            len++;
        }
    } else {
        while (sum <= S/2) {
            sum += k;
            max = k;
            k++;
            len++;
        }
        
        while (--k != L) {
            sum += k;
            len++;
        }
        
        while (sum <= S) {
            sum += max;
            len++;
        }
    }
    
    return len;
}

int main(void) {
    unsigned long long S;
    int L;
    
    scanf("%lld %d", &S, &L);
    
    int result = solve(S, L);
    printf("%d\n", result);
}
