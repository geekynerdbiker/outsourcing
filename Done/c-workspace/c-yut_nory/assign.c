#pragma warning(disable:4996)

#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#define ROW 7
#define COL 7

#define LEN 20

#define USER_TURN 0
#define COMP_TURN 1

int available; 
int map[ROW][COL];


void roll();
int is_shortcut_available(int* pos, int* shortcut);
void using_shortcut(int* pos, int* shortcut);
int back_shortcut();
int is_catch_available();

int main()
{
	printf("중간 프로젝트\n");
	printf("학번: 2024xxxxx, 이름: 고준환\n\n");

	int cmd, turn = 0;
	int user_pos = 0, comp_pos = 0;
	int user_shortcut = 0, comp_shortcut = 0;

	while (1) {
		available = 0;
		printf("====================================================================\n");
		if (turn == USER_TURN) {
			printf("당신의 차례입니다!\n");
			printf("윷을 던지려면 1을 입력하세요! ");

			scanf(" %d", &cmd);
			if (cmd == 1)
				roll();

			printf("이동할 수 있는 칸 수는 %d칸 입니다!\n", available);
			using_shortcut(&user_pos, &user_shortcut);
			if (available < 0) {
				printf("당신 말이 이동한 칸수는 0 입니다.\n");
				continue;
			}
			printf("당신 말이 이동한 칸수는 %d 입니다.\n", available);
			user_pos -= available;

			if (is_catch_available()) {
				continue;
			}

			printf("완주까지 %d칸 남았습니다.\n", LEN - user_pos);
			turn = COMP_TURN;
		}
		else {
			;
		}
	}
}

void roll() { 
	srand((unsigned)time(NULL));
	int result = rand() % 6;

	int cmd;
	if (result == 1) {
		printf("도가 나왔습니다!\n");
		available += 1;
	}
	else if (result == 2) {
		printf("개가 나왔습니다!\n");
		available += 2;
	}
	else if (result == 3) {
		printf("걸이 나왔습니다!\n");
		available += 3;
	}
	else if (result == 4) {
		printf("윷이 나왔습니다! 1을 입력하면 한번 더 던집니다! ");
		available += 4;

		scanf(" %d", &cmd);
		if (cmd == 1)
			roll();
	}
	else if (result == 5) {
		printf("모가 나왔습니다! 1을 입력하면 한번 더 던집니다! ");
		available += 5;

		scanf(" %d", &cmd);
		if (cmd == 1)
			roll();
	}
	else if (result == 0) {
		printf("빽도가 나왔습니다!\n");
			available -= 1;
	}
}

int is_shortcut_available(int* pos, int* shortcut) {
	if (*pos == 5)
		return 1;
	if (*pos == 10 && *shortcut == 0)
		return 1;
	if (*pos == 12 && *shortcut == 1)
		return 1;
	return 0; 
}

void using_shortcut(int* pos, int* shortcut) { 
	if (is_shortcut_available(pos, shortcut))
		return;
	
	if (available == -1)
		return;

	printf("지름길을 이용합니다!\n");
	shortcut++;
	printf("현재 지름길 이용횟수: %d\n", shortcut);
	if (*pos == 5) {
		*pos -= 4;
	}
	else if (*pos == 10) {
		*pos -= 4;
	}
	else if (*pos == 12) {
		*pos -= 5;
	}
}

int back_shortcut() { return 0; }
int is_catch_available(int turn, int user_pos, int comp_pos) { 
	if (turn == USER_TURN) {
		if (user_pos + available == comp_pos)
			return 1;
	}
	else {
		if (comp_pos + available == user_pos)
			return 1;
	}
	
	return 0; 
}