#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

void read_file();
void RETURN();
void FACTOR();
void COND();
void TERM();
void TERM_CHECK();
void EXPR();
void EXPR_CHECK();
void RHS();
void ASSIGN();
void STMT();
void BLOCK();
void ARG();
void ARGS();
void DECL(int n);
void RUN();
void TREE();

static char LINE[200];
static char ERROR[200];
static char TABLE[200][200];

static int i = 0;
static int len = 0;

bool error = false;