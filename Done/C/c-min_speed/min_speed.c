#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

// B가 승리할 수 있는 최소 속도를 구하는 함수
int find_min (int Apos, int Bpos, int v) {
    if ((10 - Apos) / (double)2 <= (10 - Bpos) / (double)v)
        return find_min(Apos, Bpos, v + 1);
    else
        return v;
}

void run() {
    // A,B의 위치와 B의 최대 속도 입력받기
    // 최소 속도를 구한 후 "B가 이길 수 있는 최소 속도는 %d 입니다." 출력
    // B가 승리할 수 있는 최소 속도가 최대 속도보다 클 경우, "B의 최대속도는 %d이므로 B는 승리할 수 없습니다." 출력
    
    printf("------------------------------------\n");
    int Apos, Bpos, v;
    printf("A의 위치를 입력하세요   :");
    scanf("%d", &Apos);
    printf("B의 위치를 입력하세요   :");
    scanf("%d", &Bpos);
    printf("B의 최대 속도를 입력하세요   :");
    scanf("%d", &v);
    
    int speed = find_min(Apos, Bpos, 1);
    
    printf("B가 이길 수 있는 최소 속도는 %d 입니다.\n", speed);
    if (speed > v) {
        printf("\nB의 최대속도는 %d이므로 B는 승리할 수 없습니다.\n", v);
        run();
    }
}


int main(void) {
    printf("학번: 202300000   , 이름: 000 \n");
    run();
    
}
