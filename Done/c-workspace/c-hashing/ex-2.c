#define TABLE_SIZE 541
#define NAME_SIZE 10
#define EMPTY 0
#define FALSE 0
#define TRUE 1

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

struct hash {
    char name[NAME_SIZE];
    unsigned short collision;
};

struct hash hash_table[TABLE_SIZE];

int hash1(char str[]) {
    int i, h;
    
    for (i = 0, h = 0; i < strlen(str); i++) {
        h = ((int)str[i] + h) % TABLE_SIZE;
    }
    
    return h;
}

int hash2(char str[], int random_values[]) {
    int i, h;
    
    for (i = 0, h = 0; i < strlen(str); i++) {
        h = (str[i] + h) * random_values[i] % TABLE_SIZE;
    }
    
    return h;
}

int hash_insert(char name[]) {
    int number = 0;
    int key = hash1(name);
    
    while (strcmp(hash_table[key].name, "") != 0) {
        hash_table[key].collision++;
        number++;
        key = (number + key) % TABLE_SIZE;
    }
    strcpy(hash_table[key].name, name);
    
    return 0;
}

void initialize_table() {
    int i;
    
    for (i = 0; i < TABLE_SIZE; i++) {
        strcpy(hash_table[i].name, "");
        hash_table[i].collision = 0;
    }
}

int hash_insert1(char name[]) {
    int number = 0;
    int key = hash1(name);
    
    while (strcmp(hash_table[key].name, "") != 0) {
        hash_table[key].collision++;
        number++;
        key = (number + key) % TABLE_SIZE;
    }
    strcpy(hash_table[key].name, name);
    
    return 0;
}


int hash_insert2(char name[], int random_values[]) {
    int number = 0;
    int key = hash2(name, random_values);
    
    while (strcmp(hash_table[key].name, "") != 0) {
        hash_table[key].collision++;
        number++;
        key = (number + key) % TABLE_SIZE;
    }
    strcpy(hash_table[key].name, name);
    
    return 0;
}


int main() {
    initialize_table();

    FILE *fp = fopen("names.txt", "r");
    if (fp == NULL) {
        printf("names.txt 파일을 열 수 없습니다.\n");
        return -1;
    }
    
    char name[NAME_SIZE];
    while (fgets(name, NAME_SIZE, fp) != NULL) {
        hash_insert1(name);
    }
    fclose(fp);

    for (int i = 0; i < TABLE_SIZE; i++) {
        if (strcmp(hash_table[i].name, "") == 0)
            printf("table[%d]: EMPTY\t%d\n", i, hash_table[i].collision);
        else
            printf("table[%d]: %s\t%d\n", i, hash_table[i].name, hash_table[i].collision);
    }

    int collision_count1 = 0;
    for (int i = 0; i < TABLE_SIZE; i++) {
        collision_count1 += hash_table[i].collision;
    }

    initialize_table();

    int random_values[10];
    
    for (int i = 0; i < 10; i++)
        random_values[i] = rand() % TABLE_SIZE;
    
    fp = fopen("names.txt", "r");
    if (fp == NULL) {
        printf("names.txt 파일을 열 수 없습니다.\n");
        return -1;
    }
    while (fgets(name, NAME_SIZE, fp) != NULL) {
        hash_insert2(name, random_values);
    }
    fclose(fp);

    for (int i = 0; i < TABLE_SIZE; i++) {
        if (strcmp(hash_table[i].name, "") == 0)
            printf("table[%d]: EMPTY\t%d\n", i, hash_table[i].collision);
        else
            printf("table[%d]: %s\t%d\n", i, hash_table[i].name, hash_table[i].collision);
    }

    int collision_count2 = 0;
    for (int i = 0; i < TABLE_SIZE; i++) {
        collision_count2 += hash_table[i].collision;
    }

    printf("Total collision number in Hash1 is %d.\n", collision_count1);
    printf("Total collision number in Hash2 is %d.\n", collision_count2);

    return 0;
}
