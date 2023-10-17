//
//  setter.c
//  c-mfq
//
//  Created by Jacob An on 2022/10/06.
//

#include "main.h"

static int init_queue(void) {
    job_queue = (t_proc**)malloc(sizeof(t_proc) * proc_num);
    if (job_queue == NULL) return -1;
    
    ready_queue0 = (t_node*)malloc(sizeof(t_node));
    if (ready_queue0 == NULL) return -1;
    ready_queue0->data = NULL;
    ready_queue0->next = NULL;
    
    ready_queue1 = (t_node*)malloc(sizeof(t_node));
    if (ready_queue1 == NULL) return -1;
    ready_queue1->data = NULL;
    ready_queue1->next = NULL;
    
    ready_queue2 = (t_proc**)malloc(sizeof(t_proc) * proc_num);
    if (ready_queue2 == NULL) return -1;
    for( int i = 0; i < proc_num; i++)
        ready_queue2[i] = NULL;
    
    sleep_queue = (t_proc**)malloc(sizeof(t_proc) * proc_num);
    if (sleep_queue == NULL) return -1;
    for (int i = 0; i < proc_num; i++)
        sleep_queue[i] = NULL;
    
    proc_table = (int**)malloc(sizeof(int*) * proc_num);
    if (proc_table == NULL) return -1;
    for (int i = 0; i < proc_num; i++) {
        proc_table[i] = malloc(sizeof(int) * 2);
        if (proc_table[i] == NULL)return -1;
    }
    return 0;
}

static t_proc* init_proc(int _PID, int _queue, int _arr_t, int _cycle_num) {
    t_proc *proc = NULL;

    proc = (t_proc*)malloc(sizeof(t_proc));
    if (proc == NULL) return proc;
    
    proc->PID = _PID;
    proc->queue = _queue;
    proc->arr_t = _arr_t;
    proc->cycle_num = _cycle_num;
    proc->cycle_index = 0;
    proc->cycle_total = 0;
    proc->seq_burst = (int*)malloc(sizeof(int) * ((_cycle_num * 2) - 1));
    
    if (proc->seq_burst == NULL) return NULL;
    return proc;
}

int set_proc(FILE *file) {
    t_proc* proc;
    int pid;
    int init_q;
    int arr_t;
    int cycle;
    int size_arr;
    int file_value;

    for (int i = 0; i < proc_num; i++) {
        int total = 0;
        file_value = 0;
        
        if (fscanf(file, "%d %d %d %d", &pid, &init_q, &arr_t, &cycle) == -1) return -1;
        
        size_arr = (cycle * 2) - 1;
        proc = init_proc(pid, init_q, arr_t, cycle);
        
        if (proc == NULL) return -1;
        for (int j = 0; j < size_arr; j++) {
            if (fscanf(file, "%d", &file_value) == -1) return -1;
            total += file_value;
            proc->seq_burst[j] = file_value;
        }
        
        proc->cycle_total = total;
        job_queue[i] = proc;
    }
    fclose(file);
    return 0;
}

int set_sim(void) {
    FILE *file = fopen("input.txt", "r");

    if (file == NULL || fscanf(file, "%d", &proc_num) == -1 || init_queue() == -1 || set_proc(file) == -1)
        return -1;
    
    return 0;
}
