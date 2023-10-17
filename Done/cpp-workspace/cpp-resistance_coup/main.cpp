#include "Duke.hpp"
#include "Assassin.hpp"
#include "Captain.hpp"
#include "Contessa.hpp"

#include <iostream>
#include <algorithm>
#include <random>
#include <vector>
#include <utility>

using namespace std;

void print_menu() {
    cout << "=======================================" << endl;
    cout << "1. 게임 설명" << endl;
    cout << "2. 게임 시작" << endl;
    cout << "3. 종료" << endl;
    cout << "=======================================" << endl;
}

void show_card() {
    cout << "플레이어들의 카드는 다음과 같습니다." << endl;
    cout << "---------------------------------------" << endl;
    cout << "플레이어 : |  "<<"  |   |  "<<"  |" << endl;
    cout << "컴퓨터 1 : |  "<<"  |   |  "<<"  |" << endl;
    cout << "컴퓨터 2 : |  "<<"  |   |  "<<"  |" << endl;
    cout << "컴퓨터 3 : |  "<<"  |   |  "<<"  |" << endl;
    cout << "---------------------------------------" << endl;
}

int main() {
    int command;
    
    cout << "=======================================" << endl;
    cout << "|                                      |" << endl;
    cout << "|    레지스탕스 쿠 게임에 오신 걸 환영합니다!!   |" << endl;
    cout << "|                                      |" << endl;
    print_menu();
    
    while (true) {
        cout << "선택 : ";
        cin >> command;
        
        if (command == 1) {
            cout << "레지스탕스 쿠는 참가자들이 다양한 역할군의 카드들과 코인을 사용하여, 추리와 거짓말을 활용한 보드게임이다." << endl;
            cout << "각 참가자는 일반 행동과 캐릭터 행동 중 하나를 고를 수 있으며, 어떤 능력을 사용할 지 결정할 수 있다." << endl;
            cout << "참가자는 거짓말로 보유하고 있지 않은 캐릭터의 능력을 사용할 수 있으며, 타 참가자는 언제든디 도정할 수 있다." << endl;
            cout << "거짓말이 들통나면 카드를 한 장 오픈하고, 진실이면 도전한 상대가 카드를 한 장 오픈한다." << endl;
            cout << "카드 2장이 모두 오픈된 참가자는 게임에서 제외되며, 한 명이 남을 때까지 게임을 계속한다." << endl;
            cout << "적절한 블러핑과 상대의 수를 간파하여 이 게임에서 최종 승자가 되어 보세요!\n" << endl;
            print_menu();
        } else if (command == 2) {
            break;
        } else if (command == 3) {
            return 0;
        } else {
            cout << "다시 선택하세요" << endl;
            continue;
        }
    }
    cout << "게임에 참여하는 참가자는 플레이어와 컴퓨터 3명으로, 총 4명입니다." << endl;
    Player p, com1, com2, com3, com4;
    
    cout << "덱을 생성하고 카드를 분배합니다." << endl;
    vector<string> deque = {"Assassin", "Captain", "Contessa" ,"Duke", "Assassin", "Captain", "Contessa" ,"Duke", "Assassin", "Captain", "Contessa" ,"Duke"};
    auto rd = std::random_device {};
    auto rng = std::default_random_engine { rd() };
    std::shuffle(deque.begin(), deque.end(), rng);
    
    cout << "참가자에게 카드 분배가 완료되었습니다.\n" << endl;
    for (int i = 0; i < 2; i++) {
        p.push_role(make_pair(deque[i], "c"));
        com1.push_role(make_pair(deque[i+1], "c"));
        com2.push_role(make_pair(deque[i+2], "c"));
        com3.push_role(make_pair(deque[i+3], "c"));
    }

    cout << "게임을 시작합니다." << endl;
    cout << "=======================================" << endl;
    
}

