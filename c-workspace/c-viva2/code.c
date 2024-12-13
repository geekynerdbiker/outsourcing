#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>

#define MAX_TEXT_LENGTH 1024
#define MAX_ROWS 500

typedef struct {
    char *content;
    int size;
} TextRow;

TextRow text_buffer[MAX_ROWS];
int total_rows = 0;
int cursor_line = 0;
int cursor_pos = 0;
char *current_file = NULL;

void init_ui();
void load_document(const char *filepath);
void save_document(const char *filepath);
void process_keyboard_input();
void update_screen();
void move_cursor_based_on_key(int key);
void add_char_to_line(char character);
void remove_char_from_line();
void cleanup_resources();
void show_footer_info();
void insert_new_line();

int main(int argc, char *argv[]) {
    if (argc > 1) {
        current_file = argv[1];
        load_document(current_file);
    }

    init_ui();
    process_keyboard_input();
    cleanup_resources();
    return 0;
}

void init_ui() {
    initscr();
    raw();
    keypad(stdscr, TRUE);
    noecho();
    curs_set(0);
    show_footer_info();
}

void load_document(const char *filepath) {
    FILE *file = fopen(filepath, "r");
    if (!file) {
        perror("Failed to open file");
        exit(1);
    }

    char buffer[MAX_TEXT_LENGTH];
    while (fgets(buffer, sizeof(buffer), file)) {
        text_buffer[total_rows].content = strdup(buffer);
        text_buffer[total_rows].size = strlen(buffer);
        total_rows++;
    }

    fclose(file);
}

void save_document(const char *filepath) {
    FILE *file = fopen(filepath, "w");
    if (!file) {
        perror("Failed to save file");
        exit(1);
    }

    for (int i = 0; i < total_rows; i++) {
        fputs(text_buffer[i].content, file);
    }

    fclose(file);
}

void process_keyboard_input() {
    int key;
    while ((key = getch()) != EOF) {
        switch (key) {
            case 'q':
                return;
            case 's':
                if (current_file) {
                    save_document(current_file);
                }
                break;
            case KEY_UP:
            case KEY_DOWN:
            case KEY_LEFT:
            case KEY_RIGHT:
                move_cursor_based_on_key(key);
                break;
            case 127:  // Backspace key
                remove_char_from_line();
                break;
            case 10:  // Enter key
                insert_new_line();
                break;
            default:
                add_char_to_line((char)key);
        }

        update_screen();
    }
}

void update_screen() {
    clear();
    for (int i = 0; i < total_rows; i++) {
        mvprintw(i, 0, "%s", text_buffer[i].content);
    }

    move(cursor_line, cursor_pos);
    refresh();
    show_footer_info();
}

void move_cursor_based_on_key(int key) {
    if (key == KEY_UP && cursor_line > 0) {
        cursor_line--;
    } else if (key == KEY_DOWN && cursor_line < total_rows - 1) {
        cursor_line++;
    } else if (key == KEY_LEFT && cursor_pos > 0) {
        cursor_pos--;
    } else if (key == KEY_RIGHT && cursor_pos < text_buffer[cursor_line].size - 1) {
        cursor_pos++;
    }
}

void add_char_to_line(char character) {
    TextRow *current_row = &text_buffer[cursor_line];
    if (current_row->size < MAX_TEXT_LENGTH - 1) {
        memmove(&current_row->content[cursor_pos + 1], &current_row->content[cursor_pos], current_row->size - cursor_pos);
        current_row->content[cursor_pos] = character;
        current_row->size++;
        cursor_pos++;
    }
}

void remove_char_from_line() {
    TextRow *current_row = &text_buffer[cursor_line];
    if (cursor_pos > 0) {
        memmove(&current_row->content[cursor_pos - 1], &current_row->content[cursor_pos], current_row->size - cursor_pos);
        current_row->size--;
        cursor_pos--;
    }
}

void cleanup_resources() {
    for (int i = 0; i < total_rows; i++) {
        free(text_buffer[i].content);
    }
    endwin();
}

void show_footer_info() {
    move(LINES - 1, 0);
    printw("파일 이름: %s   라인: %d   커서 위치: %d, %d", current_file ? current_file : "새 파일", total_rows, cursor_line, cursor_pos);
    refresh();
}

void insert_new_line() {
    cursor_line++;
    if (cursor_line >= total_rows) {
        cursor_line = total_rows - 1;
    }
}
