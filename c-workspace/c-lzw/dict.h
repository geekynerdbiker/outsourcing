#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_DICT_SIZE 256
#define MAX_STRING_SIZE 1024
#define DICT_FILE "dictionary.dat"

typedef struct _node {
	int code;
	char str[MAX_STRING_SIZE];
} DictionaryEntry;

void initializeDictionary(DictionaryEntry **dictionary, int *dictSize, int *dictCapacity);
int findInDictionary(DictionaryEntry *dictionary, int dictSize, char *str);
void addToDictionary(DictionaryEntry **dictionary, int *dictSize, int *dictCapacity, char *str);
void saveDictionaryToFile(DictionaryEntry *dictionary, int dictSize, int dictCapacity);
void loadDictionaryFromFile(DictionaryEntry **dictionary, int *dictSize, int *dictCapacity);
char* findInDictionaryByCode(DictionaryEntry *dictionary, int dictSize, int code);
void printDictionary(DictionaryEntry *dictionary, int dictSize);
void freeDictionary(DictionaryEntry *dictionary, int dictSize);