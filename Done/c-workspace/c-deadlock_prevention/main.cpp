#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <Windows.h>

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
    int time = 0;
    char car_temp;
    int direction_temp;
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
        getchar();
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

    /*


     구현 1. Car_info를 이용하여 load 업데이트


     */
    for (int i = 0; i < ROW; i++)
        for (int j = 0; j < COL; j++)
            load[i][j] = 0;

    for (int i = 0; i < 4; i++) {
        int x = car[i]->current_point[0];
        int y = car[i]->current_point[1];
        char c = car[i]->car;

        load[x][y] = c;
    }
}

Car_info* createCar(char** load, char car, int direction, int using_load) {
    Car_info* tempCar = (Car_info*)malloc(sizeof(Car_info));

    /*

     구현 2. 매개변수를 바탕으로 자동차 정보를 car_info 구조체 형태로 리턴

     */
    tempCar->car = car;
    tempCar->direction = direction;
    tempCar->using_load = using_load;

    if (direction == 0) {
        tempCar->current_point[0] = ROW - 1;
        tempCar->destination[0] = 0;
        tempCar->current_point[1] = using_load;
        tempCar->destination[1] = using_load;
        tempCar->hold = -1;
    } else if (direction == 1) {
        tempCar->current_point[0] = 0;
        tempCar->destination[0] = ROW - 1;
        tempCar->current_point[1] = using_load;
        tempCar->destination[1] = using_load;
        tempCar->hold = -1;
    } else if (direction == 2) {
        tempCar->current_point[0] = using_load;
        tempCar->destination[0] = using_load;
        tempCar->current_point[1] = COL - 1;
        tempCar->destination[1] = 0;
        tempCar->hold = -1;
    } else if (direction == 3) {
        tempCar->current_point[0] = using_load;
        tempCar->destination[0] = using_load;
        tempCar->current_point[1] = 0;
        tempCar->destination[1] = COL - 1;
        tempCar->hold = -1;
    }

    return tempCar;
}


void No_prevention(char** load, Car_info* car[]) {

    /*

     구현 3. 자동차의 기본 이동 조건(No Prevention)
     이동하려는 위치에 이동 가능할 경우 1칸 이동

     */
    int time = 0;
    int flag = 0;

    while (!flag) {
        printf("시간 : %d\n", time++);
        print_load(load);

        int x, y, des_x, des_y;
        for (int i = 0; i < 4; i++) {
            int direction = car[i]->direction;
            x = car[i]->current_point[0];
            y = car[i]->current_point[1];
            des_x = car[i]->destination[0];
            des_y = car[i]->destination[1];

            if (direction == 0) {
                if (x != des_x)
                    if( load[x-1][y] == 0)
                        car[i]->current_point[0] = x - 1;
            } else if (direction == 1) {
                if (x != des_x)
                    if( load[x+1][y] == 0)
                        car[i]->current_point[0] = x + 1;
            } else if (direction == 2) {
                if (y != des_y)
                    if( load[x][y-1] == 0)
                        car[i]->current_point[1] = y - 1;
            } else if (direction == 3) {
                if (y != des_y)
                    if( load[x][y+1] == 0)
                        car[i]->current_point[1] = y + 1;
            }

            update_load(load, car);
        }

        for (int i = 0; i < 4; i++) {
            if (x == des_x && y == des_y)
                flag = 1;
            else {
                flag = 0;
                break;
            }
        }
    }
}

