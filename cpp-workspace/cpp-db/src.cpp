//#include <mysql.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)

/*
Change this part to connect to mysql server
*/

#define HOST "localhost"
#define USER "root"
#define PWD "-awawa45097"
#define DB "cheil_hospital"

/*
Change this part to connect to mysql server
*/

#define VARCHAR_SIZE 50

MYSQL mysql;

void sign_up();
void sign_in();

void user_view(char* ID); // Show menu to user after sign in
void check_reservations(char* ID); // Get reservations list of user
void make_reservations(char* ID); // Make reservations
void pay_reservations(char* ID); // Update payment status of reservations

char* is_exist(char* ID);

typedef struct user {
	char user_id[50];
	char payment_id[50];
	char name[50];
	char age[50];
	char user_tel[50];
	char email[50];
	char password[50];
} User;

int main(void) {
	int command;

	while (1) {
		mysql_init(&mysql);
		if (!mysql_real_connect(&mysql, HOST, USER, PWD, DB, 3306, NULL, 0)) {
			printf("Connection Failed\n");
		}
		else {
			printf("1: Sign In\n");
			printf("2: Sign Up\n");
			printf("3: Quit \n");
			printf("Select Menu: ");
			scanf("%d", &command);

			switch (command) {
			case 1:
				system("cls");
				sign_in();
			case 2:
				sign_up();
				break;
			default:
				exit(1);
			}
		}
	}

	mysql_close(&mysql);
	return 0;
}

void sign_up(void) {
	char ch;
	char* qry = (char*)malloc(sizeof(char) * 50);;
	char qry_END[150];

	int qry_user_id;
	char qry_password[50];
	int qry_payment_id;
	char qry_name[50];
	char qry_user_tel[50];
	char qry_email[50];
	int qry_age;

	printf("Enter ID: ");
	scanf("%d", &qry_user_id);

	printf("Enter Password: ");
	scanf("%s", qry_password);

	printf("Enter Payment ID: ");
	scanf("%d", &qry_payment_id);

	printf("Enter Name: ");
	scanf("%s", qry_name);

	printf("Enter Tel: ");
	scanf("%s", qry_user_tel);

	printf("Enter E-mail: ");
	scanf("%s", qry_email);

	printf("Enter Age: ");
	scanf("%d", &qry_age);


	strcpy(qry, "insert patient values(");

	sprintf(qry_END, "%s%d, %d, '%s', %d, '%s', '%s', '%s')", qry, qry_user_id, qry_payment_id, qry_name, qry_age, qry_user_tel, qry_email, qry_password);
	printf("%s", qry_END);

	if (mysql_real_query(&mysql, qry_END, strlen(qry_END))) {
		printf("send query err");
	}

	printf("Press 'X' to Continue.");
	while (1) {
		scanf("%c", &ch);
		if (ch == 'x') {
			system("cls");
			break;
		}
	}
}

void sign_in(void) {
	char* compare_ID;
	char* ID;

	while (1) {

		system("cls");

		compare_ID = (char*)malloc(sizeof(char) * 50);
		ID = (char*)malloc(sizeof(char) * 50);

		printf("Enter ID : ");

		scanf("%s", ID);
		compare_ID = is_exist(ID);

		if (strcmp(ID, "0") != 0) {
			printf("No such ID exist.\n");
			break;
		}
	}

	system("cls");
	user_view(ID);
}

void user_view(char* ID) {
	int command;

	char ch;
	char* qry = (char*)malloc(sizeof(char) * 50);
	char qry_END[150];

	while (1) {
		printf("1: Check my reservations\n");
		printf("2: Make reservations\n");
		printf("3: Pay for reservations\n\n");
		printf("Select Menu: ");
		scanf("%d", &command);
		switch (command) {
		case 1:
			system("cls");
			check_reservations(ID);
			break;
		case 2:
			system("cls");
			make_reservations(ID);
			break;
		case 3:
			system("cls");
			pay_reservations(ID);
			break;
		default:
			exit(1);
		}

	}
}

