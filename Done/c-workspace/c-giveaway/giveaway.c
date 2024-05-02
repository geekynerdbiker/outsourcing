#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 중복 체크 함수
int check_duplicate(int arr[], int size, int num)
{
    for (int i = 0; i < size; i++)
        if (num == arr[i])
            return 1;
    return 0;
}

int get_match(int answer[], int data[], int size) {
    int match = 0;
    
    for (int i = 0; i < 10; i++)
        for (int j = 0; j < size; j++) {
            if (answer[i] == data[j]) {
                match++;
                break;
            }
        }
    
    return match;
}


int main() {
    printf("******************************\n");
    printf("<중간프로젝트2>\n");
    printf("학번 : 2020XXXXX, 이름 : 홍길동\n\n");
    printf("백화점에서 물건을 구매하십시오.\n\n");
    printf("TV의 가격은 20만원이며 응모 기회는 10번 주어집니다.\n");
    printf("냉장고의 가격은 10만원이며 응모 기회는 5번 주어집니다.\n");
    printf("청소기의 가격은 5만원이며 응모 기회는 2번 주어집니다.\n");
    printf("오븐의 가격은 1만원이며 응모 기회는 1번 주어집니다.\n\n");
    
    int budget, chance = 0;
    printf("당신의 현재 보유 자금은?(x만원) : "); // 프로그램 안내 메시지
    scanf(" %d", &budget);
    
    while (budget > 500 || budget < 0) {
        printf("잘못된 금액입니다. 0~500만원 이하의 금액을 입력하세요.\n\n");
        printf("당신의 현재 보유 자금은?(x만원) : ");
        scanf(" %d", &budget);
    }
    
    int shopping = 1;
    while (shopping) {
        int product, amount;
        printf("\n무엇을 구매하시겠습니까?\n");
        printf("1.TV 2.냉장고 3.청소기 4.오븐 5.구입을 멈춘다\n"); // "물건 구입 메뉴"
        scanf(" %d", &product);
        
        switch (product) {
            // 1~4 메뉴 선택 시, 각 물건을 A라 하면 "내가 구매할 A의 개수는? : " 출력 이후 "잔돈은 n만원입니다" 출력
            // 잔돈을 초과하여 구매 시 "보유한 자금을 %d만원만큼 초과하였습니다." 출력
            // 이후 해당 물건의 구매 가능 개수가 0개이면 "현재 잔돈은 n만원이며, A는 더 이상 구매할 수 없습니다." 출력, 구매가능 개수가 x개이면 "현재 잔돈은 n만원이며, A는 x개 이하로 구매할 수 있습니다." 출력 이후 다시 "물건 구입 메뉴" 출력
            case 1:
                printf("\n내가 구매할 TV의 개수는? : ");
                scanf("%d", &amount);
                
                if (budget < amount * 20) {
                    printf("보유한 자금을 %d만원만큼 초과하였습니다.\n", amount * 20 - budget);
                    
                    if (budget < 20)
                        printf("현재 잔돈은 %d만원이며, TV는 더 이상 구매할 수 없습니다.\n", budget);
                    else
                        printf("현재 잔돈은 %d만원이며, TV는 %d개 이하로 구매할 수 있습니다.\n", budget, budget / 20);
                    
                } else {
                    budget -= amount * 20;
                    chance += amount * 10;
                    printf("잔돈은 %d만원입니다\n", budget);
                }
                
                break;
            case 2:
                printf("\n내가 구매할 냉장고의 개수는? : ");
                scanf("%d", &amount);
                
                if (budget < amount * 10) {
                    printf("보유한 자금을 %d만원만큼 초과하였습니다.\n", amount * 10 - budget);
                    
                    if (budget < 10)
                        printf("현재 잔돈은 %d만원이며, 냉장고는 더 이상 구매할 수 없습니다.\n", budget);
                    else
                        printf("현재 잔돈은 %d만원이며, 냉장고는 %d개 이하로 구매할 수 있습니다.\n", budget, budget / 10);
                    
                } else {
                    budget -= amount * 10;
                    chance += amount * 5;
                    printf("잔돈은 %d만원입니다\n", budget);
                }
                
                break;
            case 3:
                printf("\n내가 구매할 청소기의 개수는? : ");
                scanf("%d", &amount);
                
                if (budget < amount * 5) {
                    printf("보유한 자금을 %d만원만큼 초과하였습니다.\n", amount * 5 - budget);
                    
                    if (budget < 5)
                        printf("현재 잔돈은 %d만원이며, 청소기는 더 이상 구매할 수 없습니다.\n", budget);
                    else
                        printf("현재 잔돈은 %d만원이며, 청소기는 %d개 이하로 구매할 수 있습니다.\n", budget, budget / 5);
                    
                } else {
                    budget -= amount * 5;
                    chance += amount * 2;
                    printf("잔돈은 %d만원입니다\n", budget);
                }
                
                break;
            case 4:
                printf("\n내가 구매할 오븐의 개수는? : ");
                scanf("%d", &amount);
                
                if (budget < amount * 1) {
                    printf("보유한 자금을 %d만원만큼 초과하였습니다.\n", amount * 1 - budget);
                    
                    if (budget < 1)
                        printf("현재 잔돈은 %d만원이며, 오븐은 더 이상 구매할 수 없습니다.\n", budget);
                    else
                        printf("현재 잔돈은 %d만원이며, 오븐은 %d개 이하로 구매할 수 있습니다.\n", budget, budget / 1);
                    
                } else {
                    budget -= amount * 1;
                    chance += amount * 1;
                    printf("잔돈은 %d만원입니다\n", budget);
                }
                
                break;
            case 5:
                // 5.구입을 멈춘다 선택 시 "더 이상 물건을 사지 않습니다", "경품 응모를 시작합니다" 출력 이후 "경품 응모 단계"로 넘어감
                shopping = 0;
                break;
            default:
                // 1~5 외의 메뉴 선택 시 "잘못된 선택입니다. 다시 선택해주세요" 출력 후 다시 "물건 구입 메뉴" 출력
                printf("잘못된 선택입니다. 다시 선택해주세요.\n");
                break;
        }
    }
    
    // "경품 응모 단계"
    printf("\n더 이상 물건을 사지 않습니다\n");
    printf("경품 응모를 시작합니다\n\n\n");
    
    // "내 응모 기회는 : %d" 출력
    printf("내 응모 기호는 : %d\n", chance);
    
    int chances[100];
    printf("경품 응모 번호는 :"); // 중복되지 않는 랜덤 경품 응모 번호 출력
    for (int i = 0; i < chance; i++) {
        int num = rand() % 100 + 1;
        
        if (i >= 100)
            break;
        if (check_duplicate(chances, i, num)) {
            i--;
            continue;
        } else {
            chances[i] = num;
            printf(" %d", chances[i]);
        }
    }
    printf("\n");
    
    int answer[10];
    printf("경품 당첨 번호는 : "); // 중복되지 않는 랜덤 경품 당첨 번호 출력
    for (int i = 0; i < 10; i++) {
        int num = rand() % 100 + 1;
        
        if (check_duplicate(answer, i, num)) {
            i--;
            continue;
        } else {
            answer[i] = num;
            printf(" %d", answer[i]);
        }
    }
    printf("\n");
    
    // "일치하는 번호 개수: %d개" 출력
    int match = get_match(answer, chances, chance);
    printf("일치하는 번호 개수: %d\n", match);
    
    // "당신의 등수: %d등" 출력
    int rank;
    
    if (match >= 10)
        rank = 1;
    else if (match >= 8)
        rank = 2;
    else if (match >= 5)
        rank = 3;
    else if (match >= 2)
        rank = 4;
    else
        rank = 5;
    
    printf("당신의 등수: %d등\n", rank);
    
    return 0;
}
