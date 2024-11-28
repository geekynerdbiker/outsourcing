#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MEMORY_START 1000

typedef struct Symbol {
    char* name;
    int address;
} Symbol;

void register_symbol(char* line, Symbol* symbols, int* pc);
int interpret_line(char* line, FILE* output, FILE* trace, int* pc, int pass);
void process_instruction(char* instruction, FILE* output, int* pc, int pass);

Symbol table[256];
int counter = 0;

int main(int argc, char* argv[]) {
    char instruction[50];
    char inputname[32];
    char* filename;
    char output_filename[32];
    char tracename[32];
    char line[128];

    int pc = MEMORY_START;

    FILE* input;
    FILE* output;
    FILE* trace;

    while (1) {
        printf(">> Enter Input File Name : ");
        scanf("%s", inputname);

        if (strcmp(inputname, "terminate") == 0)
            break;

        input = fopen(inputname, "r");
        if (!input) {
            printf("Input file does not exist!!\n");
            continue;
        }

        char eraser[] = ".";
        filename = strtok(inputname, eraser);

        snprintf(output_filename, sizeof(output_filename), "%s.o", filename);
        snprintf(tracename, sizeof(tracename), "%s.trace", filename);

        output = fopen(output_filename, "w");
        trace = fopen(tracename, "w");

        for (int pass = 1; pass <= 2; pass++) {
            pc = MEMORY_START;
            while (fgets(line, sizeof(line), input)) {
                char *trimmed_line = strtok(line, "\n");
                if (!trimmed_line || trimmed_line[0] == '#') {
                    continue;
                }
                if (strchr(trimmed_line, ':')) {
                    char *symbol = strtok(trimmed_line, ":");
                    if (pass == 1) {
                        register_symbol(symbol, table, &pc);
                    }
                } else if (!interpret_line(line, output, trace, &pc, pass)) {
                    printf("Syntax Error.\n");
                    fclose(output);
                    fclose(trace);
                    remove(output_filename);
                    remove(tracename);
                    break;
                }
                
                if(pass == 2) 
                    fprintf(trace, "%d\n", pc);
                pc += 4;
            }
            fseek(input, 0, SEEK_SET);
        }
        fclose(input);
        fclose(output);
        fclose(trace);
        
        for (int i = 0; i < counter; i++) {
            free(table[i].name);
        }
    }
    return 0;
}



void register_symbol(char* line, Symbol* symbols, int* pc) {
    char* name = strtok(line, ":");
    if (name == NULL) {
        fprintf(stderr, "Error: Invalid symbol format\n");
        return;
    }

    symbols[counter].name = strdup(name);
    symbols[counter].address = *pc;
    printf("%s %d\n", symbols[counter].name, symbols[counter].address);
    counter++;

    if (counter > 256) {
        fprintf(stderr, "Error: Symbol array overflow\n");
        exit(EXIT_FAILURE);
    }
}

int interpret_line(char* line, FILE* output, FILE* trace, int* pc, int pass) {
    if (pass == 2)
        process_instruction(line, output, pc, pass);

    return 1;
}


void print_binary(unsigned int num, FILE* output) {
    for (int i = 31; i >= 0; i--)
        fprintf(output, "%d", (num >> i) & 1);
    fprintf(output, "\n");
}

