/**
 * File Name: You should name your source file as your student ID (e.g., 20204870.c)
 * Author: Ix Lab TA Dohwa Kim
 * Year: 2024
 *
 * Description:
 * This file is the skeleton code for the PL parser project.
 * Basic code is provided in the main function and some other functions.
 * Students should not modify the main function or the provided functions.
 * Students should add additional functions and variables to complete the parser.
 * It is IMPORTANT to use the provided functions when you need to print information.
 * Detailed descriptions are given below, so please read carefully.
 * Our automated scoring system may give you 0 points if you modify the provided code, and no exceptions will be accepted.
 *
 * Instructions:
 * - Complete the parser project according to the instructions provided in the word file from the class.
 * - You should NOT modify the pre-made code.
 * - You may add standard library headers like string.h or stdlib.h, but do not use custom headers from the internet.
 *   (Standard libraries should be sufficient for this project.)
 * - You have to submit cmake file too, so you have to modify it little bit like in instruction file. Please just follow instruction
 *
 * Note:
 * If you have any questions about this project, please email me at: kimdohwa2@cau.ac.kr
 */

#include <stdio.h>
#include <string.h>  // Consider adding string.h for strcmp

/**
 * @brief Represents an identifier with a name and value.
 *
 * This structure is used to store information about identifiers
 * in the PL parser project. Each identifier has a name and an associated value.
 * The value can be a string or a numeric value depending on the use case.
 * You can add more fields if you want but DO NOT MODIFY predefined fields
 */
typedef struct {
	char name[50];
	char value[100];
}Ident;

typedef enum {
    assignOp, addOperator, multOperator, semiColon, ident, constant, endOfFile, leftParen, rightParen, unknownToken
}TokenType;

typedef struct {
    TokenType type;
    char tokenString[50];
}Token;

char line[100];
FILE *file;
Ident idArray[50];

void printResultByLine(char *line, int ID, int CON, int OP);
void printIdent(int num_ident);
void parse();
void parse_V();
void printOPWarning(int code);
void printIDError(char *name);

void printOK(void);
void printToken(char *token);
void parseStatements(char *line);
void parseStatement(char *line);
void getNextChar(char *line);
void appendChar(char *line);
void skipWhitespace(char *line);
void getToken(char *line);
void setIdentValue(char *name, char *value);

char *parseExpression(char *line, char *result);
char *parseTermTail(char *line, char *inheritedValue, char *result);
char *parseTerm(char *line, char *result);
char *parseFactor(char *line, char *result);
char *parseFactorTail(char *line, char *inheritedValue, char *result);
char *getIdentValue(char *name);

int isInteger(const char *str);

int addPosition;
int getPosition;
int pushPosition;
int idCount;
int constCount;
int opCount;
int totalId;
int idErrorFlag;
int opWarningFlag;
int verboseFlag;

char currentChar;
char tokenString[100];
char errorIdent[50];

Token nextToken;
Token tokenArray[200];
/**
 *
 * @brief Main function for processing a file.
 *
 * This program expects a file path as a command-line argument.
 * You should provide the absolute path to the file as the first argument
 * when running this program. An absolute path is the complete path from the
 * root directory of your file system to the file.
 *
 * Examples:
 * - On Windows:
 *   student_program.exe C:/Users/YourName/Desktop/test_input.txt
 *   or
 *   student_program.exe C:\\Users\\YourName\\Desktop\\test_input.txt
 *
 * - On Linux/MacOS:
 *   ./student_program /home/yourname/Desktop/test_input.txt
 *
 * Make sure that the file exists at the specified path, and that you have the
 * correct permissions to read the file.
 * 
 *
 *
 */

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s [-v] <filepath>\n", argv[0]);
        return 1;
    }

    int verbose = 0;
    char *filepath = NULL;

    if (strcmp("-v", argv[1]) == 0) {
        verbose = 1;
        if (argc < 3) {
            fprintf(stderr, "Error: No file specified.\n");
            return 1;
        }
        filepath = argv[2];
    } else {
        filepath = argv[1];
    }

    file = fopen(filepath, "r");

    if (file == NULL) {
        fprintf(stderr, "Error: Could not open file %s\n", filepath);
        return 1;
    }

    totalId = 0;
    verboseFlag = verbose;

    while (fgets(line, sizeof(line), file)) {
        if (verbose) {
            parse_V(line);
        } else {
            int i, s;
            char buffer[100];
            for (i = 0, s = 0; line[i] >= 32; i++, s++) {
                buffer[s] = line[i];
                if (line[i] == ';') {
                    buffer[s + 1] = '\0';
                    parse(buffer);
                    s = -1;
                }
            }
            if (s > 1) {
                buffer[s] = '\0';
                parse(buffer);
            }
        }
    }

    if (!verbose) printIdent(totalId);

    fclose(file);
    return 0;
}

