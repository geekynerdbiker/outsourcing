#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 프로그램 카운터 초기 값
#define START_PC 1000
#define EXIT_CODE 0xFFFFFFFF

// 명령어 매핑 구조체
typedef struct {
    char name[10];
    unsigned int opcode;
} Instruction;

// 명령어 리스트 정의
Instruction instructions[] = {
    {"ADD", 0x33}, {"SUB", 0x40000033}, {"ADDI", 0x13},
    {"AND", 0x7033}, {"OR", 0x6033}, {"XOR", 0x4033},
    {"ANDI", 0x7013}, {"ORI", 0x6013}, {"XORI", 0x4013},
    {"SLL", 0x1033}, {"SRL", 0x5033}, {"SRA", 0x40005033},
    {"SLLI", 0x1013}, {"SRLI", 0x5013}, {"SRAI", 0x40005013},
    {"LW", 0x2003}, {"SW", 0x2023}, {"BEQ", 0x63},
    {"BNE", 0x1063}, {"BGE", 0x5063}, {"BLT", 0x4063},
    {"JAL", 0x6F}, {"JALR", 0x67}, {"EXIT", EXIT_CODE}
};

// 명령어 개수
#define INSTRUCTION_COUNT (sizeof(instructions) / sizeof(Instruction))

// 파일 존재 여부 확인
int file_exists(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file) {
        fclose(file);
        return 1;
    }
    return 0;
}

// 명령어 변환 함수
unsigned int assemble_instruction(char *line) {
    char command[10];
    sscanf(line, "%s", command);

    for (int i = 0; i < INSTRUCTION_COUNT; i++) {
        if (strcasecmp(command, instructions[i].name) == 0) {
            return instructions[i].opcode;
        }
    }
    return 0; // 오류 발생 시 0 반환
}

int main() {
    char input_file[100];
    unsigned int pc = START_PC;

    while (1) {
        printf("Enter Input File Name: ");
        scanf("%s", input_file);

        if (strcmp(input_file, "terminate") == 0) {
            break;
        }

        if (!file_exists(input_file)) {
            printf("Input file does not exist!!\n");
            continue;
        }

        FILE *input = fopen(input_file, "r");
        FILE *output_o = fopen(strcat(input_file, ".o"), "w");
        FILE *output_trace = fopen(strcat(input_file, ".trace"), "w");

        char line[100];
        int valid = 1;

        while (fgets(line, sizeof(line), input)) {
            if (line[0] == '\n') continue; // 빈 줄 무시

            unsigned int machine_code = assemble_instruction(line);
            if (machine_code == 0) {
                printf("Syntax Error!!\n");
                valid = 0;
                break;
            }

            fprintf(output_o, "%08X\n", machine_code);
            fprintf(output_trace, "%d\n", pc);
            pc += 4;
        }

        fclose(input);
        fclose(output_o);
        fclose(output_trace);

        if (!valid) {
            remove(strcat(input_file, ".o"));
            remove(strcat(input_file, ".trace"));
        }
    }

    return 0;
}
