#include "main.h"

void print_table_Top(int isFixed, int i);
void print_table_Content_fixed(int time, int page_string, int isLoaded);
void print_table_Content_vari(int time, int page_string, int isLoaded, int out_page, int * working_set);
void print_table_Bottom(int isFixed, int page_fault);
void resource_return(void);

extern int N;
extern int M;
extern int *pg_ref;
extern int *memory;
extern int *timestamp1;
extern int *timestamp2;
extern int *reference_cnt;

void print_table_Top(int isFixed, int i) {
    if( isFixed == true ) {
        if( i == MIN ) {
            printf("MIN\n");
        } else if ( i == FIFO ) {
            printf("FIFO\n");
        } else if ( i == LRU ) {
            printf("LRU\n");
        } else if ( i == LFU ) {
            printf("LFU\n");
        } else { }
        printf("+------+-----+-----+\n");
        printf("| Time | str | P.f | Memory\n");
        printf("+------+-----+-----+\n");
    } else {
        printf("WS\n");
        printf("+------+-----+-----+-----+\n");
        printf("| Time | str | P.f | out | Memory\n");
        printf("+------+-----+-----+-----+\n");
    }
    return;
}

void print_table_Content_fixed(int time, int page_string, int isLoaded) {
    int asc = (isLoaded == true) ? 32 : 70;
    printf("| %4d | %3d | %2c  | ", time, page_string, asc);

    for(int j=0; j<M; j++) {
        if( memory[j] == -1 ) {
            printf("  ");
        } else {
            printf("%2d ", memory[j]);
        }
    }
    
    printf("\n");
    return;
}

void print_table_Content_vari(int time, int page_string, int isLoaded, int out_page, int * working_set) {
    int asc = (isLoaded == true) ? 32 : 70;
    if(out_page == -1) {
        char out = 32;
        printf("| %4d | %3d | %2c  | %2c  | ", time, page_string, asc, out);
    } else {
        printf("| %4d | %3d | %2c  | %2d  | ", time, page_string, asc, out_page);

    }
    for(int i=0; i<N; i++) {
        if( working_set[i] == true ) {
            printf("%2d ", i);
        }
    }
    printf("\n");
    return;
}

void print_table_Bottom(int isFixed, int page_fault) {
    if(isFixed == true) {
        printf("+------+-----+-----+\n");
    } else {
        printf("+------+-----+-----+-----+\n");
    }
    printf("Total page fault: %d\n\n\n", page_fault);
    return;
}

void resource_return(void) {
    free(pg_ref);
    free(memory);
    free(timestamp1);
    free(timestamp2);
    free(reference_cnt);
    return ;
}