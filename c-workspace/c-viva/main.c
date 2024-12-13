#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>

#define MAX_LINE_LENGTH 1024
#define MAX_LINES 1000

char *lines[MAX_LINES];
int num_lines = 0;
int cursor_row = 0;
int cursor_col = 0;
char search_term[MAX_LINE_LENGTH];

void init_editor();
void read_file(const char *filename);
void write_file(const char *filename);
void refresh_display();
void move_cursor(int direction);
void search_text(const char *term);
void process_input();
void cleanup();

int main(int argc, char *argv[]) {
    if (argc > 1) {
        read_file(argv[1]);
    }
    init_editor();
    process_input();
    cleanup();
    return 0;
}

void init_editor() {
    initscr();
    raw();
    keypad(stdscr, TRUE);
    noecho();
    curs_set(1);
    move(LINES - 2, 0);
    printw("파일 이름: 새 파일   라인 수: 0   커서 위치: 0, 0");
    refresh();
}

void read_file(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("파일 열기 실패");
        exit(1);
    }

    char buffer[MAX_LINE_LENGTH];
    while (fgets(buffer, sizeof(buffer), file)) {
        lines[num_lines] = strdup(buffer);
        num_lines++;
    }

    fclose(file);
}

void write_file(const char *filename) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        perror("파일 저장 실패");
        exit(1);
    }

    for (int i = 0; i < num_lines; i++) {
        fputs(lines[i], file);
    }

    fclose(file);
}

void refresh_display() {
    clear();
    for (int i = 0; i < num_lines; i++) {
        mvprintw(i, 0, "%s", lines[i]);
    }
    move(cursor_row, cursor_col);
    refresh();
}

void move_cursor(int direction) {
    if (direction == KEY_UP && cursor_row > 0) {
        cursor_row--;
    } else if (direction == KEY_DOWN && cursor_row < num_lines - 1) {
        cursor_row++;
    } else if (direction == KEY_LEFT && cursor_col > 0) {
        cursor_col--;
    } else if (direction == KEY_RIGHT && cursor_col < strlen(lines[cursor_row]) - 1) {
        cursor_col++;
    }
}

void search_text(const char *term) {
    for (int i = 0; i < num_lines; i++) {
        if (strstr(lines[i], term)) {
            mvprintw(LINES - 1, 0, "찾았습니다: %s", term);
            move(i, 0);
            break;
        }
    }
}

void process_input() {
    int ch;
    while ((ch = getch()) != EOF) {
        if (ch == 'q') {
            break;
        } else if (ch == KEY_UP || ch == KEY_DOWN || ch == KEY_LEFT || ch == KEY_RIGHT) {
            move_cursor(ch);
        } else if (ch == 10) {
            cursor_row++;
            if (cursor_row >= num_lines) {
                cursor_row = num_lines - 1;
            }
        } else if (ch == 4) {
            break;
        } else if (ch == 19) {
            write_file("output.txt");
        } else if (ch == 6) {
            search_text(search_term);
        } else {
            if (cursor_col < MAX_LINE_LENGTH - 1) {
                lines[cursor_row][cursor_col++] = (char)ch;
                lines[cursor_row][cursor_col] = '\0';
            }
        }

        refresh_display();
    }
}

void cleanup() {
    for (int i = 0; i < num_lines; i++) {
        free(lines[i]);
    }
    endwin();
}
