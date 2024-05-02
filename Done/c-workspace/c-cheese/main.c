#include <stdio.h>

#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable: 4996)

int n;
int idx;
char room[51][51];
int answer[51][4];


int isValid(int x, int y) {
    return x >= 0 && y >= 0 && x < n && y < n;
}

int around(int x, int y) {
    int dir[][2] = {{1, 0}, {-1 , 0}, {0, 1}, {0, -1}};
    
    for (int d = 0; d < 4; d++) {
        int nX = x + dir[d][0];
        int nY = y + dir[d][1];
        
        if (!isValid(nX, nY))
            continue;
        if (room[nX][nY] == 'c')
            return 0;
    }
    
    return 1;
}

int nothing(int x, int y) {
    return room[x][y] == '.';
}

void put(int x, int y) {
    if (!nothing(x, y) || !around(x, y))
        return;
    int v = -1, h = -1;
    int vX, vY, hX, hY;
    
    for (int i = 1; i <= n; i++) {
        int vX = x + i;
        int vY = y + 0;
        int hX = x + 0;
        int hY = y + i;
        
        if (!isValid(vX, vY) || !around(vX, vY) || !nothing(vX, vY)) {
            if (v == -1)
                v = i;
        } if (!isValid(hX, hY) || !around(hX, hY) || !nothing(hX, hY)) {
            if (h == -1)
                h = i;
        }
        
    }

    if (v > h) {
        for (int i = x; i < x+v; i++)
            room[i][y] = 'c';
        answer[idx][0] = x;
        answer[idx][1] = y;
        answer[idx][2] = v;
        answer[idx++][3] = 1;
    } else {
        for (int i = y; i < y+h; i++)
            room[x][i] = 'c';
        answer[idx][0] = x;
        answer[idx][1] = y;
        answer[idx][2] = h;
        answer[idx++][3] = 0;
    }
}


int main(void) {
    idx = 0;
    scanf("%d", &n);
    
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf(" %c", &room[i][j]);
    
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            put(i, j);
    
//    for (int i = 0; i < n; i++) {
//        for (int j = 0; j < n; j++)
//            printf("%c ", room[i][j]);
//        printf("\n");
//    }
    printf("%d\n", idx);
    for (int i = 0; i < idx; i++) {
        printf("%d %d %d %d\n", answer[i][0], answer[i][1], answer[i][2], answer[i][3]);
    }
    
    return 0;
}

/*
5
.X...
.XXX.
.....
.X...
.....
 */
