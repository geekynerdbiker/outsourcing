// Program name
//
// This program was written by [your name] (z5555555)
// on [date]
//
// TODO: Description of program

#include <stdio.h>

////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////  CONSTANTS  /////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

// Provided constants
#define SIZE        9
#define TRUE        1
#define FALSE       0
#define RIGHT       2
#define LEFT        3

// TODO: you may choose to add additional #defines here.

// Provided Enums
enum tile_type {LILLYPAD, BANK, WATER, TURTLE, LOG};

////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////  STRUCTS  //////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

// Provided structs
struct board_tile {
    enum tile_type type; // The type of piece it is (water, bank, etc.)
    int occupied;        // TRUE or FALSE based on if Frogger is there.
    int bug;
    int bug_moved;
    int direction;
};

////////////////////////////////////////////////////////////////////////////////
/////////////////////////////  FUNCTION PROTOTYPES  ////////////////////////////
////////////////////////////////////////////////////////////////////////////////

// TODO: Your function prototypes here
void init_bug_move(struct board_tile board[SIZE][SIZE]);
void move_bug(struct board_tile board[SIZE][SIZE]);


// Prints out the current state of the board.
void print_board(struct board_tile board[SIZE][SIZE]);
char type_to_char(enum tile_type type);

////////////////////////////////////////////////////////////////////////////////
//////////////////////////  FUNCTION IMPLEMENTATIONS  //////////////////////////
////////////////////////////////////////////////////////////////////////////////

