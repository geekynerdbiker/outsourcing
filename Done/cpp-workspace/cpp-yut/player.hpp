//
//  player.hpp
//  cpp-yut
//
//  Created by Jacob An on 2022/04/19.
//

#ifndef player_hpp
#define player_hpp

#include <iostream>

using namespace std;

class Player {
public:
    // 현재 칸 번호
    int position = 0;
    // 플레이어의 차례
    int turn = -1;
    // 플레이어를 나타내는 문자
    char initial;
    
    void setTurn(int);
    int getTurn(void);
    int throwYut(void);
    void move(int);
};

#endif /* player_hpp */
