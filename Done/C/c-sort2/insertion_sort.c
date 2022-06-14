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

void insertion_sort_asc(char *list[]) {
    int i, j;
    
    for (i = 1; i < SIZE; i++) {
        char* key = (char*)malloc(sizeof(char));
        strcpy(key, list[i]);
        for (j = i-1; j >= 0 && strcmp(to_lower(list[j]), to_lower(key)) > 0; j--) {
            list[j+1] = list[j];
        }
        list[j+1] = key;
    }
}

void insertion_sort_desc(char **list) {
    int i, j;
    
    for (i = 1; i < SIZE; i++) {
        char *key = (char*)malloc(sizeof(char));
        strcpy(key, list[i]);
        for (j = i-1; j >= 0 && strcmp(to_lower(list[j]), to_lower(key)) < 0; j--) {
            list[j+1] = list[j];
        }
        list[j+1] = key;
    }
}

void print_list(char *list[]) {
    for (int i=0; i < SIZE; i++) {
        if (i == SIZE - 1) printf("%s\n", list[i]);
        else printf("%s, ", list[i]);
    }
}

int main(int argc, const char *argv[]) {
    printf("INSERTION SORT\n");
    printf("------------------------------------------\n");
    printf("[Input String] : ");
    print_list(strings);
    
    printf("[Ascending order] : ");
    insertion_sort_asc(strings);
    print_list(strings);
    
    printf("[Descending order] : ");
    insertion_sort_desc(strings);
    print_list(strings);
    return 0;
}
