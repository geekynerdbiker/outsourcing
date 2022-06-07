//
//  main.c
//  c-sequence
//
//  Created by Jacob An on 2022/06/06.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/wait.h>
#include "ku_fs_input.h"

// 결과 오름차순 정렬을 위한 함수
void sort(int arr[], int count) {
    int tmp;
    
    for (int i = 0; i < count; i++)
        for (int j = 0; j < count - 1; j++)
            if (arr[j] > arr[j + 1]) {
                tmp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tmp;
            }
}

int main(int argc, char* argv[]) {
    int max_iter = (int)(MAXS - strlen(argv[1]));
    int c_num = (MAXS - strlen(argv[1])) / (float)atoi(argv[2])+0.999;
    int msg_get, max_id = 0;
    int arrived_msg[1000];
    
    key_t ipc_key;
    size_t buffer_len;
    
    struct {
        long id;
        int value;
    }msg;
    
    buffer_len = sizeof(msg.value);
    // IPC Key 생성 및 생성된 키로부터 메세지 GET
    ipc_key = ftok("./tmp/foo", 1946);
    msg_get = msgget(ipc_key, IPC_CREAT|0600);
    
    // 메세지를 받지 못하면 종료.
    if (msg_get < 0) {
        perror("msgget()");
        exit(0);
    }
    
    // 입력받은 i만큼의 child process 생성
    for (int cnt = 0; cnt < atoi(argv[2]); cnt++) {
        if (fork() == 0) {
            int send_num = 0;
            // 각각의 child process에 대해서 inputs[]의 process order * c_num번째 부터 검사
            for (int i = cnt * c_num; i < (cnt+1) * c_num; i++) {
                // inputs[]의 최대 길이보다 크면 다음으로 이동
                if (i > max_iter) continue;
                
                // 문자열의 첫 글자와 같을 때
                if (input[i] == argv[1][0]) {
                    int k = 0;
                    // 나머지 길이만큼 검사
                    for (int j = 1; j < strlen(argv[1]); j++) {
                        // 다음 글자가 다르면 k = 1
                        if (input[i+j] != argv[1][j]) {
                            k = 1;
                            j = (int)strlen(argv[1]);
                        }
                    }
                    // 동일한 문자열을 시퀀스를 발견하면
                    if (k == 0) {
                        send_num += 1;
                        msg.id = i;
                        msg.value = i;
                        // 메세지 전송
                        if (msgsnd(msg_get, &msg, buffer_len, 0) == -1) {
                            perror("msgsnd()");
                            exit(0);
                        }
                    }
                }
            }
            exit(send_num);
        }
    }
    
    int child_status;
    for (int i = 0; i < atoi(argv[2]); i++){
        pid_t wpid= wait(&child_status);
        max_id += WEXITSTATUS(child_status);
    }
    
    for (int i = 0; i < max_id; i++){
        if (msgrcv(msg_get, &msg, buffer_len, 0, 0) == -1) {
            perror("msgrcv()");
            exit(0);
        }
        else {
            arrived_msg[i] = msg.value;
        }
        
    }
    
    // 메세지 배열 정렬
    sort(arrived_msg, sizeof(int) * max_id);
    
    for (int i = 0; i < max_id; i++) {
        printf("%d\n", arrived_msg[i]);
    }
}
