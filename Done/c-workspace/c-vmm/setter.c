#include "main.h"

int     set_simulation(void);
int     init_ptr(void);
void    init_frame(void);

int N;
int M;
int W;
int K;
int *pg_ref;
int *memory;
int *timestamp1;
int *timestamp2;
int *reference_cnt;

int set_simulation(void) {
    if (scanf("%d %d %d %d", &N, &M, &W, &K) != 4)
    {
        printf("Error code 01: failed to receive user input.\n");
        return (-1);
    }
    if (init_ptr() == -1)
    {
        printf("Error code 02: failed to allocate memory bytes.\n");
        return (-1);
    }
    init_frame();
    return (0);
}

int init_ptr(void)
{
    pg_ref = (int*)malloc(sizeof(int) * K);
    if (pg_ref == NULL)
        return (-1);
    memory = (int*)malloc(sizeof(int) * M);
    if (memory == NULL)
        return (-1);
    timestamp1 = (int*)malloc(sizeof(int) * M);
    if (timestamp1 == NULL)
        return (-1);
    timestamp2 = (int*)malloc(sizeof(int) * M);
    if (timestamp2 == NULL)
        return (-1);
    reference_cnt = (int*)malloc(sizeof(int) * N);
    if (reference_cnt == NULL)
        return (-1);
    for(int i=0; i<K; i++) {
        scanf("%d", &pg_ref[i]);
    }
    return (0);
}

void init_frame(void) {
    for(int i=0; i<M; i++) {
        memory[i] = -1;
        timestamp1[i] = 0;
        timestamp2[i] = 0;
    }
    for(int i=0; i<N; i++) {
        reference_cnt[i] = 0;
    }
    return ;
}