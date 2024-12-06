#include "dict.h"

void initializeDictionary(DictionaryEntry **dictionary, int *dictSize, int *dictCapacity) {
    *dictCapacity = INITIAL_DICT_SIZE;
    *dictionary = (DictionaryEntry *)malloc(*dictCapacity * sizeof(DictionaryEntry));
    if (*dictionary == NULL) {
        perror("Failed to allocate memory for dictionary");
        exit(EXIT_FAILURE);
    }
    *dictSize = 256;

    for (int i = 0; i < 256; i++) {
        (*dictionary)[i].code = i;
        (*dictionary)[i].str[0] = (char)i;
        (*dictionary)[i].str[1] = '\0';
    }
}

int findInDictionary(DictionaryEntry *dictionary, int dictSize, char *str) {
    for (int i = 0; i < dictSize; i++) {
        if (strcmp(dictionary[i].str, str) == 0) {
            return dictionary[i].code;
        }
    }
    return -1;
}

void addToDictionary(DictionaryEntry **dictionary, int *dictSize, int *dictCapacity, char *str) {
    if (*dictSize >= *dictCapacity) {
        *dictCapacity *= 2;
        *dictionary = (DictionaryEntry *)realloc(*dictionary, *dictCapacity * sizeof(DictionaryEntry));
        if (*dictionary == NULL) {
            perror("Failed to reallocate memory for dictionary");
            exit(EXIT_FAILURE);
        }
    }
    (*dictionary)[*dictSize].code = *dictSize;
    strcpy((*dictionary)[*dictSize].str, str);
    (*dictSize)++;
}

void saveDictionaryToFile(DictionaryEntry *dictionary, int dictSize, int dictCapacity) {
    FILE *file = fopen(DICT_FILE, "wb");
    if (file == NULL) {
        perror("Failed to open dictionary file for writing");
        exit(EXIT_FAILURE);
    }
    fwrite(&dictSize, sizeof(int), 1, file);
    fwrite(&dictCapacity, sizeof(int), 1, file);
    fwrite(dictionary, sizeof(DictionaryEntry), dictCapacity, file);
    fclose(file);
}

void loadDictionaryFromFile(DictionaryEntry **dictionary, int *dictSize, int *dictCapacity) {
    FILE *file = fopen(DICT_FILE, "rb");
    if (file == NULL) {
        initializeDictionary(dictionary, dictSize, dictCapacity);
        return;
    }
    fread(dictSize, sizeof(int), 1, file);
    fread(dictCapacity, sizeof(int), 1, file);
    *dictionary = (DictionaryEntry *)realloc(*dictionary, *dictCapacity * sizeof(DictionaryEntry));
    if (*dictionary == NULL) {
        perror("Failed to reallocate memory for dictionary");
        exit(EXIT_FAILURE);
    }
    fread(*dictionary, sizeof(DictionaryEntry), *dictCapacity, file);
    fclose(file);
}

char* findInDictionaryByCode(DictionaryEntry *dictionary, int dictSize, int code) {
    for (int i = 0; i < dictSize; i++) {
        if (dictionary[i].code == code) {
            return dictionary[i].str;
        }
    }
    return NULL; // Not found
}

void printDictionary(DictionaryEntry *dictionary, int dictSize) {
    for (int i = 0; i < dictSize; i++) {
        printf("[%d: \"%s\"] ", dictionary[i].code, dictionary[i].str);
        if (i % 5 == 0 && i > 0) {
            printf("\n");
        }
    }
}

void freeDictionary(DictionaryEntry *dictionary, int dictSize) {
    if (dictionary != NULL) {
        free(dictionary);
    }
}
