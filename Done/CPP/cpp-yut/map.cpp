//
//  map.cpp
//  cpp-yut
//
//  Created by Jacob An on 2022/04/19.
//

#include "map.hpp"

// 2인 플레이 세팅
void Map::setPlayer(Player p, Player c1) {
    p1 = p;
    p2 = c1;
    players = 2;
}

// 3인 플레이 세팅
void Map::setPlayer(Player p, Player c1, Player c2) {
    p1 = p;
    p2 = c1;
    p3 = c2;
    players = 3;
}

// 윷놀이판 출력
void Map::printMap(void) {
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 7; j++) {
            // 현재 좌표에 플레이어가 있으면 플레이어 이니셜 표시
            if (i == position[p1.position][0] && j == position[p1.position][1]) {
                if (p1.position != 100) cout << p1.initial << " ";
                else cout << map[i][j] << " ";
            } else if (i == position[p2.position][0] && j == position[p2.position][1]) {
                if (p2.position != 100) cout << p2.initial << " ";
                else cout << map[i][j] << " ";
                // 3인 플레이일 경우에만 검사
            } else if (players == 3 && i == position[p3.position][0] && j == position[p3.position][1]) {
                if (p3.position != 100) cout << p3.initial << " ";
                else cout << map[i][j] << " ";
            }
            // 그외 일반 윷놀이판 출력
            else cout << map[i][j] << " ";
        }
        cout << endl;
    }
}

void Map::printMapFile(ofstream& fout) {
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 7; j++) {
            // 현재 좌표에 플레이어가 있으면 플레이어 이니셜 표시
            if (i == position[p1.position][0] && j == position[p1.position][1]) {
                if (p1.position != 100) fout << p1.initial << " ";
                else fout << map[i][j] << " ";
            } else if (i == position[p2.position][0] && j == position[p2.position][1]) {
                if (p2.position != 100) fout << p2.initial << " ";
                else fout << map[i][j] << " ";
                // 3인 플레이일 경우에만 검사
            } else if (players == 3 && i == position[p3.position][0] && j == position[p3.position][1]) {
                if (p3.position != 100) fout << p3.initial << " ";
                else fout << map[i][j] << " ";
            }
            // 그외 일반 윷놀이판 출력
            else fout << map[i][j] << " ";
        }
        fout << endl;
    }
}
// 말을 잡았는지 검사
int Map::checkCatch(int turn) {
    // p1 플레이어의 턴에
    if (p1.turn == turn) {
        // 말을 잡았다면 p1이 p2를 잡았을 때
        if (p1.position == p2.position) {
            // p2를 시작 위치로 보냄
            p2.position = 0;
            return 1;
            // 말을 잡았다면 p1이 p3를 잡았을 때
        } else if (p1.position == p3.position) {
            // p3을 시작 위치로 보냄
            p3.position = 0;
            return 1;
        }
    } else if (p2.turn == turn) {
        if (p2.position == p1.position) {
            p1.position = 0;
            return 1;
        } else if (p2.position == p3.position) {
            p3.position = 0;
            return 1;
        }
        // 3인 플레이일 경우에만 검사
    } else if (players == 3 && p3.turn == turn) {
        if (p3.position == p1.position) {
            p1.position = 0;
            return 1;
        } else if (p3.position == p2.position) {
            p2.position = 0;
            return 1;
        }
    }
    // 잡았으면 1, 그렇지 않으면 0 반환
    return 0;
}
