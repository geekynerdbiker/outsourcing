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

// TODO: you may choose to add additional #defines here.

// Provided Enums
enum tile_type {LILLYPAD, BANK, WATER, TURTLE, LOG, BUG};

////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////  STRUCTS  //////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

// Provided structs
struct board_tile {
    enum tile_type type; // The type of piece it is (water, bank, etc.)
    int occupied;        // TRUE or FALSE based on if Frogger is there.
};

////////////////////////////////////////////////////////////////////////////////
/////////////////////////////  FUNCTION PROTOTYPES  ////////////////////////////
////////////////////////////////////////////////////////////////////////////////

// TODO: Your function prototypes here
void move_board(struct board_tile board[SIZE][SIZE], int g);

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
    
    printf("Enter pairs: \n");
    for (int i = 0; i < turtles; i++) {
        int x = -1, y = -1;
        scanf("%d %d", &x, &y);
        if (x >= 0 && y >= 0)
            game_board[x][y].type = TURTLE;
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
    
    int g = 0, tmp_g = 0;
    
    int lives = 3;
    while (scanf(" %c", &command) != EOF) {
        switch (command) {
            case 'l':
                scanf("%d %d %d", &row, &start_column, &end_column);
                if (row >= 0 && row < SIZE) {
                    if (start_column >= 0 && start_column < SIZE) {
                        if (end_column >= 0 && end_column < SIZE) {
                            int isWater = TRUE;
                            for (int col = start_column; col <= end_column; col++)
                                if (game_board[row][col].type != WATER) {
                                    if (game_board[row][col].type == LOG)
                                        continue;
                                    isWater = FALSE;
                                    break;
                                }
                            if (isWater) {
                                for (int col = start_column; col <= end_column; col++)
                                    game_board[row][col].type = LOG;
                            }
                        } else printf("This command is not supported in game mode.\n");
                    }else printf("This command is not supported in game mode.\n");
                }else printf("This command is not supported in game mode.\n");
                break;
                
            case 'c':
                scanf("%d", &row);
                if (row >= 0 && row < SIZE) {
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
                        for (int col = 0; col < SIZE; col++)
                            game_board[row][col].type = WATER;
                    }else printf("This command is not supported in game mode.\n");
                }else printf("This command is not supported in game mode.\n");
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
                            if (game_board[row][col].type == LOG || game_board[row][col].type == BUG) {
                                int left = col, right = col+1;
                                while (game_board[row][left].type == LOG || game_board[row][col].type == BUG) {
                                    if (left < 0)
                                        break;
                                    game_board[row][left].type = WATER;
                                    left--;
                                } while (game_board[row][right].type == LOG || game_board[row][col].type == BUG) {
                                    if (right >= SIZE)
                                        break;
                                    game_board[row][right].type = WATER;
                                    right++;
                                }
                            }
                        }else printf("This command is not supported in game mode.\n");
                    }
                break;
                
            case 'w':
                tmp_x = pos_x - 1;
                if (tmp_x >= 0 && tmp_x < SIZE)
                    if (pos_y >= 0 && pos_y < SIZE) {
                        game_board[pos_x][pos_y].occupied = FALSE;
                        game_board[tmp_x][pos_y].occupied = TRUE;
                        pos_x -= 1;
                        move_board(game_board, g);
                    }
                break;
                
            case 's':
                tmp_x = pos_x + 1;
                if (tmp_x >= 0 && tmp_x < SIZE)
                    if (pos_y >= 0 && pos_y < SIZE) {
                        game_board[pos_x][pos_y].occupied = FALSE;
                        game_board[tmp_x][pos_y].occupied = TRUE;
                        pos_x += 1;
                        move_board(game_board, g);
                    }
                break;
                
            case 'a':
                tmp_y = pos_y - 1;
                if (pos_x >= 0 && pos_x < SIZE)
                    if (tmp_y >= 0 && tmp_y < SIZE) {
                        game_board[pos_x][pos_y].occupied = FALSE;
                        game_board[pos_x][tmp_y].occupied = TRUE;
                        pos_y -= 1;
                        move_board(game_board, g);
                    }
                break;
                
            case 'd':
                tmp_y = pos_y + 1;
                if (pos_x >= 0 && pos_x < SIZE)
                    if (tmp_y >= 0 && tmp_y < SIZE) {
                        game_board[pos_x][pos_y].occupied = FALSE;
                        game_board[pos_x][tmp_y].occupied = TRUE;
                        pos_y += 1;
                        move_board(game_board, g);
                    }
                break;
                
            case 'b':
                for (int i = 0; i < turtles; i++) {
                    scanf("%d %d", &row, &col);
                    if (row >= 0 && col >= 0) {
                        if (game_board[row][col].type == LOG || game_board[row][col].type == TURTLE) {
                            game_board[row][col].type = BUG;
                        }else printf("This command is not supported in game mode.\n");
                    }else printf("This command is not supported in game mode.\n");
                }
                break;
                
            case 'g':
                scanf("%d", &tmp_g);
                if (!g && tmp_g)
                    printf("\n### GAME MODE ACTIVATED ###\n\n");
                else if (g && !tmp_g)
                    printf("\n### GAME MODE EXITED ###\n\n");
                else printf("This command is not supported in game mode.\n");
                g = tmp_g;
                
            default:
                printf("This command is not supported in game mode.\n");
                break;
        }
        
        print_board(game_board);
        
        if (game_board[pos_x][pos_y].type == WATER || game_board[pos_x][pos_y].type == BUG)
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
void move_board(struct board_tile board[SIZE][SIZE], int g) {
    if (g)
        for (int row = 1; row < SIZE - 1; row++) {
            if (row % 2 == 1) {
                enum tile_type tmp = board[row][0].type;
                for (int col = 0; col < SIZE; col++) {
                    if (col == SIZE - 1) {
                        board[row][col].type = tmp;
                        break;
                    }
                    board[row][col].type = board[row][col+1].type;
                }
            } else {
                enum tile_type tmp = board[row][SIZE-1].type;
                for (int col = SIZE - 1; col >= 0; col--) {
                    if (col == 0) {
                        board[row][col].type = tmp;
                        break;
                    }
                    board[row][col].type = board[row][col-1].type;
                }
            }
        }
}

void move_bug(struct board_tile board[SIZE][SIZE]) {
    for (int row = 0; row < SIZE; row++) {
        for (int col = 0; col < SIZE; col++) {
            if (board[row][col].type == BUG) {
                int x = row, y = col;
                
                if (board[x][y].type == LOG || board[x][y].type == TURTLE) {
                    if (board[x][y+1].type == LOG || board[x][y+1].type == TURTLE) {
                        board[x][y].type = board[x][y+1].type;
                        board[x][y+1].type = BUG;
                    } else if (board[x][y-1].type == LOG || board[x][y-1].type == TURTLE) {
                        board[x][y].type = board[x][y+1].type;
                        board[x][y+1].type = BUG;
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
    } else if (type == BUG) {
        type_char = 'B';
    }
    return type_char;
}
