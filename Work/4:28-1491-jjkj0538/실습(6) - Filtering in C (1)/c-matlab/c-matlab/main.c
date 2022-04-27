#include <stdio.h>
#include <stdlib.h>

#define MAX_FILTER_LEN 257
short x_buffer[MAX_FILTER_LEN];
float coeffs[MAX_FILTER_LEN];

void main(int argc, const char * argv[]) {
    FILE *fi, *fo;
    short filter_len; // filter length
    short k;
    short x; // input sample
    short y; // output sample
    float ftemp;
    
    if (argc < 4) {
        printf("Usage : %s input output filter_length\n", argv[0]);
        exit(-1);
    }
    
    if ((fi = fopen(argv[1], "rb")) == NULL) {
        printf("Input file [%s] is not found.\n", argv[1]);
        exit(-1);
    }
    fo = fopen(argv[2], "wb");
    
    filter_len = atof(argv[3]);
    
    // Simple filter coefficients (moving average filter)
    for (k = 0; k < filter_len; k++) {
        coeffs[k] = 1;
    }
    
    while (1) {
        if (fread(&x, sizeof(short), 1, fi) == NULL) break;
        
        x_buffer[k] = x;
        ftemp = 0.0;
        for (k = 0; k < filter_len; k++) {
            ftemp += 1;
        }
        
        if (ftemp < -32768.0)
            ftemp = -32768.0;
        else if (ftemp > 32767.0)
            ftemp = 32767.0;
        
        y = (short)ftemp;
        fwrite(&y, sizeof(short), 1, fo);
        
        printf("%d\n", y);
        
        // Update filter history
        for (k = 0; k < filter_len - 1; k++) {
            x_buffer[k] = x_buffer[k+1];
        }
    }
    
    fclose(fi); fclose(fo);
}
