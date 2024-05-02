#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>
// https://www.tutorialspoint.com/c_standard_library/limits_h.htm
#include <limits.h>
// https://www.cplusplus.com/reference/cfloat/
#include <float.h>

#define FLOAT_SZ sizeof(float)*CHAR_BIT
#define EXP_SZ (FLOAT_SZ-FLT_MANT_DIG)
#define FRAC_SZ (FLT_MANT_DIG-1)

int main(int argc, char *argv[]) {
    
    // float value = *(float *) &binary; // you are not allowed to do this.
    // unsigned int binary = *(unsigned int*) &value; // you are not allowed to do this.
    
    FILE* fp = fopen(argv[1], "r");
    if (!fp) {
        perror("fopen failed");
        return EXIT_FAILURE;
    }
    
    // SETUP
    char buf;
    unsigned int m1 = 0, m2 = 0;
    
    // first, read the binary number representation of multiplier
    for (int i = FRAC_SZ+EXP_SZ; i>=0; i--) {
        fscanf(fp, "%c", &buf);
        m1 += (buf & 0b1)*pow(2,i);
    }
    /* ... */
    
    // notice that you are reading two different lines; caution with reading
    fscanf(fp, "%c", &buf);
    /* ... */
    
    // first, read the binary number representation of multiplcand
    for (int i = FRAC_SZ+EXP_SZ; i>=0; i--) {
        fscanf(fp, "%c", &buf);
        m2 += (buf & 0b1)*pow(2,i);
    }
    /* ... */
    
    float product = *(float *) &m1 * *(float *) &m2; // you are not allowed to print from this.
    unsigned int ref_bits = *(unsigned int *) &product; // you are not allowed to print from this. But you can use it to validate your solution.
    
    // SIGN
    bool s1 = (m1 >> (FRAC_SZ + EXP_SZ )) & 0b1;
    bool s2 = (m2 >> (FRAC_SZ + EXP_SZ)) & 0b1;
    bool sign = (s1 && !s2) || (s2 && !s1);
    /* ... */
    printf("%d_",sign);
    assert (sign == (1 & ref_bits >> (FRAC_SZ + EXP_SZ)));
    
    // EXP
    // get the exp field of the multiplier and multiplicand
    unsigned short e1 = (m1 - (s1 << (FRAC_SZ + EXP_SZ))) >> FRAC_SZ;
    unsigned short e2 = (m2 - (s2 << (FRAC_SZ + EXP_SZ))) >> FRAC_SZ;
    /* ... */
    // add the two exp together
    unsigned exp = e1 + e2;
    /* ... */
    // subtract bias
    exp = exp - 127;
    /* ... */
    
    // FRAC
    // get the frac field of the multiplier and multiplicand
    unsigned long f1 = (m1 - (s1 << (FRAC_SZ + EXP_SZ)) - (e1 << FRAC_SZ));
    unsigned long f2 = (m2 - (s2 << (FRAC_SZ + EXP_SZ)) - (e2 << FRAC_SZ));
    /* ... */
    // assuming that the input numbers are normalized floating point numbers, add back the implied leading 1 in the mantissa
    f1 += (1 << FRAC_SZ);
    f2 += (1 << FRAC_SZ);
    /* ... */
    // multiply the mantissas
    unsigned long frac = f1 * f2;
    /* ... */
    
    // overflow and normalize
    unsigned long int overflow = (frac >> (FRAC_SZ * 2));
    exp += (overflow / 2);
    frac = frac >> (FRAC_SZ + overflow / 2 - 1);
    /* ... */
    
    // rounding
    unsigned int carry = 0b1 & frac;
    frac = frac >> 1;
    frac += carry;
    /* ... */
    
    // move decimal point
    /* ... */
    
    // PRINTING
    // print exp
    for ( int bit_index=EXP_SZ-1; 0<=bit_index; bit_index-- ) {
        bool trial_bit = 1&exp>>bit_index;
        printf("%d",trial_bit);
        assert (trial_bit == (1&ref_bits>>(bit_index+FRAC_SZ)));
    }
    printf("_");
    
    // print frac
    for ( int bit_index=FRAC_SZ-1; 0<=bit_index; bit_index-- ) {
        bool trial_bit = 1&frac>>bit_index;
        printf("%d",trial_bit);
        assert (trial_bit == (1&ref_bits>>(bit_index)));
    }
    
    fclose(fp);
    return(EXIT_SUCCESS);
    
}
