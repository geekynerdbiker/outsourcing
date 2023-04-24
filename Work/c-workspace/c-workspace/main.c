#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>

#define ROW 8
#define COL 8
#define CARNUM 4

#define DIR_UP 0
#define DIR_DOWN 1
#define DIR_LEFT 2
#define DIR_RIGHT 3

typedef struct Car_info {
    char car;
    int direction;
    int using_load;
    int current_point[2];
    int destination[2];
    int hold;
} Car_info;

void init_load(char** load);
void print_load(char** load);

Car_info* createCar(char** load, char car, int direction, int using_load);
void update_load(char** load, Car_info* car[]);

void No_prevention(char** load, Car_info* car[]);
void Prevention_Hold_and_Wait(char** load, Car_info* car[]);
void Prevention_No_Preemption(char** load, Car_info* car[]);
void Prevention_Circular_Wait(char** load, Car_info* car[], int* std_num);

int main()
{
    char** load = NULL;
    int prevention;
    char car_temp;
    int using_load;
    int std_num[13] = { 0, };

    std_num[9] = 0;
    std_num[10] = 1;
    std_num[11] = 2;
    std_num[12] = 3;

    Car_info* car[4];

    load = (char**)malloc(sizeof(char*) * ROW);
    for (int i = 0; i < ROW; i++) {
        load[i] = (char*)malloc(sizeof(char) * (COL + 1));
    }

    init_load(load);

    for (int i = 0; i < 4; i++) {

        printf("자동차(%d) ID,도로 입력(문자 숫자) : ", i);
        scanf(" %c %d", &car_temp, &using_load);
        car[i] = createCar(load, car_temp, i, using_load);
    }

    update_load(load, car);

    printf("\n교착상태 예방 방법 선택.\n");
    printf("1.No Prevention, 2.Hold and Wait, 3.No Preemption, 4.Circular Wait :");
    scanf("%d", &prevention);


    switch (prevention) {
    case 1:
        No_prevention(load, car);
        break;
    case 2:
        Prevention_Hold_and_Wait(load, car);
        break;
    case 3:
        Prevention_No_Preemption(load, car);
        break;
    case 4:

            printf("\n교차로 진입 순서(학번) 입력 : ");
        for (int i = 0; i < 9; i++)
            scanf("%1d", &std_num[i]);

        Prevention_Circular_Wait(load, car, std_num);
        break;
    }
    return 0;
}

void init_load(char** load) {
    for (int i = 0; i < ROW; i++)
        memset(load[i], 0, COL);
}

