#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define MAX_YEAR_DURATION    10    // 기간
#define LINEAR_SEARCH 0
#define BINARY_SEARCH 1

// 구조체 선언
typedef struct {
    char    name[20];        // 이름
    char    sex;            // 성별 M or F
    int        freq[MAX_YEAR_DURATION]; // 연도별 빈도
} tName;

typedef struct {
    int        len;        // 배열에 저장된 이름의 수
    int        capacity;    // 배열의 용량 (배열에 저장 가능한 이름의 수)
    tName* data;        // 이름 배열의 포인터
} tNames;

// 선형탐색(linear search) 버전
void load_names_lsearch(FILE* fp, int year_index, tNames* names);

// 이진탐색(binary search) 버전
void load_names_bsearch(FILE* fp, int year_index, tNames* names);

// 구조체 배열을 화면에 출력
void print_names(tNames* names, int num_year);

// qsort를 위한 비교 함수
// 정렬 기준 : 이름(1순위), 성별(2순위)
int compare(const void* n1, const void* n2);

////////////////////////////////////////////////////////////////////////////////
// 함수 정의 (definition)

void load_names_lsearch(FILE* fp, int year_index, tNames* names) {

    char line[50];
    tName sName;
    int check = 0;
    
    while (fgets(line, sizeof(line), fp) != NULL){
        sscanf(line, "%[^','],%[^','],%d", sName.name, &sName.sex, &sName.freq[0]);
        if (names->len >= names->capacity) {
            names->capacity *= 2;
            names->data = (tName *)realloc(names->data, names->capacity * sizeof(tName));
        }
        
        for (int i = 0; i < names->len; i++) {
            if (compare(&sName,&names->data[i]) == 0) {
                names->data[i].freq[year_index] = sName.freq[0];
                check++;
                break;
            }
            else {
                continue;
            }
        }
        if (check == 0) {
            names->data[names->len] = sName;
            memset(names->data[names->len].freq, 0, MAX_YEAR_DURATION * sizeof(int));
            names->data[names->len].freq[year_index] = sName.freq[0];
            names->len++;
        }
        check = 0;
    }
}
void load_names_bsearch(FILE* fp, int year_index, tNames* names) {

    char line[50];
    tName sName;
    tName* find;
    int num = 0;
    
    while (fgets(line, sizeof(line), fp) != NULL) {
        sscanf(line, "%[^','],%[^','],%d", sName.name, &sName.sex, &sName.freq[0]);
        if ((names->len + num) >= names->capacity) {
            names->capacity *= 2;
            names->data = (tName *)realloc(names->data, names->capacity * sizeof(tName));
        }

        if (year_index == 0) {
            names->data[names->len] = sName;
            memset(names->data[names->len].freq, 0, MAX_YEAR_DURATION * sizeof(int));
            names->data[names->len].freq[year_index] = sName.freq[0];
            names->len++;
        }
        else {
            find = (tName *)bsearch(&sName, names->data, names->len, sizeof(tName), compare);
            if (find == NULL) {
                names->data[names->len+num] = sName;
                memset(names->data[names->len+num].freq, 0, MAX_YEAR_DURATION * sizeof(int));
                names->data[names->len+num].freq[year_index] = sName.freq[0];
                num++;
            }
            else { find->freq[year_index] = sName.freq[0]; }
        }


    }
    if (num > 0) {
        names->len = names->len + num;
        num = 0;
    }

}
int compare(const void* n1, const void* n2) {
    tName* nameA = (tName*)n1;
    tName* nameB = (tName*)n2;

    if (strcmp(nameA->name, nameB->name) == 0) {
        if (nameA->sex - nameB->sex > 0) {
            return 1;
        }
        else if (nameA->sex - nameB->sex < 0) {
            return -1;
        }
        else { return 0; }
    }
    else {
        if (strcmp(nameA->name, nameB->name) > 0) {
            return 1;
        }
        else {
            return -1;
        }
    }
}

void print_names(tNames* names, int num_year) {
    for (int i = 0; i < names->len; i++) {
        printf("%s\t", names->data[i].name);
        printf("%c\t", names->data[i].sex);
        for (int j = 0; j < num_year; j++) {
            printf("%d\t", names->data[i].freq[j]);
        }
        printf("\n");
    }
}


// 이름 구조체를 초기화
// len를 0으로, capacity를 1로 초기화
// return : 구조체 포인터
tNames* create_names(void)
{
    tNames* pnames = (tNames*)malloc(sizeof(tNames));

    pnames->len = 0;
    pnames->capacity = 1;
    pnames->data = (tName*)malloc(pnames->capacity * sizeof(tName));

    return pnames;
}

// 이름 구조체에 할당된 메모리를 해제
void destroy_names(tNames* pnames)
{
    free(pnames->data);
    pnames->len = 0;
    pnames->capacity = 0;

    free(pnames);
}

////////////////////////////////////////////////////////////////////////////////
int main(int argc, char** argv)
{
    tNames* names;
    int mode;

    FILE* fp;
    int num_year = 0;

    if (argc <= 2)
    {
        fprintf(stderr, "Usage: %s mode FILE...\n\n", argv[0]);
        fprintf(stderr, "mode\n\t-l\n\t\twith linear search\n\t-b\n\t\twith binary search\n");
        return 1;
    }

    if (strcmp(argv[1], "-l") == 0) mode = LINEAR_SEARCH;
    else if (strcmp(argv[1], "-b") == 0) mode = BINARY_SEARCH;
    else {
        fprintf(stderr, "unknown mode : %s\n", argv[1]);
        return 1;
    }

    // 이름 구조체 초기화
    names = create_names();

    // 첫 연도 알아내기 "yob2009.txt" -> 2009
    int start_year = atoi(&argv[2][strlen(argv[2]) - 8]);

    for (int i = 2; i < argc; i++)
    {
        num_year++;
        fp = fopen(argv[i], "r");
        if (!fp) {
            fprintf(stderr, "cannot open file : %s\n", argv[i]);
            return 1;
        }

        int year = atoi(&argv[i][strlen(argv[i]) - 8]); // ex) "yob2009.txt" -> 2009

        fprintf(stderr, "Processing [%s]..\n", argv[i]);

        if (mode == LINEAR_SEARCH)
        {
            // 연도별 입력 파일(이름 정보)을 구조체에 저장
            // 선형탐색 모드
            load_names_lsearch( fp, year-start_year, names);

        }
        else // (mode == BINARY_SEARCH)
        {
            // 이진탐색 모드
            load_names_bsearch( fp, year-start_year, names);

            // 정렬 (이름순 (이름이 같은 경우 성별순))
            qsort( names->data, names->len, sizeof(tName), compare);
        }
        fclose(fp);

    }

    // 정렬 (이름순 (이름이 같은 경우 성별순))
    qsort( names->data, names->len, sizeof(tName), compare);

    // 이름 구조체를 화면에 출력
    print_names( names, num_year);

    // 이름 구조체 해제
    destroy_names(names);

    return 0;
}
