#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 600 // 노드갯수
#define M 9999 // 최대값

FILE* fp;
int data[N][N];

typedef struct {
    char lineNumber[N][20]; // 역 고유번호
    char name[N][20]; // 역 이름
    char nosun[N][20]; // 역 노성
    int number[N]; // 역 순서 번호
    int dist[N]; // 정점까지의 거리
    int via[N]; // 이전 정점
    int startNumber; // 시작 정점
    int destNumber; // 도착 정점
} GraphNode;

int checkName(char insert[], GraphNode* subway);
int findIndexByName(char name[], GraphNode* subway);
int findIndexByLineNumber(char lineNumber[], GraphNode* subway);
void readFile(GraphNode* subway);
void findStartAndDest(GraphNode* subway, char start[], char dest[]);
void findPath(GraphNode* subway, int option);
void printPath(GraphNode *subway, char start[], char dest[], int option);

// 역이름 확인
int checkName(char insert[], GraphNode* subway) {
    int i;
    for (i = 0; i < N; i++) {
        if (!strcmp(insert, subway->name[i]))
            return 1;
    }
    return 0;
}
// 역이름으로 인덱스 확인
int findIndexByName(char name[], GraphNode* subway) {
    int i;
    for (i = 0; i < N; i++) {
        if (strcmp(name, subway->name[i]) == 0)
            return i;
    }
    return -1;
}
// 고유 번호로 인덱스 확인
int findIndexByLineNumber(char lineNumber[], GraphNode* subway) {
    int i;
    for (i = 0; i < N; i++) {
        if (strcmp(lineNumber, subway->lineNumber[i]) == 0)
            return i;
    }
    return -1;
}
// 역이름으로 정점 간의 거리정보 입력
void readFile(GraphNode* subway) {
    int weight, num1, num2, w = 0;
    int i = 0, s, e, temp = 0;

    for (s = 0; s < N; s++) {
        for (e = 0; e < N; e++) {
            if (s == e) // 정점이 같을 때
                data[s][e] = 0;
            else // 최대로 초기화
                data[s][e] = M;
        }
    }

    char* filename = "data/역이름.csv";
    fp = fopen(filename, "r");
    if (!fp) {
        printf("Missing input file: %s\n", filename);
        return;
    }

    int count = 0;
    char line[1024];
    while (!feof(fp)) {
        fgets(line, 1024, fp);
        if (count == 0) {
            count++;
            continue;
        }


        char* p = strtok(line, ",");
        strcpy(subway->lineNumber[count], p);

        p = strtok(NULL, "\n");
        strcpy(subway->name[count], p);
        

        subway->number[count] = count;
        count++;
    }
    fclose(fp);

    char* filename_list[18] = { "data/1지선.csv", "data/1호선.csv", "data/2지선.csv", "data/2호선.csv", "data/3호선.csv", "data/4호선.csv", "data/5지선.csv",
                        "data/5호선.csv", "data/6호선.csv", "data/7호선.csv", "data/8호선.csv", "data/9호선.csv", "data/경의선.csv", "data/경춘선.csv",
                        "data/공항철도.csv", "data/분당선.csv", "data/인천1선.csv", "data/중앙선.csv" };

    char* nosun[18] = { "1지선", "1호선", "2지선", "2호선", "3호선", "4호선", "5지선", "5호선", "6호선",
                    "7호선", "8호선", "9호선", "경의선", "경춘선", "공항철도", "분당선", "인천1호선", "중앙선" };

    for (s = 0; s < 18; s++) {
        fp = fopen(filename_list[s], "r");
        if (!fp) {
            printf("Missing input file: %s\n", filename_list[s]);
            return;
        }

        i = 1;
        char seq[N][100]; // 해당 노선의 모든 고유번호 저장
        fgets(line, 1024, fp);
        count = 0;
        char* p = strtok(line, ",");
        while (p != NULL) {
            strcpy(seq[count], p);
            p = strtok(NULL, ",");
            count++;
        }

        while (!feof(fp)) {
            fgets(line, 1024, fp);
            char* p = strtok(line, ",");
            int start_number = findIndexByLineNumber(p, subway); // 고유번호의 인덱스 찾아 저장
            strcpy(subway->nosun[start_number], nosun[s]); // 인덱스로 노선 정보 삽입
            int end_number;

            count = 1;
            while (1) {
                p = strtok(NULL, ",");
                if (p == NULL) break;
                weight = atoi(p);
                if (weight < M) { // 최대값보다 작으면 연결된 정점
                    end_number = findIndexByLineNumber(seq[count], subway); //고유번호 행렬로 정점 인덱스 탐색
                    if (end_number == -1) {
                        for (int i = 0; seq[count][i] != 0; i++) {
                            if (seq[count][i] == '\n') {
                                seq[count][i] = 0;
                                break;
                            }
                        }
                        end_number = findIndexByLineNumber(seq[count], subway);
                    }
                    // 양방향 연결
                    data[start_number - 1][end_number - 1] = weight;
                    data[end_number - 1][start_number - 1] = weight;
                }
                count++;
            }
        }

        fclose(fp);
    }

    srand(time(NULL));
    filename = "data/환승정보.csv";
    fp = fopen(filename, "r");
    if (!fp) {
        printf("Missing input file: %s\n", filename);
        return;
    }

    char seq[N][100];
    fgets(line, 1024, fp);
    count = 0;
    char* p = strtok(line, ",");
    while (p != NULL) {
        strcpy(seq[count], p);
        p = strtok(NULL, ",");
        count++;
    }

    while (!feof(fp)) {
        fgets(line, 1024, fp);
        char* p = strtok(line, ",");
        int start_number = findIndexByLineNumber(p, subway);
        int end_number;

        count = 1;
        while (1) {
            p = strtok(NULL, ",");
            if (p == NULL) break;
            weight = atoi(p);

            if (weight != 0 && weight < M) {
                int random = (rand() % weight) + 1;
                end_number = findIndexByLineNumber(seq[count], subway);
                if (end_number == -1) {
                    for (int i = 0; seq[count][i] != 0; i++) {
                        if (seq[count][i] == '\n') {
                            seq[count][i] = 0;
                            break;
                        }
                    }
                    end_number = findIndexByLineNumber(seq[count], subway);
                }
                data[start_number - 1][end_number - 1] = random;
                data[end_number - 1][start_number - 1] = random;
            }
            count++;
        }
    }

    fclose(fp);
}

