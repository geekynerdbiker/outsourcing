#include "analyzer.h"
#pragma warning(disable:4996)

void read_file() {
	FILE* fp = fopen("input.txt", "r");

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
		}
		else {
			array[row][col] = c;
			col++;
		}
	} while (c != EOF);

	fclose(fp);

	int i = 0;

	while (i < 200) {
		strcpy(TABLE[i], array[i]);
		i++;
		len++;
	}
}

void RETURN() {
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
			if (i >= len)
				return;
			error = true;
			strcpy(LINE, "[FACTOR] Expected rparent");
			strcpy(ERROR, TABLE[i]); i++;
		}
	}
	else if (strcmp(TABLE[i], "id") == 0 || strcmp(TABLE[i], "num") == 0)
		i++;
	else {
		if (i >= len)
			return;
		error = true;
		strcpy(LINE, "[FACTOR] Expected NUM or ID");
		strcpy(ERROR, TABLE[i]); i++;
	}
}

void COND() {
	FACTOR();

	if (strcmp(TABLE[i], "comp") != 0) {
		if (i >= len)
			return;
		error = true;
		strcpy(LINE, "[COND] Expected comp");
		strcpy(ERROR, TABLE[i]); i++;
	}
	else {
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
	}
	else if (strcmp(TABLE[i], "addsub") != 0) {
		if (i >= len)
			return;
		error = true;
		strcpy(LINE, "[TERM] Expected multdiv or addsub");
		strcpy(ERROR, TABLE[i]); i++;
	}
}

void EXPR() {
	TERM();
	EXPR_CHECK();
}

void EXPR_CHECK() {
	if (strcmp(TABLE[i], "addsub") == 0) {
		i++;
		EXPR();
	}
	else if (strcmp(TABLE[i], "semi") != 0 && strcmp(TABLE[i], "rparen") != 0) {
		if (i >= len)
			return;
		error = true;
		strcpy(LINE, "[EXPR] Expected addsub, rparen or semi");
		strcpy(ERROR, TABLE[i]); i++;

	}
}

void RHS() {
	if (strcmp(TABLE[i], "lparen") == 0 || strcmp(TABLE[i], "id") == 0 || strcmp(TABLE[i], "num") == 0)
		EXPR();
	else if (strcmp(TABLE[i], "literal") == 0)
		i++;
	else {
		if (i >= len)
			return;
		error = true;
		strcpy(LINE, "[RHS] Expected literal");
		strcpy(ERROR, TABLE[i]); i++;
	}
}

void ASSIGN() {
	if (strcmp(TABLE[i], "assign") == 0) {
		i++;
		RHS();
	}
	else {
		if (i >= len)
			return;
		error = true;
		strcpy(LINE, "[RHS] Expected assign");
		strcpy(ERROR, TABLE[i]); i++;

	}
}

void STMT() {
	if (strcmp(TABLE[i], "vtype") == 0) {
		i++;

		if (strcmp(TABLE[i], "id") == 0) {
			i++;

			if (strcmp(TABLE[i], "semi") == 0)
				i++;
			else {
				if (i >= len)
					return;
				error = true;
				strcpy(LINE, "[STMT] Expected semi");
				strcpy(ERROR, TABLE[i]); i++;
			}
		}
		else {
			if (i >= len)
				return;
			error = true;
			strcpy(LINE, "[STMT] Expected id");
			strcpy(ERROR, TABLE[i]); i++;
		}
	}
	else if (strcmp(TABLE[i], "id") == 0) {
		i++;
		ASSIGN();
		if (strcmp(TABLE[i], "semi") == 0)
			i++;
		else {
			if (i >= len)
				return;
			error = true;
			strcpy(LINE, "[STMT] Expected semi");
			strcpy(ERROR, TABLE[i]); i++;
		}
	}
	else if (strcmp(TABLE[i], "if") == 0) {
		if (strcmp(TABLE[i], "lparen") == 0) {
			i++;
			COND();

			if (strcmp(TABLE[i], "rparen") == 0) {
				i++;

				if (strcmp(TABLE[i], "lbrace") == 0) {
					i++;
					BLOCK();

					if (strcmp(TABLE[i], "rbrace") == 0) {
						i++;

						if (strcmp(TABLE[i], "else") == 0) {
							i++;

							if (strcmp(TABLE[i], "lbrace") == 0) {
								i++;
								BLOCK();

								if (strcmp(TABLE[i], "rbrace") == 0)
									i++;
								else {
									if (i >= len)
										return;
									error = true;
									strcpy(LINE, "[STMT] Expected rbrace");
									strcpy(ERROR, TABLE[i]); i++;
								}
							}
							else {
								if (i >= len)
									return;
								error = true;
								strcpy(LINE, "[STMT] Expected lbrace");
								strcpy(ERROR, TABLE[i]); i++;
							}
						}
						else {
							if (i >= len)
								return;
							error = true;
							strcpy(LINE, "[STMT] Expected else");
							strcpy(ERROR, TABLE[i]); i++;
						}
					}
					else {
						if (i >= len)
							return;
						error = true;
						strcpy(LINE, "[STMT] Expected rbrace");
						strcpy(ERROR, TABLE[i]); i++;
					}
				}
				else {
					if (i >= len)
						return;
					error = true;
					strcpy(LINE, "[STMT] Expected lbrace");
					strcpy(ERROR, TABLE[i]); i++;
				}
			}
			else {
				if (i >= len)
					return;
				error = true;
				strcpy(LINE, "[STMT] Expected rparen");
				strcpy(ERROR, TABLE[i]); i++;
			}
		}
		else {
			if (i >= len)
				return;
			error = true;
			strcpy(LINE, "[STMT] Expected lparen");
			strcpy(ERROR, TABLE[i]); i++;
		}
	}
	else if (strcmp(TABLE[i], "while") == 0) {
		if (strcmp(TABLE[i], "lparen") == 0) {
			i++;
			COND();

			if (strcmp(TABLE[i], "rparen") == 0) {
				i++;

				if (strcmp(TABLE[i], "lbrace") == 0) {
					i++;
					BLOCK();

					if (strcmp(TABLE[i], "rbrace") == 0)
						i++;
					else {
						if (i >= len)
							return;
						error = true;
						strcpy(LINE, "[STMT] Expected rbrace");
						strcpy(ERROR, TABLE[i]); i++;
					}
				}
				else {
					if (i >= len)
						return;
					error = true;
					strcpy(LINE, "[STMT] Expected lbrace");
					strcpy(ERROR, TABLE[i]); i++;
				}
			}
			else {
				if (i >= len)
					return;
				error = true;
				strcpy(LINE, "[STMT] Expected rparen");
				strcpy(ERROR, TABLE[i]); i++;
			}
		}
		else {
			if (i >= len)
				return;
			error = true;
			strcpy(LINE, "[STMT] Expected lparen");
			strcpy(ERROR, TABLE[i]); i++;
		}
	}
	else {
		if (i >= len)
			return;
		error = true;
		strcpy(LINE, "[STMT] Expected while");
		strcpy(ERROR, TABLE[i]); i++;

	}
}