void Prevention_Hold_and_Wait(char** load, Car_info* car[]) {

    /*

     구현 4. 점유대기(Hold and Wait) 조건 제거
     자동차 이동 시, 이동방향의 도로(직선 방향의 모든 칸)을 점유한 후 이동

     */
    int time = 0;
    int flag = 0;

    while (!flag) {
        printf("시간 : %d\n", time);
        print_load(load);

        int x, y, des_x, des_y, hold_direction;
        for (int i = 0; i < 4; i++) {
            int direction = car[i]->direction;
            x = car[i]->current_point[0];
            y = car[i]->current_point[1];
            des_x = car[i]->destination[0];
            des_y = car[i]->destination[1];

            if (direction == 0) {
                if (x != des_x) {
                    int movable = 0;
                    for (int j = 0; j < 4; j++) {
                        hold_direction = car[j]->direction;

                        if (hold_direction == 2 || hold_direction == 3)
                            if (car[j]->hold != -1) {
                                movable = 1;
                                break;
                            }
                    } if (movable == 0) {
                        car[i]->hold = 1;
                        car[i]->current_point[0] = x - 1;

                        if (x - 1 == des_x) {
                            car[i]->hold = -1;
                        }
                    }
                }
            } else if (direction == 1) {
                if (x != des_x) {
                    int movable = 0;
                    for (int j = 0; j < 4; j++) {
                        hold_direction = car[j]->direction;

                        if (hold_direction == 2 || hold_direction == 3)
                            if (car[j]->hold != -1) {
                                movable = 1;
                                break;
                            }
                    } if (movable == 0) {
                        car[i]->hold = 1;
                        car[i]->current_point[0] = x + 1;

                        if (x + 1 == des_x) {
                            car[i]->hold = -1;
                        }
                    }
                }
            } else if (direction == 2) {
                if (y != des_y) {
                    int movable = 0;
                    for (int j = 0; j < 4; j++) {
                        hold_direction = car[j]->direction;

                        if (hold_direction == 0 || hold_direction == 1)
                            if (car[j]->hold != -1) {
                                movable = 1;
                                break;
                            }
                    } if (movable == 0) {
                        car[i]->hold = 1;
                        car[i]->current_point[1] = y - 1;

                        if (y - 1 == des_y) {
                            car[i]->hold = -1;
                        }
                    }
                }
            } else if (direction == 3) {
                if (y != des_y) {
                    int movable = 0;
                    for (int j = 0; j < 4; j++) {
                        hold_direction = car[j]->direction;

                        if (hold_direction == 0 || hold_direction == 1)
                            if (car[j]->hold != -1) {
                                movable = 1;
                                break;
                            }
                    } if (movable == 0) {
                        car[i]->hold = 1;
                        car[i]->current_point[1] = y + 1;

                        if (y + 1 == des_y) {
                            car[i]->hold = -1;
                        }
                    }
                }
            }

            update_load(load, car);
        }
        time++;


        for (int i = 0; i < 4; i++) {
            if (x == des_x && y == des_y)
                flag = 1;
            else {
                flag = 0;
                break;
            }
        }
    }
}

void Prevention_No_Preemption(char** load, Car_info* car[]) {

    /*

     구현 5. 비전섬(No Preemption) 조건 제거
     이동하려는 위치에 다른 자동차가 있을 경우, 1칸 후진

     */
    int time = 0;
    int flag = 0;

    while (1) {
        printf("시간 : %d\n", time);
        print_load(load);

        if (flag == 1)
            return;

        int x, y, des_x, des_y;
        for (int i = 0; i < 4; i++) {
            int direction = car[i]->direction;
            x = car[i]->current_point[0];
            y = car[i]->current_point[1];
            des_x = car[i]->destination[0];
            des_y = car[i]->destination[1];

            if (direction == 0) {
                if (x != des_x) {
                    if (load[x-1][y] == 0)
                        car[i]->current_point[0] = x - 1;
                    else
                        car[i]->current_point[0] = x + 1;
                }
            } else if (direction == 1) {
                if (x != des_x) {
                    if (load[x+1][y] == 0)
                        car[i]->current_point[0] = x + 1;
                    else
                        car[i]->current_point[0] = x - 1;
                }
            } else if (direction == 2) {
                if (y != des_y) {
                    if (load[x][y-1] == 0)
                        car[i]->current_point[1] = y - 1;
                    else
                        car[i]->current_point[1] = y + 1;
                }
            } else if (direction == 3) {
                if (y != des_y) {
                    if (load[x][y+1] == 0)
                        car[i]->current_point[1] = y + 1;
                    else
                        car[i]->current_point[1] = y - 1;
                }
            }

            update_load(load, car);
        }
        time++;

        for (int i = 0; i < 4; i++) {
            x = car[i]->current_point[0];
            y = car[i]->current_point[1];
            des_x = car[i]->destination[0];
            des_y = car[i]->destination[1];

            if (x == des_x && y == des_y)
                flag = 1;
            else {
                flag = 0;
                break;
            }
        }
    }
}