// 출발지와 도착지에 따른 고유 번호 찾기
void findStartAndDest(GraphNode* subway, char start[], char dest[]) {
    subway->startNumber = findIndexByName(start, subway);
    subway->destNumber = findIndexByName(dest, subway);
}

// 최소환승 혹은 최단거리 찾음
void findPath(GraphNode* subway, int option) {
    int i = 0, j, k, min;
    int v[N];

    // 최소 환승일 경우 초기화
    if (option == 2)
    {
        for (i = 0; i < N; i++) {
            for (j = 0; j < N; j++) {
                // 환승역은 이름이 같으므로 고유번호로 비교
                if (strcmp(subway->name[i + 1], subway->name[j + 1]) == 0) {
                    data[i][j] += 1000;
                }


                if (i == j) {
                    data[i][j] = 0;
                }
            }
        }
    }

    // 시작점으로부터의 최단거리들 구하기
    for (j = 0; j < N; j++)
    {
        v[j] = 0;
        subway->dist[j] = M;
    }

    // 시작번호 지정
    subway->dist[subway->startNumber - 1] = 0;

    // 정점의 수만큼 반복
    for (i = 0; i < N; i++)
    {
        // 최단거리 초기화
        min = M;
        for (j = 0; j < N; j++)
        {
            // 최단거리이면 갱신
            if (v[j] == 0 && subway->dist[j] < min) {
                k = j;
                min = subway->dist[j];
            }
        }
        // 방문 확인
        v[k] = 1;
        if (min == M)break;// 최단거리이면 갱신
        for (j = 0; j < N; j++)
        {
            if (subway->dist[j] > subway->dist[k] + data[k][j])
            {
                subway->dist[j] = subway->dist[k] + data[k][j];
                subway->via[j] = k;
            }
        }
    }
}

