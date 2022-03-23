//
//  main.c
//  c-linux
//
//  Created by Jacob An on 2022/03/22.
//

/* Name: Jeongtak Nam
 * unikey: jnam4637
 */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct node{
    int b0, b1, b2, sw, cs;
    int start;
    struct node *next, *prev;
} Node;

Node *head;
FILE* f;

int convertCtoI(char c) {
    return c >= 0 ? c : 256 + c;
}

int hexToDec(char *str) {
    int decimal = 0, position = 0;
    
    for (unsigned long i = strlen(str) - 1; i > 1; i--) {
        char ch = str[i];
        
        if (ch >= '0' && ch <= '9')
            decimal += (ch - 48) * pow(16, position);
        else if (ch >= 'A' && ch <= 'Z')
            decimal += (ch - (65 - 10)) * pow(16, position);
        else if (ch >= 'a' && ch <= 'z')
            decimal += (ch - (97 - 10)) * pow(16, position);
        
        position++;
    }
    
    return decimal;
}

void findTrailer(char buffer[], int p0, int p1, int p2, int parity) {
    for (int i = 0; i < 127;) {
        int b0 = convertCtoI(buffer[i]);
        int b1 = convertCtoI(buffer[i+1]);
        int b2 = convertCtoI(buffer[i+2]);
        int b3 = convertCtoI(buffer[i+3]);
        int b4 = convertCtoI(buffer[i+4]);
        
        Node *p = head;
        Node *q = p;
        
        Node *t = (Node *)malloc(sizeof(Node));
        memset(t, 0, sizeof(Node));
        
        if (b0 == p0 && b1 == p1 && b2 == p2 && b3 == parity) {
            t->b0 = b0;
            t->b1 = b1;
            t->b2 = b2;
            t->cs = b3;
            t->sw = 0;
            t->start = i;
            t->next = NULL;
            t->prev = NULL;
            
            if (head == NULL)
                head = t;
            else {
                while (p->next != NULL) {
                    q = p;
                    p = p->next;
                }
                t->prev = q;
                p->next = t;
            }
            i += 4;
        } else {
            bool isValid = (b0 ^ b1 ^ b2 ^ b3) == b4;
            if (b3 < 0 || b3 > 6) break;
            if (!isValid)
                break;
            
            t->b0 = b0;
            t->b1 = b1;
            t->b2 = b2;
            t->sw = b3;
            t->cs = b4;
            t->start = i;
            t->next = NULL;
            t->prev = NULL;
            
            if (head == NULL)
                head = t;
            else {
                while (p->next != NULL) {
                    q = p;
                    p = p->next;
                }
                t->prev = q;
                p->next = t;
                
            }
            i += 5;
        }
    }
}

int isValidPacket(Node *p) {
    if (p->prev == NULL) return 0;
    if (p->next == NULL) return 0;
    if (p->next->sw == 0) return 0;
    
    int x1 = p->b0, x2 = p->prev->b0;
    int y1 = p->b1, y2 = p->prev->b1;
    int z1 = p->b2, z2 = p->prev->b2;
    
    if (abs(x1 - x2) > 25)
        return 1;
    else if (abs(y1 - y2) > 25)
        return 2;
    else if (abs(z1 - z2) > 25)
        return 3;
    return 0;
}

