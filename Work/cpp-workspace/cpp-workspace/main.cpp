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
            
    for (int i = 0; i < 4; i++)
        load[car[i]->current_point[0]][car[i]->current_point[1]] = car[i]->car;
}

Car_info* createCar(char** load, char car, int direction, int using_load) {
    Car_info* tempCar = (Car_info*)malloc(sizeof(Car_info));

    /*

    구현 2. 매개변수를 바탕으로 자동차 정보를 car_info 구조체 형태로 리턴

    */
    tempCar->car = car;
    tempCar->direction = direction;
    tempCar->using_load = using_load;
    
    switch (direction) {
        case 0:
            tempCar->current_point[0] = ROW - 1;
            tempCar->current_point[1] = using_load;
            tempCar->destination[0] = 0;
            tempCar->destination[1] = using_load;
            break;
            
        case 1:
            tempCar->current_point[0] = 0;
            tempCar->current_point[1] = using_load;
            tempCar->destination[0] = ROW - 1;
            tempCar->destination[1] = using_load;
            break;
            
        case 2:
            tempCar->current_point[0] = using_load;
            tempCar->current_point[1] = COL - 1;
            tempCar->destination[0] = using_load;
            tempCar->destination[1] = 0;
            break;
            
        case 3:
            tempCar->current_point[0] = using_load;
            tempCar->current_point[1] = 0;
            tempCar->destination[0] = using_load;
            tempCar->destination[1] = COL - 1;
            break;
            
        default:
            break;
    }
    tempCar->hold = false;
    return tempCar;
}


