#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#define BELT_LEN 21

char status[BELT_LEN] = { ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'M', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' };

int event = -1;
int gold = 1000;
int atk = 0;

void gold_box() {
    int found = rand() % 501;
    printf("보물상자에서 %d골드를 발견했다!\n", found);
    
    Sleep(3000);
    gold += found;
}

void item_box() {
    int found = rand() % 5 + 6;
    printf("아이템을 발견했다!\n");
    printf("루피의 추가 공격력이 %d이(가) 되었다.\n", found);
    
    Sleep(3000);
    atk = found;
}

void battle() {
    int result = rand() % 2;
    
    if (result == 0) {
        printf("승자는 크로커다일!\n");
        printf("크로커다일에게 가진 돈을 모두 빼았겼다!\n");
        gold = 0;
    } else {
        int found = rand() % 501 + 500;
        printf("승자는 루피!\n");
        printf("크로커다일에게 %d원을 갈취했다!\n", found);
        gold += found;
    }
    
}

void meet() {
    int found = rand() % 301;
    int boss = rand() % 4;
    
    if (boss == 0) {
        printf("사황 카이도우를 만났다!");
        printf("사황 카이도우에게 %d골드를 갈취당했다...\n", found);
        Sleep(3000);
        gold -= found;
    } else if (boss == 1) {
        printf("사황 빅맘을 만났다!");
        printf("사황 빅맘에게 %d골드를 갈취당했다...\n", found);
        Sleep(3000);
        gold -= found;
    } else if (boss == 2) {
        printf("사황 흰수염을 만났다!");
        printf("사황 흰수염에게 인사를 했다!\n");
        printf("아무런 일도 일어나지 않았다...\n");
        Sleep(3000);
    } else if (boss == 3) {
        printf("사황 샹크스를 만났다!");
        printf("사황 샹크스에게 %d골드를 지원받았다!\n", found);
        Sleep(3000);
        gold += found;
    }
}

void sail(void) {
    while(1) {
        int event_number = -1;
        
        printf("소지금: %d골드\n", gold);
        printf("추가 공격력: %d\n", atk);
        
        for (int i = 0; i < BELT_LEN; i++)
            printf("*");
        printf("\n");
        
        if (event < 0)
            event = BELT_LEN - 1;
        for (int i = 0; i < BELT_LEN; i++) {
            if (event >= 0 && event < BELT_LEN && event == i) {
                if (event == 10) {
                    printf("!");
                    event_number = rand() % 4;
                }
                else
                    printf("?");
            } else
                printf("%c", status[i]);
        }
        event--;
        printf("\n");
        
        for (int i = 0; i < BELT_LEN; i++)
            printf("*");
        printf("\n");
        
        switch (event_number) {
            case 0:
                gold_box();
                break;
            case 1:
                item_box();
                break;
            case 2:
                meet();
                break;
            case 3:
                battle();
                break;
        }
        
        if (gold == 0) {
            printf("가진 돈을 모두 잃은 루피는 해적을 은퇴하게 된다...\n");
            return;
        } else if (gold >= 2000) {
            printf("루피는 %d골드를 모아 해적왕이 되었다고 한다...\n", gold);
            return;
        }
        
        Sleep(200);
        system("cls");
    }
}

int main(void) {
    sail();
}
