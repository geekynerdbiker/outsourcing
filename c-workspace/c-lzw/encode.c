#include "encode.h"
#include "dict.h"

void compress(char *input, int *output, int *outputSize, DictionaryEntry **dictionary, int *dictSize, int *dictCapacity) {
char currentString[MAX_STRING_SIZE] = "";
    int inputLength = strlen(input);

    for (int i = 0; i < inputLength; i++) {
        char currentChar = input[i];
        char tempString[MAX_STRING_SIZE];
        snprintf(tempString, sizeof(tempString), "%s%c", currentString, currentChar);

        if (findInDictionary(*dictionary, *dictSize, tempString) == -1) {
            output[*outputSize] = findInDictionary(*dictionary, *dictSize, currentString);
            (*outputSize)++;
            addToDictionary(dictionary, dictSize, dictCapacity, tempString);
            currentString[0] = currentChar;
            currentString[1] = '\0';
        } else {
            strncat(currentString, &currentChar, 1);
        }
    }

    if (strlen(currentString) > 0) {
        output[*outputSize] = findInDictionary(*dictionary, *dictSize, currentString);
        (*outputSize)++;
    }
}

void encode(int p, int maxBits, int stage) {
char input[MAX_STRING_SIZE];
    int outputSize = 0;
    int bitLength = 9;
    DictionaryEntry *dictionary;
    int dictSize, dictCapacity;

    initializeDictionary(&dictionary, &dictSize, &dictCapacity);

    while (fgets(input, MAX_STRING_SIZE, stdin) != NULL) {
        char currentString[MAX_STRING_SIZE] = "";
        for (int i = 0; i < strlen(input); i++) {
            char currentChar = input[i];
            snprintf(currentString, sizeof(currentString), "%s%c", currentString, currentChar);

            if (findInDictionary(dictionary, dictSize, currentString) == -1) {
                int code = findInDictionary(dictionary, dictSize, currentString);
                writeCode(stdout, code, bitLength);

                addToDictionary(&dictionary, &dictSize, &dictCapacity, currentString);

                if (dictSize > (1 << bitLength) - 1) {
                    bitLength++;
                    if (bitLength > maxBits) {
                        if (p) {
                            initializeDictionary(&dictionary, &dictSize, &dictCapacity);
                            bitLength = 9;
                        } else {
                            fprintf(stderr, "Error: Maximum bit length exceeded.\n");
                            exit(EXIT_FAILURE);
                        }
                    }
                }

                snprintf(currentString, sizeof(currentString), "%c", currentChar);
            }
        }

        if (strlen(currentString) > 0) {
            int code = findInDictionary(dictionary, dictSize, currentString);
            writeCode(stdout, code, bitLength);
        }
    }

    flushBuffer(stdout);
    free(dictionary);
}