// 최단거리 출력함수
void printPath(GraphNode *subway, char start[], char dest[], int option) {
    int path[N], path_cnt = 0;
    int i = 0, k, temp = 600;
    int count = 0;
    int transfer = 0;
    int transfer_time = 0;

    // 경로 저장
    k = subway->destNumber - 1;
    while (1)
    {
        path[path_cnt++] = k;
        if (k == (subway->startNumber - 1))break;
        k = subway->via[k];
    }

    // 경로 출력
    printf("<출발>\n");
    while (strcmp(start, subway->name[path[path_cnt - 1] + 1]) == 0) {
        path_cnt--;
        if (option == 2 && !(strcmp(start, subway->name[path[path_cnt - 1] + 1])))
        {
            subway->dist[subway->destNumber - 1] -= 1000;
            data[path[path_cnt]][path[path_cnt - 1]] -= 1000;
        }
        subway->dist[subway->destNumber - 1] -= data[path[path_cnt]][path[path_cnt - 1]];
    }
    count = path_cnt + 1;
    for (i = path_cnt; i >= 1; i--)
    {
        if (strcmp(subway->name[temp], subway->name[path[i] + 1]) == 0) {
            transfer += 1;
            if (option == 2)
            {
                subway->dist[subway->destNumber - 1] -= 1000;
                printf("─> <환승: 소요시간 %d분> %s\n", data[path[i]][path[i + 1]] - 1000, subway->name[path[i] + 1]);
                transfer_time += data[path[i]][path[i + 1]] - 1000;
            }
            else {
                printf("─> <환승: 소요시간 %d분> %s\n", data[path[i]][path[i + 1]], subway->name[path[i] + 1]);
                transfer_time += data[path[i]][path[i + 1]];
            }
            continue;
        }
        if (!(strcmp(dest, subway->name[path[i] + 1])))
        {
            if (option == 2 && !(strcmp(dest, subway->name[path[i] + 1])))
            {
                subway->dist[subway->destNumber - 1] -= 1000;
                data[path[i]][path[i + 1]] -= 1000;
            }
            subway->dist[subway->destNumber - 1] -= data[path[i]][path[i + 1]];
            transfer++;
            break;
        }
        printf("─> <%s> %s\n", subway->nosun[path[i] + 1], subway->name[path[i] + 1]);
        temp = path[i] + 1;
    }

    printf("─> <%s> %s\n", subway->nosun[path[i] + 1], subway->name[path[i] + 1]);

    count -= transfer;
    printf("\n소요시간 : %d (%d + 환승 소요 시간: %d) 분\n",
        subway->dist[subway->destNumber - 1], subway->dist[subway->destNumber - 1] - transfer_time, transfer_time);
    printf("정거장 수 : %d 개\n", count);
    getchar();
}

int main() {
    GraphNode *subway = (GraphNode *)malloc(sizeof(GraphNode));
    readFile(subway);

    int way;
    char start[100], dest[100];

    do {
        printf("출발역을 입력해주세요: ");
        scanf("%s", start);

        printf("도착역을 입력해주세요: ");
        scanf("%s", dest);

        if (strcmp(start, dest) == 0)
            printf("출발역과 도착역이 같습니다. 다시 입력하시오\n");
        else if (checkName(start, subway) && checkName(dest, subway))
            break;
        else
            printf("잘못된 역을 입력했습니다. 다시 입력하시오\n");

    } while (1);

    findStartAndDest(subway, start, dest);

    printf("\n방식? 1. 최단경로 2. 최소환승\n:");
    scanf("%d", &way);
    printf("\n");
    switch (way)
    {
    case 1:
        printf("최단경로\n");
        findPath(subway, way);
        printPath(subway, start, dest, way);
        break;
    case 2:
        printf("최소환승\n");
        findPath(subway, way);
        printPath(subway, start, dest, way);
        break;
    default:
        printf("잘못된 값을 입력했습니다. 종료합니다.");
        break;
    }
}
