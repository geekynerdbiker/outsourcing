#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern char *lines[];
extern int num_lines;
extern int cursor_row;
extern int cursor_col;

void insert_text(int row, int col, const char *text) {
    if (row >= 0 && row < num_lines) {
        int len = strlen(lines[row]);
        if (col <= len) {
            memmove(&lines[row][col + strlen(text)], &lines[row][col], len - col + 1);
            memcpy(&lines[row][col], text, strlen(text));
        }
    }
}

void delete_text(int row, int col, int length) {
    if (row >= 0 && row < num_lines) {
        int len = strlen(lines[row]);
        if (col < len) {
            memmove(&lines[row][col], &lines[row][col + length], len - col - length + 1);
        }
    }
}
