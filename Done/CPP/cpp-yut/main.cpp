//
//  main.cpp
//  cpp-yut
//
//  Created by Jacob An on 2022/04/19.
//

#include "player.hpp"
#include "map.hpp"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

Map map;

// 모드 1
void mode1(int players) {
    ofstream fout;
    
    // 로그 파일 생성
    fout.open("play.log");
    
    Player p, c1, c2;
    // 랜덤 순서 지정
    int order = rand() % players + 1;
    
    switch (order) {
        case 1:
            cout << "가장 먼저 플레이 합니다." << endl;
            cout << "플레이어는 A로 표시됩니다." << endl;
            
            fout << "가장 먼저 플레이 합니다." << endl;
            fout << "플레이어는 A로 표시됩니다." << endl;
            p.setTurn(order);
            c1.setTurn(order+1);
            c2.setTurn(order+2);
            break;
            
        case 2:
            cout << "플레이어의 플레이 순서는 " << players << "명의 참가자 중 두번째입니다." << endl;
            cout << "플레이어는 B로 표시됩니다." <<endl;
            
            fout << "플레이어의 플레이 순서는 " << players << "명의 참가자 중 두번째입니다." << endl;
            fout << "플레이어는 B로 표시됩니다." <<endl;
            p.setTurn(order);
            c1.setTurn(order-1);
            c2.setTurn(order+1);
            break;
            
        case 3:
            cout << "플레이어의 플레이 순서는 " << players << "명의 참가자 중 세번째입니다." << endl;
            cout << "플레이어는 C로 표시됩니다." <<endl;
            
            fout << "플레이어의 플레이 순서는 " << players << "명의 참가자 중 세번째입니다." << endl;
            fout << "플레이어는 C로 표시됩니다." <<endl;
            p.setTurn(order);
            c1.setTurn(order-2);
            c2.setTurn(order-1);
            break;
            
        default:
            break;
    }
    
    bool isEnd = false;
    int turn = 1;
    
    // 플레이 인원수에 따른 세팅
    if (players == 2) map.setPlayer(p, c1);
    else if (players == 3) map.setPlayer(p, c1, c2);
    
    while (!isEnd) {
        cout << "엔터를 눌러 윷을 던지세요." <<endl;
        getchar();
        
        // 윷을 던져 나온 숫자 k, 누군가 잡혔는지 판단하는 변수 isCatch
        int k = 0, isCatch = 0;
        // p1 플레이어의 차례일 때
        if (map.p1.getTurn() == turn) {
            // p1이 윷을 던지고
            fout << "플레이어가 윷을 던집니다." << endl;
            cout << "플레이어가 윷을 던집니다." << endl;
            k = map.p1.throwYut();
            // 윷놀이 판 위에서 이동
            map.p1.move(k);
            // 말을 잡았는지 검사
            isCatch = map.checkCatch(turn);
        } else if (map.p2.getTurn() == turn) {
            fout << "컴퓨터 1이 윷을 던집니다." << endl;
            cout << "컴퓨터 1이 윷을 던집니다." << endl;
            k = map.p2.throwYut();
            map.p2.move(k);
            isCatch = map.checkCatch(turn);
        } else if (map.p3.getTurn() == turn) {
            fout << "컴퓨터 2가 윷을 던집니다." << endl;
            cout << "컴퓨터 2가 윷을 던집니다." << endl;
            k = map.p2.throwYut();
            map.p3.move(k);
            isCatch = map.checkCatch(turn);
        }
        
        // 던져진 윷의 수에 따라 결과 출력
        switch (k) {
            case 1:
                fout << "도가 나왔습니다." << endl;
                cout << "도가 나왔습니다." << endl;
                break;
                
            case 2:
                fout << "개가 나왔습니다." << endl;
                cout << "개가 나왔습니다." << endl;
                break;
            
            case 3:
                fout << "걸이 나왔습니다." << endl;
                cout << "걸이 나왔습니다." << endl;
                break;
            
            case 4:
                fout << "윷이 나왔습니다." << endl;
                cout << "윷이 나왔습니다." << endl;
                break;
            
            case 5:
                fout << "모가 나왔습니다." << endl;
                cout << "모가 나왔습니다." << endl;
                break;
        }
        
        // 윷놀이 판 출력
        map.printMap();
        map.printMapFile(fout);
        
        // 말을 잡지 못했거나 던진 결과가 윷이나 모가 아니면 다음 턴으로 이동
        if (k < 4 && !isCatch) turn++;
        // 마지막 플레이어의 차례가 끝나면 다시 첫번재 플레이어의 차례
        if (players == 2 && turn == 3) turn = 1;
        else if (players == 3 && turn == 4) turn = 1;
        
        // -1로 이동했다면 승리한 경우
        if (map.p1.position == -1) {
            isEnd = true;
            fout << map.p1.initial << " 승리!" << endl;
            cout << map.p1.initial << " 승리!" << endl;
        } if (map.p2.position == -1) {
            isEnd = true;
            fout << map.p2.initial << " 승리!" << endl;
            cout << map.p2.initial << " 승리!" << endl;
        } if (map.p3.position == -1) {
            isEnd = true;
            fout << map.p3.initial << " 승리!" << endl;
            cout << map.p3.initial << " 승리!" << endl;
        }
    }
    fout.close();
}