/**
 * @brief This function is the starting point of this project with no option -v (print option a).
 *
 * You can freely modify this code or add more functions.
 * However, you SHOULD use the print functions below when you need to print some lines on screen,
 * or you might risk receiving 0 points even if the program works perfectly.
 */
void parse() {
    idCount = constCount = opCount = 0; // ID, 상수, 연산자 카운트 초기화
    getPosition = pushPosition = 0;    // 문자열 읽기 및 토큰 저장 위치 초기화
    idErrorFlag = opWarningFlag = 0;   // 에러와 경고 플래그 초기화

    getNextChar(line); // 현재 줄의 첫 번째 문자 가져오기
    while (currentChar != '\0') { // 줄 끝까지 처리
        getToken(line);          // 토큰 분석
        parseStatements(line);   // 문장(Statements) 파싱
    }

    // 포맷된 결과 문자열 생성
    char formattedLine[100] = "";
    for (int i = 0; i < pushPosition; i++) { // 저장된 토큰 배열 처리
        const char *current = tokenArray[i].tokenString; // 현재 토큰 문자열
        strcat(formattedLine, current); // 결과 문자열에 추가
        if (i < pushPosition - 1) { // 마지막 토큰이 아니면
            const char *next = tokenArray[i + 1].tokenString; // 다음 토큰 문자열
            // 괄호, 세미콜론에 대한 공백 규칙 처리
            if (!strcmp(current, "(") || !strcmp(next, ")") || !strcmp(next, ";")) continue;
            strcat(formattedLine, " "); // 공백 추가
        }
    }

    // 결과 출력
    printResultByLine(formattedLine, idCount, constCount, opCount); // 포맷된 결과 출력
    if (!idErrorFlag && !opWarningFlag) {
        printOK(); // 에러와 경고가 없는 경우 "OK" 출력
    } else if (opWarningFlag > 0 && !idErrorFlag) {
        printOPWarning(opWarningFlag); // 경고만 있는 경우 경고 메시지 출력
    } else {
        printIDError(errorIdent); // 식별자 에러가 있는 경우 에러 메시지 출력
    }
}

/**
 * @brief This function is the starting point of this project with option -v (print option b).
 *
 * You can freely modify this code or add more functions.
 * However, you SHOULD use the print functions below when you need to print some lines on screen,
 * or you might risk receiving 0 points even if the program works perfectly.
 */
