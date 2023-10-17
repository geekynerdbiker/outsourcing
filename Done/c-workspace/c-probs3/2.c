//
//  main.c
//  dknsd
//
//  Created by Jacob An on 2021/12/13.
//

#include <stdio.h>

float getGradient(int x1, int x2, int y1, int y2);
float getIntercept(float a, int x, int y);

int main(int argc, const char * argv[]) {
    int x1, x2, y1, y2;
    float a, i;
    
    printf("첫번째 점의 x, y좌표를 입력하시오: ");
    scanf("%d %d", &x1, &y1);
    
    printf("두번째 점의 x, y좌표를 입력하시오: ");
    scanf("%d %d", &x2, &y2);
    
    a = getGradient(x1, x2, y1, y2);
    i = getIntercept(a, x1, y1);
    printf("계산된 직선 방정식의 기울기는 %.6lf, y절편은 %.6lf이다.\n", a, i);
    
    return 0;
}

float getGradient(int x1, int x2, int y1, int y2) {
    return (float)(y2 - y1) / (float)(x2 - x1);
}

float getIntercept(float a, int x, int y) {
    return (float)(y - (a * (float)x));
}
