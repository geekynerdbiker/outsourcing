#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char * argv[]) {
    FILE *fi, *fo, *fi_coeff;
    int filter_len, k;
    
    fopen_s(fi, argv[1],"rb");
    if (fi == NULL) {
        printf("Input file [%s] is not found. \n", argv[1]);
        getchar(); exit(-1);
    }
    fopen_s(fo, argv[2],"rb");
    if (fo == NULL) {
        printf("Output file [%s] is not found. \n", argv[2]);
        getchar(); exit(-1);
    }
    
    filter_len = atoi(argv[3]);
    fopen_s(&fi_coeff, "coeffs_iir.txt", "r");
    
    if (fi_coeff == NULL) {
        printf("Could not find the file !!! \n");
        getchar(); exit(-1);
    }
    
    float coeffs_a[filter_len], coeffs_b[filter_len];
    for (k = 0; k < filter_len; k++) {
        fscanf_s(fi_coeff, "%e", &coeffs_b[k], sizeof(float));
        printf("%e \n", coeffs_b[k]);
    }
    
    for (k = 0; k < filter_len; k++) {
        fscanf_s(fi_coeff, "%e", &coeffs_a[k], sizeof(float));
        printf("%e \n", coeffs_a[k]);
    }
    fclose(fi_coeff);
    
    printf("Press any key \n");
    getchar();
    
    fclose(fi);
    fclose(fo);
    
    return 0;
}
