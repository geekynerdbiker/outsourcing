#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//#include<Windows.h>

#define BOARD_SIZE 20 // 땅 사이즈는 20으로 고정
#define GOLD 1 // 황금을 1로 설정
#define BOMB 2 // 폭탄을 2로 설정

//사용자의 차례 함수
//사용자의 위치, 가지고 있는 돈, 황금 땅의 위치를 배열로 받는 함수 작성
int YourTurn(int data[], int board[]) {
    int dice = -1; // 최초 실행시 주사위를 -1로 초기화
    while (dice > 6 || dice < 1) { // 주사위가 범위 안에 있는 동안 반복.
        if (dice != -1) // 최초 실행시 출력하지 않음
            printf("주사위의 수를 다시 입력해주세요.\n");
        printf("주사위의 수를 입력해주세요: ");
        scanf("%d", &dice);
    }

    if (data[0] + dice >= BOARD_SIZE) // 현재 칸에서 이동할 칸이 20을 넘을 경우
        data[0] = data[0] + dice - BOARD_SIZE;
    else // 일반적인 경우
        data[0] += dice;
    printf("당신은 %d번 땅에 도착했습니다.\n", data[0]);

    if (board[data[0]] == GOLD) { // 보드 위 사용자의 좌표가 황금일 경우
        data[1] += 100; // 현재 황금 +100
        printf("\n황금을 찾았습니다! +100만원\n");
        printf("보유 금액: 0 -> %d 만원", data[1]);
    } else if (board[data[0]] == BOMB) { // 보드 위 사용자의 좌표가 폭탄일 경우 1을 반환.
        printf("\n당신은 폭탄에 맞았습니다.\n");
        printf(" Game Over.\n");
        return 1;
    }

    return 0; // 통상적으로 0을 반환
}

//컴퓨터의 차례 함수
//컴퓨터의 위치, 가지고 있는 돈, 황금 땅의 위치를 배열로 받는 함수 작성
int ComputerTurn(int data[], int board[]) {
    int dice = rand() % 6 + 1; // 주사위를 rand() 함수를 통해 1~6 난수 생성
    printf("The computer rolled a %d!\n", dice);

    if (data[0] + dice >= BOARD_SIZE) // 현재 칸에서 이동할 칸이 20을 넘을 경우
        data[0] = data[0] + dice - BOARD_SIZE;
    else // 일반적인 경우
        data[0] += dice;
    printf("Computer은 %d번 땅에 도착했습니다.\n", data[0]);

    // 사용자 함수와 동일
    if (board[data[0]] == GOLD) {
        data[1] += 100;
        printf("\nComputer가 황금을 찾았습니다! +100만원\n");
        printf("보유 금액: 0 -> %d 만원", data[1]);
    } else if (board[data[0]] == BOMB) {
        printf("\nComputer가 폭탄에 맞았습니다.\n");
        printf(" Game Over.\n");
        return 1;
    }

    return 0;
}

int main(void) {
    printf("중간프로젝트 Problem 3\n");
    printf("학 번:202320000 , 이름: 김00\n\n");

    printf("============= 황금 땅 찾기 게임 =============\n");
    printf(" 게임 진행 중 황금 땅에 도착하면 +100만원 지급\n");
    printf(" 5 라운드 후에 보유한 금액이 더 많은 플레이어가 승리합니다.\n");

    // 땅의 크기만큼 보드 0으로 초기화
    int board[BOARD_SIZE] = { 0 };
    // 황금 3개와 폭탄의 좌표를 저장할 배열
    int card[4];

    // 랜덤 시드 생성
    srand((unsigned int)time(NULL));

    // 황금과 폭탄의 좌표를 난수로 생성하되, 중복되지 않게 검사하며 생성
    for (int i = 0; i < 4; i++) {
        card[i] = (rand() % BOARD_SIZE) + 1;

        for (int j = 0; j < i; j++)
            if (card[i] == card[j])
                i--;
    }

    // 황금 3개를 보드에 GOLD로 마킹
    for (int i = 0; i < 3; i++)
        board[card[i]] = GOLD;
    // 폭탄을 보드에 BOMB로 마킹
    board[card[3]] = BOMB;

    // 플레이어와 컴퓨터의 데이터를 저장. 순서대로 좌표, 보유 재산
    int data_player[2] = { 0 };
    int data_computer[2] = { 0 };

    // 라운드와 승자를 나타내기 위한 변수
    int round = 1, winner = 0;

    // 라운드 5회간 진행
    while (round <= 5) {
        // 플레이어 차례
        printf("\n============ ROUND %d ===========\n", round);

        printf("[Your turn]\n");
        int reward_player = YourTurn(data_player, board);
        // 만약 차례에서 폭탄을 밟고 1을 반환했다면 게임 즉시 종료.
        if (reward_player) {
            winner = -2;
            break;
        }
//        Sleep(1000);


        printf("\n[Computer's turn]\n");
        int reward_computer = ComputerTurn(data_computer, board);
        // 만약 차례에서 폭탄을 밟고 1을 반환했다면 게임 즉시 종료.
        if (reward_computer) {
            winner = -1;
            break;
        }
//        Sleep(1000);

        printf("\n=================================\n");

        printf("\n========== %d ROUND 결과 =========\n", round++);
        printf("- Your position: %d번 땅, money: %d 만원\n\n", data_player[0], data_player[1]);
        printf("- Computer's position: %d번 땅, money: %d 만원\n\n", data_computer[0], data_computer[1]);
    }

    // 폭탄을 밟고 종료시
    if (winner == -1) {
        printf("You Win!\n\n");
    } else if (winner == -2) {
        printf("Computer Wins!\n\n");
    } else { // 폭탄을 밟지 않고 정상적인 종료시
        printf("\n================= GAME OVER ================\n");
        printf(" Total money: Computer %d 만원 vs. You %d 만원\n", data_computer[1], data_player[1]);

        if (data_player[1] > data_computer[1]) {
            printf("You Win!\n\n");
        } else if (data_player[1] < data_computer[1]) {
            printf("Computer Wins!\n\n");
        } else
            printf("무승부 입니다.\n\n");
    }

    return 0;
}