void parse_V() {
    idCount = constCount = opCount = 0; // ID, 상수, 연산자 카운트 초기화
    getPosition = addPosition = pushPosition = 0; // 포인터 초기화
    idErrorFlag = opWarningFlag = 0; // 에러와 경고 플래그 초기화

    getNextChar(line); // 현재 줄의 첫 번째 문자 가져오기
    while (currentChar != '\0') { // 줄 끝까지 처리
        addPosition = 0;          // 현재 토큰 문자열 포인터 초기화
        getToken(line);           // 토큰 분석

        if (nextToken.type != unknownToken) { // 인식된 토큰만 처리
            switch (nextToken.type) {
                case assignOp:
                    printToken("assignment_op"); break; // 할당 연산자 출력
                case addOperator:
                    printToken("add_operator"); break; // 덧셈/뺄셈 연산자 출력
                case multOperator:
                    printToken("mult_operator"); break; // 곱셈/나눗셈 연산자 출력
                case semiColon:
                    printToken("semi_colon"); break; // 세미콜론 출력
                case ident:
                    printToken("ident"); break; // 식별자 출력
                case constant:
                    printToken("const"); break; // 상수 출력
                case leftParen:
                    printToken("left_paren"); break; // 왼쪽 괄호 출력
                case rightParen:
                    printToken("right_paren"); break; // 오른쪽 괄호 출력
                default:
                    break; // 처리하지 않는 경우
            }
        }
    }
}

/**
 * @brief Function that prints the line and the number of IDs, constants, and operands.
 *
 * YOU SHOULD NOT MODIFY THIS CODE,
 * or you might risk receiving 0 points.
 *
 * @param line The line that the program has read.
 * @param ID The number of IDs.
 * @param CON The number of constants.
 * @param OP The number of operands.
 * @param 0 to print (OK)
 */
void printResultByLine(char *line, int ID, int CON, int OP) {
    printf("%s\n", line);
    printf("ID: %d; CONST: %d; OP: %d;\n", ID, CON, OP);
}

/**
 * @brief Function that prints the warning message about Operands
 *
 * YOU SHOULD NOT MODIFY THIS CODE,
 * or you might risk receiving 0 points.
 *
 * @param code The warning code of operand
 * 1 : Multiple (+) Operation | 2 : Multiple (-) Operation
 * 3 : Multiple (*) Operation | 4 : Multiple (/) Operation
 * 5 : Wrong Assignment Operation (:=)
 */
void printOPWarning(int code){
	switch(code){
	
    	case 1:
    		printf("(Warning) \"Eliminating duplicate operator (+)\"\n");
    		break;
    	case 2:
    		printf("(Warning) \"Eliminating duplicate operator (-)\"\n");
    		break;
    	case 3:
    		printf("(Warning) \"Eliminating duplicate operator (*)\"\n");
    		break;
    	case 4:
    		printf("(Warning) \"Eliminating duplicate operator (/)\"\n");
    		break;
    	case 5:
    		printf("(Warning) \"Substituting assignment operator (:=)\"\n"); 
    		break;
    	}
}
/**
 * @brief Function that prints OK sign
 *
 */
void printOK(){
	printf("(OK)\n");
}

/**
 * @brief Function that prints the line and the number of IDs, constants, and operands.
 *
 * YOU SHOULD NOT MODIFY THIS CODE,
 * or you might risk receiving 0 points.
 *
 * @param name The name of Identifier that didn't referenced before
 */
void printIDError(char *name){
	printf("(Error) \"referring to undefined identifiers(%s)\"\n",name);
}

/**
 * @brief Function that prints the result of identifiers.
 *
 * YOU SHOULD NOT MODIFY THIS CODE,
 * or you might risk receiving 0 points.
 *
 * Save identifiers in predefined array
 * @param num_ident The number of identifiers.
 * 
 * Result ==> operand1: 2; total: 2;
 */
void printIdent(int num_ident) {
    int i;
    printf("Result ==>");
    for (i = 0; i < num_ident; i++) {
        printf(" %s: %s;", idArray[i].name, idArray[i].value);
    }
}
/**
 * @brief Funtion that prints token by line
 *
 * YOU SHOULD NOT MODIFY THIS CODE,
 * or you might risk receiving 0 points
 *
 * Print token by line
 * This function is used for verbose mode(-v)
 * @param token Token that you want to print
 *
 */
void printToken(char *token){
	printf("%s\n", token);
}

