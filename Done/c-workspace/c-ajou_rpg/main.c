//프로그램에 필요한 헤더 파일
#include <string.h> 
#include <stdio.h>
#include <stdlib.h>

//아이템 구조체 정의
typedef struct {
    char name[30];
    int bonusDamage; // 추가 공격력
    int bonusDefense; // 추가 방어력
} Item;

//플레이어 구조체 정의
typedef struct {
    char name[30];
    int hp;
    int swordDamage;
    int arrowDamage;
    int arrowCount;
    int fireDamage;
    int iceDamage;
    int fireCount;
    int iceCount;
    int potion;
    int potionCount;
    int job;
    Item equippedItem; // 장착한 아이템
} Player;


//몬스터 구조체 정의
typedef struct {
    char name[30];
    int hp;
    int damage;
} Monster;

void initPlayer(Player* player, const char* name);
void initMonster(Monster* monster, int difficulty, const char* name);

void equipItem(Player* player, Item item);
void unequipItem(Player* player);

void attackMonster(Monster* monster, int damage);
void attackPlayer(Player* player, int damage);

int usePotion(Player* player);

void playerTurn(Player* player, Monster* monster, Item* itemList, int itemCount);

void initPlayer(Player* player, const char* name) {
    printf("'%s'님, 아주 던전에 오신 것을 환영합니다. 던전을 탈출하기 위해서는 몬스터 3마리를 처치해야합니다.\n", name);
    int job = 0;

    // 직업이 1 또는 2가 아닌 경우 계속 입력받음
    while (job != 1 && job != 2) { 
        printf("직업을 선택하세요(1.전사 2.마법사): ");
        scanf_s("%d", &job);
    }
    printf("\n");

    // 초기화
    strcpy_s(player->name, strlen(player->name), name);
    player->job = job;

    player->hp = 20;
    player->swordDamage=5;
    player->arrowDamage=10;
    player->arrowCount=3;
    player->fireDamage=7;
    player->iceDamage=12;
    player->fireCount=4;
    player->iceCount=2;
    player->potion=15;
    player->potionCount=2;

    strcpy_s(player->equippedItem.name, strlen(player->equippedItem.name), "");
    player->equippedItem.bonusDamage = 0;
    player->equippedItem.bonusDefense = 0;
}

void initMonster(Monster* monster, int difficulty, const char* name) { 
    strcpy_s(monster->name, strlen(monster->name), name);

    // 난이도에 따라 몬스터 체력과 데미지 초기화
    switch (difficulty) {
    case 0:
        monster->hp = 10;
        monster->damage = 4;
        break;
    case 1:
        monster->hp = 15;
        monster->damage = 5;
        break;
    case 2:
        monster->hp = 20;
        monster->damage = 6;
        break;
    }
}

void equipItem(Player* player, Item item) {
    // 장비 장착
    printf("아이템 '%s'을(를) 장착했습니다. ", item.name);
    player->equippedItem = item;
    printf(" 추가 공격력: %d, 추가 방어력: %d\n", item.bonusDamage, item.bonusDefense);
}

void unequipItem(Player* player) {
    // 장비 해제 (초기화 상태와 동일)
    printf("아이템 '%s'을(를) 해제했습니다. ", player->equippedItem.name);
    strcpy_s(player->equippedItem.name, strlen(player->equippedItem.name), "");
    player->equippedItem.bonusDamage = 0;
    player->equippedItem.bonusDefense = 0;
    printf("\n");
}

void attackMonster(Monster* monster, int damage) {
    // 몬스터의 체력을 데미지만큼 줄이고, 음수이면 0으로
    monster->hp -= damage;

    if (monster->hp < 0)
        monster->hp = 0;

    printf("몬스터 HP: %d\n", monster->hp);
}

void attackPlayer(Player* player, int damage) {
    // 플레이어의 체력을 데미지만큼 줄이고, 음수이면 0(최소 체력)으로
    player->hp -= damage;

    if (player->hp < 0)
        player->hp = 0;

    printf("플레이어 HP: %d\n", player->hp);
}