void check_reservations(char* ID) {
	char ch;
	char* qry = (char*)malloc(sizeof(char) * 50);
	char qry_END[150];

	strcpy(qry, "select price, date, time, station_name, seat_id from reservation where user_id =");

	sprintf(qry_END, "%s %s", qry, ID);
	printf("%s\n", qry_END);

	if (mysql_real_query(&mysql, qry, strlen(qry))) {
		printf("send query err");
	}

	MYSQL_RES* res = mysql_store_result(&mysql);
	MYSQL_ROW row;

	system("cls");
	printf("|Resvertaion ID\t|Price\t|Date\t|Time\t|Station\t\t|Seat\t|\n");

	while (row = mysql_fetch_row(res))
		printf("|\%s\t|\t%s\t|\t%s\t|\t%s\t|\t%s\t|\n", row[0], row[1], row[2], row[3], row[4]);

	printf("Press 'X' to Continue.");
	while (1) {
		scanf("%c", &ch);
		if (ch == 'x') {
			system("cls");
			break;
		}
	}
}

void make_reservations(char* ID) {
	char ch;
	char* qry = (char*)malloc(sizeof(char) * 50);
	char qry_END[150];

	char* qry_station_list = (char*)malloc(sizeof(char) * 50);
	char* qry_seat_list = (char*)malloc(sizeof(char) * 50);

	char qry_station[50];
	int qry_date;
	int qry_time;
	int qry_seat;

	strcpy(qry_station_list, "select station_name from station");
	if (mysql_real_query(&mysql, qry, strlen(qry)))
		printf("send query err");

	MYSQL_RES* res = mysql_store_result(&mysql);
	MYSQL_ROW row;

	while (row = mysql_fetch_row(res))
		printf("STATION %s", row[0]);
	printf("Select Station : ");
	scanf("%s", qry_station);

	printf("Select Date :");
	scanf("%d", &qry_date);

	printf("Select Time :");
	scanf("%d", &qry_time);

	strcpy(qry_seat_list, "select seat_num, seat_available from seat");
	if (mysql_real_query(&mysql, qry, strlen(qry)))
		printf("send query err");

	while (row = mysql_fetch_row(res))
		printf("SEAT NUMBER : %d \t %d available", row[0], row[1]);
	printf("Select Seat :");
	scanf("%d", &qry_seat);

	strcpy(qry, "insert reservation values(");

	sprintf(qry_END, "%s, , %d, %d, %s, '%s', %d, %d)", qry, qry_date, qry_time, ID, qry_station, ID, qry_seat);
	printf("%s\n", qry_END);
	if (mysql_real_query(&mysql, qry_END, strlen(qry_END))) {
		printf("send query err");
	}

	printf("Reservation is made successfully.\n");
	printf("Press 'X' to Continue.");
	while (1) {
		scanf("%c", &ch);
		if (ch == 'x') {
			system("cls");
			break;
		}
	}
}

void pay_reservations(char* ID) {
	char ch;
	char* qry = (char*)malloc(sizeof(char) * 50);
	char qry_END[200];

	char* qry_reservation_id = (char*)malloc(sizeof(char) * 50);

	printf("Input reservation ID: ");
	scanf("%s", qry_reservation_id);

	strcpy(qry, "update payment setpayment_type =");

	sprintf(qry_END, "%s %s where reservation_id = %s", qry, "paid", qry_reservation_id);
	printf("%s\n", qry_END);
	if (mysql_real_query(&mysql, qry_END, strlen(qry_END)))
		printf("send query err");

	printf("Payment status updated successfully.\n");
	printf("Press 'X' to Continue.");
	while (1) {
		scanf("%c", &ch);
		if (ch == 'x') {
			system("cls");
			break;
		}
	}
}

char* is_exist(char* ID) {
	char none[2] = "0";
	int row_length;

	char* qry = (char*)malloc(sizeof(char) * 50);
	strcpy(qry, "select user_id from user");

	if (mysql_real_query(&mysql, qry, strlen(qry)))
		printf("send query err");

	MYSQL_RES* res = mysql_store_result(&mysql);
	MYSQL_ROW row;

	row_length = mysql_num_fields(res);

	while (row = mysql_fetch_row(res)) {
		for (int i = 0; i < row_length; i++) {
			if (strcmp(ID, row[i]) == 0)
				return row[i];
		}
	}
	mysql_free_result(res);

	return none;
}