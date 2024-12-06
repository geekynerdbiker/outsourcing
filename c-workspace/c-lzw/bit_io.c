#include "bit_io.h"

uint32_t bitBuffer = 0;
int bitCount = 0;

void writeCode(FILE *output, int code, int bitLength) {
    bitBuffer = (bitBuffer << bitLength) | code;
    bitCount += bitLength;

    while (bitCount >= 8) {
        uint8_t byte = (bitBuffer >> (bitCount - 8)) & 0xFF;
        fputc(byte, output);
        bitCount -= 8;
    }
}

void flushBuffer(FILE *output) {
    if (bitCount > 0) {
        uint8_t byte = (bitBuffer << (8 - bitCount)) & 0xFF;
        fputc(byte, output);
        bitBuffer = 0;
        bitCount = 0;
    }
}

int readCode(FILE *input, int bitLength) {
    while (bitCount < bitLength) {
        int byte = fgetc(input);
        if (byte == EOF) {
            return EOF;
        }
        bitBuffer = (bitBuffer << 8) | (byte & 0xFF);
        bitCount += 8;
    }

    int code = (bitBuffer >> (bitCount - bitLength)) & ((1 << bitLength) - 1);
    bitCount -= bitLength;
    return code;
}
