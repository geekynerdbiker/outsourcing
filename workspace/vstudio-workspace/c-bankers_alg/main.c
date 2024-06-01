#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_TASKS 100
#define MAX_RESOURCES 100
#define MAX_LEN 1000

int available[MAX_RESOURCES]; // 사용 가능한 자원의 수
int max[MAX_TASKS][MAX_RESOURCES]; // 각 프로세스의 최대 자원 요구
int allocation[MAX_TASKS][MAX_RESOURCES]; // 각 프로세스에 현재 할당된 자원 수
int need[MAX_TASKS][MAX_RESOURCES]; // 각 프로세스가 필요로 하는 자원 수
char result[MAX_TASKS][MAX_LEN]; // 결과 저장
int P, R, resource; // 프로세스 수와 자원 유형 수

void calculateNeed() { // 필요한 자원 계산
    for (int i = 0; i < P; i++) {
        for (int j = 0; j < R; j++) {
            need[i][j] = max[i][j] - allocation[i][j]; // 최대값 - 명령 할당량
        }
    }
}

bool isSafe() { // 교착 상태 확인
    int work[MAX_RESOURCES]; // 필요 자원
    bool finish[MAX_TASKS] = { 0 }; // 상태

    for (int i = 0; i < R; i++) {
        work[i] = available[i];
    }

    while (true) {
        bool found = false;
        for (int i = 0; i < P; i++) {
            if (!finish[i]) { // 작업이 끝나지 않았는데
                bool possible = true;
                for (int j = 0; j < R; j++) {
                    if (need[i][j] > work[j]) { // 자원이 필요한 경우
                        possible = false;
                        break;
                    }
                }
                if (possible) {
                    for (int k = 0; k < R; k++) {
                        work[k] += allocation[i][k];
                    }
                    finish[i] = true;
                    found = true;
                }
            }
        }
        if (!found) {
            break;
        }
    }

    for (int i = 0; i < P; i++) {
        if (!finish[i]) { // 마쳐지진 작업이 있는 경우
            return false;
        }
    }
    return true;
}

bool requestResource(int process, int request[]) {
    bool isGranted = false;
    bool isWaiting = false;

    for (int i = 0; i < R; i++) {
        if (request[i] > need[process][i]) { // 자원이 부족하면 대기
            strcat(result[process], "-");
            isWaiting = true;
            break;
        }
    }

    if (!isWaiting) {
        for (int i = 0; i < R; i++) {
            if (request[i] > available[i]) { // 가용 자원이 모자랄 때
                strcat(result[process], "-");
                isWaiting = true;
                break;
            }
        }
    }

    if (!isWaiting) {
        for (int i = 0; i < R; i++) {
            available[i] -= request[i];
            allocation[process][i] += request[i];
            need[process][i] -= request[i];
        }

        if (isSafe()) { // 교착 상태가 아닌지 체크
            isGranted = true;
            strcat(result[process], "Q");
        }
        else {
            strcat(result[process], "q");
        }
    }

    if (!isGranted && !isWaiting) { // 할당 실패 시 자원 돌려 받음
        for (int i = 0; i < R; i++) {
            available[i] += request[i];
            allocation[process][i] -= request[i];
            need[process][i] += request[i];
        }
    }

    return isGranted;
}

void releaseResource(int process, int release[]) {
    for (int i = 0; i < R; i++) { // 자원 돌려 받음
        available[i] += release[i];
        allocation[process][i] -= release[i];
        need[process][i] += release[i];
    }
    strcat(result[process], "R");
}

void terminateProcess(int process) {
    for (int i = 0; i < R; i++) { // 자원 삭제
        available[i] += allocation[process][i];
        allocation[process][i] = 0;
        need[process][i] = 0;
    }
    strcat(result[process], "T ");
}

int main() {
    FILE* file = fopen("input.txt", "r");

    if (file == NULL) {
        printf("File not found.\n");
        return 1;
    }

    // 자원 초기화
    fscanf(file, "%d %d %d", &R, &P, &resource);
    for (int i = 0; i < P; i++) {
        available[i] = resource;
    }

    // 결과 배열 초기화
    for (int i = 0; i < P; i++) {
        strcpy(result[i], "");
    }

    // 명령 처리
    int t, d, r, u;
    char o[10];

    while (fscanf(file, "%d %d %s %d %d", &t, &d, o, &r, &u) != EOF) {
        int process = t;
        int request[MAX_RESOURCES] = { 0 };

        if (u > available[process-1]) {
            result[process][0] = 'C';
            continue;
        }
        if (r > 0)
            request[process] = u;

        // delay는 무시하고, 실제 명령어만 처리
        if (strcmp(o, "initiate") == 0) {
            max[process][r - 1] = u;
            allocation[process][r - 1] = 0;
            strcat(result[process], "I");
        }
        else if (strcmp(o, "request") == 0) {
            requestResource(process, request);
        }
        else if (strcmp(o, "release") == 0) {
            releaseResource(process, request);
        }
        else if (strcmp(o, "terminate") == 0) {
            terminateProcess(process);
        }
    }

    fclose(file);

    // 결과 출력
    for (int i = 1; i <= P; i++) {
        if (result[i][0] == 'C')
            continue;

        printf("task%d\t", i);
        for (int j = 0; result[i][j] != '\0' != 0; j++) {
            printf("%c ", result[i][j]);
        }
        printf("\n");
    }

    return 0;
}