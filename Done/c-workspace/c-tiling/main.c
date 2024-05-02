//
//  main.c
//  c-tiling
//
//  Created by Jacob An on 2022/04/04.
//

#include<cstdio>
  
  
using namespace std;
  
int floor[128][128];
  
  
int pow2 (int n) {
    int ans = 1;
    for (int i = 0; i < n; i++) ans *= 2;
    return ans;
}
  
  
void tiling(int r, int c, int k, int rd, int cd, int nstart) {
    if (k == 1) {
        for (int i = 0; i < 2; i++)
            for (int j = 0; j < 2; j++)
                if (!(i == rd && j == cd))
                    floor[r+i][c+j] = nstart;
        return;
    }
     
    int sh = pow2(k-1);
    int didx = 2 * (rd / sh) + cd / sh;
    int ntroq = (sh * sh - 1) / 3;
     
    tiling(r + sh * (rd / sh), c + sh * (cd / sh), k-1, rd % sh, cd % sh, nstart);
    for (int i = 1; i < 4; i++) {
        int idx_nxt = (didx + i) % 4;
        int nrd = idx_nxt / 2 == 0? sh-1 : 0;
        int ncd = idx_nxt % 2 == 0? sh-1 : 0;
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
  
    tiling(0, 0, k, a-1, b-1, 1);
    floor[a-1][b-1] = -1;
  
    int s = pow2(k);
    for (int i = s-1; i >= 0; i--) {
        for (int j = 0; j < s; j++)
            printf("%d ", floor[j][i]);
        printf("\n");
    }
    return 0;
}