int main(void) {
    
    printf("Welcome to CSE Frogger!\n");
    struct board_tile game_board[SIZE][SIZE];
    
    // TODO (Stage 1.1) Initialise the gameboard.
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++) {
            game_board[i][j].bug = FALSE;
            game_board[i][j].bug_moved = FALSE;
            game_board[i][j].direction = RIGHT;
            if (i == 0 && (j % 2 == 0)) {
                game_board[i][j].type = LILLYPAD;
                game_board[i][j].occupied = FALSE;
            } else if (i == 8) {
                game_board[i][j].type = BANK;
                game_board[i][j].occupied = FALSE;
                
                if (j == 4) game_board[i][j].occupied = TRUE;
            } else {
                game_board[i][j].type = WATER;
                game_board[i][j].occupied = FALSE;
            }
        }
    
    // Read user input and place turtles.
    printf("How many turtles? ");
    // TODO (Stage 1.2): Scan in the turtles, and place them on the map.
    int turtles = 0;
    scanf("%d", &turtles);
    
    if (turtles) {
        printf("Enter pairs: \n");
        for (int i = 0; i < turtles; i++) {
            int x = -1, y = -1;
            scanf("%d %d", &x, &y);
            if (x >= 1 && x < SIZE - 1 && y >= 0 && y < SIZE)
                game_board[x][y].type = TURTLE;
        }
    }
    
    // Start the game and print out the gameboard.
    printf("Game Started\n");
    print_board(game_board);
    
    printf("Enter command: ");
    // TODO (Stage 1.3): Create a command loop, to read and execute commands!
    char command = '0';
    int row = 0, col = 0, start_column = 0, end_column = 0;
    int init_x = 8, init_y = 4;
    int pos_x = init_x, pos_y = init_y;
    int tmp_x = pos_x, tmp_y = pos_y;
    int lives = 3;
    
    while (scanf(" %c", &command) != EOF) {
        switch (command) {
            case 'l':
                scanf("%d %d %d", &row, &start_column, &end_column);
                if (row >= 0 && row < SIZE) {
                    if (start_column >= 0 && start_column < SIZE) {
                        if (end_column >= start_column) {
                            int isWater = TRUE;
                            for (int col = start_column; col <= end_column && col < SIZE; col++)
                                if (game_board[row][col].type != WATER) {
                                    if (game_board[row][col].type == LOG)
                                        continue;
                                    isWater = FALSE;
                                    break;
                                }
                            if (isWater) {
                                for (int col = start_column; col <= end_column && col < SIZE; col++)
                                    game_board[row][col].type = LOG;
                            }
                        }
                    }
                }
                break;
            case 'c':
                scanf("%d", &row);
                if (row >= 1 && row < SIZE-1) {
                    int isLogOrTurtle = TRUE;
                    for (int col = 0; col < SIZE; col++) {
                        if (game_board[row][col].occupied == TRUE) {
                            isLogOrTurtle = FALSE;
                            break;
                        } if (game_board[row][col].type == LOG)
                            continue;
                        if (game_board[row][col].type == WATER)
                            continue;
                        if (game_board[row][col].type == TURTLE)
                            continue;
                        isLogOrTurtle = FALSE;
                        break;
                    }
                    if (isLogOrTurtle) {
                        for (int col = 0; col < SIZE; col++) {
                            game_board[row][col].bug = FALSE;
                            game_board[row][col].type = WATER;
                        }
                    }
                }
                break;
            case 'r':
                scanf("%d %d", &row, &col);
                if (row >= 0 && row < SIZE)
                    if (col >= 0 && col < SIZE) {
                        int left = col, right = col+1;
                        int isFrogger = FALSE;
                        while (left >= 0) {
                            if (game_board[row][left].occupied == TRUE) {
                                isFrogger = TRUE;
                                break;
                            }
                            left--;
                        } while (!isFrogger && right < SIZE) {
                            if (game_board[row][right].occupied == TRUE) {
                                isFrogger = TRUE;
                                break;
                            }
                            right++;
                        }
                        if (!isFrogger) {
                            if (game_board[row][col].type == LOG) {
                                int left = col, right = col+1;
                                while (left >= 0 && game_board[row][left].type == LOG) {
                                    game_board[row][left].type = WATER;
                                    left--;
                                } while (right < SIZE && game_board[row][right].type == LOG) {
                                    game_board[row][right].type = WATER;
                                    right++;
                                }
                            }
                        }
                    }
                break;
            case 'w':
                tmp_x = pos_x - 1;
                if (tmp_x >= 0 && tmp_x < SIZE)
                    if (pos_y >= 0 && pos_y < SIZE) {
                        move_bug(game_board);
                        init_bug_move(game_board);
                        game_board[pos_x][pos_y].occupied = FALSE;
                        game_board[tmp_x][pos_y].occupied = TRUE;
                        pos_x -= 1;
                        //                        move_board(game_board, g);
                    }
                break;
                
            case 's':
                tmp_x = pos_x + 1;
                if (tmp_x >= 0 && tmp_x < SIZE)
                    if (pos_y >= 0 && pos_y < SIZE) {
                        move_bug(game_board);
                        init_bug_move(game_board);
                        game_board[pos_x][pos_y].occupied = FALSE;
                        game_board[tmp_x][pos_y].occupied = TRUE;
                        pos_x += 1;
                        //                        move_board(game_board, g);
                    }
                break;
                
            case 'a':
                tmp_y = pos_y - 1;
                if (pos_x >= 0 && pos_x < SIZE)
                    if (tmp_y >= 0 && tmp_y < SIZE) {
                        move_bug(game_board);
                        init_bug_move(game_board);
                        game_board[pos_x][pos_y].occupied = FALSE;
                        game_board[pos_x][tmp_y].occupied = TRUE;
                        pos_y -= 1;
                        //                        move_board(game_board, g);
                    }
                break;
                
            case 'd':
                tmp_y = pos_y + 1;
                if (pos_x >= 0 && pos_x < SIZE)
                    if (tmp_y >= 0 && tmp_y < SIZE) {
                        move_bug(game_board);
                        init_bug_move(game_board);
                        game_board[pos_x][pos_y].occupied = FALSE;
                        game_board[pos_x][tmp_y].occupied = TRUE;
                        pos_y += 1;
                        //                        move_board(game_board, g);
                    }
                break;
            case 'b':
                scanf("%d %d", &row, &col);
                if (row >= 0 && row < SIZE && col >= 0 && col < SIZE) {
                    if ((game_board[row][col].type == LOG || game_board[row][col].type == TURTLE) && !game_board[row][col].occupied) {
                        game_board[row][col].bug = TRUE;
                    }
                }
                break;
            default:
                break;
        }
        print_board(game_board);
        if (game_board[pos_x][pos_y].type == WATER || game_board[pos_x][pos_y].bug == TRUE)
            if (game_board[pos_x][pos_y].occupied) {
                if (--lives) {
                    printf("\n# LIVES LEFT: %d #\n\n", lives);
                    game_board[pos_x][pos_y].occupied = FALSE;
                    pos_x = init_x;
                    pos_y = init_y;
                    game_board[pos_x][pos_y].occupied = TRUE;
                    print_board(game_board);
                } else {
                    printf("\n !! GAME OVER !!\n\n");
                    break;
                }
            }
        
        if (game_board[pos_x][pos_y].type == LILLYPAD)
            if (game_board[pos_x][pos_y].occupied) {
                printf("\nWahoo!! You Won!\n\n");
                break;
            }
        printf("Enter command: ");
    }
    
    printf("Thank you for playing CSE Frogger!\n");
    return 0;
}

