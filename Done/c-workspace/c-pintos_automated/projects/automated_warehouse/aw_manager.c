#include "projects/automated_warehouse/aw_manager.h"

// #####################################################################
// DO NOT TOUCH THIS CODE
// #####################################################################

unsigned int step = 0;
const char threads[4][10] = {
    "RUNNING",
    "READY",
    "BLOCKED",
    "DYING"
};

const char map[6][7] = {
    {'X', 'X', 'A', 'X', 'X', 'X', 'X' },
    {'X', '1', ' ', '2', '3', '4', 'X' },
    {'B', ' ', ' ', ' ', ' ', ' ', 'X' },
    {'X', ' ', ' ', ' ', ' ', ' ', 'X' },
    {'X', '5', ' ', '6', '7', 'S', 'X' },
    {'X', 'X', 'C', 'X', 'X', 'W', 'X' }
};

/**
 * Before starting the simulator, initialize essential component
 * It must be called top of the main code
 */
void init_automated_warehouse(char** __argv){
    printf("arguments list:%s, %s, %s\n", __argv[0], __argv[1], __argv[2]);
    list_init(&blocked_threads);
}

/**
 * Private code for printing
 */
void _print_place(Robot* __robots, int __number_of_robots, int __row, int __col){
    for (int robotIdx = 0; robotIdx < __number_of_robots; robotIdx++){
        Robot* __robot = &__robots[robotIdx];
        if (__robot->row == __row && __robot->col == __col) printf("%sM%d,",__robot->name, __robot->current);
    }
}
/**
 * Print a map of warehouse and robots
 * It requires array of robots and length of array
 * It must be called before unblocking robot threads
 */
void print(Robot* __robots, int __number_of_robots) {    
    printf("STEP_INFO_START::%d\n", step);
    printf("MAP_INFO::\n");
    for (int row = 0; row < 6; row++){
        for (int col = 0; col < 7; col++){
            if (map[row][col] == 'A' ||
                map[row][col] == 'B' ||
                map[row][col] == 'C' ||
                map[row][col] == 'W'){
                printf("%c    ", map[row][col]);
            }
            else {
                int isFound = 0;
                for (int robotIdx = 0; robotIdx < __number_of_robots; robotIdx++){
                    Robot* __robot = &__robots[robotIdx];
                    if (__robot->col == col && __robot->row == row){
                        if (__robot->current > 0) printf("%sM%d ", __robot->name, __robot->current);
                        else printf("%s   ", __robot->name);
                        isFound = 1;
                    }
                }
                if (!isFound) printf("%c    ", map[row][col]);
            }
        }
        printf("\n");
    }

    printf("\n");
    printf("PLACE_INFO::\n");
    printf("W:");
    _print_place(__robots, __number_of_robots, ROW_W, COL_W);
    printf("\n");

    printf("A:");
    _print_place(__robots, __number_of_robots, ROW_A, COL_A);
    printf("\n");

    printf("B:");
    _print_place(__robots, __number_of_robots, ROW_B, COL_B);
    printf("\n");

    printf("C:");
    _print_place(__robots, __number_of_robots, ROW_C, COL_C);
    printf("\n");
    printf("STEP_INFO_DONE::%d\n", step);
}

/**
 * A function increasing 1 step
 * It must be called before unblocking and after print
 */
void increase(void){
    step++;
}