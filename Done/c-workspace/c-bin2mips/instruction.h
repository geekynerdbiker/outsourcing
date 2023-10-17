//
//  instruction.h
//  bin2mips
//
//  Created by Jacob An on 2022/04/08.
//

#ifndef instruction_h
#define instruction_h

void getOpCode(char*, char*);
void getFnCode(char*, char*);
char getInstructionType(char*);
void getInstruction(char*, char*, char*);

#endif /* instruction_h */
