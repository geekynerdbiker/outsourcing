#include <stdio.h>
#include <stdlib.h>

#define MAX_FILTER_LEN 257

short x_buffer[MAX_FILTER_LEN];
float coeffs[MAX_FILTER_LEN];

void main(int argcLPF, const char * argvLPF[]) {
    FILE *fi, *fo;
    short filter_len = 8;
    short k;
    short x;
    short y;
    float ftemp;
    
    if (argcLPF < 3) {
        printf("Usage : %s input output\n", argvLPF[0]);
        exit(-1);
    }
    
    if ((fi = fopen(argvLPF[1], "rb")) == NULL) {
        printf("Input file [%s] is not found.\n", argvLPF[1]);
        exit(-1);
    }
    fo = fopen(argvLPF[2], "wb");
    
    for (k = 0; k < filter_len; k++) {
        coeffs[k] = 1.0 / 8.0;
    }
    
    while (1) {
        if (fread(&x, sizeof(short), 1, fi) == NULL) break;
        
        x_buffer[filter_len-1] = x;
        ftemp = 0.0;
        for (k = 0; k < filter_len; k++) {
            ftemp += coeffs[k] * x_buffer[k];
        }
        
        if (ftemp < -32768.0)
            ftemp = -32768.0;
        else if (ftemp > 32767.0)
            ftemp = 32767.0;
        
        y = (short)ftemp;
        fwrite(&y, sizeof(short), 1, fo);
        
        printf("%d\n", y);
        
        for (k = 0; k < filter_len; k++) {
            x_buffer[k] = x_buffer[k+1];
        }
    }
    
    fclose(fi); fclose(fo);
}
