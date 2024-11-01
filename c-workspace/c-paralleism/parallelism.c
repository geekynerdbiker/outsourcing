#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include <string.h>

#define MATRIX_SIZE 1000 // 행렬 크기 정의
int A[MATRIX_SIZE][MATRIX_SIZE], B[MATRIX_SIZE][MATRIX_SIZE], C[MATRIX_SIZE][MATRIX_SIZE]; // 행렬 선언
int num_threads_or_processes; // 사용할 스레드 또는 프로세스 개수

char* files[] = {"file1.txt", "file2.txt", "file3.txt", "file4.txt"}; // 압축할 파일 목록
int num_files = sizeof(files) / sizeof(files[0]); // 파일 개수 계산

// 행렬 초기화 함수
void initialize_matrices() {
    srand(time(NULL)); // 랜덤 시드 설정
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            A[i][j] = rand() % 10; // A 행렬에 랜덤 값 대입
            B[i][j] = rand() % 10; // B 행렬에 랜덤 값 대입
        }
    }
}

// 결과 행렬 C 초기화 함수
void reset_result_matrix() {
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            C[i][j] = 0; // C 행렬 초기화
        }
    }
}

// 스레드를 이용한 행렬 곱셈 함수
void* multiply_thread(void* arg) {
    int thread_id = *(int*)arg; // 스레드 ID 얻기
    int rows_per_thread = MATRIX_SIZE / num_threads_or_processes; // 각 스레드가 처리할 행 수
    int start = thread_id * rows_per_thread; // 시작 인덱스
    int end = (thread_id == num_threads_or_processes - 1) ? MATRIX_SIZE : start + rows_per_thread; // 끝 인덱스 설정

    for (int i = start; i < end; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            for (int k = 0; k < MATRIX_SIZE; k++) {
                C[i][j] += A[i][k] * B[k][j]; // 행렬 곱셈 연산
            }
        }
    }
    return NULL; // 스레드 종료
}

// 프로세스를 이용한 행렬 곱셈 함수
void multiply_process(int process_id) {
    int rows_per_process = MATRIX_SIZE / num_threads_or_processes; // 각 프로세스가 처리할 행 수
    int start = process_id * rows_per_process; // 시작 인덱스
    int end = (process_id == num_threads_or_processes - 1) ? MATRIX_SIZE : start + rows_per_process; // 끝 인덱스 설정

    for (int i = start; i < end; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            for (int k = 0; k < MATRIX_SIZE; k++) {
                C[i][j] += A[i][k] * B[k][j]; // 행렬 곱셈 연산
            }
        }
    }
}

// 스레드를 이용한 행렬 곱셈 실행 함수
void multiply_with_threads() {
    for (num_threads_or_processes = 1; num_threads_or_processes <= 16; num_threads_or_processes *= 2) {
        pthread_t threads[num_threads_or_processes]; // 스레드 배열
        int thread_ids[num_threads_or_processes]; // 스레드 ID 배열
        struct timespec start, end; // 시간 측정을 위한 변수

        reset_result_matrix(); // 결과 행렬 초기화
        clock_gettime(CLOCK_MONOTONIC, &start); // 시작 시간 기록

        for (int i = 0; i < num_threads_or_processes; i++) {
            thread_ids[i] = i; // 스레드 ID 초기화
            pthread_create(&threads[i], NULL, multiply_thread, &thread_ids[i]); // 스레드 생성
        }

        for (int i = 0; i < num_threads_or_processes; i++) {
            pthread_join(threads[i], NULL); // 스레드 종료 대기
        }

        clock_gettime(CLOCK_MONOTONIC, &end); // 종료 시간 기록
        double elapsed = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9; // 경과 시간 계산
        printf("\t\tThreads: %d, Time: %f seconds\n", num_threads_or_processes, elapsed); // 결과 출력
    }
}

// 프로세스를 이용한 행렬 곱셈 실행 함수
void multiply_with_processes() {
    for (num_threads_or_processes = 1; num_threads_or_processes <= 16; num_threads_or_processes *= 2) {
        struct timespec start, end; // 시간 측정을 위한 변수

        reset_result_matrix(); // 결과 행렬 초기화
        clock_gettime(CLOCK_MONOTONIC, &start); // 시작 시간 기록

        for (int i = 0; i < num_threads_or_processes; i++) {
            pid_t pid = fork(); // 프로세스 생성
            if (pid == 0) {
                multiply_process(i); // 자식 프로세스에서 행렬 곱셈 수행
                exit(0); // 자식 프로세스 종료
            }
        }

        for (int i = 0; i < num_threads_or_processes; i++) {
            wait(NULL); // 모든 자식 프로세스 종료 대기
        }

        clock_gettime(CLOCK_MONOTONIC, &end); // 종료 시간 기록
        double elapsed = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9; // 경과 시간 계산
        printf("\t\tProcesses: %d, Time: %f seconds\n", num_threads_or_processes, elapsed); // 결과 출력
    }
}

