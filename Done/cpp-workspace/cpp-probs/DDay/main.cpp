#include "DDay.h"
#include <string>
#include <cstdlib>

using namespace std;

const int BUFFER_SIZE = 9;

int main() {
	DDay currentDate;
	char input[BUFFER_SIZE];
    
	while (1) {
		cout << currentDate << endl;
		cout << "Move date(yyyymmdd, (tomorrow)+, (yesterday)-, set D-day(+/-int), Quit(Q/q)) : ";
		cin >> input;

		if (isdigit(input[0])) currentDate.setToday(input);
		else {
			if (!strcmp(input, "+")) {
                currentDate.setToday(++currentDate.getToday());
                currentDate.setDDate(currentDate.getDDay());
            } else if (!strcmp(input, "-")) {
                currentDate.setToday(--currentDate.getToday());
                currentDate.setDDate(currentDate.getDDay());
            } else if (!strcmp(input, "q") || !strcmp(input, "Q")) {
                break;
            } else {
 				int dday = atoi(input);
                currentDate.setDDate(dday);
			}
		}
	}
    cout << "=== END ===" << endl;
}
