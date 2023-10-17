//
//  map.hpp
//  cpp-yut
//
//  Created by Jacob An on 2022/04/19.
//

#ifndef map_hpp
#define map_hpp

#include <iostream>
#include <fstream>
#include "player.hpp"

using namespace std;

class Map {
public:
    // 플레이어 수
    int players = 0;
    
    // 최대 3인까지 플레이
    Player p1, p2, p3;
    
    // 윷놀이 판
    char map[7][7] = {{'O','o','o', ' ', 'o','o','O'}, {'o','o',' ',' ',' ','o','o'}, {'o',' ','o',' ','o',' ','o'}, {' ', ' ', ' ', 'O',' ', ' ', ' '}, {'o',' ','o',' ','o',' ','o'}, {'o','o',' ',' ',' ','o','o'}, {'O','o','o', ' ', 'o','o','O'}};
    
    // 인덱스에 따른 윷놀이 판에서의 좌표 (과제 자료 표 참고)
    int position[29][2] = {{6, 6}, {5, 6}, {4, 6}, {2, 6}, {1, 6}, {0, 6}, {0, 5}, {0, 4}, {0, 2}, {0, 1}, {0, 0}, {1, 0}, {2, 0}, {4, 0}, {5, 0}, {6, 0}, {6, 1}, {6, 2}, {6, 4}, {6, 5}, {1, 5}, {2, 4}, {3, 3}, {4, 4}, {5, 5}, {1, 1}, {2, 2}, {4, 2}, {5, 1}};

    void setPlayer(Player, Player);
    void setPlayer(Player, Player, Player);
    void printMap(void);
    void printMapFile(ofstream&);
    int checkCatch(int);
};

#endif /* map_hpp */