int usePotion(Player* player) {
    // 체력이 20미만 일 때만 사용 가능
    if (player->hp < 20) {
        // 포션 사용 횟수가 남아있는 경우게만 사용가능
        if (player->potionCount > 0) {
            // 횟수를 소모하여 15만큼 체력 회복
            player->potionCount--;
            printf("포션을 마셨습니다. 체력이 회복됩니다! ");
            player->hp += player->potion;

            // 체력이 20을 초과하면 20(최대 체력)으로
            if (player->hp > 20) {
                player->hp = 20;
            }

            printf("플레이어 HP: %d\n", player->hp);
        }
        else {
            printf("포션이 더 이상 없습니다!\n");
        }
    }
    else {
        printf("이미 체력이 충분합니다!\n");
    }
}

void playerTurn(Player* player, Monster* monster, Item* itemList, int itemCount) {
    printf("플레이어 HP: %d, 장착 아이템: %s (추가 공격력: %d, 추가 방어력: %d)\n", player->hp, player->equippedItem.name, player->equippedItem.bonusDamage, player->equippedItem.bonusDefense);

    // 전사인 경우
    if (player->job == 1) {
        printf("1. 검공격(기본 공격력:%d)\n", player->swordDamage);
        printf("2. 화살 공격(기본 공격력:%d) (%d/3)\n", player->arrowDamage, player->arrowCount);
    }
    // 마법사인 경우
    else {
        printf("1. 화염 공격(기본 공격력:%d) (%d/4)\n", player->fireDamage, player->fireCount);
        printf("2. 얼음 공격(기본 공격력:%d) (%d/2)\n", player->iceDamage, player->iceCount);
    }
    // 직업에 상관없이 동일한 기능
    printf("3. 포션 마시기(체력회복:%d) (%d/2)\n", player->potion, player->potionCount);
    printf("4. 아이템 장착\n");
    printf("5. 아이템 해제\n");

    int command = 0;
    // 올바른 메뉴를 선택할 때까지 반복
    while (command < 1 || command > 5) {
        printf("선택: ");
        scanf_s("%d", &command);
    }

    switch (command) {
    case 1:
        // 전사인 경우
        if (player->job == 1) {
            // 검으로 공격.
            printf("검으로 몬스터를 공격했습니다. ");
            // 공격시 착용한 장비의 추가 공격력 + 기본 공격력만큼 공격
            attackMonster(monster, player->swordDamage + player->equippedItem.bonusDamage);

            printf("몬스터의 반격! ");
            // 몬스터로부터 몬스터의 공격력 - 추가 방어력 만큼 플레이어 체력 소모
            attackPlayer(player, monster->damage - player->equippedItem.bonusDefense);
        }
        else {
            // 마법사인 경우
            if (player->arrowCount > 0) {
                // 화염으로 공격
                printf("화염 공격으로 몬스터를 공격했습니다. ");
                attackMonster(monster, player->fireDamage + player->equippedItem.bonusDamage);
                player->fireCount--;

                printf("몬스터의 반격! ");
                attackPlayer(player, monster->damage - player->equippedItem.bonusDefense);
            }
            else {
                printf("화살이 부족합니다!\n");
            }
            
        }
        break;
    case 2:
        if (player->job == 1) {
            if (player->fireCount > 0) {
                printf("화살로 몬스터를 공격했습니다. ");
                attackMonster(monster, player->arrowDamage + player->equippedItem.bonusDamage);
                player->arrowCount--;

                printf("몬스터의 반격! ");
                attackPlayer(player, monster->damage - player->equippedItem.bonusDefense);
            }
            else {
                printf("화염 공격 횟수가 부족합니다!\n");
            }
        }
        else {
            if (player->iceCount > 0) {
                printf("얼음 공격으로 몬스터를 공격했습니다. ");
                attackMonster(monster, player->iceDamage + player->equippedItem.bonusDamage);
                player->iceCount--;

                printf("몬스터의 반격! ");
                attackPlayer(player, monster->damage - player->equippedItem.bonusDefense);
            }
            else {
                printf("얼음 공격 횟수가 부족합니다!\n");
            }
        }
        break;
    case 3:
        // 포션 사용
        usePotion(player);
        // 포션 사용 후 몬스터의 공격을 받음
        printf("몬스터의 반격! ");
        attackPlayer(player, monster->damage - player->equippedItem.bonusDefense);
        break;
    case 4:
        // 아이템 목록 출력
        printf("\n아이템 목록:\n");

        for (int i = 0; i < 3; i++)
            printf("%d. %s (추가 공격력: %d, 추가 방어력: %d)\n", i + 1, itemList[i].name, itemList[i].bonusDamage, itemList[i].bonusDefense);

        int selection = 0;
        // 올바른 아이템을 선택할 때까지 반복
        while (selection < 1 || selection > 3) {
            printf("장착할 아이템을 선택하세요: ");
            scanf_s("%d", &selection, sizeof(selection));
        }

        // 장비 장착
        equipItem(player, itemList[selection - 1]);
        break;
    case 5:
        // 장비 해제
        unequipItem(player);
        break;
    }
    printf("\n");
}


