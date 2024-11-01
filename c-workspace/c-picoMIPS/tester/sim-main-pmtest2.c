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
						0x0000,	// 0104: eq
						0x0000,	// 0106: max
						0x000F,	// 0108: TRUE
						0x0001,	// 010A: FALSE
						END_OF_ARG);

	// CODE section
	writeWords(0x0200,			//		 r1_max: // r2 < r1
						0x5102,	// 0200: sw	r4, #2(r0) // eq
						0x5043,	// 0202: sw	r1, #3(r0) // max
						0x300A,	// 0204: j	final
								//		 main:
						0x0003,	// 0206: sub	r0, r0, r0
						0xA010,	// 0208: addi	r0, r0, 0x10
						0x0004,	//		 mul	r0, r0, r0
						0x4040,	//		 lw	r1, #0(r0) // a
						0x4081,	//		 lw	r2, #1(r0) // b
						0x40C4,	// 0210: lw	r3, #4(r0) // TRUE
						0x4105,	//		 lw	r4, #5(r0) // FALSE
						0x1443,	//		 beq	r1, r2, equal
						0x2445,	//		 bles	r1, r2, r2_max
						0x22B3,	//		 bles	r2, r1, r1_max
								//		 final:
						0xF000,	// 021C: halt
								//		 equal: // r1 == r2
						0x50C2,	// 021E: sw	r3, #2(r0) // eq
						0x5043,	// 0220: sw	r1, #3(r0) // max
						0x3FFC,	// 0222: j	final
								//		 r2_max: // r1 < r2
						0x5102,	// 0224: sw	r4, #2(r0) // eq
						0x5083,	// 0226: sw	r2, #3(r0) // max
						0x3FF9,	// 0228: j	final
						END_OF_ARG);

	return 0x0206;	// return start address of program
}

//========================================
// Main Function
//========================================
int main() {
	int exit_code;							// 0: normal exit, 1: error exit
	WORD start_addr;						// start address of program
	char program[] = "picoMIPS Test #2";	// program title

	printf("================================\n");
	printf(" picoMIPS Computer Simulator\n");
	printf(" Author: %s\n", author);
	printf(" Program: %s\n", program);
	printf("================================\n");

	short a[]   = {  3, 4, -5, -2 };
	short b[]   = {  3, 6, -5, -7 };
	short eq[]  = { 15, 1, 15,  1 };
	short max[] = {  3, 6, -5, -2 };
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
		checkData("eq = (a == b)", 0x0104, eq[t]);
		checkData("max(a, b)    ", 0x0106, max[t]);
	}
}
