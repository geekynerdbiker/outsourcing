#include "sfp.h"
#include <stdlib.h>
#include <string.h>

typedef union fbit {
    float f;
    unsigned int i;
} fbit;

sfp int2sfp(int input){
    sfp output;
    if (!input) output = 0b000000000000000;
    else if (input > 65504) output = 0b0111110000000000;
    else if (input < -65504) output = 0b1111110000000000;
    else {
        unsigned char sign = (input >= 0 ? 0 : 1);
        unsigned char exp;
        unsigned short frac = (input >= 0 ? input : -input);
        unsigned char frac_length = 0;
        unsigned short count_exp = frac;

        while (count_exp != 1) {
            count_exp = count_exp >> 1;
            frac_length++;
        }

        exp = frac_length + (1 << 4) - 1;

        while (frac_length > 10) {
            frac = frac >> 1;
            frac_length--;
        }
             
        while (frac_length < 10) {
            frac = frac << 1;
            frac_length++;
        }
        
        output = (sign << 15) + (exp << 10) + (frac & ((1 << 10) - 1));
    }

    return output;
}

int sfp2int(sfp input){
    int output;

    if ((input >> 10) == 0b011111) {
        if (input & ((1 << 10) - 1) != 0) output = (1 << 31);
        else output = (unsigned) (1 << 31) - 1;
    }
    else if ((input >> 10) == 0b111111) output = (1 << 31);
    else {
        unsigned char sign = ((input >> 15) & 1);
        unsigned char exp = ((input >> 10) & ((1 << 5) - 1)) - ((1 << 4) - 1);
        unsigned short frac = ((input & ((1 << 10) - 1)) + (1 << 10));
        
        if (exp >= 10) output = frac << (exp - 10);
        else output = frac >> (10 - exp);
        if (sign) output = -output;
    }
    return output;
}

sfp float2sfp(float input){
    sfp output;
    fbit uInput;
    uInput.f = input;

    unsigned char sign = (uInput.i >> 31);
    short exp = ((uInput.i & ((unsigned) (1 << 31) - (1 << 23))) >> 23) - ((1 << 7) - (1 << 4));
    unsigned int frac = (uInput.i & ((1 << 23) - 1));
    
    if (uInput.i == 0) output = 0;
    else if (uInput.i == (1 << 31)) output = 0b1000000000000000;
    else if ((exp <= 0)) {
        frac = frac + (1 << 23);
        frac = frac >> (-exp + 1);
        output = (sign << 15) + (frac >> (23 - 10));
    }

    else if ( (exp >= ((1 << 5) - 1)) || ((exp == ((1 << 5) - 2)) && (frac > (((1 << 10) - 1) << (23 - 10)))) ) {
        if (sign == 0) output = 0b0111110000000000;
        else output = 0b1111110000000000;
    }
    
    else output = (sign << 15) + (exp << 10) + (frac >> (23 - 10));
    return output;
}

float sfp2float(sfp input) {
    fbit uOutput;
    unsigned int sign = (input & (1 << 15)) << 16;
    unsigned int exp = ((input & ((1 << 15) - (1 << 10))) + (((1 << 7) - (1 << 4)) << 10)) << (23 - 10);
    unsigned int frac = (input & ((1 << 10) - 1)) << (23 - 10);

    if (exp == ((((1 << 7) - (1 << 4)) << 10) << (23 - 10))) {
        while (((frac & (1 << 23)) == 0) && (frac != 0)) {
            frac = frac << 1;
            exp = exp - (1 << 23);
        }
    }
    uOutput.i = sign + exp + frac;
    return uOutput.f;
}

