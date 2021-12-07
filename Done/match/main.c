//
//  main.c
//  match
//
//  Created by Jacob An on 2021/12/05.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// If you want, you can change the SEED value to check your program.
#define SEED 0
#define SWAP(x, y, t) ((t) = (x), (x) = (y), (y) = (t))

enum CharacterMode{
    RESET,  // Value 0 -> Reset character mode  ("\033[0m")
    UL,     // Value 1 -> Underline             ("\033[4m")
    BR,     // Value 2 -> Bright Red            ("\033[91m")
    BG,     // Value 3 -> Bright Green          ("\033[92m")
    BY,     // Value 4 -> Bright Yellow         ("\033[93m")
    BB,     // Value 5 -> Bright Blue           ("\033[94m")
    BM,     // Value 6 -> Bright Magenta        ("\033[95m")
};

// const string literal (ANSI Escape Sequence)
const char* ch_mode[7]  =  {"\033[0m" , "\033[4m" , "\033[91m", "\033[92m",
                            "\033[93m", "\033[94m", "\033[95m"};

const char* clear_screen = "\033[1;1H\033[2J"; // clear the whole screen

// For printing the game map
int map[8][8];
int pop_flag[8][8];

// function prototype (Already implemented functions)
void init();
void drawMap(int score);
int isDone();

// function prototype (you have to implement this functions)
int selectAction(int *row, int *col, char *direction);
void swipe(int row, int col, char direction);
int isPop();
int pop();
void updateMap();

// You have to complete the main function.
int main()
{
    int score = 0;
    int row, col;
    char direction;

    init();
    drawMap(score);
    
    /* Fill the code here */
    while (1) {
        int validation = selectAction(&row, &col, &direction);
        if (validation != 0) continue;
        swipe(row, col, direction);
        drawMap(score);
        
        if (isPop()) {
            score += pop();
            updateMap();
            drawMap(score);
        }
        if (isDone()) break;
        drawMap(score);
    }
    
    return 0;
}

/******************************************/
/****** Already implemented functions *****/
/******************************************/

/* DO NOT change the printf statement in already implemented functions */

void init()
{
    // set the random seed
    srand(SEED);
    for(int row = 0; row < 8; row ++)
    {
        for(int col = 0; col < 8; col ++)
        {
            // fill the map with rand function.
            map[row][col] = (rand() % 5) + BR;
        }
    }
}

void drawMap(int score)
{
    // clear the screen and move cursor to start point
    printf("%s%s", ch_mode[RESET], clear_screen);

    // print the score
    printf("||| SCORE : %4d |||\n   ", score);

    // print the column index
    for(int i = 0; i < 8; i++)
    {
        printf("%s%d %s", ch_mode[UL], i, ch_mode[RESET]);
    }
    printf("\n");

    // print the map with row index
    for(int row = 0; row < 8; row++)
    {
        printf(" %d|", row);
        for(int col = 0 ; col < 8; col++)
        {
            if(pop_flag[row][col])
            {
                printf("%s\u25CB %s", ch_mode[map[row][col]], ch_mode[RESET]);
            }
            else
            {
                printf("%s\u25CF %s", ch_mode[map[row][col]], ch_mode[RESET]);
            }
        }
        printf("\n");
    }
        printf("\n");
    usleep(1500000);
}

int isDone()
{
    int flag = 1, temp;
    
    for(int row = 0; row < 8; row ++)
    {
        for(int col = 0; col < 8; col++)
        {
            // For every blocks, it will do swipe toward up, down, left, right,
            // And check whehter there are some blocks that will be popped.
            // After checking, it will undo the swipe.
            // If there are, it will return 0, Otherwise, return 1.
            if(row > 0)
            {
                SWAP(map[row][col], map[row-1][col], temp);
                if(isPop()) flag = 0;
                SWAP(map[row][col], map[row-1][col], temp);
            }
            if(flag == 0) return 0;
            if(col > 0)
            {
                SWAP(map[row][col], map[row][col-1], temp);
                if(isPop()) flag = 0;
                SWAP(map[row][col], map[row][col-1], temp);
            }
            if(flag == 0) return 0;
            if(row < 7)
            {
                SWAP(map[row][col], map[row+1][col], temp);
                if(isPop()) flag = 0;
                SWAP(map[row][col], map[row+1][col], temp);
            }
            if(flag == 0) return 0;
            if(col < 7)
            {
                SWAP(map[row][col], map[row][col+1], temp);
                if(isPop()) flag = 0;
                SWAP(map[row][col], map[row][col+1], temp);
            }
            if(flag == 0) return 0;
        }
    }
    printf("|||  GAME OVER  |||\n");
    return 1;
}

