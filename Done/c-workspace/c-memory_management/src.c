#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>

#define ROW 10
#define COL 4

void init_memory(char** memory);
void show_memory(char** memory);
void memory_allocation(char** memory, char* data, int position, int frame_table[][2]);
void remove_memory(char** memory, int frame_table[][2], int position);
void compaction_memory(char** memory, int frame_table[][2]);

int main() {

    int position = 0;

    int frame_table[ROW][2];
    char** memory = NULL;
    char data[12] = { "\0", };

    memory = (char**)malloc(sizeof(char*) * ROW);
    for (int i = 0; i < ROW; i++) {
        memory[i] = (char*)malloc(sizeof(char) * (COL + 1));
        frame_table[i][0] = 0;
        frame_table[i][1] = 0;
    }

    init_memory(memory);
    show_memory(memory);
    printf("\n");

    while (1) {

        /*

        1. main 함수 구현
        명령어 입력, 데이터 입력, 할당 위치 입력,
        명령에 따른 함수 실행

        */
        char command[20] = { "\0", };
        printf("명령 입력 : ");
        scanf("%s", command);

        if (!strcmp(command, "allocation")) {
            printf("데이터 입력 : ");
            scanf("%s", data);
            printf("메모리 할당 위치(ROW) 입력 : ");
            scanf("%d", &position);
            memory_allocation(memory, data, position, frame_table);
        }
        else if (!strcmp(command, "remove")) {
            printf("메모리 할당 위치(ROW) 입력 : ");
            scanf("%d", &position);
            remove_memory(memory, frame_table, position);
        }
        else if (!strcmp(command, "compaction")) {
            compaction_memory(memory, frame_table);
        }
        else continue;

        Sleep(1000);
        system("cls");
        show_memory(memory);
    }
    for (int i = 0; i < ROW; i++)
        free(memory[i]);
    free(memory);

    return 0;
}

void init_memory(char** memory) {
    for (int i = 0; i < ROW; i++) {
        memset(memory[i], '\0', sizeof(memory[i]));
        memset(memory[i], 0, COL);
    }
}

void show_memory(char** memory) {

    char value;
    printf("메모리 정보\n\n");

    for (int i = 0; i < ROW; i++) {
        printf("%2d ", i);

        for (int j = 0; j < COL; j++) {
            value = memory[i][j];
            if (value == 0)
                printf("□ ");
            else
                printf("%2c ", memory[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}


/*
2. 메모리 할당 함수 구현 (실습 1 참고)
메모리(2차원 배열)의 원하는 위치(position)에 입력된 데이터(data) 삽입
데이터 크기 >= 할당 가능 공간 : 메모리의 해당 위치에 데이터 입력
데이터 크기 <  할당 가능 공간 : 할당 실패

frame_table : 2차원 배열에 데이터 정보(저장 시작 위치, 데이터 크기) 저장
*/
void memory_allocation(char** memory, char* data, int position, int frame_table[][2]) {
    int data_size = strlen(data);
    int require = 1 + (data_size - 1) / COL;
    int available = 0;

    if (frame_table[position][0] == 0) {
        for (int i = 0; i < data_size; i++) {

            memory[position + i / COL][i % COL] = data[i];
            frame_table[position + i / COL][0] = 1;
            frame_table[position + i / COL][1] = i % COL + 1;
        }
    }
}

/*
3. 메모리 제거 함수 구현
메모리(2차원 배열)의 원하는 위치(position)에 입력된 데이터(data) 제거
frame_table 확인하여 해당 위치에 데이터 저장되어있을 경우 저장된 데이터 크기만큼 제거
*/
void remove_memory(char** memory, int frame_table[][2], int position) {
    int data_size = frame_table[position][1];
    int require = 1 + (data_size - 1) / COL;

    if (frame_table[position][0] == 0) {
        printf("올바르지 않은 인덱스");
    }
    else {
        for (int i = 0; i < data_size; i++) {
            memory[position + i / COL][i % COL] = 0;
            frame_table[position + i / COL][0] = 0;
            frame_table[position + i / COL][1] = 0;
        }
    }
}

/*
4. 메모리 압축 함수 구현
frame_table을 확인하여 차례대로 가능한 낮은 ROW의 메모리 위치로 데이터 이동
*/
void compaction_memory(char** memory, int frame_table[][2]) {
    int position = 0;
    char *temp;

    for (int i = 0; i < ROW; i++) {
        if (frame_table[i][0]) {
            if (frame_table[position][0]) {
                position++;
                continue;
            }
            temp = (char*)malloc(sizeof(char) * (COL + 1));
            memset(temp, '\0', sizeof(temp));
            strncpy(temp, memory[i], sizeof(temp));
            memory_allocation(memory, temp, position++, frame_table);
            remove_memory(memory, frame_table, i);
        }
    }
}

/*

allocation
123456
0
allocation
1223456
5
allocation
1234
8
allocation
ssss
9
remove
9
compaction
remove
1
compaction

 */
