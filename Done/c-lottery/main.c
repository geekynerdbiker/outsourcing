#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    int lottery[5][6] = {{1, 2, 3, 4, 5, 6}, {10, 15, 25, 45, 40, 42}, {1, 9, 11, 22, 23, 25}, {9, 28, 31, 34, 35, 36}, {1, 9, 23, 28, 33, 35}};
    int answer[7];
    char check[5][6];
    
//    char* line = (char* )malloc(sizeof(char) * 20);
    
    printf("금주의 로또 번호를 입력하세요 -> ");
//    gets(line);
//
//    char* ptr = strtok(line, " ");
//
//    for (int i=0; ptr != NULL; i++) {
//        answer[i] = ptr - 48;
//        ptr = strtok(NULL, " ");
//    }
    
    for (int i=0; i < 6; i++)
        scanf("%d", &answer[i]);
    
    printf("보너스 번호를 입력하세요 -> ");
    scanf("%d", &answer[6]);
    
    printf("\n홍길동님의 로또 당첨 결과는 다음과 같습니다.\n");
    
    for (int i=0; i <5; i++) {
        int rank = 0;
        int bonus = 0;
        
        printf("%d세트 번호<", i+1);
        for (int j=0; j<5 ;j++)
            printf("%d ", lottery[i][j]);
        printf("%d> -> ", lottery[i][5]);
        
        for (int j=0; j <6;j++) {
            int isCorrect = 0;
            bonus = 0;
            
            for (int k=0; k<7; k++) {
                if (lottery[i][j] == answer[k]) {
                    if(k == 6) {
                        bonus = 1;
                        break;
                    }
                    isCorrect = 1;
                    rank = rank + 1;
                    break;
                }
            }
            if (isCorrect == 0 && bonus == 0) check[i][j] = 'X';
            else if (isCorrect == 1) check[i][j] = lottery[i][j];
            else if (bonus == 1) check[i][j] = -1 * lottery[i][j];
        }
        
        for (int j=0; j<6 ;j++)
            if (check[i][j] < 0 && rank == 5 && bonus == 1) printf("%d", -1 * check[i][j]);
            else if(check[i][j] == 88 || check[i][j] < 0) printf("X ");
            else printf("%d ", check[i][j]);
        
        if (rank < 3)
            printf("<꽝>\n");
        else if (rank == 3)
            printf("<5등>\n");
        else if (rank == 4)
            printf("<4등>\n");
        else if (rank == 5 && bonus == 1)
            printf("<2등>\n");
        else if (rank == 5)
            printf("<3등>\n");
        else if (rank == 6)
            printf("<1등>\n");


    }
    return 0;
}