void read_file(FILE* f, int p0, int p1, int p2, int parity){
    char buffer[128], swizzle[4];
    
    fread(buffer, sizeof(char), 127, f);
    findTrailer(buffer, p0, p1, p2, parity);
    
    Node *t = head;
    int chunk = 0,  packet = 0;
    
    while (t != NULL) {
            double avgX = 0, avgY = 0, avgZ = 0;
            printf("Chunk: %d at offset: %d\n", chunk, t->start);
            for (int k = 0; t->sw != 0; k++) {
                
                int b0 = t->b0;
                int b1 = t->b1;
                int b2 = t->b2;
                int sw = t->sw;
                int cs = t->cs;
                
                bool isValidSwizzle = true;
                if (!isValidSwizzle) continue;
                
                
                printf("\tPacket: %d\n", k);
                printf("\t\tData before swizzle -> B0: %d, B1: %d, B2: %d\n", t->b0, t->b1, t->b2);
                
                switch (sw) {
                    case 0:
                        t->b0 = 0;
                        t->b1 = 0;
                        t->b2 = 0;
                        break;
                    case 1:
                        strcpy(swizzle, "XYZ");
                        t->b0 = b0;
                        t->b1 = b1;
                        t->b2 = b2;
                        break;
                    case 2:
                        strcpy(swizzle, "XZY");
                        t->b0 = b0;
                        t->b1 = b2;
                        t->b2 = b1;
                        break;
                    case 3:
                        strcpy(swizzle, "YXZ");
                        t->b0 = b1;
                        t->b1 = b0;
                        t->b2 = b2;
                        break;
                    case 4:
                        strcpy(swizzle, "YZX");
                        t->b0 = b2;
                        t->b1 = b0;
                        t->b2 = b1;
                        break;
                    case 5:
                        strcpy(swizzle, "ZXY");
                        t->b0 = b1;
                        t->b1 = b2;
                        t->b2 = b0;
                        break;
                    case 6:
                        strcpy(swizzle, "ZYX");
                        t->b0 = b2;
                        t->b1 = b1;
                        t->b2 = b0;
                        break;
                    default:
                        printf("Invalid Swizzle Information.\n");
                        isValidSwizzle = false;
                        break;
                }
                
                printf("\t\tSwizzle: %s\n", swizzle);
                printf("\t\tData after swizzle -> X: %d, Y: %d, Z: %d\n", t->b0, t->b1, t->b2);
                
                if (!isValidPacket(t)){
                avgX += t->b0;
                avgY += t->b1;
                avgZ += t->b2;
                packet++;
                }
                
                switch(isValidPacket(t)) {
                    case 0:
                        break;
                    case 1:
                        printf("\tIgnoring packet. X: %d. Previous valid packet's X: %d. %d > 25.\n", t->b0, t->prev->b0, abs(t->b0-t->prev->b0));
                        break;
                    case 2:
                        printf("\tIgnoring packet. Y: %d. Previous valid packet's Y: %d. %d > 25.\n", t->b1, t->prev->b1, abs(t->b1-t->prev->b1));
                        break;
                    case 3:
                        printf("\tIgnoring packet. Z: %d. Previous valid packet's Z: %d. %d > 25.\n", t->b2, t->prev->b2, abs(t->b2-t->prev->b2));
                        break;
                    default:
                        break;
                }
                
                if (t->next == NULL) break;
                t = t->next;
            }
            avgX /= (double)packet; avgY /= (double)packet; avgZ /= (double)packet;
            printf("\tChunk Average X: %.2lf, Average Y: %.2lf, Average Z: %.2lf\n\n", avgX, avgY, avgZ);
            packet = 0;
        
        chunk++;
        if (t->next == NULL) break;
        t = t->next;

    }
    
    printf("\n");
}


int main(int argc, char * argv[]) {
    if (argc >= 6) {
        printf("Error: Too many command line arguments.\n");
        return 0;
    }
    if (argc == 5) {
        f = fopen(argv[1], "r");
        if (!f) perror("fopen");
        else {
            // Get delimiter bytes hex to dec
            for (int i = 0; i < 3; i++)
                printf("Delimiter byte %d is: %d\n", i, hexToDec(*(argv+2+i)));
            
            // Get parity byte using XOR
            int p0 = hexToDec(argv[2]), p1 = hexToDec(argv[3]), p2 = hexToDec(argv[4]);
            int parity = p0 ^ p1 ^ p2;
            printf("Checksum is: %d\n\n", parity);
            read_file(f, p0, p1, p2, parity);
            
            fclose(f);
        }
        
    } else {
        printf("Error: Not enough command line arguments.\n");
        return 0;
    }
}
