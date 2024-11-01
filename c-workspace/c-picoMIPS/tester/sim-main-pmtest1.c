
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
						0x0000,	// 0104: c
						0x0000,	// 0106: d
						0x0000,	// 0108: e
						0x0000,	// 010A: f
						0x0000,	// 010C: g
						0x0000,	// 010E: h
						0x0000,	// 0110: i
						0x0000,	// 0112: j
						0x0000,	// 0114: k
						0x0000,	// 0116: l
						END_OF_ARG);

	// CODE section
	writeWords(0x0200,	0x0003,	// 0200: sub	r0, r0, r0
						0xA010,	//		 addi	r0, r0, #0x10
						0x0004,	//		 mul	r0, r0, r0
						0x4040,	//		 lw	r1, #0(r0)		// a
						0x4081,	// 0208: lw	r2, #1(r0)		// b
						0x5042,	//		 sw	r1, #2(r0)		// c
						0x0298,	//		 and	r3, r1, r2
						0x50C3,	//		 sw	r3, #3(r0)		// d
						0x02A1,	// 0210: or	r4, r1, r2
						0x5104,	//		 sw	r4, #4(r0)		// e
						0x02AA,	//		 add	r5, r1, r2
						0x5145,	//		 sw	r5, #5(r0)		// f
						0x02B3,	// 0218: sub	r6, r1, r2
						0x5186,	//		 sw	r6, #6(r0)		// g
						0x02BC,	//		 mul	r7, r1, r2
						0x51C7,	//		 sw	r7, #7(r0)		// h
						0x029D,	// 0220: div	r3, r1, r2
						0x50C8,	//		 sw	r3, #8(r0)		// i
						0xA33E,	//		 addi	r4, r1, #-2
						0x5109,	//		 sw	r4, #9(r0)		// j
						0xB343,	// 0228: subi	r5, r1, #3
						0x514A,	//		 sw	r5, #10(r0)		// k
						0xB3BC,	//		 subi	r6, r1, #-4
						0x518B,	//		 sw	r6, #11(r0)		// l
						0xF000,	//		 halt
						END_OF_ARG);

	return 0x0200;	// return start address of program
}

//========================================
// Main Function
//========================================
int main() {
	int exit_code;							// 0: normal exit, 1: error exit
	WORD start_addr;						// start address of program
	char program[] = "picoMIPS Test #1";	// program title

	printf("================================\n");
	printf(" picoMIPS Computer Simulator\n");
	printf(" Author: %s\n", author);
	printf(" Program: %s\n", program);
	printf("================================\n");

	short a[] = {  6,   9,  -9 };
	short b[] = {  2,  -3,   5 };
	short c[] = {  6,   9,  -9 };	// a
	short d[] = {  2,   9,   5 };	// a and b
	short e[] = {  6,  -3,  -9 };	// a or b
	short f[] = {  8,   6,  -4 };	// a + b
	short g[] = {  4,  12, -14 };	// a - b
	short h[] = { 12, -27, -45 };	// a * b
	short i[] = {  3,  -3,  -1 };	// a / b
	short j[] = {  4,   7, -11 };	// a + (-2)
	short k[] = {  3,   6, -12 };	// a - 3
	short l[] = { 10,  13,  -5 };	// a - (-4)
	int tc_size = 3;

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
		checkData("c =   a   ", 0x0104, c[t]);
		checkData("d = a & b ", 0x0106, d[t]);
		checkData("e = a | b ", 0x0108, e[t]);
		checkData("f = a + b ", 0x010A, f[t]);
		checkData("g = a - b ", 0x010C, g[t]);
		checkData("h = a * b ", 0x010E, h[t]);
		checkData("i = a / b ", 0x0110, i[t]);
		checkData("j = a+(-2)", 0x0112, j[t]);
		checkData("k = a - 3 ", 0x0114, k[t]);
		checkData("l = a-(-4)", 0x0116, l[t]);
	}
}
