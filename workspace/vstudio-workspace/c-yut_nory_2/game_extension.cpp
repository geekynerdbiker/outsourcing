#include "game.hpp"
#include <fstream>
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

/*
>> required cout statements in run function
1. cout << "ID : ";
   cout << "PASSWORD : ";
2. cout << "Login Failed!" << endl;
   cout << "Login Succeed!" << endl;
*/
void GameExtension::login() {}

/* menuSelect function
This function is used to choose "game start / login / end program"
The function returns 0 if the user selects the end
program, and returns 1 if the user selects the game start.

>> required cout statements in run function
1. cout << "More than 1 player is needed to start the game" << endl;
2. cout << "Logged-in ID List : ";
3. cout << "No player is logged in" << endl;
*/
int GameExtension::menuSelect() {
    int i;
    while (1) {
        cout << "************************************************************"
             << endl;
        cout << "************************   Menu   **************************"
             << endl;
        cout << "************************************************************"
             << endl;

        cout << "1. game start" << endl;
        cout << "2. login" << endl;
        cout << "3. end program" << endl;
        cout << "Select the function you want : ";
        //////////////////IMPLEMENT HERE//////////////////////////////////////

        return 0;
        /////////////////////////////////////////////////////////////////////////
    }
}

/*
This function is used to run the game.
The function is called when the user selects the game start.
The function is used to run the game until the game ends.

>> required cout statements in run function
1. cout << "There is a saved game. Start a new game (0) / Resume (1) : ";
2. cout << "Select animal type of " << ??? << endl;
   cout << "(0: pig, 1: dog, 2: sheep, 3:cow) : ";
3. cout << "Continue (0) / Save and Exit the game (1) : ";
4. cout << "Game saved successfully!" << endl;
5. cout << "Write down the position of the player to move and yut" << endl;
   cout << "(back-do, do, gae, geol, yut, and mo)" << endl;
   cout << ">> position : ";
   cout << ">> yut : ";
6. cout << "Player " << ??? << " win" << endl;
;*/
void GameExtension::run() {
    //////////////////IMPLEMENT HERE//////////////////////////////////////

    /////////////////////////////////////////////////////////////////////////
}
