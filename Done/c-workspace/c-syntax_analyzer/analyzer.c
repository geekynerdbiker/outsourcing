#include "analyzer.h"

void read_file() {
	FILE *fp = fopen("input.txt", "r");

	if (!fp) {
		printf("Cannot open file.\n");
		exit(0);
	}

	char c;
	char array[200][200];
	int row = 0, col = 0;
	
    do {
		c = fgetc(fp);

		if (c == '\n' || c == EOF) {
			array[row][col] = '\0';
			row++;
			col = 0;
		} else {
			array[row][col] = c;
			col++;
		}
	} while (c != EOF);
	
	fclose(fp);

	int i = 0;

	while (i < 200) {
		strcpy(TABLE[i], array[i]);
		i++;
	}
}

void RETURN()  {
	FACTOR();

	if (strcmp(TABLE[i], "semi") == 0)
		i++;
}

void FACTOR() {
	if (strcmp(TABLE[i], "lparen") == 0) {
		i++;
		FACTOR();

		if (strcmp(TABLE[i], "rparen") == 0)
            i++;
		else {
			error = true;
			LINE[200] = "[FACTOR] Expected rparent";
			ERROR[200] = TABLE[i]; i++;
		}
	} else if (strcmp(TABLE[i], "id") == 0 || strcmp(TABLE[i], "num" ) == 0)
		i++;
	else {
		error = true;
		LINE[200] = "[FACTOR] Expected NUM or ID";
		ERROR[200] = TABLE[i]; i++;
	}
}

void COND() {
	FACTOR();

	if (strcmp(TABLE[i], "comp") != 0) {
		error = true;
		LINE[200] = "[COND] Expected comp";
		ERROR[200] = TABLE[i]; i++;
	} else {
		i++;
		FACTOR();
	}
}

void TERM() {
	FACTOR();
	TERM_CHECK(); 
}

void TERM_CHECK() {
	if (strcmp(TABLE[i], "multdiv") == 0) {
		i++;
		TERM();
	} else if (!strcmp(TABLE[i], "addsub") == 0) {
		error = true;
		LINE[200] = "[TERM] Expected multdiv or addsub";
		ERROR[200] = TABLE[i]; i++;		
	}
}

void EXPR() {
	TERM();
	EXPR_CHECK();
}

void EXPR_CHECK() {
	if (strcmp(TABLE[i],  "addsub") == 0) {
		i++;
		EXPR();
	} else if (!strcmp(TABLE[i],  "semi" ) == 0 && !strcmp(TABLE[i], "rparen") == 0 ) {
		error = true;
		LINE[200] = "[EXPR] Expected addsub, rparen or semi";
		ERROR[200] = TABLE[i]; i++;
		
	}
}

void RHS() {
	if (strcmp(TABLE[i], "lparen") == 0 || strcmp(TABLE[i], "id") == 0 || strcmp(TABLE[i], "num") == 0)
		EXPR();
	else if (strcmp(TABLE[i],  "literal") == 0)
		i++;
	else
		error = true;
		LINE[200] = "[RHS] Expected literal";
		ERROR[200] = TABLE[i]; i++;
}

void ASSIGN() {
	if (strcmp(TABLE[i],  "assign") == 0) {
		i++;
		RHS();
	} else {
		error = true;
		LINE[200] = "[RHS] Expected assign";
		ERROR[200] = TABLE[i]; i++;
		
	}
}

void STMT() {
	if (strcmp(TABLE[i],  "vtype") == 0) {
		i++;
		
        if (strcmp(TABLE[i],  "id") == 0) {
			i++;
			
            if (strcmp(TABLE[i],  "semi") == 0)
				i++;
			else {
				error = true;
				LINE[200] = "[STMT] Expected semi";
				ERROR[200] = TABLE[i]; i++;
			}
		} else {
			error = true;
			LINE[200] = "[STMT] Expected id";
			ERROR[200] = TABLE[i]; i++;
		}
	} else if (strcmp(TABLE[i],  "id") == 0) {
		i++;
		ASSIGN();
			if (strcmp(TABLE[i],  "semi") == 0)
				i++;
			else {	error = true;
				LINE[200] = "[STMT] Expected semi";
				ERROR[200] = TABLE[i]; i++;
			}
	} else if (strcmp(TABLE[i],  "if") == 0) {
		if (strcmp(TABLE[i],  "lparen") == 0) {
			i++;
			COND();

			if (strcmp(TABLE[i],  "rparen") == 0) {
				i++;

				if (strcmp(TABLE[i],  "lbrace") == 0) {
					i++;
					BLOCK();

					if (strcmp(TABLE[i],  "rbrace") == 0) {
						i++;
						
                        if (strcmp(TABLE[i],  "else") == 0) {
							i++;
							
                            if (strcmp(TABLE[i],  "lbrace") == 0) {
								i++;
								BLOCK();
								
                                if (strcmp(TABLE[i],  "rbrace") == 0)
									i++;
								else {
									error = true;
									LINE[200] = "[STMT] Expected rbrace";
									ERROR[200] = TABLE[i]; i++;
								}
							} else {
								error = true;
								LINE[200] = "[STMT] Expected lbrace";
								ERROR[200] = TABLE[i]; i++;
							}
						} else {
							error = true;	
							LINE[200] = "[STMT] Expected else";
							ERROR[200] = TABLE[i]; i++;
						}
					} else {
						error = true;	
						LINE[200] = "[STMT] Expected rbrace";
						ERROR[200] = TABLE[i]; i++;
					}
				} else {
					error = true;	
					LINE[200] = "[STMT] Expected lbrace";
					ERROR[200] = TABLE[i]; i++;
				}
			} else {
				error = true;	
				LINE[200] = "[STMT] Expected rparen";
				ERROR[200] = TABLE[i]; i++;
			}
		} else {
			error = true;	
			LINE[200] = "[STMT] Expected lparen";
			ERROR[200] = TABLE[i]; i++;
		}
	} else if (strcmp(TABLE[i],  "while") == 0) {
		if (strcmp(TABLE[i],  "lparen") == 0) {
			i++;
			COND();

			if (strcmp(TABLE[i],  "rparen") == 0) {
				i++;
				
                if (strcmp(TABLE[i],  "lbrace") == 0) {
					i++;
					BLOCK();
					
                    if (strcmp(TABLE[i],  "rbrace") == 0)
						i++;
					else {
						error = true;	
						LINE[200] = "[STMT] Expected rbrace";
						ERROR[200] = TABLE[i]; i++;
					}
				} else {
					error = true;	
					LINE[200] = "[STMT] Expected lbrace";
					ERROR[200] = TABLE[i]; i++;
				}
			} else {
				error = true;	
				LINE[200] = "[STMT] Expected rparen";
				ERROR[200] = TABLE[i]; i++;
			}
		} else {
			error = true;	
			LINE[200] = "[STMT] Expected lparen";
			ERROR[200] = TABLE[i]; i++;
		}
	} else {
		error = true;
		LINE[200] = "[STMT] Expected while";
		ERROR[200] = TABLE[i]; i++;
		
	}
}

