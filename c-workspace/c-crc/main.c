//
//  main.c
//  c-crc
//
//  Created by Jacob An on 2022/05/02.
//

#include <stdio.h>
#include <string.h>
#define _CRT_SECURE_NO_WARNINGS

int main(void) {
    unsigned long keylen, msglen;
    char input[100], key[30], temp[30], quot[100], rem[30], key1[30];
    
    
    printf("Please, type 4-bit generation code: ");
    gets(key);
    
    printf("Please, type 10-digit data bits: ");
    gets(input);
    
    keylen = strlen(key);
    msglen = strlen(input);
    strcpy(key1, key);
    
    for (int i = 0; i < keylen - 1; i++)
        input[msglen+i] = '0';
    
    for (int i = 0; i < keylen; i++)
        temp[i] = input[i];
    
    for (int i = 0; i < msglen; i++) {
        quot[i] = temp[0];
        if (quot[i] == '0')
            for (int j = 0; j < keylen; j++)
                key[j] = '0';
        else
            for (int j = 0; j < keylen; j++)
                key[j] = key1[j];
        for (int j = keylen - 1; j > 0; j--) {
            if (temp[j] == key[j])
                rem[j-1] = '0';
            else
                rem[j-1] = '1';
        }
        rem[keylen-1] = input[i+keylen];
        strcpy(temp, rem);
    }
    strcpy(rem, temp);
    
    //print output
    printf("The Data with Checksum is ");
    for (int i = 0; i < msglen; i++)
        printf("%c", input[i]);
    for (int i = 0; i < keylen-1; i++)
        printf("%c", rem[i]);
    
    return 0;
}
