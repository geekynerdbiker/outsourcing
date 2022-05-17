
#include <stdio.h>
#include "sim-com.h"

//========================================
// Load picoMIPS program to memory
// - return start address of program
//========================================
unsigned int loadProgram() {

	// DATA section
	writeWords(0x0100,	0x0000,	// 0100: a
						0x0000,	// 0102: b
						0x0000,	// 0104: s
						END_OF_ARG);

	// CODE section
	writeWords(0x0200,	0x0003,	// 0200: sub	r0, r0, r0
						0xA010,	//		 addi	r0, r0, #0x10
						0x0004,	//		 mul	r0, r0, r0
						0x4040,	//		 lw		r1, #0(r0)
						0x4081,	//		 lw		r2, #1(r0)
						0xA481,	//		 addi	r2, r2, #1
						0x06DB,	//		 sub	r3, r3, r3
								//		 loop_begin:
						0x1283,	//		 beq	r1, r2, loop_end(+3)
						0x065A,	// 0210: add	r3, r3, r1
						0xA241,	//		 addi	r1, r1, #1
						0x3FFC,	//		 j		loop_begin(-4)
								//		 loop_end:
						0x50C2,	//		 sw		r3, #2(r0)
						0xF000,	//		 halt
						END_OF_ARG);

	return 0x0200;	// return start address of program
}

//========================================
// Main Function
//========================================
int main() {
	int exit_code;						// 0: normal exit, 1: error exit
	WORD start_addr;					// start address of program
	char program[] = "Sum of a to b";	// program title

	printf("================================\n");
	printf(" picoMIPS Computer Simulator\n");
	printf(" Author: %s\n", author);
	printf(" Program: %s\n", program);
	printf("================================\n");

	short a[]   = { -2,  0, -100,    1 };
	short b[]   = {  3, 10,   99,  100 };
	short sum[] = {  3, 55, -100, 5050 };
	int tc_size = 4;

	for (int t = 0; t < tc_size; t++) {
		printf("\n*** Test Case %d ***\n", t + 1);

		// load program into memory
		start_addr = loadProgram();

		// input variable value
		inputData("a", 0x0100, a[t]);
		inputData("b", 0x0102, b[t]);

		// run processor module
		exit_code = runProcessor(start_addr);
		printf("  exit code = %d\n", exit_code);

		// check result value
		checkData("s", 0x0104, sum[t]);
	}
}
