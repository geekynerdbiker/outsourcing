#include "board.hpp"
#include "player.hpp"
#include "yut.hpp"
#include <algorithm>
#include <string>
#include <vector>
#ifndef __GAME_H_INCLUDED__
#define __GAME_H_INCLUDED__

using namespace std;

class Game {
    /////////Feel free to add or subtract functions or variables. //////////
  public:
    Game() {}
    ~Game() {}
    int menuSelect();
    void run();
    void printPieceState();
    void printCurrentTurn(int player_order);

  protected:
    int player_num;
    int piece_num;
    Board board;
    Yut yut = Yut(0.5);

  private:
    Player *pPlayer;
};

class GameExtension : public Game {
    /////////Feel free to add or subtract functions or variables. //////////
  public:
    int menuSelect();
    void login();
    void run();
};

#endif
