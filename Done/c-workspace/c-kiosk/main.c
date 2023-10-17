#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <termios.h>

typedef struct {
    char name[25];
    int price;
} Food;

Food rice_cart[2], soup_cart[3], side_cart[9], drink_cart[100];
int rice_index = 0, soup_index = 0, side_index = 0, drink_index = 0;

char rice[][25] = {"오므라이스", "백반", "볶음밥", "카레라이스", "비빔밥"};
char soup[][25] = {"미역국", "황태국", "된장국", "소고기무국", "시래기국"};
char side[][25] = {"돈가스", "멧돼지고기", "돼지고기두루치기", "수육", "소고기", "달걀프라이", "오징어", "콩나물", "김치"};
char drink[][25] = {"사케", "생맥주", "하이볼", "소주", "카이", "하이트", "소맥"};

int rice_price[5] = {5000, 6000, 4000, 5500, 4500};
int soupe_price[5] = {5000, 6000, 4000, 5500, 4500};
int side_price[9] = {5000, 6000, 4000, 5500, 4500, 5000, 6000, 4000, 5500};
int drink_price[7] = {5000, 6000, 4000, 5500, 4500, 5000, 6000};

int side_selected[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};

int total = 0, totalTime = 0;
int total_price = 0;



int printMenu() {
    int selection = 0;
    printf("1. 밥 종류, 2. 국 종류, 3. 반찬, 4. 술 종류: ");
    scanf("%d", &selection);
    
    printf("\n");
    switch (selection) {
        case 1:
            for (int i = 0; i < 5; i++)
                printf("%d %s - %d\n", i+1, rice[i], rice_price[i]);
            break;
        case 2:
            for (int i = 0; i < 5; i++)
                printf("%d %s - %d\n", i+1, soup[i], soupe_price[i]);
            break;
        case 3:
            for (int i = 0; i < 5; i++)
                printf("%d %s - %d\n", i+1, side[i], side_price[i]);
            break;
        case 4:
            for (int i = 0; i < 5; i++)
                printf("%d %s - %d\n", i+1, drink[i], drink_price[i]);
            break;
        default:
            printf("잘못된 입력입니다.\n");
            break;
    }
    return selection;
}

void printTotal() {
    printf("현재 장바구니 목록입니다.\n");
    
    printf("\n[밥 종류]\n");
    for (int i = 0; i < rice_index; i++)
        printf("%s ", rice_cart[i].name);
    
    
    printf("\n[국 종류]\n");
    for (int i = 0; i < soup_index; i++)
        printf("%s ", soup_cart[i].name);
    
    printf("\n[반찬]\n");
    for (int i = 0; i < side_index; i++)
        printf("%s ", side_cart[i].name);
    
    printf("\n[술 종류]\n");
    for (int i = 0; i < drink_index; i++)
        printf("%s ", drink_cart[i].name);
    
}

int getTotal() {
    int subtotal_price = 0;
    for (int i = 0; i < rice_index; i++)
        subtotal_price += rice_cart[i].price;
    
    for (int i = 0; i < soup_index; i++)
        subtotal_price += soup_cart[i].price;
    
    for (int i = 0; i < side_index; i++)
        subtotal_price += side_cart[i].price;
    
    for (int i = 0; i < drink_index; i++)
        subtotal_price += drink_cart[i].price;
    
    for (int i = 0; i < 9; i++)
        if (side_selected[i] == 0)
            return subtotal_price;
    
    return subtotal_price *= 0.8;
}

int getch(void) {
    int c;
    struct termios oldattr, newattr;

    tcgetattr(STDIN_FILENO, &oldattr);
    newattr = oldattr;
    newattr.c_lflag &= ~(ICANON | ECHO);
    newattr.c_cc[VMIN] = 1;
    newattr.c_cc[VTIME] = 0;
    tcsetattr(STDIN_FILENO, TCSANOW, &newattr);
    c = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);
    return c;
}

