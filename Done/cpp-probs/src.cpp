#include <stdio.h>
#include <stdlib.h>
#include <windows.h>  // srand, rand, Sleep, system
#include <time.h>  // time

#define SPEED 2 // m per sec
#define HEIGHT 3 // m
#define DOOR_MOVING_TIME 3 // sec
#define ELEVATOR_WAIT_TIME 10 // sec

typedef struct elevator
{
	short floor;
	short height;
	short currentUser = 0;
} Elevator;

Elevator elv;

int routine(int input);
void door_routine();
void user_move();
void print_current();
void print_user();

int main() // 엘리베이터 초기화 후 반복문 실행
{
	int input;
	int result = 1;

	memset(&elv, 0, sizeof(Elevator));

	srand(time(0));

	elv.floor = rand() % 25 - 2;
	elv.currentUser = rand() % 10;

	if (elv.floor > 0)
		elv.height = (elv.floor - 1) * HEIGHT;
	else {
		elv.floor--;
		elv.height = elv.floor * HEIGHT;
	}

	print_current();

	while (1)
	{
		printf("Input floor to move: ");
		scanf_s("%d", &input);

		if (input > 25) input = 25;
		else if (input < -2) input = -2;
		else if (input == 0) break;

		elv.floor = routine(input);
		if (elv.floor > 0) elv.height = (elv.floor - 1) * HEIGHT;
		else elv.height = elv.floor * HEIGHT;

		printf("Arrived at [%d floor]\n", elv.floor);
		print_current();
		door_routine();
	}
	return 0;
}

int routine(int input) // 입력받은 층 만큼 엘리베이터가 이동
{
	while (1)
	{
		printf("[%d floor]\n", elv.floor);
		Sleep(1000 * HEIGHT / SPEED);
		if (elv.floor == input) break;

		elv.floor < input ? elv.floor++ : elv.floor--;
		if (elv.floor == 0) elv.floor < input ? elv.floor++ : elv.floor--;
	}
	return elv.floor;
}

void door_routine() { // 문이 열리고 대기했다가 닫히는 시나리오
	printf("The door is opening.\n");
	Sleep(1000 * DOOR_MOVING_TIME);
	printf("The door opened.\n");
	Sleep(1000 * ELEVATOR_WAIT_TIME);
	user_move();
	printf("The door is closing.\n");
	Sleep(1000 * DOOR_MOVING_TIME);
	printf("The door closed.\n");
	Sleep(1000);
	system("cls");
}

void user_move() { // 층을 이동할 때 마다 승객을 랜덤하게 태우거나 내려보냄
	elv.currentUser += rand() % 3 - 6;
	if (elv.currentUser < 0) elv.currentUser = 0;

	print_user();
	if (elv.currentUser > 10) {
		printf("The elevator is full. Please use next elevator.\n");
		elv.currentUser = 10;
		print_user();
	}
}

void print_current() { // 현재 층과 지상으로부터의 높이를 출력
	Sleep(1000);
	system("cls");
	printf("-------------------------------------------------\n");
	printf("Current location : %d floor \n", elv.floor);
	printf("Height is %dm\n", elv.height);
	print_user();
	printf("-------------------------------------------------\n");
}

void print_user() { // 현재 탑승객 수 출력
	if (elv.currentUser > 1) printf("There are %d people in the elevator.\n", elv.currentUser);
	else if (elv.currentUser == 1) printf("There is 1 person in the elevator.\n");
	else printf("There is no person in the elevator.\n");
}