void No_prevention(char** load, Car_info* car[]) {

    /*

    구현 3. 자동차의 기본 이동 조건(No Prevention)
    이동하려는 위치에 이동 가능할 경우 1칸 이동

    */
    int t = 0;
    int isDone = false;
    
    while (true) {
        printf("시간 : %d\n", t++);
        print_load(load);
        
        if (isDone)
            return;
        
        for (int i = 0; i < 4; i++) {
            switch (car[i]->direction) {
                case 0:
                    if (car[i]->current_point[0] != car[i]->destination[0])
                        car[i]->current_point[0]--;
                    break;
                    
                case 1:
                    if (car[i]->current_point[0] != car[i]->destination[0])
                        car[i]->current_point[0]++;
                    break;
                    
                case 2:
                    if (car[i]->current_point[1] != car[i]->destination[1])
                        car[i]->current_point[1]--;
                    break;
                    
                case 3:
                    if (car[i]->current_point[1] != car[i]->destination[1])
                        car[i]->current_point[1]++;
                    break;
                    
                default:
                    break;
            }
            update_load(load, car);
        }
        
        for (int i = 0; i < 4; i++) {
            if (car[i]->current_point[0] == car[i]->destination[0] && car[i]->current_point[1] == car[i]->destination[1])
                isDone = true;
            else {
                isDone = false;
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
    int t = 0;
    int isDone = false;
    
    while (true) {
        printf("시간 : %d\n", t++);
        print_load(load);
        
        if (isDone)
            return;
        
        for (int i = 0; i < 4; i++) {
            switch (car[i]->direction) {
                case 0:
                    if (car[i]->current_point[0] != car[i]->destination[0]) {
                        int isHeld = false;
                        for (int j = 0; j < 4; j++)
                            if (car[j]->direction == 2 || car[j]->direction == 3)
                                if (car[j]->hold) {
                                    isHeld = true;
                                    break;
                                }
                        if (!isHeld) {
                            car[i]->hold = true;
                            car[i]->current_point[0]--;
                            
                            if (car[i]->current_point[0] == car[i]->destination[0]) {
                                car[i]->hold = false;
                            }
                        }
                    }
                    break;
                    
                case 1:
                    if (car[i]->current_point[0] != car[i]->destination[0]) {
                        int isHeld = false;
                        for (int j = 0; j < 4; j++)
                            if (car[j]->direction == 2 || car[j]->direction == 3)
                                if (car[j]->hold) {
                                    isHeld = true;
                                    break;
                                }
                        if (!isHeld) {
                            car[i]->hold = true;
                            car[i]->current_point[0]++;
                            
                            if (car[i]->current_point[0] == car[i]->destination[0]) {
                                car[i]->hold = false;
                            }
                        }
                    }
                    break;
                    
                case 2:
                    if (car[i]->current_point[1] != car[i]->destination[1]) {
                        int isHeld = false;
                        for (int j = 0; j < 4; j++)
                            if (car[j]->direction == 0 || car[j]->direction == 1)
                                if (car[j]->hold) {
                                    isHeld = true;
                                    break;
                                }
                        if (!isHeld) {
                            car[i]->hold = true;
                            car[i]->current_point[1]--;
                            
                            if (car[i]->current_point[0] == car[i]->destination[0]) {
                                car[i]->hold = false;
                            }
                        }
                    }
                    break;
                    
                case 3:
                    if (car[i]->current_point[1] != car[i]->destination[1]) {
                        int isHeld = false;
                        for (int j = 0; j < 4; j++)
                            if (car[j]->direction == 0 || car[j]->direction == 1)
                                if (car[j]->hold) {
                                    isHeld = true;
                                    break;
                                }
                        if (!isHeld) {
                            car[i]->hold = true;
                            car[i]->current_point[1]++;
                            
                            if (car[i]->current_point[0] == car[i]->destination[0]) {
                                car[i]->hold = false;
                            }
                        }
                    }
                    break;
                    
                default:
                    break;
            }
            update_load(load, car);
        }
        
        for (int i = 0; i < 4; i++) {
            if (car[i]->current_point[0] == car[i]->destination[0] && car[i]->current_point[1] == car[i]->destination[1])
                isDone = true;
            else {
                isDone = false;
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
    int t = 0;
    int isDone = false;
    
    while (true) {
        printf("시간 : %d\n", t++);
        print_load(load);
        
        if (isDone)
            return;
        
        for (int i = 0; i < 4; i++) {
            switch (car[i]->direction) {
                case 0:
                    if (car[i]->current_point[0] != car[i]->destination[0]) {
                        if (load[car[i]->current_point[0]-1][car[i]->current_point[1]] == 0)
                            car[i]->current_point[0]--;
                        else
                            car[i]->current_point[0]++;
                    }
                    break;
                    
                case 1:
                    if (car[i]->current_point[0] != car[i]->destination[0]) {
                        if (load[car[i]->current_point[0]+1][car[i]->current_point[1]] == 0)
                            car[i]->current_point[0]++;
                        else
                            car[i]->current_point[0]--;
                    }
                    break;
                    
                case 2:
                    if (car[i]->current_point[1] != car[i]->destination[1]) {
                        if (load[car[i]->current_point[0]][car[i]->current_point[1]-1] == 0)
                            car[i]->current_point[1]--;
                        else
                            car[i]->current_point[1]++;
                    }
                    break;
                    
                case 3:
                    if (car[i]->current_point[1] != car[i]->destination[1]) {
                        if (load[car[i]->current_point[0]][car[i]->current_point[1]+1] == 0)
                            car[i]->current_point[1]++;
                        else
                            car[i]->current_point[1]--;
                    }
                    break;
                    
                default:
                    break;
            }
            update_load(load, car);
        }
        
        for (int i = 0; i < 4; i++) {
            if (car[i]->current_point[0] == car[i]->destination[0] && car[i]->current_point[1] == car[i]->destination[1])
                isDone = true;
            else {
                isDone = false;
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
    for (int i = 0; i < 4; i++) {
        if (car[i]->direction == 0 || car[i]->direction == 1) {
            if (x1 < 0)
                x1 = car[i]->using_load;
            else
                x2 = car[i]->using_load;
        } else {
            if (y1 < 0)
                y1 = car[i]->using_load;
            else
                y2 = car[i]->using_load;
        }
    }
    
    if (x2 < x1) {
        int temp = x2;
        x2 = x1;
        x1 = temp;
    }
    
    if (y2 < y1) {
        int temp = y2;
        y2 = y1;
        y1 = temp;
    }
    
    int t = 0;
    int isDone = false;
    int isUsing = -1;
    int *order_list = (int *)malloc(sizeof(int) * 4 + sizeof(std_num));
    int len = sizeof(std_num);
    for (int i = 0; i < len + 4; i++) {
        if (i < len)
            order_list[i] = std_num[i];
        else
            order_list[i] = i - len;
    } len += 4;
    
    while (true) {
        int order = order_list[t % len] % 4;
        
        printf("시간 : %d\n", t);
        printf("교차로 진입 가능 : %d(%c)\n", order, car[order]->car);
        t++;
        print_load(load);
        
        if (isDone)
            return;
        
        for (int i = 0; i < 4; i++) {
            switch (car[i]->direction) {
                case 0:
                    if (car[i]->current_point[0] != car[i]->destination[0]) {
                        if (car[i]->current_point[0]-1 > y2 || car[i]->current_point[0] <= y2)
                            car[i]->current_point[0]--;
                        else if (isUsing == i || (order == i && isUsing == -1)) {
                            car[i]->current_point[0]--;
                            isUsing = i;
                        } if (car[i]->current_point[0]-1 < y1)
                            isUsing = -1;
                    }
                    break;
                    
                case 1:
                    if (car[i]->current_point[0] != car[i]->destination[0]) {
                        if (car[i]->current_point[0]+1 < y1 || car[i]->current_point[0] >= y1)
                            car[i]->current_point[0]++;
                        else if (isUsing == i || (order == i && isUsing == -1)) {
                            car[i]->current_point[0]++;
                            isUsing = i;
                        } if (car[i]->current_point[0]+1 > y2)
                            isUsing = -1;
                    }
                    break;
                    
                case 2:
                    if (car[i]->current_point[1] != car[i]->destination[1]) {
                        if (car[i]->current_point[1]-1 > x2 || car[i]->current_point[1] <= x2)
                            car[i]->current_point[1]--;
                        else if (isUsing == i || (order == i && isUsing == -1)) {
                            car[i]->current_point[1]--;
                            isUsing = i;
                        } if (car[i]->current_point[1]-1 < x1)
                            isUsing = -1;
                    }
                    break;
                    
                case 3:
                    if (car[i]->current_point[1] != car[i]->destination[1]) {
                        if (car[i]->current_point[1]+1 < x1 || car[i]->current_point[1] >= x1)
                            car[i]->current_point[1]++;
                        else if (isUsing == i || (order == i && isUsing == -1)) {
                            car[i]->current_point[1]++;
                            isUsing = i;
                        } if (car[i]->current_point[1]+1 > y2)
                            isUsing = -1;
                    }
                    break;
                    
                default:
                    break;
            }
            update_load(load, car);
        }
        
        for (int i = 0; i < 4; i++) {
            if (car[i]->current_point[0] == car[i]->destination[0] && car[i]->current_point[1] == car[i]->destination[1])
                isDone = true;
            else {
                isDone = false;
                break;
            }
        }
    }
}
