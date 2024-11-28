#include "decode.h"
#include "dict.h"
#include "bit_io.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void decomp(int *input, int inputSize, DictionaryEntry **dictionary, int *dictSize, int *dictCapacity) {
    char previousString[MAX_STRING_SIZE] = "";
    char currentString[MAX_STRING_SIZE] = "";

    for (int i = 0; i < inputSize; i++) {
        int currentCode = input[i];
        char *currentEntry = findInDictionaryByCode(*dictionary, *dictSize, currentCode);

        if (currentEntry == NULL) {
            fprintf(stderr, "Error: Invalid code %d\n", currentCode);
            exit(EXIT_FAILURE);
        }

        printf("%s", currentEntry);

        if (strlen(previousString) + strlen(currentEntry) + 1 < MAX_STRING_SIZE) {
            char tempString[MAX_STRING_SIZE];
            snprintf(tempString, sizeof(tempString), "%s%c", previousString, currentEntry[0]);
            addToDictionary(dictionary, dictSize, dictCapacity, tempString);

            if (*dictSize >= *dictCapacity) {
                fprintf(stderr, "Warning: Dictionary size exceeds capacity.\n");
                break;
            }
        } else {
            fprintf(stderr, "Warning: Skipping dictionary update due to buffer overflow.\n");
        }

        strncpy(previousString, currentEntry, MAX_STRING_SIZE - 1);
        previousString[MAX_STRING_SIZE - 1] = '\0';
    }
}



void decode(int stage) {
    DictionaryEntry *dictionary;
    int dictSize, dictCapacity;
    int bitLength = 9;

    initializeDictionary(&dictionary, &dictSize, &dictCapacity);

    if (stage >= 2) {
        loadDictionaryFromFile(&dictionary, &dictSize, &dictCapacity);
    }

    int currentCode;
    char previousString[MAX_STRING_SIZE] = "";

    while ((currentCode = readCode(stdin, bitLength)) != EOF) {
        char *currentEntry = findInDictionaryByCode(dictionary, dictSize, currentCode);
        if (currentEntry == NULL) {
            fprintf(stderr, "Error: Invalid code %d\n", currentCode);
            exit(EXIT_FAILURE);
        }

        printf("%s", currentEntry);

        if (strlen(previousString) > 0) {
            char newString[MAX_STRING_SIZE];
            snprintf(newString, sizeof(newString), "%s%c", previousString, currentEntry[0]);
            addToDictionary(&dictionary, &dictSize, &dictCapacity, newString);

            if (dictSize > (1 << bitLength) - 1) {
                bitLength++;
            }
        }

        strncpy(previousString, currentEntry, MAX_STRING_SIZE - 1);
        previousString[MAX_STRING_SIZE - 1] = '\0';
    }

    freeDictionary(dictionary, dictSize);
}