sfp sfp_add(sfp in1, sfp in2) {
    sfp output;
    unsigned char in1sign = (in1 >> 15) & 1;
    unsigned char in1exp = (in1 >> 10) & ((1 << 5) - 1);
    unsigned short in1frac = in1 & ((1 << 10) - 1);

    unsigned char in2sign = (in2 >> 15) & 1;
    unsigned char in2exp = (in2 >> 10) & ((1 << 5) - 1);
    unsigned short in2frac = in2 & ((1 << 10) - 1);

    unsigned char sum_sign = in1sign ^ in2sign;
    unsigned char sum_exp;
    unsigned short sum_frac;
    unsigned short exp_dif;

    if ((in1exp == 0) && (in2exp > 0)) exp_dif = in2exp - (in1exp + 1);
    else if ((in1exp > 0) && (in2exp == 0)) exp_dif = in1exp - (in2exp + 1);
    else exp_dif = (in1exp >= in2exp ? in1exp - in2exp : in2exp - in1exp);

    if (in1exp == 0b11111 && in2exp == 0b11111) {
        if (in1frac == 0 && in2frac == 0) {
            if (in1sign == 0 && in2sign == 0) output = 0b0111110000000000;
            else if (in1sign == 1 && in2sign == 1) output = 0b1111110000000000;
            else output = 0b0111110000000001;
        }
        else output = 0b0111110000000001;

    }
    else if (in1exp == 0b11111) output = in1;
    else if (in2exp == 0b11111) output = in2;
    else if (in1sign == in2sign) {
        if (in1exp != 0) in1frac += (1 << 10);
        else in1exp++;
        if (in2exp != 0) in2frac += (1 << 10);
        else in2exp++;

        if (in1exp >= in2exp) {
            sum_exp = in1exp;
            sum_frac = in1frac + (in2frac >> exp_dif);
        }

        else {
            sum_exp = in2exp;
            sum_frac = (in1frac >> exp_dif) + in2frac;
        }

        if ((sum_exp == 1) && ((sum_frac & ((1 << 12) - (1 << 10))) == 0)) sum_exp--;
        
        if (sum_frac & (1 << 11)) {
            sum_exp++;
            sum_frac = sum_frac >> 1;
        }

        if (sum_exp >= 0b11111) {
            if (in1sign == 0) return output = 0b0111110000000000;
            else return output = 0b1111110000000000;
        }

        output = (in1sign << 15) + (sum_exp << 10) + (sum_frac & ((1 << 10) - 1));
    }

    else {
        if (in1frac == in2frac && in1exp == in2exp) return output = 0;
        
        if (in1exp != 0) in1frac += (1 << 10);
        else in1exp++;
        if (in2exp != 0) in2frac += (1 << 10);
        else in2exp++;

        if (in1exp > in2exp) {
            sum_sign = in1sign;
            sum_exp = in1exp;
            sum_frac = in1frac - (in2frac >> exp_dif);
        }

        else if (in1exp < in2exp){
            sum_sign = in2sign;
            sum_exp = in2exp;
            sum_frac = in2frac - (in1frac >> exp_dif);
        }

        else {
            if (in1frac > in2frac){
                sum_sign = in1sign;
                sum_exp = in1exp;
                sum_frac = in1frac - in2frac;
            }
            else {
                sum_sign = in2sign;
                sum_exp = in2exp;
                sum_frac = in2frac - in1frac;
            }
        }

        while (((sum_frac & (1 << 10)) == 0) && (sum_exp > 1)) {
            sum_exp--;
            sum_frac = sum_frac << 1;
        }

        if ((sum_exp == 1) && ((sum_frac & (1 << 10)) == 0)) sum_exp--;

        output = (sum_sign << 15) + (sum_exp << 10) + (sum_frac & ((1 << 10) - 1));
    }

    return output;
}

sfp sfp_mul(sfp in1, sfp in2) {

    sfp output;
    unsigned char in1sign = (in1 >> 15) & 1;
    unsigned char in1exp = (in1 >> 10) & ((1 << 5) - 1);
    unsigned short in1frac = in1 & ((1 << 10) - 1);

    unsigned char in2sign = (in2 >> 15) & 1;
    unsigned char in2exp = (in2 >> 10) & ((1 << 5) - 1);
    unsigned short in2frac = in2 & ((1 << 10) - 1);

    unsigned char mul_sign = in1sign ^ in2sign;
    char mul_exp = in1exp + in2exp - ((1 << 4) - 1);
    unsigned int mul_frac;

    if (in1exp == 0b11111 && in2exp == 0b11111) {
        if (in1frac == 0 && in2frac == 0) output = (mul_sign << 15) + (0b11111 << 10);
        else output = 0b0111110000000001;
    }
    else if (in1exp == 0b11111) {
        if (in1frac == 0) {
            if (in2 == 0) output = 0b0111110000000001;
            else output = (mul_sign << 15) + (0b11111 << 10);
        }
        else output = 0b0111110000000001;
    }

    else if (in2exp == 0b11111) {
        if (in2frac == 0) {
            if (in1 == 0) output = 0b0111110000000001;
            else output = (mul_sign << 15) + (0b11111 << 10);
        }
        else output = 0b0111110000000001;
    }

    else {
        if (mul_exp >= ((1 << 5) - 1)) return output = (mul_sign << 15) + (0b11111 << 10);
        
        if (in1exp != 0) in1frac += (1 << 10);
        if (in2exp != 0) in2frac += (1 << 10);
        
        mul_frac = in1frac * in2frac;

        if ((mul_frac & (1 << 21)) != 0) {
            mul_exp++;
            mul_frac = mul_frac >> 1;
        }
        while ((mul_frac & ((1 << 21)-(1 << 11))) != 0) mul_frac = mul_frac >> 1;

        if (mul_exp >= 0b11111) return output = (mul_sign << 15) + (0b11111 << 10);
        else if (mul_exp < 0) return output = 0;

        output = (mul_sign << 15) + (mul_exp << 10) + (mul_frac & ((1 << 10) - 1));
    }
    return output;
}

char* sfp_cmp(sfp in1, sfp in2) {
    char *sfpcmp = (char *)calloc(1, sizeof(char));
    
    float a = sfp2float(in1);
    float b = sfp2float(in2);
    
    if (a > b) strcpy(sfpcmp, ">");
    else if(a < b) strcpy(sfpcmp, "<");
    else strcpy(sfpcmp, "=");
    
    return sfpcmp;
}
char* sfp2bits(sfp result){
    char *sfpstr = (char * )calloc(17, sizeof(char));
    for (int i = 15; i >= 0; i--) {
        sfpstr[i] = '0' + (result & 1);
        result = result >> 1;
    }
    return sfpstr;
}
