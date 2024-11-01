
#include <stdio.h>
#include <stdlib.h>
#include "sim-com.h"

char author[] = "201912345 Gildong Hong";	// student id and name


//========================================
// picoMIPS processor simulation function
// - start_addr: start address of program
// - return exit state = 0: normal exit
//                       1: error exit
//========================================
WORD reg[8] = { 0, }; // register file

int runProcessor(WORD start_addr) {
    int n = 0, count = 1;
    
    WORD ir_op = 0;
    WORD ir_rs = 0;
    WORD ir_rt = 0;
    WORD ir_rd = 0;
    WORD ir_fn = 0;
    WORD ir_imm = 0;
    WORD ir_a = 0;
    
    WORD pc = start_addr;
    
    while (1) {
        // fetch cycle
        WORD ir = readWord(pc);
        
        // execution cycle
        if (ir == 0xF000)		// halt
            return 0;
        ir_op = ir & 0xF000;
        ir_imm = ir & 0x003F;
        
        if ((ir_imm & 0x0020) == 0x0020)
        {
            ir_imm = (short)ir_imm | 0xFFC0;
        }
        ir_a = ir & 0x0FFF;
        if ((ir_a & 0x0800) == 0x0800){
            ir_a = (short)(ir_a | 0xF000);
        }
        
        pc += (WORD)2;    // set PC to next instruction addr
        count += 1;
        
        ir_rs = ((ir & 0x0E00) >> 9);
        ir_rt = ((ir & 0x01C0) >> 6);
        ir_rd = ((ir & 0x0038) >> 3);
        ir_fn = ir & 0x0007;
        
        // execution cycle
        switch (ir_op)
        {
                
            case 0x0000: // Register function
                
                switch (ir_fn)
                {
                    case 0x0000: // and
                        reg[ir_rd] = reg[ir_rs] & reg[ir_rt];
                        break;
                    case 0x0001: // or
                        reg[ir_rd] = reg[ir_rs] | reg[ir_rt];
                        break;
                    case 0x0002: // add
                        reg[ir_rd] = reg[ir_rs] + reg[ir_rt];
                        break;
                    case 0x0003: // sub
                        reg[ir_rd] = reg[ir_rs] - reg[ir_rt];
                        break;
                    case 0x0004: // mul
                        reg[ir_rd] = (short)reg[ir_rs] * (short)reg[ir_rt];
                        break;
                    case 0x0005: // div
                        if (reg[ir_rt] == 0) return 1;
                        reg[ir_rd] = (short)reg[ir_rs] / (short)reg[ir_rt];
                        printf("%d / %d = %d\n", reg[ir_rs], reg[ir_rt], reg[ir_rd]);
                        break;
                }
                break;
            case 0xA000: // addi
                reg[ir_rt] = reg[ir_rs] + ir_imm;
                writeWord(ir & 0x1C00, ir_rt);
                break;
            case 0xB000: // subi
                reg[ir_rt] = reg[ir_rs] - ir_imm;
                break;
            case 0x4000: // lw
                reg[ir_rt] = readWord(reg[ir_rs] + ir_imm * 2);
                break;
            case 0x5000: // sw
                writeWord((reg[ir_rs] + ir_imm * 2), reg[ir_rt]);
                break;
            case 0x1000: // beq
                if (reg[ir_rs] - reg[ir_rt] == 0)
                    pc += ir_imm * 2;
                break;
            case 0x2000: // bles
                if (reg[ir_rs] > reg[ir_rt])
                    pc += ir_imm * 2;
                break;
            case 0x3000: // j addr
                pc += ir_a * 2;
                break;
            case 0xF000: // j halt
                return 0;
                break;
        }
    }
    
    return 0;
}