void BLOCK() {
	if (strcmp(TABLE[i], "if") == 0 || strcmp(TABLE[i], "vtype") == 0 || strcmp(TABLE[i], "id") == 0 || strcmp(TABLE[i], "while") == 0) {
		STMT();
		BLOCK();
	}
	else if (strcmp(TABLE[i], "rbrace") != 0 && strcmp(TABLE[i], "return") != 0) {
		if (i >= len)
			return;
		error = true;
		strcpy(LINE, "[BLOCK] Expected if, vtype, id, while, rbrace or return");
		strcpy(ERROR, TABLE[i]); i++;
	}
}

void ARG() {
	if (strcmp(TABLE[i], "vtype") == 0) {
		i++;

		if (strcmp(TABLE[i], "id") == 0) {
			i++;
			ARGS();
		}
		else if (strcmp(TABLE[i], "rparen") == 0)
			i++;
		else {
			if (i >= len)
				return;
			error = true;
			strcpy(LINE, "[ARGS] Expected id or rparn");
			strcpy(ERROR, TABLE[i]); i++;
		}
	}
	else if (strcmp(TABLE[i], "rparen") != 0) {
		if (i >= len)
			return;
		error = true;
		strcpy(LINE, "[ARGS] Expected vtype or rparen");
		strcpy(ERROR, TABLE[i]); i++;
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
			}
			else {
				if (i >= len)
					return;
				error = true;
				strcpy(LINE, "[ARGS] Expected id");
				strcpy(ERROR, TABLE[i]); i++;
			}
		}
		else {
			if (i >= len)
				return;
			error = true;
			strcpy(LINE, "[ARGS] Expected vtype");
			strcpy(ERROR, TABLE[i]); i++;
		}
	}
	else if (strcmp(TABLE[i], "rparen") != 0) {
		if (i >= len)
			return;
		error = true;
		strcpy(LINE, "[ARGS] Expected vtype or rparen");
		strcpy(ERROR, TABLE[i]); i++;
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
					if (i >= len)
						return;
					error = true;
					strcpy(LINE, "[DECL] Expected rbrace");
					strcpy(ERROR, TABLE[i]); i++;
				}
				else
					i++;
			}
			else {
				if (i >= len)
					return;
				error = true;
				strcpy(LINE, "[DECL] Expected lbrace");
				strcpy(ERROR, TABLE[i]); i++;
			}
		}
		else {
			if (i >= len)
				return;
			error = true;
			strcpy(LINE, "[DECL] Expected rparen");
			strcpy(ERROR, TABLE[i]); i++;
		}
	}
	else if (strcmp(TABLE[i], "semi") != 0) {
		if (i >= len)
			return;
		error = true;
		strcpy(LINE, "[DECL] Expected semi or lparen");
		strcpy(ERROR, TABLE[i]); i++;
	}
}

void RUN() {
	int i = 0;

	if (strcmp(TABLE[i], "vtype") == 0) {
		i++;

		if (strcmp(TABLE[i], "id") == 0) {
			i++;
			DECL(i);
		}
		else {
			if (i >= len)
				return;
			error = true;
			strcpy(LINE, "[RUN] Expected id");
			strcpy(ERROR, TABLE[i]); i++;
		}
	}
	else if (strcmp(TABLE[i], "$") != 0) {
		if (i >= len)
			return;
		error = true;
		strcpy(LINE, "[RUN] Expected vtype or $");
		strcpy(ERROR, TABLE[i]); i++;
	}

	
}

void TREE() {
	for (int k = 0; k < i - 1; k++)
		printf("%s - ", TABLE[k]);
	printf("%s\n", TABLE[i - 1]);
}

int main(int argc, char* argv[]) {
	read_file();
	RUN();

	if (error) {
		printf("Code does not pass the parser\n");
		printf(LINE);
		printf("Got instead:");
		printf(ERROR);
		printf("\n");
	}
	else {
		printf("Accept\n");
		TREE();
	}

	return 0;
}