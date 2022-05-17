
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
int runProcessor(WORD start_addr) {
	WORD pc = start_addr;		// set PC to start address of program

	while (1) {
		// fetch cycle
		WORD ir = readWord(pc);
		pc += (unsigned int)2;	// set PC to next instruction addr

		// execution cycle
		if (ir == 0xF000)		// halt
			return 0;
	}

	return 1;
}
