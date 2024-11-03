#include <fcntl.h>
#include <search.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define BUFSIZE 1024

typedef struct {
    char word[42];
    unsigned count;
} WORD_T;

WORD_T *words = NULL;
size_t total_words = 0;

void print_and_free(WORD_T *words, size_t total_words, char *infile);

int comparator(const void *a, const void *b) {
    char *key = (char*)a;
    WORD_T *entry = (WORD_T*)b;
    return strcmp(key, entry->word);
}

int main(int argc, char **argv) {
    if (argc != 2) return -1;

    char *infile = argv[1];
    int fd = open(infile, O_RDONLY);
    if (fd == -1) return -2;

    char buffer[BUFSIZE];
	char *p_buffer = buffer;
	size_t bytes_read = -1;
	size_t last_word_len = 0;

	while ((bytes_read  = read(fd, p_buffer + last_word_len, BUFSIZE - last_word_len - 1)) > 0){
		buffer[bytes_read + last_word_len] = '\0';
		
        while (p_buffer) {
			char *token = strsep(&p_buffer, "\n ");
			
            if (!p_buffer) {
				last_word_len = strlen(token);
				strncpy(&buffer[0], token, last_word_len + 1);
				token = NULL;
				break;
			} if (strlen(token)) {
				WORD_T *result = lfind(token, words, &total_words, sizeof(WORD_T), comparator);
				
                if (result != NULL) result->count++;
				else {
					words = realloc(words, sizeof(WORD_T) * (total_words + 1));
					strcpy(words[total_words].word, token);
					words[total_words].count = 1;
					total_words++;
				}
			}
		}
		p_buffer = buffer;
	}

    print_and_free(words, total_words, infile);

    close(fd);
    return 0;
}

void print_and_free(WORD_T *words, size_t total_words, char *infile) {
    int sum = 0;
    for (int i = 0; i < total_words; ++i) {
        if (words[i].count > 1)
            printf("%s: %u\n", words[i].word, words[i].count);
        sum += words[i].count;
    }
    printf("\n%d %s\n", sum, infile);
    printf("\n");
    free(words);
}
