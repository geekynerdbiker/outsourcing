#include "board.hpp"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Initialize the board
void Board::initializeBoard() {
    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++) {
            player_to_board[i][j] = {-1, 0};
        }
    }
}

// If a player's pieces are on the board, print the number of pieces
void Board::printPlayer(int player_order, int num_pieces) {
    if (player_order == 0) {
        cout << COLOR_RED << num_pieces << COLOR_DEFAULT;
    } else if (player_order == 1) {
        cout << COLOR_BLUE << num_pieces << COLOR_DEFAULT;
    } else if (player_order == 2) {
        cout << COLOR_GREEN << num_pieces << COLOR_DEFAULT;
    } else if (player_order == 3) {
        cout << COLOR_YELLOW << num_pieces << COLOR_DEFAULT;
    } else {
        cout << COLOR_DEFAULT << ' ' << COLOR_DEFAULT;
    }
}

/*
- print the entire board state
(initialized board state)
[ ] - [ ] - [ ] - [ ] - [ ] - [ ]
 | [ ]                     [ ] |
[ ]    .                 .    [ ]
 |       [ ]         [ ]       |
[ ]          .     .          [ ]
 |             [ ]             |
[ ]          .     .          [ ]
 |       [ ]         [ ]       |
[ ]    .                 .    [ ]
 | [ ]                     [ ] |
[ ] - [ ] - [ ] - [ ] - [ ] - [ ]^Start
*/

void Board::printBoard() {
    //////////////////IMPLEMENT HERE//////////////////////////////////////
    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++) {
            if (i == 0 || i == ROW - 1) {
                if ((i + j) % 2 == 0)
                    cout << "[ ]";
                else
                    cout << " - ";
            }
            else if (j == 0 || j == COL - 1) {
                if ((i + j) % 2 == 0)
                    cout << "[ ]";
                else
                    cout << " | ";
            }
            else if (i + j == 10) {
                if (i % 2 == 1)
                    cout << "[ ]";
                else
                    cout << " . ";
            }
            else if (i == j) {
                if (i % 2 == 1)
                    cout << "[ ]";
                else
                    cout << " . ";
            }
            else
                cout << "   ";
        }
        cout << endl;
    }
    /////////////////////////////////////////////////////////////////////////
}
