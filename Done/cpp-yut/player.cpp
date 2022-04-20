//
//  player.cpp
//  cpp-yut
//
//  Created by Jacob An on 2022/04/19.
//

#include "player.hpp"

// 차례에 맞는 이니셜 지정
void Player::setTurn(int t) {
    turn = t;
    
    switch (t) {
        case 1:
            initial = 'A';
            break;
            
        case 2:
            initial = 'B';
            break;
            
        case 3:
            initial = 'C';
            break;
        
        default:
            break;
    }
}

// 차례를 얻음
int Player::getTurn(void) { return turn; }

// 윷을 던짐
int Player::throwYut(void) {
    return rand() % 5 + 1;
}

// 던진 윷에 따른 이동
void Player::move(int k) {
    // 모서리 및 좌표에 따른 이동 방향 및 게임 끝 처리
    if (position == 5) {
        if (k <= 3)
            position += 14 + k;
        else
            position += 18 + k;
    } else if (position == 10) {
        if (k <= 2)
            position += 14 + k;
        else
            position += 9 + k;
    } else if (position  == 20 || position == 21) {
        if (position + k <= 22)
            position += k;
        else if (position + k <= 24)
            position += 4 + k;
        else
            position += k - 10;
    } else if (position == 25 || position == 26) {
        if (position + k > 29)
            position = -1;
        else if (position + k > 26)
            position += k - 5;
    } else if (position == 27 || position == 28) {
        if (position + k > 28)
            position += k - 14;
    } else if (position >= 15 && position <= 19) {
        if (position + k > 19)
            position = -1;
    } else if (position >= 22 && position <= 24) {
        if (position + k > 24)
            position = -1;
    } else position += k;
}
