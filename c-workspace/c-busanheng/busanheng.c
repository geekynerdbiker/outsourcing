#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#pragma warning(disable:4996)

// 파라미터
#define LEN_MIN			15	// 기차 길이
#define LEN_MAX			50
#define PROB_MIN		10	// 확률
#define PROB_MAX		90

void intro() {
	char *intro[] = {
"",
" /$$$$$$$",
"| $$__  $$",
"| $$  \\ $$ /$$   /$$  /$$$$$$$  /$$$$$$  /$$$$$$$",
"| $$$$$$$ | $$  | $$ /$$_____/ |____  $$| $$__  $$",
"| $$__  $$| $$  | $$|  $$$$$$   /$$$$$$$| $$  \\ $$",
"| $$  \\ $$| $$  | $$ \\____  $$ /$$__  $$| $$  | $$",
"| $$$$$$$/|  $$$$$$/ /$$$$$$$/|  $$$$$$$| $$  | $$",
"|_______/  \\______/ |_______/  \\_______/|__/  |__/",
"",
"             /$$   /$$                               /$$",
"            | $$  | $$                              | $$",
"            | $$  | $$  /$$$$$$  /$$$$$$$   /$$$$$$ | $$",
"            | $$$$$$$$ /$$__  $$| $$__  $$ /$$__  $$| $$",
"            | $$__  $$| $$$$$$$$| $$  \\ $$| $$  \\ $$|__/",
"            | $$  | $$| $$_____/| $$  | $$| $$  | $$",
"            | $$  | $$|  $$$$$$$| $$  | $$|  $$$$$$$ /$$",
"            |__/  |__/ \\_______/|__/  |__/ \\____  $$|__/",
"                                           /$$  \\ $$",
"                                          |  $$$$$$/",
"                                           \\______/" };


	for (int i = 0; i < sizeof(intro) / sizeof(intro[0]); i++) {
		printf("%s\n", intro[i]);
		Sleep(100);
	}
	Sleep(1000);
}

void outro_success() {
	char* outro[] = {
"",
"  /$$$$$$$ /$$   /$$  /$$$$$$$  /$$$$$$$  /$$$$$$   /$$$$$$$ /$$$$$$$",
" /$$_____/| $$  | $$ /$$_____/ /$$_____/ /$$__  $$ /$$_____//$$_____/",
"|  $$$$$$ | $$  | $$| $$      | $$      | $$$$$$$$|  $$$$$$|  $$$$$$",
" \\____  $$| $$  | $$| $$      | $$      | $$_____/ \\____  $$\\____  $$",
" /$$$$$$$/|  $$$$$$/|  $$$$$$$|  $$$$$$$|  $$$$$$$ /$$$$$$$//$$$$$$$/",
"|_______/  \\______/  \\_______/ \\_______/ \\_______/|_______/|_______/"};

	for (int i = 0; i < sizeof(outro) / sizeof(outro[0]); i++) {
		printf("%s\n", outro[i]);
		Sleep(100);
	}
	Sleep(1000);
}

void outro_gameover() {
	char* outro[] = {
"",
"  /$$$$$$   /$$$$$$  /$$$$$$/$$$$   /$$$$$$",
" /$$__  $$ |____  $$| $$_  $$_  $$ /$$__  $$",
"| $$  \\ $$  /$$$$$$$| $$ \\ $$ \\ $$| $$$$$$$$",
"| $$  | $$ /$$__  $$| $$ | $$ | $$| $$_____/",
"|  $$$$$$$|  $$$$$$$| $$ | $$ | $$| $$$$$$$",
" \\____  $$ \\_______/|__/ |__/ |__ /\\_______/",
" /$$  \\ $$",
"|  $$$$$$/",
" \\______/",
"                   /$$$$$$  /$$    /$$ /$$$$$$   /$$$$$$",
"                  /$$__  $$|  $$  /$$//$$__  $$ /$$__  $$",
"                 | $$  \\ $$ \\  $$/$$/| $$$$$$$$| $$  \\__/",
"                 | $$  | $$  \\  $$$/ | $$_____/| $$",
"                 |  $$$$$$/   \\  $/  |  $$$$$$$| $$",
"                  \\______/     \\_/    \\_______/|__/"};

	for (int i = 0; i < sizeof(outro) / sizeof(outro[0]); i++) {
		printf("%s\n", outro[i]);
		Sleep(100);
	}
	Sleep(1000);
}

void print_train(int len, int C, int Z, int M) {
	for (int i = 0; i < len; i++)
		printf("#");
	printf("\n");

	for (int i = 0; i < len; i++) {
		if (i == 0 || i == len - 1)
			printf("#");
		else if (i == C)
			printf("C");
		else if (i == Z)
			printf("Z");
		else if (i == M)
			printf("M");
		else
			printf(" ");
	}
	printf("\n");

	for (int i = 0; i < len; i++)
		printf("#");
	printf("\n");
	printf("\n");
}

void print_status(int C, int C_move, int Z, int Z_move, int Z_turn) {
	if (C == C_move)
		printf("citizen: stay %d\n", C);
	else
		printf("citizen: %d -> %d\n", C, C_move);

	if (Z == Z_move) {
		if (Z_turn < 0)
			printf("zombie: stay %d (cannot move)\n", Z);
		else
			printf("zombie: stay %d\n", Z);
	} else
		printf("zombie: %d -> %d\n", Z, Z_move);
	printf("\n");
}

int move_citizen(int C, int p) {
	int r = rand() % 100;

	if (100 - p > r)
		return C - 1;
	return C;
}

int move_zombie(int Z, int p, int Z_turn) {
	if (Z_turn < 0)
		return Z;

	int r = rand() % 100;

	if (p > r)
		return Z - 1;
	return Z;
}

int is_gameover(int C, int Z) {
	if (C == 1)
		return 1;
	if (C == Z - 1)
		return -1;
	return 0;
}

int main(void) {
	// 인트로
	intro();

	int len, prob;
	printf("train length(15~50)>> ");
	scanf("%d", &len);

	if (len < LEN_MIN || len > LEN_MAX)
		return 0;

	printf("percentile probability 'p'(10~90)>> ");
	scanf("%d", &prob);

	if (prob < PROB_MIN || prob > PROB_MAX)
		return 0;

	// 열차 초기 상태 출력
	int C = len - 6, Z = len - 3, M = len - 2;
	print_train(len, C, Z, M);

	int result = 0;
	int C_move = C, Z_move = Z, Z_turn = 1;
	while (1) {
		// 시민 이동
		C_move = move_citizen(C, prob);

		// 좀비 이동
		Z_move = move_zombie(Z, prob, Z_turn);

		// 열차 상태 출력
		print_train(len, C_move, Z_move, M);

		// 시민, 좀비 상태 출력
		print_status(C, C_move, Z, Z_move, Z_turn);

		C = C_move;
		Z = Z_move;
		Z_turn *= -1;

		result = is_gameover(C, Z);
		if (result == 1) {
			printf("SUCCESS!\ncitizen(s) escaped to the next train\n");
			break;
		}
		else if (result == -1) {
			printf("GAME OVER!\nCitizen(s) has(have) been attacked by a zombie\n");
			break;
		}

		Sleep(4000);
	}

	// 아웃트로
	if (result == 1)
		outro_success();
	else
		outro_gameover();
}