////////////////////////////////////////////////////////////////////////////////
///////////////////////////// ADDITIONAL FUNCTIONS /////////////////////////////
////////////////////////////////////////////////////////////////////////////////

// TODO: Add more functions here!

void init_bug_move(struct board_tile board[SIZE][SIZE]) {
    for (int row = 0; row < SIZE; row++) {
        for (int col = 0; col < SIZE; col++) {
            if (board[row][col].bug)
                board[row][col].bug_moved = FALSE;
        }
    }
}

void move_bug(struct board_tile board[SIZE][SIZE]) {
    for (int row = 0; row < SIZE; row++) {
        for (int col = 0; col < SIZE; col++) {
            if (board[row][col].bug && !board[row][col].bug_moved) {
                if (board[row][col].direction == RIGHT) {
                    int index = 0;
                    int opposite = FALSE;
                    while (col+index < SIZE) {
                        if (board[row][col+index].type == LOG || board[row][col+index].type == TURTLE) {
                            if (board[row][col+index].bug) index++;
                            else break;
                        } else {
                            board[row][col].direction = LEFT;
                            if (col - 1 >= 0 && (board[row][col-1].type == TURTLE || board[row][col-1].type == LOG)) {
                                board[row][col-1].bug = TRUE;
                                board[row][col-1].direction = board[row][col].direction;
                                board[row][col-1].bug_moved = TRUE;
                                board[row][col].bug = FALSE;
                                board[row][col].direction = RIGHT;
                                opposite = TRUE;
                                break;
                            }
                        }
                    } if (!opposite) {
                        board[row][col+index].bug = TRUE;
                        board[row][col+index].direction = board[row][col].direction;
                        board[row][col+index].bug_moved = TRUE;
                        board[row][col].bug = FALSE;
                        board[row][col].direction = RIGHT;
                        
                    }
                } else {
                    int index = 0;
                    int opposite = FALSE;
                    while (col-index < SIZE) {
                        if (board[row][col-index].type == LOG || board[row][col-index].type == TURTLE) {
                            if (board[row][col-index].bug) index++;
                            else break;
                        } else {
                            board[row][col].direction = RIGHT;
                            if (col - 1 >= 0 && (board[row][col-1].type == TURTLE || board[row][col+1].type == LOG)) {
                                board[row][col+1].bug = TRUE;
                                board[row][col+1].direction = board[row][col].direction;
                                board[row][col+1].bug_moved = TRUE;
                                board[row][col].bug = FALSE;
                                board[row][col].direction = RIGHT;
                                
                                opposite = TRUE;
                                break;
                            }
                        }
                    } if (!opposite) {
                        board[row][col-index].bug = TRUE;
                        board[row][col-index].direction = board[row][col].direction;
                        board[row][col-index].bug_moved = TRUE;
                        board[row][col].bug = FALSE;
                        board[row][col].direction = RIGHT;
                        
                    }
                }
            }
        }
    }
}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////// PROVIDED FUNCTIONS //////////////////////////////
////////////////////////////////////////////////////////////////////////////////

void print_board(struct board_tile board[SIZE][SIZE]) {
    for (int row = 0; row < SIZE; row++) {
        for (int col = 0; col < SIZE; col++) {
            char type_char = '\0';
            if (board[row][col].occupied) {
                type_char = 'F';
            } else if (board[row][col].bug) {
                type_char = 'B';
            } else {
                type_char = type_to_char(board[row][col].type);
            }
            printf("%c ", type_char);
        }
        printf("\n");
    }
}

char type_to_char(enum tile_type type) {
    char type_char = ' ';
    if (type == LILLYPAD) {
        type_char = 'o';
    } else if (type == BANK) {
        type_char = 'x';
    } else if (type == WATER) {
        type_char = '~';
    } else if (type == TURTLE) {
        type_char = 'T';
    } else if (type == LOG) {
        type_char = 'L';
    }
    return type_char;
}
