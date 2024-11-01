typedef unsigned char  BYTE;
typedef unsigned short WORD;

#define MEM_SIZE	0x1000	// memory size
#define END_OF_ARG	0xFFFF	// end of argument

// Read a byte/word data from memory
BYTE readByte(WORD addr);
WORD readWord(WORD addr);

// Write a byte/word data to memory
void writeByte(WORD addr, BYTE data);
void writeWord(WORD addr, WORD data);

// Write variable # of words data to memory until END_OF_ARG
WORD writeWords(WORD addr, WORD data, ...);

// Input and check variable for main function
void inputData(char *vid, WORD addr, WORD data);
void checkData(char *vid, WORD addr, WORD data);

// STUDENT id and name
extern char author[];

// Processor simulation function coded by STUDENT
int runProcessor(WORD start_addr);