int main() {

    //메모리 할당
    Player** playerList = (Player**)malloc(sizeof(Player*));
    playerList[0] = (Player*)malloc(sizeof(Player));
    
    Monster** monsterList = (Monster**)malloc(3 * sizeof(Monster*));
    for (int i = 0; i < 3; ++i) {
        monsterList[i] = (Monster*)malloc(sizeof(Monster));
    }
    
    // 몬스터 3종 초기화
    initMonster(monsterList[0], 0, "고블린");
    initMonster(monsterList[1], 1, "트롤");
    initMonster(monsterList[2], 2, "드래곤");

    // 아이템 리스트 초기화
    Item* itemList = (Item*)malloc(sizeof(Item) * 3);

    strcpy_s(itemList[0].name, strlen(itemList[0].name), "천연 스테로이드");
    itemList[0].bonusDamage = 3;
    itemList[0].bonusDefense = 0;

    strcpy_s(itemList[1].name, strlen(itemList[1].name), "강철 방패");
    itemList[1].bonusDamage = 0;
    itemList[1].bonusDefense = 3;

    strcpy_s(itemList[2].name, strlen(itemList[2].name), "균형의 목걸이");
    itemList[2].bonusDamage = 2;
    itemList[2].bonusDefense = 1;

    char name[30];

    printf("플레이어 이름을 입력하세요: ");
    scanf_s("%s", name, sizeof(name));

    // 입력받은 이름으로 플레이어 초기화
    initPlayer(playerList[0], name);

    // 현재 스테이지를 나타내는 변수. 몬스터 처치 시 다음 스테이지(몬스터)로 이동
    int stage = 0;
    // 플레이어의 체력이 남아있고, 스테이지를 모두 통과하지 않은 동안 반복
    while (playerList[0]->hp > 0 && stage < 3) {
        printf("'%s' 몬스터가 나타났습니다! 몬스터 HP: %d, 몬스터 공격력: %d\n\n", monsterList[stage]->name, monsterList[stage]->hp, monsterList[stage]->damage);
        
        // 현재 스테이지의 몬스터와 플레이어의 체력이 모두 남아 있는 동안(전투가 끝나지 않은 동안) 반복
        while (monsterList[stage]->hp > 0 && playerList[0]->hp > 0) { 
            playerTurn(playerList[0], monsterList[stage], itemList, 0);
        }
        // 몬스터 또는 플레이어가 죽으면 다음 스테이지로 이동하며, 플레이어가 죽은 경우 바깥 반복문의 조건을 만족하지 못해 반복문 종료됨.
        stage++;
    }

    // 플레이어의 체력이 남아있는 경우
    if (playerList[0]->hp > 0) {
        printf("----------------------------------------------------------------------------------------------------------------------\n");
        printf("당신은 모든 몬스터를 처치하고 던전을 탈출했습니다!\n");
    }
    // 플레이어의 체력이 0인 경우
    else {
        printf("----------------------------------------------------------------------------------------------------------------------\n");
        printf("당신은 죽었습니다...\n");
        printf("탈출 실패...\n");
    }

    //*/

    //메모리 할당 해제
    for (int i = 0; i < 3; ++i) {
        free(monsterList[i]);
    }
    free(monsterList);
    free(playerList[0]);
    free(playerList);

    return 0;
}