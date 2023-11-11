#include <stdio.h>
#include <string.h>


short ID[5];
char names[5][20];
int points[5];
int totals[5];

char codes[5];
char pnames[5][20];
int prices[5];
int amounts[5];

void initProduct(void) {
    codes[0] = 'A';
    codes[1] = 'B';
    codes[2] = 'C';
    codes[3] = 'D';
    codes[4] = 'E';
    
    strcpy(names[0],"Apple");
    strcpy(names[1],"Bread");
    strcpy(names[2],"Coffee");
    strcpy(names[3],"Desk");
    strcpy(names[4],"Euiod");
    
    prices[0] = 12000;
    prices[1] = 8000;
    prices[2] = 15000;
    prices[3] = 100000;
    prices[4] = 56000;
    
    amounts[0] = 50;
    amounts[1] = 30;
    amounts[2] = 80;
    amounts[3] = 20;
    amounts[4] = 70;
}

void initUser(void) {
    ID[0] = 101;
    ID[1] = 102;
    ID[2] = 103;
    ID[3] = 105;
    ID[4] = 201;
    
    strcpy(names[0],"Kim");
    strcpy(names[1],"Lee");
    strcpy(names[2],"Park");
    strcpy(names[3],"Chang");
    strcpy(names[4],"Song");
    
    points[0] = 100;
    points[1] = 90;
    points[2] = 120;
    points[3] = 50;
    points[4] = 0;
    
    totals[0] = 0;
    totals[1] = 0;
    totals[2] = 0;
    totals[3] = 0;
    totals[4] = 0;
}

void swapProduct(int p1, int p2) {
    char tmpCode = codes[p1];
    char tmpPname[20];
    strcpy(tmpPname, pnames[p2]);
    int tmpPrice = prices[p1];
    int tmpAmount = amounts[p1];
    
    codes[p1] = codes[p2];
    strcpy(pnames[p1], pnames[p2]);
    prices[p1] = prices[p2];
    amounts[p1] = amounts[p2];
    
    codes[p2] = tmpCode;
    strcpy(pnames[p2], tmpPname);
    prices[p2] = tmpPrice;
    amounts[p2] = tmpAmount;
}

void swapUser(int u1, int u2) {
    short tmpID = ID[u1];
    char tmpName[20];
    strcpy(tmpName, names[u1]);
    int tmpPoint = points[u1];
    int tmpTotal = totals[u1];
    
    ID[u1] = ID[u2];
    strcpy(names[u1], names[u2]);
    points[u1] = points[u2];
    totals[u1] = totals[u2];
    
    ID[u2] = tmpID;
    strcpy(names[u2], tmpName);
    points[u2] = tmpPoint;
    totals[u2] = tmpTotal;
}

int getMostTotal(void) {
    int result = 0;
    for (int i = 0; i < 5; i++) {
        if (totals[i] > result) {
            result = totals[i];
        }
    }
    return result;
}

int getMostPoint(void) {
    int result = 0;
    for (int i = 0; i < 5; i++) {
        if (points[i] > result) {
            result = points[i];
        }
    }
    return result;
}

int getID(short id) {
    for (int i = 0; i < 5; i++) {
        if (id == ID[i]) {
            return i;
        }
    }
    return -1;
}

int getCode(char code) {
    for (int i = 0; i < 5; i++) {
        if (code == codes[i]) {
            return i;
        }
    }
    return -1;
}

int checkAmount(char code, int amount) {
    for (int i = 0; i < 5; i++) {
        if (code == codes[i]) {
            if (amount <= amounts[i]) {
                return 1;
            } else {
                return 0;
            }
        }
    }
    return 0;
}

int buy(void) {
    short id;
    printf("구매자 ID를 입력하세요. > ");
    scanf("%hd", &id);
    
    int user = getID(id);
    if (user < 0) {
        printf("존재하지 않는 사용자입니다.\n\n");
        return 0;
    }
    
    char code;
    int amount;
    printf("구매상품코드와 수량을 입력하세요. > ");
    scanf("%c %d", &code, &amount);
    
    int product = getCode(code);
    if (product < 0) {
        printf("존재하지 않는 상품입니다.\n\n");
        return 0;
    }
    
    if (!checkAmount(code, amount)) {
        printf("상품의 재고 수량이 부족합니다. \n\n");
        return 0;
    }
    
    amounts[product] -= amount;
    totals[user] += prices[product] * amounts[product];
    points[user] += prices[product] * amounts[product] / 100;
    
    return 1;
}

void summary(void) {
    int total = 0;
    int average;
    for (int i = 0; i < 5; i++) {
        total += totals[i];
    }
    average = total / 5;
    
    printf("총 매출액은 %d원입니다.\n", total);
    printf("평균 매출액은 %d원입니다.\n\n", average);
}

void printAll(void) {
    printf("이름\t당일구매액\t보유포인트\n");
    for (int i = 0; i < 5; i++) {
        printf("%s\t%d\t%d\n", names[i], totals[i], points[i]);
    }
    printf("\n");
}

int main(void) {
    initProduct();
    initUser();
    
    int command;
    while (1) {
        printf("1: 상품구매\n");
        printf("2: 매출출력\n");
        printf("3: 전체출력\n");
        printf("0: 구매종료\n\n");
        printf("메뉴를 선택하세요. > ");
        scanf("%d", &command);
        
        if (command == 1) {
            int result = buy();
            if (result) {
                printf("상품을 성공적으로 구매했습니다.\n\n");
            } else {
                printf("상품 구매를 실패했습니다.\n\n");
            }
        } else if (command == 2) {
            summary();
        } else if (command == 3) {
            printAll();
        } else if (command == 0) {
            break;
        } else {
            printf("잘못된 입력입니다.\n\n");
        }
    }
    
    printf("프로그램을 종료합니다.\n");
}
