
#include <stdio.h>
#include <stdarg.h>
#include "sim-com.h"

// memory array buffer
WORD memory[MEM_SIZE];

// Read a byte data from memory
BYTE readByte(WORD addr) {
	return memory[addr];
}

// Read a word data from memory
WORD readWord(WORD addr) {
	return (memory[addr] << 8) | memory[addr + 1];
}

// Write a byte data to memory
void writeByte(WORD addr, BYTE data) {
	memory[addr] = data;
}

// Write a word data to memory
void writeWord(WORD addr, WORD data) {
	memory[addr	   ] = (BYTE)((data & 0xFF00) >> 8);
	memory[addr + 1] = (BYTE) (data & 0x00FF);
}

// Write variable # of words data to memory until END_OF_ARG
WORD writeWords(WORD addr, WORD data, ...) {
	va_list ap;
	WORD d;

	va_start(ap, data);
	for (d = data; d != END_OF_ARG; d = va_arg(ap, int)) {
		writeWord(addr, d);
		addr += 2;
	}
	va_end(ap);

	return addr;	// return last address
}

// Input variable value
void inputData(char *vid, WORD addr, WORD data) {
	writeWord(addr, data);
	printf("  %s = %04X: %04X(%d)\n", vid, addr, data, (short)data);
}

// Check result with correct data
void checkData(char *vid, WORD addr, WORD data) {
	WORD data_m = readWord(addr);

	printf("  %s = %04X: %04X(%d) ", vid, addr, data_m, (short)data_m);
	if (data == data_m)
		printf("// correct\n");
	else
		printf("// %04X(%d) incorrect!\n", data, (short)data);
}
