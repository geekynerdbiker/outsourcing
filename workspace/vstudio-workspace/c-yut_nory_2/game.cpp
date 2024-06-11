#include "game.hpp"
#include <iostream>
#include <set>
#include <string>
#include <vector>

using namespace std;

/* menuSelect function
This function is used to choose "game start / end program"
The function returns 0 if the user selects the end
program, and returns 1 if the user selects the game start.
*/
int Game::menuSelect() {
    int i;
    //////////////////IMPLEMENT HERE//////////////////////////////////////

    //////////////////////////////////////////////////////////////////////
    while (1) {
        cout << "************************************************************"
             << endl;
        cout << "************************   Menu   **************************"
             << endl;
        cout << "************************************************************"
             << endl;

        cout << "1. game start" << endl;
        cout << "2. end program" << endl;
        cout << "Select the function you want : ";
        cin >> i;
        if (i < 1 || i > 2) {
            cout << "Type an integer from 1 to 2!" << endl;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        }
        if (i == 2) {
            return 0;
        } else {
            run();
            return 1;
        }
    }
    return 1;
}

/* run function
This function is used to run the game.
The function is called when the user selects the game start.
The function is used to run the game until the game ends.

>> required cout statements in run function
1. cout << "number of players (2, 3, 4) : ";
2. cout << "number of pieces per player (1, 2, 3, 4) : ";
3. cout << "Write down the position of the player to move and yut" << endl;
   cout << "(back-do, do, gae, geol, yut, and mo)" << endl;
   cout << ">> position : ";
   cout << ">> yut : ";
4. cout << "Player " << ??? << " win" << endl;
*/
void Game::run() {
    //////////////////IMPLEMENT HERE//////////////////////////////////////
    cout << "number of players (2, 3, 4) : ";
    cin >> player_num;
    cout << "number of pieces per player (1, 2, 3, 4) : ";
    cin >> piece_num;

    board.initializeBoard();
    pPlayer = new Player[player_num];

    for (int i = 0; i < player_num; i++)
        pPlayer[i].initPieces(piece_num);

    int turn = 0;
    while (true) {
        board.printBoard();
        printPieceState(); 
        printCurrentTurn(turn);

        cout << "Write down the position of the player to move and yut" << endl;
        cout << "(back-do, do, gae, geol, yut, and mo)" << endl;

        while (pPlayer[turn].remainYut()) {
            int pos;
            cout << ">> position : ";
            cin >> pos;

            string yuts;
            cout << ">> yut : ";
            cin >> yuts;

            pPlayer[turn].movePlayer(pos, yuts);
        }
        turn++;
        if (turn == player_num)
            turn = 0;
    }
    // cout << "Player " << ? ? ? << " win" << endl;
    /////////////////////////////////////////////////////////////////////////
}

/* printCurrentTurn function
This function is used to print the current player's turn.
The function is called when the player's turn is changed.
The function is used to print information of which player's turn, the player's
current piece positions, and the current yut result list.

(example)
Player 0 turn
Piece : 0 1 1 3
Yut : gae
*/
void Game::printCurrentTurn(int player_order) {
    //////////////////IMPLEMENT HERE//////////////////////////////////////
    if (player_order == 0) {
        cout << "Player " << COLOR_RED << player_order << COLOR_DEFAULT
             << " turn" << endl;
    }
    else if (player_order == 1) {
        cout << "Player " << COLOR_BLUE << player_order << COLOR_DEFAULT
            << " turn" << endl;
    }
    else if (player_order == 2) {
        cout << "Player " << COLOR_GREEN << player_order << COLOR_DEFAULT
            << " turn" << endl;
    }
    else if (player_order == 3) {
        cout << "Player " << COLOR_YELLOW << player_order << COLOR_DEFAULT
            << " turn" << endl;
    }
    cout << "Piece : ";
    pPlayer[player_order].printPieces();
    cout << '\n';

    pPlayer[player_order].throwYut(yut);

    cout << "Yut : ";
    pPlayer[player_order].printYuts();
    cout << '\n';
    /////////////////////////////////////////////////////////////////////////
}

/* printPieceState function
This function is used to print the state of the pieces.
The function is called when the user selects the game start.
The function is used to print the state of the pieces that are not started
and the pieces that have arrived.

(example)
-----------------------------------------
Not started : 
 □  □  □  □  □  □  □  □  □  □  □  □ 
Arrived : 
 ■  ■ 
-----------------------------------------
*/
void Game::printPieceState() {
    cout << "-----------------------------------------" << endl;
    cout << "Not started : ";
    cout << endl;
    //////////////////IMPLEMENT HERE//////////////////////////////////////
    for (int i = 0; i < player_num; i++) {
        for (int j = 0; j < piece_num - pPlayer[i].getArrived(); j++) {
            if (i == 0) 
                cout << COLOR_RED << "□ " << COLOR_DEFAULT;
            else if (i == 1) 
                cout << COLOR_BLUE << "□ " << COLOR_DEFAULT;
            else if (i == 2) 
                cout << COLOR_GREEN << "□ " << COLOR_DEFAULT;
            else if (i == 3) 
                cout << COLOR_YELLOW << "□ " << COLOR_DEFAULT;
        }
    }
    
    cout << endl;
    /////////////////////////////////////////////////////////////////////////
    cout << "Arrived : ";
    //////////////////IMPLEMENT HERE//////////////////////////////////////
    for (int i = 0; i < player_num; i++) {
        for (int j = 0; j < pPlayer[i].getArrived(); j++) {
            if (i == 0)
                cout << COLOR_RED << "■ " << COLOR_DEFAULT;
            else if (i == 1)
                cout << COLOR_BLUE << "■ " << COLOR_DEFAULT;
            else if (i == 2)
                cout << COLOR_GREEN << "■ " << COLOR_DEFAULT;
            else if (i == 3)
                cout << COLOR_YELLOW << "■ " << COLOR_DEFAULT;
        }
    }

    cout << endl;
    cout << endl;
    /////////////////////////////////////////////////////////////////////////
    cout << "-----------------------------------------" << endl;
}