int main(int argc, char *argv[]) {
    for (int i = 0; i < 3; i++) {
        char id[10], pw_input[10], pw[] = "password";
        int pw_wrong_counter = 0;
        
        printf("이름:");
        scanf("%s", id);
        getchar();
        
        while (1) {
            if (pw_wrong_counter == 3)
                return 0;
            
            printf("암호:");
//            scanf("%s", pw_input);
            int buffer = 0;
            int i = 0;
            for (i = 0; buffer != 13; i++) {
                pw_input[i] = getch();
                if (pw_input[i] == '\0') {
                    i--;
                    continue;
                } else if (pw_input[i] == '\n')
                    break;
                printf("*");
                buffer = (int)pw_input[i];
            }
            pw_input[i] = '\0';
            
            if (strcmp(pw, pw_input) == 0)
                break;
            else pw_wrong_counter++;
        }
        
        int startTime = (unsigned)time(NULL);
        printf("천주굥 돼지고기 전문점에 오신것을 환영합니다!\n");
        
        while (1) {
            int order, confirm, bday, selection = printMenu();
            
            printf("주문하실 메뉴의 번호를 입력하세요: ");
            scanf("%d", &order);
            
            switch (selection) {
                case 1:
                    if (rice_index == 2) {
                        printf("배터져요\n");
                        break;
                    }
                    
                    strcpy(rice_cart[rice_index].name, rice[order-1]);
                    rice_cart[rice_index++].price = rice_price[order-1];
                    break;
                case 2:
                    if (soup_index == 3) {
                        printf("배터져요\n");
                        break;
                    }
                    
                    strcpy(soup_cart[soup_index].name, soup[order-1]);
                    soup_cart[soup_index++].price = soupe_price[order-1];
                    break;
                case 3:
                    if (side_selected[order-1] == 1) {
                        printf("이미 선택하신 반찬입니다.\n");
                        break;
                    }
                    
                    strcpy(side_cart[side_index].name, side[order-1]);
                    side_cart[side_index++].price = side_price[order-1];
                    side_selected[order-1] = 1;
                    break;
                case 4:
                    printf("생년월일 6자리를 입력하세요: ");
                    scanf("%d", &bday);
                    
                    if (bday > 030000 && bday < 240000) {
                        printf("미성년자는 구매할 수 없습니다.\n");
                        break;
                    }
                    
                    strcpy(drink_cart[drink_index].name, drink[order-1]);
                    drink_cart[drink_index++].price = drink_price[order-1];
                    break;
                default:
                    break;
            }
            
            int subtotal_price = getTotal();
            printf("\n예상 가격: %d\n", subtotal_price);
            
            printTotal();
            printf("주문 목록을 확인하세요. (1: 확인, 2: 취소) ");
            scanf("%d", &confirm);
            
            if (confirm == 1) {
                int answer;
                printf("추가로 주문하시겠습니까? (1: 확인, 2: 취소) ");
                scanf("%d", &answer);
                
                if (answer == 'n') {
                    total_price = subtotal_price;
                    break;
                }
            } else {
                rice_index = 0;
                soup_index = 0;
                side_index = 0;
                drink_index = 0;
                total_price = 0;
            }
        }
        
        int payment;
        printf("결제방식을 선택하세요. (1: 카드, 2: 현금) ");
        scanf("%d", &payment);
        
        if (payment == 2) {
            total_price *= 0.9;
            total += total_price;
        } else {
            char card[4];
            
            printf("카드번호 4자리를 입력하세요: ");
            scanf("%s", card);
            
            if (card[0] == '1' && card[1] == '0') {
                printf("입력하신 현대카드로 결제되었습니다.\n");
                total += total_price;
            } else if (card[0] == '2' && card[1] == '0') {
                printf("입력하신 삼성카드로 결제되었습니다.\n");
                total += total_price;
            } else if (card[0] == '3' && card[1] == '0') {
                printf("입력하신 신한카드로 결제되었습니다.\n");
                total += total_price;
            } else if (card[0] == '4' && card[1] == '0') {
                printf("입력하신 국민카드로 결제되었습니다.\n");
                total += total_price;
            } else
                printf("잘못된 카드번호입니다. 결제에 실패했습니다.\n");
        }
        
        int endTime = (unsigned)time(NULL);
        totalTime += endTime - startTime;
        printf("\n이용해주셔서 감사합니다.\n\n");
        
        rice_index = 0;
        soup_index = 0;
        side_index = 0;
        drink_index = 0;
        total_price = 0;
    }
    printf("최종 사용시간: %d초, 총 매출: %d원\n", totalTime, total);
    for (int i = 20; i > 0; i--) {
        printf("%d초 후 프로그램을 종료합니다.\n", i);
        sleep(100);
    }
}
