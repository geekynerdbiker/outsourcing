#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <libgen.h> // Include for basename

#include "encode.h"
#include "decode.h"
#include "dict.h"

int main(int argc, char *argv[])
{
    static char bin[64], bout[64];
    setvbuf(stdin, bin, _IOFBF, 64);
    setvbuf(stdout, bout, _IOFBF, 64);

    char *exec_name = basename(argv[0]); // Get the executable name

    int maxBits = 12;
    int pruning = 0;
    int stage = 1;
        
    // TODO: Parsing logic
    char *stage_env = getenv("STAGE");
    if (stage_env != NULL) {
        stage = atoi(stage_env);
    }

    int opt;

    while ((opt = getopt(argc, argv, "m:p")) != -1) {
        switch (opt) {
            case 'm':
                maxBits = atoi(optarg);
                if (maxBits == 8 || maxBits > 20) {
                    maxBits = 12;
                }
                if (maxBits < 9 || maxBits > 16) {
                    fprintf(stderr, "Error: MAXBITS must be between 9 and 16\n");
                    exit(1);
                }
                break;
            case 'p':
                pruning = 1;
                break;
            default:
                fprintf(stderr, "Usage: %s [-m MAXBITS] [-p] < input > output\n", argv[0]);
                exit(1);
        }
    }

    if (strcmp(exec_name, "encode") == 0) {
        encode(pruning, maxBits, stage);
    } else if (strcmp(exec_name, "decode") == 0) {
        if (argc > 1) {
            fprintf(stderr, "decode: invalid option '%s'\n", argv[1]);
            exit(1);
        }
        decode(stage);
    } else {
        fprintf(stderr, "Usage: %s [-m MAXBITS] [-p] < input > output\n", argv[0]);
        fprintf(stderr, "       %s < input > output\n", argv[0]);
        exit(1);
    }
    exit (0);
}