void parseStatements(char *line) {
    // 하나 이상의 문장을 파싱하는 함수.
    // 현재 문장을 파싱하고 세미콜론(;)이 있다면 다음 문장도 재귀적으로 파싱.
    parseStatement(line);
    if (nextToken.type == semiColon) { // 세미콜론으로 문장 구분
        getToken(line); // 다음 토큰을 읽음
        parseStatements(line); // 다음 문장 파싱
    }
}

void parseStatement(char *line) {
    // 단일 문장을 파싱하는 함수.
    // 식별자가 있고, 뒤에 할당 연산자(:=)가 있으면 값을 파싱하여 저장.
    char identName[50];

    if (nextToken.type == ident) { // 식별자 확인
        strcpy(identName, nextToken.tokenString); // 식별자 이름 저장
        getToken(line); // 다음 토큰 읽기

        if (nextToken.type == assignOp) { // 할당 연산자 확인
            char exprValue[50] = "";
            getToken(line); // 다음 토큰 읽기
            parseExpression(line, exprValue); // 표현식 파싱
            setIdentValue(identName, exprValue); // 식별자에 값 설정
        }
    }
}

char *parseExpression(char *line, char *result) {
    // 표현식(Expression)을 파싱하는 함수.
    // 예: "a + b - c" 형태를 처리.
    char termResult[50] = "";
    parseTerm(line, termResult); // 항(Term) 파싱
    parseTermTail(line, termResult, result); // 이어지는 항 파싱
    return result;
}

char *parseTermTail(char *line, char *inheritedValue, char *result) {
    // 이어지는 항(Term)을 처리하는 함수.
    // '+' 또는 '-' 연산자를 만나면 연산을 수행.
    if (nextToken.type == addOperator) { // 덧셈/뺄셈 연산자 확인
        char termResult[50] = "";
        char operator = nextToken.tokenString[0]; // 연산자 저장
        getToken(line); // 다음 토큰 읽기

        parseTerm(line, termResult); // 다음 항(Term) 파싱
        if (strcmp(inheritedValue, "Unknown") && strcmp(termResult, "Unknown")) {
            // 두 값이 모두 "Unknown"이 아닌 경우 계산 수행
            int answer = (operator == '+') ? atoi(inheritedValue) + atoi(termResult)
                                           : atoi(inheritedValue) - atoi(termResult);
            sprintf(result, "%d", answer); // 결과 저장
        } else {
            strcpy(result, "Unknown"); // 값이 하나라도 "Unknown"이면 결과도 "Unknown"
        }
        return parseTermTail(line, result, result); // 재귀 호출로 다음 항 처리
    }
    if (result != inheritedValue) // 값 복사
        strcpy(result, inheritedValue);
    return result;
}

char *parseTerm(char *line, char *result) {
    // 항(Term)을 파싱하는 함수.
    // 예: "a * b / c" 형태를 처리.
    char factorResult[50] = "";
    parseFactor(line, factorResult); // 인수(Factor) 파싱
    parseFactorTail(line, factorResult, result); // 이어지는 인수 처리
    return result;
}

char *parseFactorTail(char *line, char *inheritedValue, char *result) {
    // 이어지는 인수(Factor)를 처리하는 함수.
    // '*' 또는 '/' 연산자를 만나면 연산 수행.
    if (nextToken.type == multOperator) { // 곱셈/나눗셈 연산자 확인
        char factorResult[50] = "";
        char operator = nextToken.tokenString[0]; // 연산자 저장
        getToken(line); // 다음 토큰 읽기

        parseFactor(line, factorResult); // 다음 인수(Factor) 파싱
        if (strcmp(inheritedValue, "Unknown") && strcmp(factorResult, "Unknown")) {
            // 두 값이 모두 "Unknown"이 아닌 경우 계산 수행
            int answer = (operator == '*') ? atoi(inheritedValue) * atoi(factorResult)
                                           : atoi(inheritedValue) / atoi(factorResult);
            sprintf(result, "%d", answer); // 결과 저장
        } else {
            strcpy(result, "Unknown"); // 값이 하나라도 "Unknown"이면 결과도 "Unknown"
        }
        return parseFactorTail(line, result, result); // 재귀 호출로 다음 인수 처리
    }
    if (result != inheritedValue) // 값 복사
        strcpy(result, inheritedValue);
    return result;
}