void Prevention_Circular_Wait(char** load, Car_info* car[], int* std_num) {

    /*

     구현 6. 순환 대기(Circular Wait) 조건 제거
     교차로(4칸)을 교차로 접근 조건 추가

     */
    int x1 = -1, x2 = -1, y1 = -1, y2 = -1;

    y1 = car[0]->using_load;
    y2 = car[1]->using_load;
    x1 = car[2]->using_load;
    x2 = car[3]->using_load;

    int time = 0;
    int flag = 0;

    int number[13];

    for (int i = 0; i < 13; i++) {
        if (i < 9)
            number[i] = std_num[i];
        else
            number[i] = i - 9;
    }

    while (1) {
        int order = number[time % 13] % 4;

        printf("시간 : %d\n", time);
        printf("교차로 진입 가능 : %d(%c)\n", order, car[order]->car);

        print_load(load);

        if (flag == 1)
            return;

        int x, y, des_x, des_y, hold_direction;
        for (int i = 0; i < 4; i++) {
            int direction = car[i]->direction;
            x = car[i]->current_point[0];
            y = car[i]->current_point[1];
            des_x = car[i]->destination[0];
            des_y = car[i]->destination[1];

            if (direction == 0) {
                if (x != des_x) {
                    if (x - 1 != x1 && x - 1 != x2)
                        car[i]->current_point[0] = x - 1;
                    else if (order == i && car[i]->hold == -1)
                        car[i]->current_point[0] = x - 1;
                } else {
                    y1 = -1;
                } if (car[0]->hold == -1) {
                    x = car[i]->current_point[0];
                    if (x1 >= 0 && x2 >= 0 && (x == x1 || x == x2)) {
                        car[1]->hold = 0;
                        car[2]->hold = 0;
                        car[3]->hold = 0;
                    } else {
                        car[1]->hold = -1;
                        car[2]->hold = -1;
                        car[3]->hold = -1;
                    }
                }
            } else if (direction == 1) {
                if (x != des_x) {
                    if (x + 1 != x1 && x + 1 != x2)
                        car[i]->current_point[0] = x + 1;
                    else if (order == i && car[i]->hold == -1)
                        car[i]->current_point[0] = x + 1;
                } else {
                    y2 = -1;
                } if (car[1]->hold == -1) {
                    x = car[i]->current_point[0];
                    if (x1 >= 0 && x2 >= 0 && (x == x1 || x == x2)) {
                        car[0]->hold = 0;
                        car[2]->hold = 0;
                        car[3]->hold = 0;
                    } else {
                        car[0]->hold = -1;
                        car[2]->hold = -1;
                        car[3]->hold = -1;
                    }
                }
            } else if (direction == 2) {
                if (y != des_y) {
                    if (y - 1 != y1 && y - 1 != y2)
                        car[i]->current_point[1] = y - 1;
                    else if (order == i && car[i]->hold == -1)
                        car[i]->current_point[1] = y - 1;
                } else {
                    x1 = -1;
                } if (car[2]->hold == -1) {
                    y = car[i]->current_point[1];
                    if (y1 >= 0 && y2 >= 0 && (y == y1 || y == y2)) {
                        car[0]->hold = 2;
                        car[1]->hold = 2;
                        car[3]->hold = 2;
                    } else {
                        car[0]->hold = -1;
                        car[1]->hold = -1;
                        car[3]->hold = -1;
                    }
                }
            } else if (direction == 3) {
                if (y != des_y) {
                    if (y + 1 != y1 && y + 1 != y2)
                        car[i]->current_point[1] = y + 1;
                    else if (order == i && car[i]->hold == -1)
                        car[i]->current_point[1] = y + 1;
                } else {
                    x2 = -1;
                } if (car[3]->hold == -1) {
                    y = car[i]->current_point[1];
                    if (y == y1 || y == y2) {
                        car[0]->hold = 3;
                        car[1]->hold = 3;
                        car[2]->hold = 3;
                    } else {
                        car[0]->hold = -1;
                        car[1]->hold = -1;
                        car[2]->hold = -1;
                    }
                }
            }
            update_load(load, car);
        }
        time++;

        for (int i = 0; i < 4; i++) {
            x = car[i]->current_point[0];
            y = car[i]->current_point[1];
            des_x = car[i]->destination[0];
            des_y = car[i]->destination[1];

            if (x == des_x && y == des_y)
                flag = 1;
            else {
                flag = 0;
                break;
            }
        }
    }
}
