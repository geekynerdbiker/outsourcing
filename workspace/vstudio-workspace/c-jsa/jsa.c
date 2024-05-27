#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <Windows.h>

#define CANVAS_ROW 20
#define CANVAS_COL 60

char front_buf[CANVAS_ROW][CANVAS_COL];
char back_buf[CANVAS_ROW][CANVAS_COL];

bool enemies[6] = { false };
int enemies_coord[6][2];
int remain;

void gotoxy(int row, int col) {
	COORD pos = { col,row };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void printxy(char ch, int row, int col) {
	gotoxy(row, col);
	printf("%c", ch);
}

void init_canvas() {
	for (int row = 0; row < CANVAS_ROW; row++) {
		for (int col = 0; col < CANVAS_COL; col++) {
			if (row == 0 || row == CANVAS_ROW - 1 || col == 0 || col == CANVAS_COL - 1) {
				back_buf[row][col] = '#';
			} else {
				back_buf[row][col] = ' ';
			}
		}
	}
}

void draw() {
	for (int row = 0; row < CANVAS_ROW; row++) {
		for (int col = 0; col < CANVAS_COL; col++) {
			if (front_buf[row][col] != back_buf[row][col]) {
				front_buf[row][col] = back_buf[row][col];
				printxy(front_buf[row][col], row, col);
			}
		}
	}
}

void display(int t) {
	draw();

	if (t >= 0) {
		gotoxy(CANVAS_ROW + 1, 13);
		printf("%.1lf", (double)((15000 - t)/10000.0));
	}
	gotoxy(CANVAS_ROW + 2, 0);
}

void set_title() {
	gotoxy(6, 19);
	printf("[ 공동 경비 구역 JSA ]");
	gotoxy(10, 7);
	printf("북한군이 등장했을 때 최대한 빨리 반응하세요!");
	gotoxy(12, 18);
	printf("조작법: 키패드 숫자 1~6번");
	gotoxy(CANVAS_ROW + 2, 0);
	printf("스페이스 바 키를 누르면 게임을 시작합니다.");
}

void remove_title() {
	gotoxy(6, 19);
	printf("                      ");
	gotoxy(10, 7);
	printf("                                            ");
	gotoxy(12, 18);
	printf("                         ");
	gotoxy(CANVAS_ROW + 2, 0);
	printf("                                          ");
}

void draw_map() {
	for (int row = 2; row < 7; row++) {
		for (int col = 15; col < CANVAS_COL - 15; col++) {
			if (row == 2 || row == 6 || col == 15 || col == CANVAS_COL - 16) {
				back_buf[row][col] = '#';
			}
			else {
				back_buf[row][col] = ' ';
			}
		}
	}

	for (int row = 8; row < 14; row++) {
		for (int col = 8; col < 12; col++) {
			if (row == 8 || row == 13 || col == 8 || col == 11) {
				back_buf[row][col] = '#';
			}
			else {
				back_buf[row][col] = ' ';
			}
		}

		for (int col = 15; col < 19; col++) {
			if (row == 8 || row == 13 || col == 15 || col == 18) {
				back_buf[row][col] = '#';
			}
			else {
				back_buf[row][col] = ' ';
			}
		}

		for (int col = 22; col < 26; col++) {
			if (row == 8 || row == 13 || col == 22 || col == 25) {
				back_buf[row][col] = '#';
			}
			else {
				back_buf[row][col] = ' ';
			}
		}

		for (int col = 29; col < 33; col++) {
			if (row == 8 || row == 13 || col == 29 || col == 32) {
				back_buf[row][col] = '#';
			}
			else {
				back_buf[row][col] = ' ';
			}
		}

		for (int col = 36; col < 40; col++) {
			if (row == 8 || row == 13 || col == 36 || col == 39) {
				back_buf[row][col] = '#';
			}
			else {
				back_buf[row][col] = ' ';
			}
		}

		for (int col = 43; col < 47; col++) {
			if (row == 8 || row == 13 || col == 43 || col == 46) {
				back_buf[row][col] = '#';
			}
			else {
				back_buf[row][col] = ' ';
			}
		}

		for (int col = 50; col < 54; col++) {
			if (row == 8 || row == 13 || col == 50 || col == 53) {
				back_buf[row][col] = '#';
			}
			else {
				back_buf[row][col] = ' ';
			}
		}
	}

	for (int row = 15; row < 18; row++) {
		for (int col = 15; col < CANVAS_COL - 15; col++) {
			if (row == 15 || row == 17 || col == 15 || col == CANVAS_COL - 16) {
				back_buf[row][col] = '#';
			}
			else {
				back_buf[row][col] = ' ';
			}
		}
	}

	gotoxy(4, 25);
	printf("판  문  각");

	gotoxy(16, 26);
	printf("자유의 집");
}

void set_phase(int i) {
	srand((unsigned)time(NULL));

	gotoxy(CANVAS_ROW + 1, 0);
	printf("[ Phase %d ]", i);

	for (int k = 0; k < i; k++) {
		int e = rand() % 6;
		while (enemies[e])
			e = rand() % 6;
		enemies[e] = true;

		int enemy_row = rand() % 4 + 9;
		int enemy_col = 13 + 7 * e;

		enemies_coord[e][0] = enemy_row;
		enemies_coord[e][1] = enemy_col;
	}
	remain = i;

	for (int k = 0; k < 6; k++) {
		int enemy_row = enemies_coord[k][0];
		int enemy_col = enemies_coord[k][1];

		if (enemies[k]) {
			back_buf[enemy_row][enemy_col] = '*';
		}
	}

	gotoxy(CANVAS_ROW + 2, 0);
}

bool shoot(int i) {
	if (enemies[i]) {
		enemies[i] = false;

		int enemy_row = enemies_coord[i][0];
		int enemy_col = enemies_coord[i][1];
		back_buf[enemy_row][enemy_col] = ' ';

		enemies_coord[i][0] = 0;
		enemies_coord[i][1] = 0;
		remain--;
	}

	if (remain == 0)
		return true;
	return false;
}

void draw_result(bool state) {
	gotoxy(4, 25);
	printf("          ");

	gotoxy(16, 26);
	printf("         ");

	gotoxy(10, 28);
	if (state)
		printf("승리!");
	else
		printf("패배.");
	gotoxy(CANVAS_ROW + 2, 0);
}

int main() {
	int tick = 0;
	int phase = 1;
	bool win = false;

	init_canvas();
	display(-1);
	set_title();

	while (1) {
		if (_kbhit()) {
			char key = getch();

			if (key == ' ')
				break;
		}
	}

	remove_title();
	draw_map();
 	set_phase(phase);
	phase++;

	display(tick);
	Sleep(1000);

	while (1) {
		display(tick);
		tick++;

		if (_kbhit()) {
			char key = getch();

			if (key >= '1' && key <= '6')
				if (shoot(key - '1')) {
					if (phase == 4) {
						win = true;
						break;
					}
					set_phase(phase);
					phase++;

					tick = 0;
					Sleep(1000);
				}

			
		}

		if (tick == 15000)
			break;
	}

	init_canvas();
	display(-1);
	draw_result(win);

	return 0;
}