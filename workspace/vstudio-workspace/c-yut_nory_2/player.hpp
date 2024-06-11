#include "yut.hpp"
#include <algorithm>
#include <set>
#include <string>
#include <vector>
#ifndef __PLAYER_H_INCLUDED__
#define __PLAYER_H_INCLUDED__
using namespace std;

#define BACK_DO 0
#define DO 1
#define GAE 2
#define GEOL 3
#define YUT 4
#define MO 5

class Player {
    /////////Feel free to add or subtract functions or variables. //////////

  public:
    Player() {}
    int movePlayer(int pos, string yut);
    void throwYut(Yut &yut);

    void initPieces(int n);
    void printPieces();
    void printYuts();

    int getArrived() const { return arrived_piece_num; }

  protected:
    vector<int> pieces;
    int arrived_piece_num = 0;
    multiset<YutName> yut_list;
};

class AnimalPlayer : public Player {
    /////////Feel free to add or subtract functions or variables. //////////
    // 0:pig 1:dog 2:sheep 3:cow
};

#endif