// 스레드를 이용한 파일 압축 함수
void* compress_thread(void* arg) {
    int thread_id = *(int*)arg; // 스레드 ID 얻기
    int files_per_thread = num_files / num_threads_or_processes; // 각 스레드가 처리할 파일 수
    int start = thread_id * files_per_thread; // 시작 인덱스
    int end = (thread_id == num_threads_or_processes - 1) ? num_files : start + files_per_thread; // 끝 인덱스 설정

    char copy_command[50]; // 파일 복사 명령어
    char gzip_command[50]; // gzip 압축 명령어
    for (int i = start; i < end; i++) {
        snprintf(copy_command, sizeof(copy_command), "cp %s %s_copy", files[i], files[i]); // 파일 복사 명령어 생성
        system(copy_command); // 파일 복사 실행

        snprintf(gzip_command, sizeof(gzip_command), "gzip -f %s_copy", files[i]); // gzip 명령어 생성
        system(gzip_command); // 파일 압축 실행
    }
    return NULL; // 스레드 종료
}

// 프로세스를 이용한 파일 압축 함수
void compress_process(int process_id) {
    int files_per_process = num_files / num_threads_or_processes; // 각 프로세스가 처리할 파일 수
    int start = process_id * files_per_process; // 시작 인덱스
    int end = (process_id == num_threads_or_processes - 1) ? num_files : start + files_per_process; // 끝 인덱스 설정

    char copy_command[50]; // 파일 복사 명령어
    char gzip_command[50]; // gzip 압축 명령어
    for (int i = start; i < end; i++) {
        snprintf(copy_command, sizeof(copy_command), "cp %s %s_copy", files[i], files[i]); // 파일 복사 명령어 생성
        system(copy_command); // 파일 복사 실행

        snprintf(gzip_command, sizeof(gzip_command), "gzip -f %s_copy", files[i]); // gzip 명령어 생성
        system(gzip_command); // 파일 압축 실행
    }
}

// 스레드를 이용한 파일 압축 실행 함수
void compress_with_threads() {
    for (num_threads_or_processes = 1; num_threads_or_processes <= 16; num_threads_or_processes *= 2) {
        pthread_t threads[num_threads_or_processes]; // 스레드 배열
        int thread_ids[num_threads_or_processes]; // 스레드 ID 배열
        struct timespec start, end; // 시간 측정을 위한 변수

        clock_gettime(CLOCK_MONOTONIC, &start); // 시작 시간 기록

        for (int i = 0; i < num_threads_or_processes; i++) {
            thread_ids[i] = i; // 스레드 ID 초기화
            pthread_create(&threads[i], NULL, compress_thread, &thread_ids[i]); // 스레드 생성
        }

        for (int i = 0; i < num_threads_or_processes; i++) {
            pthread_join(threads[i], NULL); // 스레드 종료 대기
        }

        clock_gettime(CLOCK_MONOTONIC, &end); // 종료 시간 기록
        double elapsed = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9; // 경과 시간 계산
        printf("\t\tThreads: %d, Time: %f seconds\n", num_threads_or_processes, elapsed); // 결과 출력
    }
}

// 프로세스를 이용한 파일 압축 실행 함수
void compress_with_processes() {
    for (num_threads_or_processes = 1; num_threads_or_processes <= 16; num_threads_or_processes *= 2) {
        struct timespec start, end; // 시간 측정을 위한 변수

        clock_gettime(CLOCK_MONOTONIC, &start); // 시작 시간 기록

        for (int i = 0; i < num_threads_or_processes; i++) {
            pid_t pid = fork(); // 프로세스 생성
            if (pid == 0) {
                compress_process(i); // 자식 프로세스에서 파일 압축 수행
                exit(0); // 자식 프로세스 종료
            }
        }

        for (int i = 0; i < num_threads_or_processes; i++) {
            wait(NULL); // 모든 자식 프로세스 종료 대기
        }

        clock_gettime(CLOCK_MONOTONIC, &end); // 종료 시간 기록
        double elapsed = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9; // 경과 시간 계산
        printf("\t\tProcesses: %d, Time: %f seconds\n", num_threads_or_processes, elapsed); // 결과 출력
    }
}

int main() {
    initialize_matrices(); // 행렬 초기화

    printf("[ Data Parallelism ]\n");
    printf("\tRunning multiply with threads...\n"); // 스레드를 이용한 곱셈 실행
    multiply_with_threads();
    printf("\tRunning multiply with processes...\n"); // 프로세스를 이용한 곱셈 실행
    multiply_with_processes();

    printf("[ Task Parallelism ]\n");
    printf("\tRunning compress with threads...\n"); // 스레드를 이용한 압축 실행
    compress_with_threads();
    printf("\tRunning compress with processes...\n"); // 프로세스를 이용한 압축 실행
    compress_with_processes();

    return 0; // 프로그램 종료
}
