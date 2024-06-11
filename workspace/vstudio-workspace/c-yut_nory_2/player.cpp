#include "player.hpp"
#include "yut.hpp"
#include <iostream>
#include <set>
#include <string>
#include <vector>

using namespace std;

/*
- player throws yut using Yut class
(Yut class declares Player class as a friend class)
- The results of the thrown yut should be insert into multiset<YutName>
yut_list;
- If the result is yut or mo, the player should throw one more time.
  (ex1) yut yut geol
  (ex2) mo gae
  (ex3) gae
  (ex4) do
  (ex5) mo yut back-do
*/
void Player::throwYut(Yut &yut) {
    string yuts = yut.throwFourYuts();
    //////////////////IMPLEMENT HERE//////////////////////////////////////
    YutName thrown(yuts);
    yut_list.insert(thrown);

    if (yuts == "mo" || yuts == "yut")
        throwYut(yut);
    //////////////////////////////////////////////////////////////////////
}

/*
- A function that moves the player's piece based on the yut result.
- The results of the position should be updated in a (vector<int> piece) and an
(int arrived_piece_num).

- Input
    - pos: current position of the player's piece
    - yut: yut result (back-do, do, gae, geol, yut, and mo)
- Output
    - return value: the final position of the player's piece
*/
int Player::movePlayer(int pos, string yut) {
    //////////////////IMPLEMENT HERE//////////////////////////////////////
    auto it = yut_list.find(yut);
    if (it == yut_list.end())
        return 0;

    int curr = pieces[pos];

    if (yut == "back-do") {
        if (curr == 0)
            return 0;
        else if (curr == 1)
            curr = 29;
        else if (curr == 29)
            curr = 19;
        else if (curr == 27)
            curr = 22;
        else if (curr == 22)
            curr = 26;
        else if (curr == 20)
            curr = 5;
        else if (curr == 25)
            curr = 10;
        else
            curr--;
    }
    else if (yut == "do") {
        if (curr == 5)
            curr = 20;
        else if (curr == 10)
            curr = 25;
        else if (curr == 22)
            curr = 27;
        else if (curr == 26)
            curr = 22;
        else if (curr == 24)
            curr = 15;
        else if (curr == 19)
            curr = 29;
        else 
            curr += 1;
    }
    else if (yut == "gae") {
        if (curr == 5)
            curr = 21;
        else if (curr == 10)
            curr = 26;
        else if (curr == 22)
            curr = 28;
        else if (curr == 25)
            curr = 22;
        else if (curr == 26)
            curr = 27;
        else if (curr == 24)
            curr = 16;
        else if (curr >= 18 && curr <= 19)
            curr = 29;
        else
            curr += 2;
    }
    else if (yut == "geol") {
        if (curr == 5 || curr == 10)
            curr = 22;
        else if (curr == 22)
            curr = 29;
        else if (curr == 25)
            curr = 27;
        else if (curr == 26)
            curr = 28;
        else if (curr == 24)
            curr = 17;
        else if (curr >= 17 && curr <= 19)
            curr = 29;
        else
            curr += 3;
    }
    else if (yut == "yut") {
        if (curr == 5)
            curr = 23;
        else if (curr == 10)
            curr == 27;
        else if (curr == 22 || curr >= 26)
            curr = 29;
        else if (curr == 25)
            curr == 28;
        else if (curr == 24)
            curr = 18;
        else if (curr >= 16 && curr <= 19)
            curr == 29;
        else
            curr += 1;
    }
    else if (yut == "mo") {
        if (curr == 5)
            curr = 24;
        else if (curr == 10)
            curr == 28;
        else if (curr == 22 || curr >= 25)
            curr = 29;
        else if (curr == 24)
            curr = 19;
        else if (curr >= 15 && curr <= 19)
            curr == 29;
        else
            curr += 1;
    }

    pieces[pos] = curr;

    auto range = yut_list.equal_range(yut);
    yut_list.erase(range.first, range.second);

    return 1;
    //////////////////////////////////////////////////////////////////////
}

void Player::initPieces(int n) {
    for (int i = 0; i < n; i++)
        pieces.push_back(0);
}

void Player::printPieces() {
    for (int i = 0; i < pieces.size(); i++)
        cout << pieces[i] << " ";
}

void Player::printYuts() {
    for (const auto &yut : yut_list)
        cout << yut.name << " ";
}