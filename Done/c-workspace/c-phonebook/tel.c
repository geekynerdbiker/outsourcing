#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 입력 최대 길이
#define MAX_BUFFER_SIZE 90

typedef struct Node Node;

// 전화번호를 저장할 단방향 연결리스트 노드
struct Node {
    char name[30];
    char phone[20];
    char memo[40];
    
    Node* next;
};

// 리스트의 헤드 전역 초기화
Node* head = NULL;

// search를 위해 작성. 검색할 문자열이 해당 노드의 이름, 전화번호, 메모 중 하나에 포함되어 있는지 검사
int isSubstring(Node *n, char* option) {
    if (strstr(n->name, option) != NULL)
        return 1;
    if(strstr(n->phone, option) != NULL)
        return 1;
    if (strstr(n->memo, option) != NULL)
        return 1;
    return 0;
}

// 탐색 함수
int search(char* option) {
    Node* p = head;
    
    // 순번 출력을 위한 인덱싱
    int index = 0;
    while (p != NULL) {
        // 현재 노드의 이름, 전화번호, 메모 중 하나에 포함되어 있다면 출력
        if (isSubstring(p, option))
            printf("%d %s %s %s\n", ++index, p->name, p->phone, p->memo);
        p = p->next;
    }
    return index;
};

// 삽입 옵션
void add(char* name, char* phone, char* memo) {
    Node* p = head;
    Node* n = (Node *)malloc(sizeof(Node));
    
    // 내용 입력 및 초기화
    strcpy(n->name, name);
    strcpy(n->phone, phone);
    strcpy(n->memo, memo);
    n->next = NULL;
    
    // 리스트가 비어있을 때
    if (p == NULL) {
        head = n;
        return;
    }
    
    // 그 외의 경우
    while (p->next != NULL)
        p = p->next;
    p->next = n;
}

// 삭제 옵션
int delete(char* option) {
    int range = search(option);
    
    // 인덱스 입력
    printf("which one? ");
    int indexToDelete;
    scanf("%d", &indexToDelete);
    
    if (indexToDelete < 1 || indexToDelete > range) return 1;
    // 입력받은 인덱스와 노드의 해당 인덱스가 같으면 삭제
    Node* p = head;
    Node* q = NULL;
    int index = 0;
    while (p != NULL) {
        if (indexToDelete == ++index) {
            // 삭제할 노드가 헤드인 경우
            if (p == head) {
                head = p->next;
                return 0;
            }
            // 그 외
            q->next = p->next;
            return 0;
        }
        q = p;
        p = p->next;
    }
    return 0;
}

// 리스트 옵션
void list(void) {
    Node* p = head;
    
    int index = 0;
    while (p != NULL) {
        printf("%d %s %s %s\n", ++index, p->name, p->phone, p->memo);
        p = p->next;
    }
}

// 파일 입력 및 노드 추가
int init(void) {
    FILE* fp = fopen("data.txt", "r");
    
    // 파일이 없으면 종료
    if (fp == NULL) {
        printf("File not found.\n");
        return 1;
    }
    
    char buffer[MAX_BUFFER_SIZE];
    char name[20], phone[30], memo[40];
    
    // 파일의 끝까지 입력 받음
    while (fgets(buffer, MAX_BUFFER_SIZE, fp) != NULL) {
        // 행의 마지막 개행문자 널문자로 변경
        buffer[strlen(buffer) - 1] = '\0';
        
        // ":"를 구분자로 토크나이징
        char* token = strtok(buffer, ":");
        strcpy(name, token);
        token = strtok(NULL, ":");
        strcpy(phone, token);
        token = strtok(NULL, ":");
        if (token != NULL) strcpy(memo, token);
        else strcpy(memo, "");
        
        // 리스트에 노드 추가
        add(name, phone, memo);
    }
    return 0;
}

int main(int argc, const char * argv[]) {
    // 파일이 없으면 종료
    if (init() == 1) return 1;
    
    char buffer[MAX_BUFFER_SIZE];
    
    while (1) {
        printf("$tel ");
        fgets(buffer, MAX_BUFFER_SIZE, stdin);
        char* cmd = strtok(buffer, " ");
        
        // 아무 옵션도 입력하지 않은 경우
        if (strcmp(cmd, "\n") == 0) {
                printf("\t- $tel [option]: search name, phone, memo included [option].\n");
                printf("\t- $tel [-a] [option 1] [option 2] [option 3]: add [option 1] as name, [option 2] as phone and [option 3] as memo.\n");
                printf("\t- $tel [-d] [option]: search [option] and print list to choose to delete.\n");
                printf("\t- $tel [-l]: print list alphabetic order.\n");
        }
        // 삽입 옵션
        else if (strcmp(cmd, "-a") == 0) {
            char name[20], phone[30], memo[40];
            
            cmd = strtok(NULL, " ");
            strcpy(name, cmd);
            cmd = strtok(NULL, " ");
            strcpy(phone, cmd);
            cmd = strtok(NULL, " ");
            if (cmd != NULL) strcpy(memo, cmd);
            else strcpy(memo, "");
            cmd[strlen(cmd) - 1] = '\0';
            
            printf("%s %s %s\n", name, phone, memo);
            printf("add? [Y/N]: ");
            char ans;
            scanf("%c", &ans);
            
            if(ans == 'Y') add(name, phone, memo);
            getchar();
        }
        // 삭제 옵션
        else if (strcmp(cmd, "-d") == 0) {
            char* option = strtok(NULL, " ");
            option[strlen(option) - 1] = '\0';
            int rst = delete(option);
            if (rst) exit(1);
            getchar();
        }
        // 리스트 옵션
        else if (strcmp(cmd, "-l\n") == 0) {
            list();
        }
        // 검색 옵션
        else {
            cmd[strlen(cmd) - 1] = '\0';
            int found = search(cmd);
            if (found) printf("match found.\n");
            else printf("no match found.\n");
        }
        printf("\n");
    }
    
    return 0;
}
