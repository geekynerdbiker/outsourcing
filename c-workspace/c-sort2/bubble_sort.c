#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SIZE 20

char *strings[SIZE] = {"Delaware", "Pennsylvania", "New Jersey", "Georgia", "Kansas", "Massachusetts", "Nevada", "South Carolina", "New Hampshire", "Virginia", "New York", "Texas", "Florida", "Michigan", "Wisconsin", "California", "Colorado", "Utah", "Oklahoma", "Kentucky"};

char * to_lower(char *word) {
    char* converted = (char *)malloc(sizeof(char));
    
    for (int i = 0; i < strlen(word); i++) {
        if (word[i] >= 'A' && word[i] <= 'Z')
            converted[i] = word[i] + 32;
        else converted[i] = word[i];
    }
    return converted;
}

void bubble_sort_asc(char **list) {
    int i, j;

    char *temp;
    for (i = 0; i < SIZE - 1; i++) {
        for (j = 0; j < SIZE - 1 - i; j++) {
            if (strcmp(to_lower(list[j]), to_lower(list[j+1])) > 0) {
                temp = list[j];
                list[j] = list[j+1];
                list[j+1] = temp;
            }
        }
    }
}

void bubble_sort_desc(char *list[]) {
    int i, j;

    char *temp;
    for (i = 0; i < SIZE - 1; i++) {
        for (j = 0; j < SIZE - 1 - i; j++) {
            if (strcmp(to_lower(list[j]), to_lower(list[j+1])) < 0) {
                temp = list[j];
                list[j] = list[j+1];
                list[j+1] = temp;
            }
        }
    }
}

void print_list(char *list[]) {
    for (int i=0; i < SIZE; i++) {
        if (i == SIZE - 1) printf("%s\n", list[i]);
        else printf("%s, ", list[i]);
    }
}

int main(int argc, const char *argv[]) {
    printf("BUBBLE SORT\n");
    printf("------------------------------------------\n");
    printf("[Input String] : ");
    print_list(strings);
    
    printf("[Ascending order] : ");
    bubble_sort_asc(strings);
    print_list(strings);
    
    printf("[Descending order] : ");
    bubble_sort_desc(strings);
    print_list(strings);
    return 0;
}
