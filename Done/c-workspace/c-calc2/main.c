#include <stdio.h>
#include <string.h>
#include "calc.h"
#pragma warning(disable:4996)

#define MAX_LEN 999 // 수식 최대 길이

/**
 * 수식 계산 과정
 * 1. 중위수식 입력
 * 2. 입력된 수식이 올바른지 판단
 * 		2-1. 올바르지 않을 시 종료
 * 		2-2. 올바르면 3으로 이동
 * 3. 중위수식 -> 후위수식 변환
 * 4. 후위수식 계산
*/

int main() {
	char infix[MAX_LEN] = { '\0' };
  
	while(1) {
		// 입력
		fgets(infix, MAX_LEN, stdin);

		// 빈 수식 입력 시 종료
		if (strcmp(infix, "\n") == 0) { 
      break;
    }
		infix[strlen(infix) - 1] = '\0'; // 수식 문자열 마지막 널 문자 처리

		// 수식 평가(계산)
    evaluate(infix);
	}
  

  return 0;
}
