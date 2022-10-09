//
//  main.h
//  c-mfq
//
//  Created by Jacob An on 2022/10/06.
//

#ifndef main_h
#define main_h

#include <stdio.h>
#include <stdlib.h>


typedef struct t_proc {
    int PID;
    int queue;
    int arr_t;
    int cycle_num;
    int cycle_index;
    int cycle_total;
    int *seq_burst;
} t_proc;

typedef struct t_node {
    struct t_node *next;
    t_proc *data;
} t_node;
 
t_proc **job_queue;
t_node *ready_queue0;
t_node *ready_queue1;
t_proc **ready_queue2;
t_proc **sleep_queue;

int **proc_table;
int proc_num;

int set_sim(void);
int start_sim(void);
void delete_queue(void);


#endif /* main_h */