void process_instruction(char* instruction, FILE* output, int* pc, int pass) {
    int offset, rd = 0, rs1 = 0, rs2 = 1;
    char opcode[10], symbol[10]; 
    
    unsigned int R = 0b0110011;
    unsigned int I = 0b0010011;
    unsigned int SB = 0b1100011;

    sscanf(instruction, "%s", opcode);

    if (strcmp(opcode, "ADD") == 0) {
        sscanf(instruction, "%*s x%d, x%d, x%d", &rd, &rs1, &rs2);
        unsigned int out_code_num = R | (rs2 << 20) | (rs1 << 15) | (rd << 7) | (0b000 << 12);
        print_binary(out_code_num, output);    
    } else if (strcmp(opcode, "SUB") == 0) {
        sscanf(instruction, "%*s x%d, x%d, x%d", &rd, &rs1, &rs2);
        unsigned int out_code_num = R | (0b0100000 << 25) | (rs2 << 20) | (rs1 << 15) | (rd << 7) | (0b000 << 12);
        print_binary(out_code_num, output);
    } else if (strcmp(opcode, "AND") == 0) {
        sscanf(instruction, "%*s x%d, x%d, x%d", &rd, &rs1, &rs2);
        unsigned int out_code_num = R | (rs2 << 20) | (rs1 << 15) | (rd << 7) | (0b111 << 12);
        print_binary(out_code_num, output);
    } else if (strcmp(opcode, "OR") == 0) {
        sscanf(instruction, "%*s x%d, x%d, x%d", &rd, &rs1, &rs2);
        unsigned int out_code_num = R | (rs2 << 20) | (rs1 << 15) | (rd << 7) | (0b110 << 12);
        print_binary(out_code_num, output);
    } else if (strcmp(opcode, "XOR") == 0) {
        sscanf(instruction, "%*s x%d, x%d, x%d", &rd, &rs1, &rs2);
        unsigned int out_code_num = R | (rs2 << 20) | (rs1 << 15) | (rd << 7) | (0b100 << 12);
        print_binary(out_code_num, output);
    } else if (strcmp(opcode, "SLL") == 0) {
        sscanf(instruction, "%*s x%d, x%d, x%d", &rd, &rs1, &rs2);
        unsigned int out_code_num = R | (rs2 << 20) | (rs1 << 15) | (rd << 7) | (0b001 << 12);
        print_binary(out_code_num, output);
    } else if (strcmp(opcode, "SRL") == 0) {
        sscanf(instruction, "%*s x%d, x%d, x%d", &rd, &rs1, &rs2);
        unsigned int out_code_num = R | (rs2 << 20) | (rs1 << 15) | (rd << 7) | (0b101 << 12);
        print_binary(out_code_num, output);
    } else if (strcmp(opcode, "SRA") == 0) {
        sscanf(instruction, "%*s x%d, x%d, x%d", &rd, &rs1, &rs2);
        unsigned int out_code_num = R | (0b0100000 << 25) | (rs2 << 20) | (rs1 << 15) | (rd << 7) | (0b101 << 12);
        print_binary(out_code_num, output);
    } else if (strcmp(opcode, "ADDI") == 0) {
        sscanf(instruction, "%*s x%d, x%d, %d", &rd, &rs1, &rs2);
        unsigned int out_code_num = I | ((rs2 & 0xFFF) << 20) | (rs1 << 15) | (rd << 7) | (0b000 << 12);
        print_binary(out_code_num, output);
    } else if (strcmp(opcode, "ANDI") == 0) {
        sscanf(instruction, "%*s x%d, x%d, %d", &rd, &rs1, &rs2);
        unsigned int out_code_num = I | ((rs2 & 0xFFF) << 20) | (rs1 << 15) | (rd << 7) | (0b111 << 12);
        print_binary(out_code_num, output);
    } else if (strcmp(opcode, "ORI") == 0) {
        sscanf(instruction, "%*s x%d, x%d, %d", &rd, &rs1, &rs2);
        unsigned int out_code_num = I | ((rs2 & 0xFFF) << 20) | (rs2 << 20) | (rs1 << 15) | (rd << 7) | (0b110 << 12);
        print_binary(out_code_num, output);
    } else if (strcmp(opcode, "XORI") == 0) {
        sscanf(instruction, "%*s x%d, x%d, %d", &rd, &rs1, &rs2);
        unsigned int out_code_num = I | ((rs2 & 0xFFF) << 20) | (rs2 << 20) | (rs1 << 15) | (rd << 7) | (0b100 << 12);
        print_binary(out_code_num, output);
    } else if (strcmp(opcode, "SLLI") == 0) {
        sscanf(instruction, "%*s x%d, x%d, %d", &rd, &rs1, &rs2);
        unsigned int out_code_num = I | ((rs2 & 0x1FF) << 20) | (rs2 << 20) | (rs1 << 15) | (rd << 7) | (0b001 << 12);
        print_binary(out_code_num, output);
    } else if (strcmp(opcode, "SRLI") == 0) {
        sscanf(instruction, "%*s x%d, x%d, %d", &rd, &rs1, &rs2);
        unsigned int out_code_num = I | ((rs2 & 0x1FF) << 20) | (rs2 << 20) | (rs1 << 15) | (rd << 7) | (0b101 << 12);
        print_binary(out_code_num, output);
    } else if (strcmp(opcode, "SRAI") == 0) {
        sscanf(instruction, "%*s x%d, x%d, %d", &rd, &rs1, &rs2);
        unsigned int out_code_num = I | (0b0100000 << 25 ) | ((rs2 & 0x1FF) << 20) | (rs2 << 20) | (rs1 << 15) | (rd << 7) | (0b101 << 12);
        print_binary(out_code_num, output);
    } else if (strcmp(opcode, "LW") == 0) {
        sscanf(instruction, "%*s x%d, %d(x%d)", &rd, &rs2, &rs1);
        unsigned int out_code_num = 0b0000011 | ((rs2 & 0xFFF) << 20) | (rs1 << 15) | (rd << 7) | (0b010 << 12);
        print_binary(out_code_num, output);
    } else if (strcmp(opcode, "JALR") == 0) {
        sscanf(instruction, "%*s x%d, %d(x%d)", &rd, &rs2, &rs1);
        unsigned int out_code_num = 0b1100111 | ((rs2 & 0xFFF) << 20) | (rs1 << 15) | (rd << 7) | (0b000 << 12);
        print_binary(out_code_num, output);
    } else if (strcmp(opcode, "BEQ") == 0) {
        sscanf(instruction, "%*s x%d, x%d, %s", &rs1, &rs2, symbol);
        char* cleaned = strtok(symbol, ":");

        for (int i = 0; i < counter; i++) {
            if (strcmp(cleaned, table[i].name) == 0) {
                unsigned int out_code_num = SB | ((table[i].address & 0x0001) << 25) | (((table[i].address & 0x7E0) >> 5) << 25) | (rs2 << 20) | (rs1 << 15) | ((table[i].address & 0x01E) << 7) | ((table[i].address & 0x800) << 7) | (0b000 << 12);
                print_binary(out_code_num, output);

                break;
            }
        }
    } else if (strcmp(opcode, "BNE") == 0) {
        sscanf(instruction, "%*s x%d, x%d, %s", &rs1, &rs2, symbol);
        char* cleaned = strtok(symbol, ":");

        for (int i = 0; i < counter; i++) {
            if (strcmp(cleaned, table[i].name) == 0) {
                rd = table[i].address - *pc;
                unsigned int out_code_num = SB | ((rd & 0x0001) << 25) | (((rd & 0x7E0) >> 5) << 25) | (rs2 << 20) | (rs1 << 15) | ((rd & 0x01E) << 7) | ((rd & 0x800) << 7) | (0b001 << 12);
                print_binary(out_code_num, output);

                break;
            }
        }
    } else if (strcmp(opcode, "BGE") == 0) {
        sscanf(instruction, "%*s x%d, x%d, %s", &rs1, &rs2, symbol);
        char* cleaned = strtok(symbol, ":");

        for (int i = 0; i < counter; i++) {
            if (cleaned == NULL || table[i].name == NULL) 
                continue;

            if (strcmp(cleaned, table[i].name) == 0) {
                rd = table[i].address - *pc;
                printf("%d\n", table[i].address);
                printf("%d\n", *pc);
                printf("%d\n", rd);

                int rd_signed = rd & 0xFFF;
                if (rd & 0x800)
                    rd_signed |= 0xFFFFF000;

                unsigned int out_code_num = SB | ((rd_signed & 0x1000) << 19) | (((rd_signed & 0x7E0) >> 5) << 25) | (rs2 << 20) | (rs1 << 15) | ((rd_signed & 0x01E) << 8) | ((rd_signed & 0x800) >> 4) | (0b101 << 12);
                print_binary(out_code_num, output);
                
                bool is_greater = false;
                if (rs1 >= rs2)
                    is_greater = true;

                if (is_greater) 
                    *pc = table[i].address;

                break;
            }
        }
    } else if (strcmp(opcode, "BLT") == 0) {
        sscanf(instruction, "%*s x%d, x%d, %d", &rs1, &rs2, &rd);
        unsigned int out_code_num = SB | ((rd & 0x0001) << 25) | (((rd & 0x7E0) >> 5) << 25) | (rs2 << 20) | (rs1 << 15) | ((rd & 0x01E) << 7) | ((rd & 0x800) << 7) | (0b100 << 12);
        print_binary(out_code_num, output);
    } else if (strcmp(opcode, "JAL") == 0) {
        sscanf(instruction, "%*s x%d, %d", &rd, &rs1);
        unsigned int out_code_num = 0b1101111 | (((rs1 << 1) & 0x8000) << 31 ) | (((rs1 & 0x7FE) >> 1) << 21) | (((rs1 & 0x00800) >> 11) << 20) | (((rs1 & 0xFF000) >> 12) << 12) | (rd << 7);
        print_binary(out_code_num, output);
    } else if (strcmp(opcode, "SW") == 0) {
        sscanf(instruction, "%*s x%d, %d(x%d)", &rs2, &rd, &rs1);
        unsigned int out_code_num = 0b0100011 | (((rd & 0xFEF0) >> 5 ) << 25) | (rs2 << 20) | (rs1 << 15) | ((rd & 0x01F) << 7) | (0b010 << 12);
        print_binary(out_code_num, output);
    } else if (strcmp(opcode, "EXIT") == 0) {
        print_binary(0xFFFFFFFF, output);

        for (int i = 0; i < counter; i++)
            free(table[i].name);
        exit(1);
    } else if (strchr(opcode, ':'))
        return;
    else 
        printf("\ndddSyntax Error!!\n");

    printf("instruction: %s\n", instruction);
    printf("rs1: %d, rs2: %d, rd: %d\n", rs1, rs2, rd);
}