// 모드 2
void mode2(void) {
    ofstream fout;
    fout.open("play.out");
    
    // 차례에 따른 승리 횟수 및 방문한 인덱스 저장할 배열 선언
    double winRateFirst = 0, winRateLast = 0;
    int positionFirst[29] = { 0 }, positionLast[29] = { 0 };
    
    srand((unsigned int)time(NULL));
    // 10만번 반복
    for (int i = 0; i < 100000; i++) {
        Player c1, c2;
        
        int order = rand() % 2 + 1;
        
        switch (order) {
            case 1:
                c1.setTurn(order);
                c2.setTurn(order+1);
                break;
                
            default:
                c1.setTurn(order);
                c2.setTurn(order-1);
        }
                
        
        bool isEnd = false;
        int turn = 1;
        
        // 2인 플레이 설정
        map.setPlayer(c1, c2);
        
        // 위와 동일하나 출력을 하지 않음
        while (!isEnd) {
            int k = 0, isCatch = 0;
            if (map.p1.getTurn() == turn) {
                k = map.p1.throwYut();
                map.p1.move(k);
                isCatch = map.checkCatch(turn);
            } else if (map.p2.getTurn() == turn) {
                k = map.p2.throwYut();
                map.p2.move(k);
                isCatch = map.checkCatch(turn);
            }
            
            if (map.p1.turn == 1) positionFirst[map.p1.position]++;
            else if (map.p1.turn == 2) positionLast[map.p1.position]++;
            
            if (k < 4 && !isCatch) turn++;
            if (turn == 3) turn = 1;
            
            if (map.p1.position == -1) {
                isEnd = true;
                if (map.p1.turn == 1) winRateFirst += 1;
                else if (map.p1.turn == 2) winRateLast += 1;
                break;
            } if (map.p2.position == -1) {
                isEnd = true;
                break;
            }
        }
    }
    
    // 승률 출력
    fout << "1." << endl;
    fout << "선공 시 승률: \t" << winRateFirst / 100000 * 100 << "%"  << endl;
    fout << "후공 시 승률: \t" << winRateLast / 100000 * 100 << "%" << endl;
    
    // 방문 위치 및 횟수 출력
    fout << "\n" << "2." << endl;
    fout << "선공 시 방문 횟수 (위치, 횟수)" << endl;
    for (int i = 1; i < 29; i++)
        fout << i << ", " << positionFirst[i] << endl;
    
    fout << "\n후공 시 방문 횟수 (위치, 횟수)" << endl;
    for (int i = 1; i < 29; i++)
        fout << i << ", " << positionLast[i] << endl;
    
    fout.close();
    return;
}

int main(int argc, const char * argv[]) {
    ifstream fin;
    int mode, players;
    
    // play.in 파일 열기
    fin.open("play.in");
    // 파일로 부터 mode와 플레이어 수를 입력받음.
    fin >> mode >> players;
    
    // 난수 생성을 위한 시간 초기화
    srand((unsigned int)time(NULL));
    
    // 모드에 따른 함수 호출
    switch (mode) {
        case 1:
            mode1(players);
            break;
            
        case 2:
            mode2();
            break;
            
        default:
            break;
    }
    
    return 0;
}