char *parseFactor(char *line, char *result) {
    // 단일 인수(Factor)를 파싱하는 함수.
    // 괄호로 둘러싸인 표현식, 식별자, 상수 등을 처리.
    if (nextToken.type == leftParen) { // 왼쪽 괄호 확인
        getToken(line); // 다음 토큰 읽기
        parseExpression(line, result); // 괄호 안의 표현식 파싱
        if (nextToken.type == rightParen) { // 오른쪽 괄호 확인
            getToken(line); // 다음 토큰 읽기
        }
    } else if (nextToken.type == ident) { // 식별자 확인
        char *foundValue = getIdentValue(nextToken.tokenString); // 식별자 값 가져오기
        if (!foundValue) { // 값이 없으면 "Unknown" 저장
            strcpy(result, "Unknown");
        } else {
            strcpy(result, foundValue); // 값 복사
        }
        getToken(line); // 다음 토큰 읽기
    } else if (nextToken.type == constant) { // 상수 확인
        strcpy(result, nextToken.tokenString); // 상수 값 복사
        getToken(line); // 다음 토큰 읽기
    }
    return result;
}

char *getIdentValue(char *name) {
    // 식별자의 값을 반환하는 함수.
    // 식별자가 없으면 "Unknown"으로 설정하고 에러 플래그 설정.
    for (int i = 0; i < totalId; i++) {
        if (!strcmp(idArray[i].name, name)) {
            return idArray[i].value; // 식별자 값 반환
        }
    }
    setIdentValue(name, "Unknown"); // 식별자가 없으면 "Unknown"으로 설정
    idErrorFlag = 1; // 에러 플래그 설정
    strcpy(errorIdent, name); // 에러난 식별자 이름 저장
    return NULL;
}

void setIdentValue(char *name, char *value) {
    // 새로운 식별자를 저장하거나 기존 식별자의 값을 업데이트하는 함수.
    for (int i = 0; i < totalId; i++) {
        if (!strcmp(idArray[i].name, name)) {
            strcpy(idArray[i].value, value); // 값 업데이트
            return;
        }
    }
    strcpy(idArray[totalId].name, name); // 새로운 식별자 추가
    strcpy(idArray[totalId++].value, value);
}

void getNextChar(char *line) {
    // 다음 문자를 읽는 함수.
    // 줄 끝에 도달하면 NULL 문자('\0')로 설정.
    if (line[getPosition] != '\0') {
        currentChar = line[getPosition++];
    } else {
        currentChar = '\0';
    }
}

void appendChar(char *line) {
    // 현재 문자를 토큰 문자열에 추가하는 함수.
    if (addPosition < 99) { // 최대 길이 제한 확인
        tokenString[addPosition++] = currentChar;
        tokenString[addPosition] = '\0'; // 문자열 종료 문자 추가
    }
}

void skipWhitespace(char *line) {
    // 공백과 무의미한 문자를 건너뛰는 함수.
    while (((int)currentChar < 33 && currentChar) || isspace(currentChar)) {
        getNextChar(line);
    }
}

Token createToken(TokenType type, char *tokenString) {
    // 새로운 토큰을 생성하는 함수.
    Token token;
    token.type = type; // 토큰 타입 설정
    strncpy(token.tokenString, tokenString, sizeof(token.tokenString) - 1); // 토큰 문자열 복사
    token.tokenString[sizeof(token.tokenString) - 1] = '\0'; // 문자열 종료 문자 추가
    return token;
}

