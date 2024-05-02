#ifndef dcl_h
#define dcl_h

#include <stdio.h>
#include <string.h>
#include "gettoken.h"

extern int crashflag;
extern int tokentype;
extern char token[];
extern char name[];
extern char out[];

void dcl(void);
void dirdcl(void);

void dcl(void)
{
    int ns=0;

    for(ns; gettoken() == '*'; ns++);

    dirdcl();
    if(crashflag) return;

    while(ns-- > 0) strcat(out, " pointer to");
}


void dirdcl(void)
{
    int type;

    if (tokentype == '('){
        
        dcl();

        if(tokentype != ')'){
             printf("error: missing )\n");
             crashflag = 1;
             return;
        }

    } else if(tokentype == NAME) {
        strcpy(name, token);

    } else {
        printf("error: expected name or (dcl)\n");
        crashflag = 1;
        return;
    }
    
    while((type = gettoken()) == PARENS || type == BRACKETS)
        if (type == PARENS) {
             strcat(out, " function taking args of type ");
             while(gettoken() != ')'){
                if(tokentype == ',') strcat(out, ", ");
                else strcat(out, token);
             }
             strcat(out, " returning");
        }
        
        else {
            strcat(out, " array");
            strcat(out, token);
            strcat(out, " of");
        }
}

#endif /* dcl_h */