void BLOCK() {
	if (strcmp(TABLE[i], "if") == 0 || strcmp(TABLE[i], "vtype") == 0 || strcmp(TABLE[i], "id") == 0 || strcmp(TABLE[i], "while") == 0) {
		STMT();
		BLOCK();
	}
	else if (!strcmp(TABLE[i], "rbrace") == 0 && !strcmp(TABLE[i], "return") == 0) {
		error = true;
		LINE[200] = "[BLOCK] Expected if, vtype, id, while, rbrace or return";
		ERROR[200] = TABLE[i]; i++;
	}
}

void ARG() {
	if (strcmp(TABLE[i], "vtype") == 0) {
		i++;
		
        if (strcmp(TABLE[i], "id") == 0) {
			i++;
			ARGS();
		} else if (strcmp(TABLE[i], "rparen") == 0)
            i++;
		else {
			error = true;
			LINE[200] = "[ARGS] Expected id or rparn";
			ERROR[200] = TABLE[i]; i++;
		}
	} else if (!strcmp(TABLE[i], "rparen") == 0) {
		error = true;
		LINE[200] = "[ARGS] Expected vtype or rparen";
		ERROR[200] = TABLE[i]; i++;
	}
}

void ARGS() {
	if (strcmp(TABLE[i], "comma") == 0) {
		i++;

		if (strcmp(TABLE[i], "vtype") == 0) {
			i++;
			
            if (strcmp(TABLE[i], "id") == 0) {
				i++;
				ARGS();
			} else {
				error = true;
				LINE[200] = "[ARGS] Expected id";
				ERROR[200] = TABLE[i]; i++;
			}
		} else {
			error = true;
			LINE[200] = "[ARGS] Expected vtype";
			ERROR[200] = TABLE[i]; i++;
		}
	} else if (!strcmp(TABLE[i], "rparen") == 0) {
		error = true;
		LINE[200] = "[ARGS] Expected vtype or rparen";
		ERROR[200] = TABLE[i]; i++;
	}
}

void DECL(int n) {
	i = n;

	if (strcmp(TABLE[i], "lparen") == 0) {
		i++;
		ARG();

		if (strcmp(TABLE[i], "rparen") == 0) {
			i++;

			if (strcmp(TABLE[i], "lbrace") == 0) {
				i++;
				BLOCK();
				RETURN();

				if (strcmp(TABLE[i], "rbrace") != 0) {
					error = true;
					LINE[200] = "[DECL] Expected rbrace";
					ERROR[200] = TABLE[i]; i++;
				}
				else 
                    i++;
			} else {
				error = true;
				LINE[200] = "[DECL] Expected lbrace";
				ERROR[200] = TABLE[i]; i++;
			}
		} else {
			error = true;
			LINE[200] = "[DECL] Expected rparen";
			ERROR[200] = TABLE[i]; i++;
		}
	} else if (!strcmp(TABLE[i], "semi") == 0) {
		error = true;
		LINE[200] = "[DECL] Expected semi or lparen";
		ERROR[200] = TABLE[i]; i++;
	}
}

void RUN() {
	int i = 0;

	if (strcmp(TABLE[i], "vtype") == 0) {
		i++;

		if (strcmp(TABLE[i], "id") == 0) {
			i++;
			DECL(i);
			RUN();
		} else {
			error = true;
			LINE[200] = "[RUN] Expected id";
			ERROR[200] = TABLE[i]; i++;
		}
	} else if (!strcmp(TABLE[i], "$") == 0) {
		error = true;
		strcpy(LINE, "[RUN] Expected vtype or $");
		strcpy(ERROR, TABLE[i]); i++;
	}
}

int main(int argc, char *argv[]) {
	read_file();
	RUN();

	if (error) {
		printf("Code does not pass the parser\n");
		printf(LINE);
		printf("Got instead:");
		printf(ERROR);
		printf("\n");
	} else
		printf("Success\n");
	
	return 0;
}