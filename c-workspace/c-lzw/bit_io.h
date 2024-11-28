#ifndef BIT_IO_H
#define BIT_IO_H

#include <stdio.h>
#include <stdint.h>

void writeCode(FILE *output, int code, int bitLength);
void flushBuffer(FILE *output);
int readCode(FILE *input, int bitLength);

extern uint32_t bitBuffer;
extern int bitCount;

#endif // BIT_IO_H
