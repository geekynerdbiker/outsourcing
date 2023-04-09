#include <stdio.h>
#include <string.h>
#include <limits.h> // 정수형 변수타입 int의 최댓값과 최솟값을 나타내기 위해 호출
#define N 500

#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable: 4996)

int user_ids[N], users[N][N];
int item_ids[N], items[N][N];
int k;
int v[N];
int T[N][N];

int dot(int x[], int y[]) { // 내적
    int result = 0;
    
    for (int i = 0; i < k; i++) // 각각의 원소들을 벡터의 크기만큼 순차적으로 곱하여 결과에 누적합 계산
        result += x[i] * y[i];
    
    return result;
}

int distance(int x[], int y[]) { // 거리
    int result = 0;
    
    for (int i = 0; i < k; i++) // 각각의 원소들을 벡터의 크기만큼 순차적으로 차의 제곱하여 결과에 누적합 계산
        result += (x[i] - y[i]) * (x[i] - y[i]);
    
    return result;
}

void add_user() {
    int id;
    scanf("%d", &id); // 유저 id를 입력받음
    
    if (user_ids[id]) { // 유저 id가 양수(이미 등록됨)이면 에러 출력 후 함수 종료
        printf("Error\n");
        return;
    }
    
    for (int i = 0; i < k; i++) // k만큼 users 배열의 id번째 인덱스에 0부터 차례로 벡터 원소 입력받음
        scanf("%d", &users[id][i]);
    user_ids[id] = 1; // 유저 등록으로 기록
}

void del_user() {
    int id;
    scanf("%d", &id);
    
    if (!user_ids[id]) {
        printf("Error\n");
        return;
    }
    
    user_ids[id] = 0; // 유저 등록 되지 않음으로 기록
    for (int i = 0; i < k; i++)
        users[id][i] = 0; // 유저 벡터 0으로 초기화
}

void add_item() {
    int id;
    scanf("%d", &id);
    
    if (item_ids[id]) { // 아이템 id가 양수(이미 등록됨)이면 에러 출력 후 함수 종료
        printf("Error\n");
        return;
    }
    
    for (int i = 0; i < k; i++) // 유저와 동일한 방식
        scanf("%d", &items[id][i]);
    item_ids[id] = 1;
}

void del_item() {
    int id;
    scanf("%d", &id);
    
    if (!item_ids[id]) {
        printf("Error\n");
        return;
    }
    
    item_ids[id] = 0; // 유저와 동일한 방식
    for (int i = 0; i < k; i++)
        items[id][i] = 0;
}

void recommend() {
    int id;
    scanf("%d", &id);
    
    if (!user_ids[id]) {
        printf("Error\n");
        return;
    }
    
    int max = INT_MIN, max_index = -1; // 최댓값을 정수 자료형의 최솟값(limits.h)으로, 최댓값의 인덱스를 음수로(인덱스는 음수 불가능) 초기화
    for (int i = 0; i < N; i++) {
        if (item_ids[i]) { // id가 i인 아이템이 존재할 때
            if (dot(users[id], items[i]) > max) { // 유저의 벡터와 아이템의 벡터의 내적값이 최댓값보다 클 때, (최초 실행시 최댓값이 정수의 최솟값이라 클 수 밖에 없음.
                max = dot(users[id], items[i]); // 최댓값에 내적값 갱신
                max_index = i; // 최댓값 인덱스에 현재 아이템의 인덱스 저장
            }
        }
    }
    
    if (max == INT_MIN) { // 최댓값이 정수의 최솟값일 때 -> 내적함수가 한번도 실행된 적이 없음 -> 아이템이 존재하지 않음.
        printf("Error\n"); // 에러 출력 후 함수 종료.
        return;
    }
    
    printf("%d\n", max_index); // 바로 위 조건문에서 종료되지 않으면 출력 -> 아이템이 최소 1개는 존재하므로 최댓값은 갱신되고, 해당 출력문 호출
}

void find_similar() { // 바로 위 추천 함수와 구조는 비슷
    int id;
    scanf("%d", &id);
    
    if (!user_ids[id]) {
        printf("Error\n");
        return;
    }
    
    int min = INT_MAX, min_index = -1; // 반대로 최솟값을 정수의 최댓값으로 초기화, 인덱스는 같은 방법으로 초기화.
    for (int i = 0; i < N; i++) {
        if (i == id) // 입력받은 id와 탐색하는 유저의 id가 동일할 경우 -> 본인과 본인을 비교할 경우 무조건 0 이므로 문제 조건에 따라 스킵
            continue;
        if (user_ids[i]) {
            if (distance(users[id], users[i]) < min) { // 거리 측정 함수를 통해 최솟값 갱신
                min = distance(users[id], users[i]);
                min_index = i;
            }
        }
    }
    
    if (min == INT_MAX) { // 전 함수와 동일
        printf("Error\n");
        return;
    }
    printf("%d\n", min_index);
}

void transform() {
    int matrix[N][N];
    
    for (int i = 0; i < k; i++) // 매트릭스 입력 받음.
        for (int j = 0; j < k; j++)
            scanf("%d", &matrix[i][j]);

    for (int i = 0; i < N; i++) { // 모든 유저의 id를 탐색할 변수 i
        int tmp[N]; // 결괏값을 임시로 저장할 배열
        if (user_ids[i]) {
            for (int j = 0; j < k; j++) { // tmp 배열의 원소 값 인덱스 -> 유저 벡터 한바퀴를 돌아야 한칸의 값이 나오기 때문
                for (int l = 0; l < k; l++) { // 매트릭스의 행 인덱스 -> k * k 이기 때문
                    for (int m = 0; m < k; m++)  { // 매트릭스의 열 인덱스 이면서 유저 벡터의 원소 인덱스
                        tmp[j] += users[i][m] * matrix[l][m]; // 행렬곱 계산
                    }
                } // 이 부분은 이해안되시면 반복문 손으로 변수 움직여가면서 한칸씩 보면 바로 이해되실거에요.
            }
        }
        memcpy(users[i], tmp, sizeof(int)*k); // 저장해놓은 tmp 값들을 해당 유저의 벡터로 갱신. 중간에 한칸한칸 갱신을 하면, 매트릭스의 행이 바뀔 때 마다 값이 갱신되어서 정상적인 계산이 안됨.
        // memcpy 함수 : (arr1, arr2, size) -> arr1 배열에 arr2 배열을 size(바이트) 만큼 복사
    }
}

// 메인 함수는 따로 작성하지 않겠습니다.
int main() {
    char cmd_type[15];
    
    while (1) {
        scanf("%s", cmd_type);
        
        if (!strcmp(cmd_type, "set_k")) {
            scanf("%d", &k);
        }
        else if (!strcmp(cmd_type, "add_user")) {
            add_user();
        }
        else if (!strcmp(cmd_type, "del_user")) {
            del_user();
        }
        else if (!strcmp(cmd_type, "add_item")) {
            add_item();
        }
        else if (!strcmp(cmd_type, "del_item")) {
            del_item();
        }
        else if (!strcmp(cmd_type, "recommend")) {
            recommend();
        }
        else if (!strcmp(cmd_type, "find_similar")) {
            find_similar();
        }
        else if (!strcmp(cmd_type, "transform")) {
            transform();
        }
        else if (!strcmp(cmd_type, "exit")) {
            break;
        }
    }
    
    return 0;
}
