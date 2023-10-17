#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#pragma warning(disable:4996)

int main() {
    int N;
    
    do {
        printf("Input N: ");
        scanf(" %d", &N);
    } while (N < 3 || N > 9);
    
    char ladder[15][18];
    char number = '1';
    char result = 'A';
    
    for (int i = 0; i < 15; i++)
        for (int j = 0; j < 2*N-1; j++) {
            if (i == 0) {
                if (j % 2 == 0)
                    ladder[i][j] = number++;
                else
                    ladder[i][j] = ' ';
            } else if (i == 14) {
                if (j % 2 == 0)
                    ladder[i][j] = result++;
                else
                    ladder[i][j] = ' ';
            } else {
                if (j % 2 == 0)
                    ladder[i][j] = '|';
                else
                    ladder[i][j] = ' ';
            }
        }
    
    srand((unsigned int)time(NULL));
    for (int i = 0; i < N-1;i++) {
        for (int j = 0; j < 2;) {
            int row = rand() % 13 + 1;
            int col = i * 2 + 1;
            
            if (ladder[row][col] == ' ') {
                if (col == 1 && ladder[row][col+2] == ' ') {
                    ladder[row][col] = '-';
                    j++;
                } else if (col == N * 2 - 3 && ladder[row][col-2] == ' ') {
                    ladder[row][col] = '-';
                    j++;
                } else if (ladder[row][col-2] == ' ' && ladder[row][col+2] == ' ') {
                    ladder[row][col] = '-';
                    j++;
                }
            }
        }
    }
    
    for (int i = 0; i < N-1;) {
        int row = rand() % 13 + 1;
        int col = rand() % N * 2 - 1;
        
        if (ladder[row][col] == ' ') {
            if (col == 1 && ladder[row][col+2] == ' ') {
                ladder[row][col] = '-';
                i++;
            } else if (col == N * 2 - 3 && ladder[row][col-2] == ' ') {
                ladder[row][col] = '-';
                i++;
            } else if (ladder[row][col-2] == ' ' && ladder[row][col+2] == ' ') {
                ladder[row][col] = '-';
                i++;
            }
        }
    }
    
    char answer[9];
    for (int i = 1; i <= N; i++) {
        int row = 1, col = 2 * (i - 1);
        while (1) {
            if (row == 14) {
                answer[i-1] = ladder[row][col];
                break;
            }
            if (col+1 < 2 * N-1 && ladder[row][col+1] == '-')
                col += 2;
            else if (col-1 > 0 && ladder[row][col-1] == '-')
                col -= 2;
            row++;
        }
    }
    
    printf("\n");
    for (int i = 0; i < 15; i++) {
        for (int j = 0; j < 2*N-1; j++)
            printf("%c", ladder[i][j]);
        printf("\n");
    }
    
    printf("\n");
    for (int i = 0; i < N; i++)
        printf("%d->%c\n", i+1, answer[i]);
}
