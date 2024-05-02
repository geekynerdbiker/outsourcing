#include "main.h"

void start_simulation(void);
void fixed_allo(int replacement);
void variable_allo(int replacement);
int MIN_algo(int time);
int FIFO_algo(void);
int LRU_algo(void);
int LFU_algo(void);

extern void print_table_Top(int isFixed, int i);
extern void print_table_Content_fixed(int time, int page_string, int isLoaded);
extern void print_table_Content_vari(int time, int page_string, int isLoaded, int out_page, int * working_set);
extern void print_table_Bottom(int isFixed, int page_fault);

extern int N;
extern int M;
extern int W;
extern int K;
extern int *pg_ref;
extern int *memory;
extern int *timestamp1;
extern int *timestamp2;
extern int *reference_cnt;

void start_simulation(void) {
    fixed_allo(MIN);
    fixed_allo(FIFO);
    fixed_allo(LRU);
    fixed_allo(LFU);

    variable_allo(WS);
    return ;
}

void fixed_allo(int replacement) {
    print_table_Top(true, replacement);    
    int page_fault = 0;

    for(int i=0; i<K; i++) {
        int time = i+1;
        int page = pg_ref[i];
        int isLoaded = false;
        reference_cnt[page] += 1;

        for(int j=0; j<M; j++) {
            if( memory[j] == page ) {
                
                timestamp2[j] = time;
                isLoaded = true;
                break;
            }
        }

        if(isLoaded == false) {
            page_fault += 1;
            int position = -1;
            int isEmpty = false;

            for(int j=0; j<M; j++) {
                if( memory[j] == -1 ) {
                    position = j;
                    isEmpty = true;
                    break;
                }
            }


            if(isEmpty == false) {
                switch (replacement) {
                case MIN:
                    position = MIN_algo(i);
                    break;
                case FIFO:
                    position = FIFO_algo();
                    break;
                case LRU:
                    position = LRU_algo();
                    break;
                case LFU:
                    position = LFU_algo();
                    break;
                default:
                    printf("ERROR: wrong replacement strategy detected.\n");
                    return;
                }
            }

            memory[position] = page;
            timestamp1[position] = time;
            timestamp2[position] = time;
        }

        print_table_Content_fixed(i+1, page, isLoaded);
    }

    print_table_Bottom(true, page_fault);
    return;
}

void variable_allo(int replacement) {
    print_table_Top(false, replacement);

    int *working_set = (int*)malloc(sizeof(int) * N);
    for(int z=0; z<N; z++) working_set[z] = false;
    
    int page_fault = 0;

    for(int i=0; i<K; i++) {
        int page = pg_ref[i];
        int isLoaded = false;
        int out_page = -1;
        
        for(int j=0; j<N; j++) 
        if(working_set[j] == true) working_set[j] = -1;
    
        for(int z=1; z<=W; z++) {

            if( i-z < 0 ) break;

            int str = pg_ref[i-z];
            working_set[str] = true;
        }

        if( working_set[page] != false ) {
            isLoaded = true;
        } else {
            page_fault += 1;
        }
        
        working_set[page] = true;

        for(int j=0; j<N; j++) {
            if(working_set[j] == -1) {
                out_page = j;
                working_set[j] = false;
            }
        }

        print_table_Content_vari(i+1, page, isLoaded, out_page, working_set);
    }
    print_table_Bottom(false, page_fault);
    free(working_set);
    
    return;
}

int MIN_algo(int time) {
    int *forward_dis = (int*)malloc(sizeof(int) * M);

    for(int i=0; i<M; i++) {
        forward_dis[i] = -1;
    }
    
    for(int i=0; i<M; i++) {
        int page_num = memory[i];
        for(int j=time+1; j<K; j++) {
            if( page_num == pg_ref[j] ) {
                forward_dis[i] = j;
                break;
            }
        }
    }
    
    int Max = forward_dis[0];
    int Max_page = 0;

    for(int i=1; i<M; i++) {
        if( forward_dis[i] == -1 ) {
            if( memory[Max_page] > memory[i] ) {
                Max = forward_dis[i];
                Max_page = i;
            }
        } else {
            if( Max != -1 && forward_dis[i] > Max ) {
                Max = forward_dis[i];
                Max_page = i;
            }
        }
    }

    free(forward_dis);
    return Max_page;
}

int FIFO_algo(void) {
    int Min = timestamp1[0];
    int Min_page = 0;
    for(int i=1; i<M; i++) {
        if( Min > timestamp1[i] ) {
            Min = timestamp1[i];
            Min_page = i;
        }
    }
    
    return Min_page;
}

int LRU_algo(void) {
    int Min = timestamp2[0];
    int Min_page = 0;
    for(int i=1; i<M; i++) {
        if( Min > timestamp2[i] ) {
            Min = timestamp2[i];
            Min_page = i;
        }
    }
    
    return Min_page;
}

int LFU_algo(void) {
    int page_num = memory[0];
    int Min = reference_cnt[page_num];
    int Min_page = 0;
    for(int i=1; i<M; i++) {
        page_num = memory[i];
        if( Min > reference_cnt[page_num] ) {
            Min = reference_cnt[page_num];
            Min_page = i;
        } else {
            if( Min == reference_cnt[page_num] ) {
                int first = timestamp2[Min_page];
                int second = timestamp2[i];
                if( first > second ) {
                    Min = reference_cnt[page_num];
                    Min_page = i;
                }
            }
        }
    }
    
    return Min_page;
}