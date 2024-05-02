//
//  main.cpp
//  cpp-tiling
//
//  Created by Jacob An on 2022/04/04.
//

#include <cstdio>
  
  
using namespace std;
  
int floor[128][128];
  
  
int pow2 (int n) {
    int ans = 1;
    for (int i = 0; i < n; i++) ans *= 2;
    return ans;
}
  
// 타일을 채우는 함수
void tiling(int r, int c, int k, int rd, int cd, int nstart) {
    if (k == 1) {
        for (int i = 0; i < 2; i++)
            for (int j = 0; j < 2; j++)
                //
                if (!(i == rd && j == cd))
                    floor[r+i][c+j] = nstart;
        return;
    }
     
    int sh = pow2(k-1);
    int didx = 2 * (rd / sh) + cd / sh;
    int ntroq = (sh * sh - 1) / 3;
     
    // 2n×2n 크기의 체스판에서 어느 한 칸이 빠져도 항상 L-트로미노로 덮을 수 있다. 재귀 호출
    tiling(r + sh * (rd / sh), c + sh * (cd / sh), k-1, rd % sh, cd % sh, nstart);
    
    
    // 구멍이 있는 사분면(flag)을 제외한 나머지 가운데 모서리들 색칠 = 트로미노 한 조각
    for (int i = 1; i < 4; i++) {
        int idx_nxt = (didx + i) % 4;
        int nrd = idx_nxt / 2 == 0? sh-1 : 0;
        int ncd = idx_nxt % 2 == 0? sh-1 : 0;
        
        // 재귀 호출
        tiling(r + sh * (idx_nxt / 2), c + sh * (idx_nxt % 2), k-1, nrd, ncd, nstart + i*ntroq);
    }
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 2; j++)
            if (2*i + j != didx)
                floor[r+sh-1+i][c+sh-1+j] = nstart + 4 * ntroq;
}
  
  
int main(void) {
    int k, a, b;
    scanf("%d %d %d", &k, &a, &b);
  
    tiling(0, 0, k, b-1, k+a, 1);
  
    int s = pow2(k);
    for (int i = s-1; i >= 0; i--) {
        for (int j = 0; j < s; j++)
            printf("%d ", floor[j][i]);
        printf("\n");
    }
    return 0;
}
