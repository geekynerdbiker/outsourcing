#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SEPARATOR "*****"

void tokenize(char* filename, char*** token_list, int* count);
void write_tokens(char* filename, char* tokens[], int count);
void write_tokens_reverse(char* filename, char* tokens[], int count);
void longest_common_subsequence(char* tokens1[], int count1, char* tokens2[], int count2, char*** common_tokens, int* common_count);

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("Usage: %s file1 file2", argv[0]);
        return 1;
    }

    char** tokens1, ** tokens2, ** common_tokens;
    int count1 = 0, count2 = 0, common_count = 0;

    tokenize(argv[1], &tokens1, &count1);
    tokenize(argv[2], &tokens2, &count2);

    longest_common_subsequence(tokens1, count1, tokens2, count2, &common_tokens, &common_count);
    
    write_tokens("hw2_output.txt", tokens1, count1);
    write_tokens("hw2_output.txt", tokens2, count2);
    write_tokens_reverse("hw2_output.txt", common_tokens, common_count);

    FILE* fp = fopen("hw2_output.txt", "a");
    if (fp == NULL) {
        printf("Cannot open output file.");
        return 1;
    }
    int lcs = 0;
    int len = count1 < count2 ? count1 : count2;

    for (int i = 0; i < len; i++) {
        if (tokens1[i] == NULL || tokens2[i] == NULL) {
            len--;
            break;
        }
        if (!strcmp(tokens1[i], tokens2[i]))
            lcs++;
    }
    
    double plagiarism_score = lcs / (double)len * 100;
    fprintf(fp, "%.2lf", plagiarism_score);
    fclose(fp);

    return 0;
}

void eliminate(char *str, char ch) {
    for (; *str != '\0'; str++) {
        if (*str == ch) {
            strcpy(str, str + 1);
            str--;
        }
    }
}

void tokenize(char* filename, char*** token_list, int* count) {
    int index = 0, buffer_size = 1000;
    *token_list = (char**)malloc(buffer_size * sizeof(char*));

    FILE* fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Cannot open file.");
        return;
    }

    char* line = NULL;
    size_t len = 0;
    size_t read;

    while ((read = getline(&line, &len, fp)) != -1) {
        char* token = strtok(line, " ");
        if (token)
            eliminate(token, '\n');

        while(token) {
            int found = 0;
            int type = 0;
            if (strstr(token, "#include") != NULL) {
                (*token_list)[index] = strdup("#include");
            } else if (strstr(token, "#define") != NULL) {
                (*token_list)[index] = strdup("#define");
            } else if (token[0] == '<' && token[strlen(token) - 1] == '>') {
                (*token_list)[index] = strdup(token);
            } else if (strstr(token, "(") != NULL && token[strlen(token) - 1] == ')') {
                (*token_list)[index] = strdup("FUNK");
            } else if (!strcmp(token, "void")) {
                type = 1;
                (*token_list)[index] = strdup("void");
            } else if (!strcmp(token, "int")) {
                type = 1;
                (*token_list)[index] = strdup("int");
            } else if (!strcmp(token, "short")) {
                type = 1;
                (*token_list)[index] = strdup("short");
            } else if (!strcmp(token, "long")) {
                type = 1;
                (*token_list)[index] = strdup("long");
            } else if (!strcmp(token, "byte")) {
                type = 1;
                (*token_list)[index] = strdup("byte");
            } else if (!strcmp(token, "char")) {
                type = 1;
                (*token_list)[index] = strdup("char");
            } else if (!strcmp(token, "float")) {
                type = 1;
                (*token_list)[index] = strdup("float");
            } else if (!strcmp(token, "double")) {
                type = 1;
                (*token_list)[index] = strdup("double");
            } else if (!strcmp(token, "unsigned")) {
                type = 1;
                (*token_list)[index] = strdup("unsigned");
            } else if (strstr(token, "return") != NULL) {
                (*token_list)[index] = strdup("return");
                token = strtok(NULL, " ");
                if (token) {
                    (*token_list)[++index] = strdup("NUM_LITERAL");
                }
            } else if (strlen(token) > 1) {
                (*token_list)[index] = strdup(token);
                (*token_list)[++index] = strdup("STR_LITERAL");
                (*token_list)[++index] = strdup("VAR");
                while (token) {
                    token = strtok(NULL, " ");
                }
            }

            if (type == 1) {
                token = strtok(NULL, " ");
                if (strstr(token, "()") != NULL) {
                    (*token_list)[++index] = strdup("FUNK");
                    while (token)
                        token = strtok(NULL, " ");
                } else {
                    (*token_list)[++index] = strdup("VAR");
                    token = strtok(NULL, " ");
                    if (token) {
                        (*token_list)[++index] = strdup("=");
                        token = strtok(NULL, " ");
                        (*token_list)[++index] = strdup("NUM_LITERAL");
                    }
                }
            }

            if (++index >= buffer_size) {
                buffer_size *= 2;
                *token_list = (char**)realloc(*token_list, buffer_size * sizeof(char*));
            }

            token = strtok(NULL, "");
            if (token)
                eliminate(token, '\n');
        }
    }

    *count = index;

    free(line);
    fclose(fp);
}

void write_tokens(char* filename, char* tokens[], int count) {
    FILE* fp = fopen(filename, "a");
    if (fp == NULL) {
        printf("Cannot open file.");
        return;
    }

    for (int i = 0; i < count; i++) {
        if (tokens[i])
            fprintf(fp, "%s\n", tokens[i]);
    }
    fprintf(fp, "%s\n", SEPARATOR);
    fclose(fp);
}

void write_tokens_reverse(char* filename, char* tokens[], int count) {
    FILE* fp = fopen(filename, "a");
    if (fp == NULL) {
        printf("Cannot open file.");
        return;
    }

    for (int i = count - 1; i >= 0; i--) {
        if (tokens[i])
            fprintf(fp, "%s\n", tokens[i]);
    }
    fprintf(fp, "%s\n", SEPARATOR);
    fclose(fp);
}

void longest_common_subsequence(char* tokens1[], int count1, char* tokens2[], int count2, char*** common_tokens, int* common_count) {
    int** lcs = (int**)malloc((count1 + 1) * sizeof(int*));
    for (int i = 0; i <= count1; i++) {
        lcs[i] = (int*)malloc((count2 + 1) * sizeof(int));
        for (int j = 0; j <= count2; j++) {
            lcs[i][j] = 0;
        }
    }
    
    for (int i = 1; i < count1; i++) {
        for (int j = 1; j < count2; j++) {
            if (strcmp(tokens1[i - 1], tokens2[j - 1]) == 0) {
                lcs[i][j] = lcs[i - 1][j - 1] + 1;
            }
            else {
                lcs[i][j] = (lcs[i - 1][j] > lcs[i][j - 1]) ? lcs[i - 1][j] : lcs[i][j - 1];
            }
        }
    }
    
    *common_tokens = (char**)malloc(lcs[count1][count2] * sizeof(char*));
    int i = count1 - 1, j = count2 - 1;
    while (i > 0 && j > 0) {
        if (strcmp(tokens1[i - 1], tokens2[j - 1]) == 0) {
            (*common_tokens)[(*common_count)++] = tokens1[i - 1];
            i--;
            j--;
        }
        else if (lcs[i - 1][j] > lcs[i][j - 1]) {
            i--;
        }
        else {
            j--;
        }
    }
    
    // 메모리 해제
    for (int i = 0; i < count1; i++) {
        free(lcs[i]);
    }
    free(lcs);
}