void print_load(char** load) {

    char value;
    printf("도로 정보\n\n");

    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++) {
            value = load[i][j];
            if (value == 0)
                printf("□ ");
            else
                printf("%2c ", load[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void update_load(char** load, Car_info* car[]) {

    for (int i = 0; i < CARNUM; i++) {
        int x = car[i]->current_point[0];
        int y = car[i]->current_point[1];
        load[x][y] = car[i]->car;
    }
}

Car_info* createCar(char** load, char car, int direction, int using_load) {
    Car_info* tempCar = (Car_info*)malloc(sizeof(Car_info));
    tempCar->car = car;
    tempCar->direction = direction;
    tempCar->using_load = using_load;
    tempCar->hold = 0;

    if (direction == DIR_UP) {
        tempCar->current_point[0] = ROW - 1;
        tempCar->current_point[1] = using_load;
        tempCar->destination[0] = 0;
        tempCar->destination[1] = using_load;
    }
    else if (direction == DIR_DOWN) {
        tempCar->current_point[0] = 0;
        tempCar->current_point[1] = using_load;
        tempCar->destination[0] = ROW - 1;
        tempCar->destination[1] = using_load;
    }
    else if (direction == DIR_LEFT) {
        tempCar->current_point[0] = using_load;
        tempCar->current_point[1] = COL - 1;
        tempCar->destination[0] = using_load;
        tempCar->destination[1] = 0;
    }
    else {
        tempCar->current_point[0] = using_load;
        tempCar->current_point[1] = 0;
        tempCar->destination[0] = using_load;
        tempCar->destination[1] = COL - 1;
    }

    

    return tempCar;
}

int can_move(char** load, int x, int y) {
    return x >= 0 && x < ROW&& y >= 0 && y < COL&& load[x][y] == 0;
}

void move_car(char** load, Car_info* car, int dx, int dy) {
    int x = car->current_point[0];
    int y = car->current_point[1];
    int nx = x + dx;
    int ny = y + dy;

    if (can_move(load, nx, ny)) {
        load[x][y] = 0;
        car->current_point[0] = nx;
        car->current_point[1] = ny;
        load[nx][ny] = car->car;
    }
}

void No_prevention(char** load, Car_info* car[]) {

    int moved = 1;
    int step = 0;

    

    while (moved) {
        printf("시간 : %d\n", step);
        print_load(load);
        moved = 0;

        for (int i = 0; i < CARNUM; i++) {
            
            int row_offset = 0;
            int col_offset = 0;
            
            if (car[i]->direction == DIR_DOWN) {
                row_offset = 1;
            }
            else if (car[i]->direction == DIR_UP) {
                row_offset = -1;
            }
            else if (car[i]->direction == DIR_RIGHT) {
                col_offset = 1;
            }
            else if (car[i]->direction == DIR_LEFT) {
                col_offset = -1;
            }
            
            int next_row = car[i]->current_point[0] + row_offset;
            int next_col = car[i]->current_point[1] + col_offset;
            
            
            if (next_row >= 0 && next_row < ROW && next_col >= 0 && next_col < COL && load[next_row][next_col] == 0) {
                load[car[i]->current_point[0]][car[i]->current_point[1]] = 0;
                car[i]->current_point[0] = next_row;
                car[i]->current_point[1] = next_col;
                load[next_row][next_col] = car[i]->car;
                moved = 1;
            }
        }
            step++;
    }

}

void Prevention_Hold_and_Wait(char** load, Car_info* car[]) {
    int moved = 1;
    int stage = 0;
    int step = 0;
    int print = 0;
    int next_row = 0;
    int next_col = 0;
    
    while (moved) {
        moved = 0;
        if (!print) {
            printf("시간 : %d\n", step);
            print_load(load);
        }
        print = 0;
        for (int i = (stage == 0 ? 0 : 2); i < (stage == 0 ? 2 : CARNUM); i++) {
            next_row = car[i]->current_point[0] + (car[i]->direction == DIR_DOWN ? 1 : (car[i]->direction == DIR_UP ? -1 : 0));
            next_col = car[i]->current_point[1] + (car[i]->direction == DIR_RIGHT ? 1 : (car[i]->direction == DIR_LEFT ? -1 : 0));

            if (next_row >= 0 && next_row < ROW && next_col >= 0 && next_col < COL && load[next_row][next_col] == 0) {
                load[car[i]->current_point[0]][car[i]->current_point[1]] = 0;
                car[i]->current_point[0] = next_row;
                car[i]->current_point[1] = next_col;
                load[next_row][next_col] = car[i]->car;
                if (next_row == car[i]->destination[0] && next_col == car[i]->destination[1])
                    continue;
                moved = 1;
            }
        }

        if ((!moved && stage == 0)) {
            stage = 1;
            moved = 1;
            print = 1;
            step--;
        }
        step++;
    }
    printf("시간 : %d\n", step);
    print_load(load);
}



void Prevention_No_Preemption(char** load, Car_info* car[]) {

    int moved = 1;
    int step = 0;

    while (moved) {
        moved = 0;
        printf("시간 : %d\n", step);
        print_load(load);

        for (int i = 0; i < CARNUM; i++) {
            int next_row = car[i]->current_point[0] + (car[i]->direction == DIR_DOWN ? 1 : (car[i]->direction == DIR_UP ? -1 : 0));
            int next_col = car[i]->current_point[1] + (car[i]->direction == DIR_RIGHT ? 1 : (car[i]->direction == DIR_LEFT ? -1 : 0));
            
            if (next_row >= 0 && next_row < ROW && next_col >= 0 && next_col < COL) {
                if (load[next_row][next_col] != 0) {
                    int prev_row = car[i]->current_point[0] - (car[i]->direction == DIR_DOWN ? 1 : (car[i]->direction == DIR_UP ? -1 : 0));
                    int prev_col = car[i]->current_point[1] - (car[i]->direction == DIR_RIGHT ? 1 : (car[i]->direction == DIR_LEFT ? -1 : 0));
                    
                    if (prev_row >= 0 && prev_row < ROW && prev_col >= 0 && prev_col < COL && load[prev_row][prev_col] == 0) {
                        load[car[i]->current_point[0]][car[i]->current_point[1]] = 0;
                        car[i]->current_point[0] = prev_row;
                        car[i]->current_point[1] = prev_col;
                        load[prev_row][prev_col] = car[i]->car;
                        moved = 1;
                    }
                } else {
                    load[car[i]->current_point[0]][car[i]->current_point[1]] = 0;
                    car[i]->current_point[0] = next_row;
                    car[i]->current_point[1] = next_col;
                    load[next_row][next_col] = car[i]->car;
                    moved = 1;
                }
            }
        }
        step++;
    }
}

void Prevention_Circular_Wait(char** load, Car_info* car[], int* std_num) {
    int moved = 1;
    int step = 0;

    while (1) {
        moved = 0;

        int allowed_car = std_num[step % 13] % 4;
//        printf("교차로 진입 가능 : %d\n", std_num[step % 13]);
        printf("시간 : %d\n", step);
        printf("교차로 진입 가능 : %d(%c)\n", allowed_car, car[allowed_car]->car);
        print_load(load);

        for (int i = 0; i < CARNUM; i++) {
            if (i == allowed_car) {
                int next_row = car[i]->current_point[0] + (car[i]->direction == DIR_DOWN ? 1 : (car[i]->direction == DIR_UP ? -1 : 0));
                int next_col = car[i]->current_point[1] + (car[i]->direction == DIR_RIGHT ? 1 : (car[i]->direction == DIR_LEFT ? -1 : 0));

                if (next_row >= 0 && next_row < ROW && next_col >= 0 && next_col < COL && load[next_row][next_col] == 0) {
                    load[car[i]->current_point[0]][car[i]->current_point[1]] = 0;
                    car[i]->current_point[0] = next_row;
                    car[i]->current_point[1] = next_col;
                    load[next_row][next_col] = car[i]->car;
                    moved = 1;
                }
            }
        }
        
        int finish = 0;
        for (int i = 0; i < CARNUM; i++) {
            if (car[i]->current_point[0] != car[i]->destination[0] || car[i]->current_point[1] != car[i]->destination[1]) {
                finish = 0;
                break;
            }
            else
                finish = 1;
        }
        
        if (finish) {
            printf("시간 : %d\n", step++);
            printf("교차로 진입 가능 : %d(%c)\n", allowed_car, car[allowed_car]->car);
            print_load(load);
            break;
        }
        step++;
    }
}