void getToken(char *line) {
    // 줄에서 다음 토큰을 읽어오는 함수.
    addPosition = 0;
    skipWhitespace(line); // 공백 건너뛰기

    if (currentChar == '(') { // 왼쪽 괄호
        getNextChar(line);
        nextToken = createToken(leftParen, "(");
        tokenArray[pushPosition++] = nextToken;
    }
    else if (currentChar == ')') { // 오른쪽 괄호
        getNextChar(line);
        nextToken = createToken(rightParen, ")");
        tokenArray[pushPosition++] = nextToken;
    }
    else if (currentChar == '+') { // 더하기 연산자
        getNextChar(line);
        skipWhitespace(line);
        if (currentChar == '+') { // 중복 연산자 처리
            getNextChar(line);
            opWarningFlag = 1; // 경고 플래그 설정
        }
        opCount++; // 연산자 카운트 증가
        nextToken = createToken(addOperator, "+");
        tokenArray[pushPosition++] = nextToken;
    }
    else if (currentChar == '*') { // 곱하기 연산자
        getNextChar(line);
        skipWhitespace(line);
        if (currentChar == '*') { // 중복 연산자 처리
            getNextChar(line);
            opWarningFlag = 3; // 경고 플래그 설정
        }
        opCount++; // 연산자 카운트 증가
        nextToken = createToken(multOperator, "*");
        tokenArray[pushPosition++] = nextToken;
    }
    else if (isdigit(currentChar)) { // 숫자 상수
        while (isdigit(currentChar)) { // 연속된 숫자 읽기
            appendChar(line);
            getNextChar(line);
        }
        constCount++; // 상수 카운트 증가
        nextToken = createToken(constant, tokenString);
        tokenArray[pushPosition++] = nextToken;
    }
    else if (isalpha(currentChar)) { // 식별자
        while (isalnum(currentChar)) { // 연속된 문자/숫자 읽기
            appendChar(line);
            getNextChar(line);
        }
        idCount++; // 식별자 카운트 증가
        nextToken = createToken(ident, tokenString);
        tokenArray[pushPosition++] = nextToken;
    }
    else if (currentChar == ':' || currentChar == '=') { // 할당 연산자 처리
        if (currentChar == ':') {
            getNextChar(line);
            if (currentChar == '=') {
                getNextChar(line);
                nextToken = createToken(assignOp, ":=");
                tokenArray[pushPosition++] = nextToken;
            }
        } else if (currentChar == '=') {
            getNextChar(line);
            nextToken = createToken(assignOp, ":=");
            tokenArray[pushPosition++] = nextToken;
        }
    }
    else if (currentChar == '/') { // 나누기 연산자
        getNextChar(line);
        skipWhitespace(line);
        if (currentChar == '/') { // 중복 연산자 처리
            getNextChar(line);
            opWarningFlag = 4; // 경고 플래그 설정
        }
        opCount++; // 연산자 카운트 증가
        nextToken = createToken(addOperator, "/");
        tokenArray[pushPosition++] = nextToken;
    }
    else if (currentChar == '-') { // 빼기 연산자
        getNextChar(line);
        skipWhitespace(line);
        if (currentChar == '-') { // 중복 연산자 처리
            getNextChar(line);
            opWarningFlag = 2; // 경고 플래그 설정
        }
        opCount++; // 연산자 카운트 증가
        nextToken = createToken(addOperator, "-");
        tokenArray[pushPosition++] = nextToken;
    }
    else if (currentChar == ';') { // 세미콜론
        getNextChar(line);
        nextToken = createToken(semiColon, ";");
        tokenArray[pushPosition++] = nextToken;
    }
    else { // 알 수 없는 토큰
        while (currentChar > 32 && currentChar != ' ') {
            appendChar(line);
            getNextChar(line);
        }
        nextToken = createToken(unknownToken, tokenString);
    }
}
