#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable:4996)

void prob1() {
    int n[5];
    
    int min = 2147483647;
    int max = -2147483647;
    
    scanf("%d %d %d %d %d", &n[0], &n[1], &n[2], &n[3], &n[4]);
    
    for(int i=0;i<5;i++) {
        if (n[i] < min) min = n[i];
        else if (n[i] > max) max = n[i];
    }
    
    printf("Min: %d, Max: %d\n", min, max);
}

void prob2() {
    int n[5] = {1, 2, 3, 4, 5};
    
    for(int i=0; i <5;i++)
        printf("Index: %d, Value: %d\n", i, *(n+4-i));
}

void prob3() {
    int scores[3][3] = {{40, 60, 80}, {70, 80, 60}, {55, 65, 75}};
    
    for(int i=0;i<3;i++) {
        int sum = 0;
        for(int j=0;j<3;j++){
            sum+= scores[i][j];
        }
        printf("%d번 평균 %d점\n", i+1, sum/3);
    }
            
}


typedef struct {
    char* id;
    int att;
    int def;
} Item;

char* trim_id(Item *item) {
    char* str = (char*)malloc(strlen(item->id));
    
    int len = 0;
    for(int i=0, k=0;i<strlen(item->id);i++)
        if(item->id[i] != ' ') {
            len++;
            str[k++] = item->id[i];
        }
    char* str2 = (char*)malloc(len);
    
    for(int i=0;i<len;i++)
        str2[i]=str[i];
    
    return str2;
}

void prob4() {
    Item item = {"qwe77               ", 9, 5};
    
    char* id = trim_id(&item);
    item.id = (char*)malloc(strlen(id)+1);
    strcpy(item.id, id);
    
    int last = strlen(id);
    item.id[last]='\0';
    
    printf("아이디 %s의 공격력은 %d, 방어력은 %d입니다.\n", item.id, item.att, item.def);
}

int main(int argc, const char * argv[]) {
//    prob1();
//    prob2();
//    prob3();
    prob4();
}
