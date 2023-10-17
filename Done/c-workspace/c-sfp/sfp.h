#ifndef SFP_H
#define SFP_H

typedef unsigned short sfp;

sfp int2sfp(int input);
int sfp2int(sfp input);
sfp float2sfp(float input);
float sfp2float(sfp input);

sfp sfp_add(sfp in1, sfp in2);
sfp sfp_mul(sfp in1, sfp in2);
char* sfp_cmp(sfp in1, sfp in2);
char* sfp2bits(sfp result);


#endif