/******************************************/
/************* Your functions *************/
/******************************************/

// You have to implement this functions.

// Choose the block the block on the map and determine the swipe direction.
// If inputs are all vaild, return 0. Ohterwise return -1.
int selectAction(int *row, int *col, char *direction)
{
    /* Fill the code here */
    printf("[Select Block (row col)] >>> ");
    scanf("%d %d", row, col);
    if (*row < 0 || *row > 8 || *col < 0 || *col > 8) // Check inputs are valid.
        return -1;
    
    getchar();
    printf("[Swipe Direction (wasd)] >>> ");
    scanf("%c", direction);
    if (*direction != 'w' && *direction != 'a' && *direction != 's' && *direction != 'd') // Check the input is valid.
        return -1;
    
    return 0;
}


// Swipe function swaps the blocks using the argument.
void swipe(int row, int col, char direction)
{
    /* Fill the code here */
    int temp;
    
    switch (direction){
        case 'w':
            if(row > 0) SWAP(map[row][col], map[row-1][col], temp); // Move north is valid.
            break;
        case 's':
            if(row < 7) SWAP(map[row][col], map[row+1][col], temp); // Move south is valid.
            break;
        case 'a':
            if(col > 0) SWAP(map[row][col], map[row][col-1], temp); // Move east is valid.
            break;
        case 'd':
            if(col < 7) SWAP(map[row][col], map[row][col+1], temp); // Move west is valid.
            break;
    }
    
}

// If there are 3 or more consecutive same blocks return 1. Ohterwise, return 0.
int isPop()
{
    /* Fill the code here */
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++) { // Check all blocks of map.
            if (j < 6 && map[i][j] == map[i][j+1] && map[i][j] == map[i][j+2]) return 1;
            if (i < 6 && map[i][j] == map[i+1][j] && map[i][j] == map[i+2][j]) return 1;
        }
    return 0;
}

// Return the score which is count of all blocks to be popped.
int pop()
{
    /* Fill the code here */
    int score = 0;
    
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) { // Check all blocks of map.
                if (j < 6 && map[i][j] == map[i][j+1] && map[i][j] == map[i][j+2]) {
                    if(!pop_flag[i][j]) score++;
                    pop_flag[i][j] = 1;
                    if(!pop_flag[i][j+1]) score++;
                    pop_flag[i][j+1] = 1;
                    if(!pop_flag[i][j+2]) score++;
                    pop_flag[i][j+2] = 1;
                }
                if (i < 6 && map[i][j] == map[i+1][j] && map[i][j] == map[i+2][j]) {
                    if(!pop_flag[i][j]) score++;
                    pop_flag[i][j] = 1;
                    if(!pop_flag[i+1][j]) score++;
                    pop_flag[i+1][j] = 1;
                    if(!pop_flag[i+2][j]) score++;
                    pop_flag[i+2][j] = 1;
                }
        }
    }
    return score;
}

void updateMap()
{
    /* Fill the code here */
    for (int i = 0; i < 8; i++){
        for (int j = 0; j < 8; j++) {
            printf("%d ", pop_flag[i][j]);
            if(pop_flag[i][j]) {
                map[i][j] = (rand() % 5) + BR; // Fill emtpy coordinate of maps with new block
                pop_flag[i][j] = 0; // Init pop_flag[x][y] to false
            }
        }
    }
}
