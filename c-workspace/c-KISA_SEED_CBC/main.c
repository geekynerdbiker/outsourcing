#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "KISA_SEED_CBC.h"

FILE *fp;

BYTE *buffer;
BYTE *processedBuffer;

unsigned int fileSize;
unsigned int processedFileSize;

void stringToByte(char* input, BYTE* output) {
    int loop = 0;
    int i = 0;
    
    while (input[loop] != '\0') {
        output[i++] = input[loop++];
    }
}

int read_file(const char *path) {
    fp = fopen(path, "rb");
    
    fseek(fp, 0, SEEK_END);
    fileSize = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    
    buffer = (BYTE *)malloc(sizeof(char) * fileSize);
    processedBuffer = (BYTE *)malloc(sizeof(char) * fileSize);
    
    unsigned long total = 0;
    unsigned long curr = 0;
    
    while ((curr = fread(&buffer[total], sizeof(unsigned char), fileSize - total, fp)) > 0) {
        total += curr;
    }
    
    if (total != fileSize) {
        return 0;
    }
    
    fclose(fp);
    return 1;
}

int main(int argc, char* argv[]) {
    char* str = "MVNO_ENC_TEST_01";
    BYTE* pbUserKey = (BYTE *)malloc(sizeof(char) * strlen(str));
    stringToByte(str, pbUserKey);
    BYTE pbszIV[] = {
        (BYTE) 0x026, (BYTE) 0x08d, (BYTE) 0x066, (BYTE) 0x0a7,
        (BYTE) 0x035, (BYTE) 0x0a8, (BYTE) 0x01a, (BYTE) 0x081,
        (BYTE) 0x06f, (BYTE) 0x0ba, (BYTE) 0x0d9, (BYTE) 0x0fa,
        (BYTE) 0x036, (BYTE) 0x016, (BYTE) 0x025, (BYTE) 0x001
    };
    
    if (argc < 2) {
        printf("-e for Encrypt, -d for Decrypt.\n");
        return 0;
    } else {
        DIR *dir_info;
        struct dirent *dir_entry;
        
        dir_info = opendir(".");
        if (dir_info) {
            while ((dir_entry = readdir(dir_info))) {
                buffer = NULL;
                processedBuffer = NULL;
                
                fileSize = 0;
                processedFileSize = 0;
                
                if (!strcmp(argv[1], "-e")) {
                    if (strstr(dir_entry->d_name, ".enc") || strstr(dir_entry->d_name, ".dec") || strstr(dir_entry->d_name, "KISA_SEED_CBC") || strstr(dir_entry->d_name, "main") || strstr(dir_entry->d_name, "Makefile"))
                        continue;
                    if (read_file(dir_entry->d_name)) {
                        printf("Encrypting %s...\n", dir_entry->d_name);
                        processedFileSize = SEED_CBC_Encrypt(pbUserKey, pbszIV, buffer, fileSize, processedBuffer);
                        char *path = strcat(dir_entry->d_name, ".enc");
                        fp = fopen(path, "w");
                        fwrite(processedBuffer, sizeof(char), processedFileSize, fp);
                        fclose(fp);
                    }
                } else if (!strcmp(argv[1], "-d")) {
                    if (!strstr(dir_entry->d_name, ".enc") || (strstr(dir_entry->d_name, ".enc") && strstr(dir_entry->d_name, ".dec")))
                        continue;
                    if (read_file(dir_entry->d_name)) {
                        printf("Decrypting %s...\n", dir_entry->d_name);
                        processedFileSize = SEED_CBC_Decrypt(pbUserKey, pbszIV, buffer, fileSize, processedBuffer);

                        char *path = strstr(dir_entry->d_name, ".enc");
                        if (path)
                            strncpy(path, ".dec", 4);
                        fp = fopen(dir_entry->d_name, "w");
                        fwrite(processedBuffer, sizeof(char), processedFileSize, fp);
                        fclose(fp);
                    }
                }
            }
            closedir(dir_info);
            free(buffer);
            free(processedBuffer);
        }
    }
    printf("Processes are Done!\n");
    return 0;
}
