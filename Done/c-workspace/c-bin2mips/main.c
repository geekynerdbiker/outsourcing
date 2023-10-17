//
//  main.c
//  bin2mips
//
//  Created by Jacob An on 2022/04/08.
//

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "radix.h"
#include "instruction.h"

#define MAX_LENGTH 32
#define BINARY_LENGTH 32
#define HEX_LENGTH 8
#define OPCODE_LENGTH 6
#define RS_LENGTH 5
#define RT_LENGTH 5
#define RD_LENGTH 5
#define SHAMT_LENGTH 5
#define FN_LENGTH 6
#define IMMEDIATE_LENGTH 16
#define ADDRESS_LENGTH 26
#define INPUT_MIPS 0
#define INPUT_BINARY 1
#define INPUT_HEX 2

void binaryToMIPS(char*, char*);
    
int main(int argc, const char * argv[]) {
    FILE *fp, *fp2;
    fp = fopen(argv[1], "rb");
    fp2 = fopen(argv[3], "w");

    if (strcmp(argv[2], ">") != 0)
        return 0; // unknown

    int i = 0;
    unsigned char input[200], hexRep[200], mipsRep[200], buffer[4];
    fread(input, sizeof(input), 1, fp);
    
    for (int k = 0; k < 4; k++)
        buffer[k] = input[4*i +k];
    
    while (buffer[0] != '\0') {
        hexToBinary(buffer, hexRep);
        binaryToMIPS(hexRep, mipsRep);
        fread(buffer, sizeof(unsigned), 1, fp);

        printf("inst %d: ", i++);
        for (int k = 0 ;k < 4; k++)
            printf("%c", hexRep[k]);
        printf("%s\n", mipsRep);
        
        for (int k = 0; k < 4; k++)
            buffer[k] = input[4*i +k];
        
    }
    return 0;
}

void binaryToMIPS(char *binary, char *output) {
    char opCode[OPCODE_LENGTH + 1];
    for (int i = 0; i < OPCODE_LENGTH; i ++) {
        opCode[i] = binary[i];
    }
    opCode[OPCODE_LENGTH] = '\0';
    
    char instructionType = getInstructionType(opCode);
    int offset = OPCODE_LENGTH;
    
    switch (instructionType) {
        case 'R': {
            char rs[RS_LENGTH + 1], rt[RT_LENGTH + 1], rd[RD_LENGTH + 1], shamt[SHAMT_LENGTH + 1], fnCode[FN_LENGTH + 1], instruction[10];
            
            for (int i = 0; i < RS_LENGTH; i ++) {
                rs[i] = binary[offset + i];
            }
            rs[RS_LENGTH] = '\0';
            offset += RS_LENGTH;
            
            for (int i = 0; i < RT_LENGTH; i ++) {
                rt[i] = binary[offset + i];
            }
            rt[RT_LENGTH] = '\0';
            offset += RT_LENGTH;
            
            for (int i = 0; i < RD_LENGTH; i ++) {
                rd[i] = binary[offset + i];
            }
            rd[RD_LENGTH] = '\0';
            offset += RD_LENGTH;
            
            for (int i = 0; i < SHAMT_LENGTH; i ++) {
                shamt[i] = binary[offset + i];
            }
            shamt[SHAMT_LENGTH] = '\0';
            offset += SHAMT_LENGTH;
            
            for (int i = 0; i < FN_LENGTH; i ++) {
                fnCode[i] = binary[offset + i];
            }
            fnCode[FN_LENGTH] = '\0';
            
            getInstruction(opCode, fnCode, instruction);
            
            if (strcmp(instruction, "sll") == 0 || strcmp(instruction, "srl") == 0) {
                snprintf(output, MAX_LENGTH, "%s $%d, $%d, %d", instruction, binaryToDecimal(rd), binaryToDecimal(rt), binaryToDecimal(shamt));
                break;
            }
            
            snprintf(output, MAX_LENGTH, "%s $%d, $%d, $%d", instruction, binaryToDecimal(rd), binaryToDecimal(rs), binaryToDecimal(rt));
            break;
        }
        case 'I': {
            char rs[RS_LENGTH + 1], rt[RT_LENGTH + 1], immediate[IMMEDIATE_LENGTH + 1], instruction[10];
            for (int i = 0; i < RS_LENGTH; i ++) {
                rs[i] = binary[offset + i];
            }
            rs[RS_LENGTH] = '\0';
            offset += RS_LENGTH;
            
            for (int i = 0; i < RT_LENGTH; i ++) {
                rt[i] = binary[offset + i];
            }
            rt[RT_LENGTH] = '\0';
            offset += RT_LENGTH;
            
            for (int i = 0; i < IMMEDIATE_LENGTH; i ++) {
                immediate[i] = binary[offset + i];
            }
            immediate[IMMEDIATE_LENGTH] = '\0';
            
            getInstruction(opCode, NULL, instruction);
            
            if (strcmp(instruction, "lw") == 0 || strcmp(instruction, "sw") == 0) {
                snprintf(output, MAX_LENGTH, "%s $%d, %d($%d)", instruction, binaryToDecimal(rt), binaryToTwoComplement(immediate), binaryToDecimal(rs));
                break;
            }
            
            if (strcmp(instruction, "beq") == 0 || strcmp(instruction, "bne") == 0) {
                snprintf(output, MAX_LENGTH, "%s $%d, $%d, %d", instruction, binaryToDecimal(rs), binaryToDecimal(rt), binaryToTwoComplement(immediate));
                break;
            }
            
            snprintf(output, MAX_LENGTH, "%s $%d, $%d, %d", instruction, binaryToDecimal(rt), binaryToDecimal(rs), binaryToTwoComplement(immediate));
            break;
        }
        case 'J': {
            char address[ADDRESS_LENGTH + 1], addressHex[9], instruction[10];
            for (int i = 0; i < ADDRESS_LENGTH; i ++) {
                address[i] = binary[offset + i];
            }
            address[ADDRESS_LENGTH] = '\0';
            
            getInstruction(opCode, NULL, instruction);
            binaryToHex(address, addressHex);
            
            snprintf(output, MAX_LENGTH, "%s 0x%s", instruction, addressHex);
            break;
        }
    }
}

