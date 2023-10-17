//
//  simulator.c
//  c-mfq
//
//  Created by Jacob An on 2022/10/06.
//

#include "main.h"

int global_t = 0;
int t_quantum;

static int get_burst_t(t_proc *proc) {
    return proc->seq_burst[proc->cycle_index];
}

static void delete_proc(t_proc *proc, int global_t) {
    int pid = proc->PID - 1;
    int arr_t = proc->arr_t;
    int total = proc->cycle_total;
    int TT = global_t - arr_t;
    
    proc_table[pid][0] = TT;
    proc_table[pid][1] = TT - total;
    
    free(proc->seq_burst);
    free(proc);
    
    return;
}

static int cpu_running(t_proc *proc) {
    int remain = get_burst_t(proc) - 1;
    int cycle_num = proc->cycle_num;
    int index = proc->cycle_index;
    int arr_size = (cycle_num * 2) - 1;
    
    proc->seq_burst[proc->cycle_index] = remain;
    
    if (remain == 0) {
        index += 1;
        proc->cycle_index = index;
        
        if (arr_size == index) {
            delete_proc(proc, global_t);
            return -1;
        }
        return 0;
    }
    return 1;
}

static int push_queue(t_proc *proc) {
    t_node  *head;
    t_node  *node;
    int queue_num = proc->queue;
    int pid = proc->PID - 1;

    switch (queue_num) {
    case 0:
        head = ready_queue0;
        break;
    case 1:
        head = ready_queue1;
        break;
    case 2:
        ready_queue2[pid] = proc;
        return 0;
    default:
        break;
    }
    
    node = (t_node*)malloc(sizeof(t_node));
    if (node == NULL) return -1;
    
    node->data = proc;
    node->next = NULL;
    
    while (head->next != NULL) {
        head = head->next;
    }
    head->next = node;
    
    return 0;
}

static int io_check(void) {
    for (int i = 0; i < proc_num; i++) {
        if (sleep_queue[i] != NULL) {
            int t = get_burst_t(sleep_queue[i]);
            if (t == 0) {
                sleep_queue[i]->cycle_index += 1;
                int queue = sleep_queue[i]->queue;
                queue = queue > 0 ? queue - 1 : 0;
                sleep_queue[i]->queue = queue;
                if (push_queue(sleep_queue[i]) == -1)
                    return -1;
                sleep_queue[i] = NULL;
            }
        }
    }
    return 0;
}

static int arr_check(void) {
    int rst = 0;

    for (int i = 0; i < proc_num; i++) {
        if (job_queue[i] != NULL) {
            if (job_queue[i]->arr_t == global_t) {
                if (push_queue(job_queue[i]) == -1)
                    return -1;
                job_queue[i] = NULL;
            } else {
                rst = 1;
            }
        }
    }
    return rst;
}

static int burst_check(t_proc* proc, int PID){
    int rst = cpu_running(proc);
    
    if (rst == 0) {
        PID -= 1;
        sleep_queue[PID] = proc;
    }
    return rst;
}

static t_proc *fcfs(int type) {
    t_proc *rst;
    t_node *head;
    t_node *remove;

    switch (type) {
    case 0:
        head = ready_queue0;
        break;
    case 1:
        head = ready_queue1;
        break;
    default:
        head = NULL;
        break;
    }
    if (head == NULL || head->next == NULL) return NULL;

    remove = head->next;
    rst = remove->data;
    head->next = remove->next;
    
    free(remove);
    
    return rst;
}

static t_proc *spn(void) {
    t_proc *rst = NULL;
    
    int min_t = -1;
    int index = -1;
    int burst_t;

    for (int i = 0; i < proc_num; i++) {
        if (ready_queue2[i] != NULL) {
            burst_t = get_burst_t(ready_queue2[i]);
            if (min_t == -1 || burst_t < min_t) {
                index = i;
                rst = ready_queue2[i];
                min_t = burst_t;
            }
        }
    }
    if (index != -1) {
        ready_queue2[index] = NULL;
        return rst;
    }
    return rst;
}

static int sleep_check(void) {
    for (int i = 0; i < proc_num; i++) {
        if (sleep_queue[i] != NULL) {
            return 1;
        }
    }
    return 0;
}

static t_proc *scheduling(void) {
    t_proc *rst;

    rst = fcfs(0);
    if (rst != NULL) {
        t_quantum = 2;
        return rst;
    }
    rst = fcfs(1);
    if (rst != NULL) {
        t_quantum = 4;
        return rst;
    }
    rst = spn();
    if (rst != NULL) {
        t_quantum = -1;
        return rst;
    }
    return rst;
}

int start_sim(void) {
    t_proc *curr_proc = NULL;
    
    int curr_proc_id = 0;
    int curr_queue = -1;
    int prev_proc_id = -1;
    int remain_proc = 1;
    int line = 0;
    
    int arr_rst;
    int break_check;

    printf("\nGantt Chart: \n\n");
    printf("  Process ID\n");
    
    while (1) {
        if (remain_proc == 1) {
            arr_rst = arr_check();
            if (arr_rst == 0) {
                remain_proc = 0;
            }
        }
        
        if (io_check() == -1)
            return -1;
        
        if (curr_proc == NULL) {
            curr_proc = scheduling();
                        
            if (curr_proc == NULL) {
                break_check = sleep_check();
               
                if (remain_proc == 0 && break_check == 0) {
                    line /= 5;
                    for(int i=0; i<line; i++) {
                        printf("|            | \n");
                    }
                    line = 0;
                    printf("|   %4d     | \n", prev_proc_id);
                    printf("+-------------  %d\n\n", global_t);
                    break;
                }
               
                curr_proc_id = 0;
                curr_queue = -1;
            } else {
                curr_proc_id = curr_proc->PID;
                curr_queue = curr_proc->queue;
            }
        }
        
        if (prev_proc_id != curr_proc_id) {
            line /= 5;
            for(int i=0; i<line; i++) {
                printf("|            | \n");
            }
            line = 0;
            if(prev_proc_id == 0) {
                printf("|   wating   | \n");
            } else {
                if(prev_proc_id != -1)
                printf("|   %4d     | \n", prev_proc_id);
            }
            printf("+-------------  %d\n", global_t);
            if(curr_proc_id == 0) {
                printf("|   wating   | \n");
            } else {
                printf("|   %4d     | \n", curr_proc_id);
            }
            prev_proc_id = curr_proc_id;
        } else {
            line++;
        }
        
        global_t += 1;
        t_quantum -= 1;
        for (int i = 0; i < proc_num; i++) {
            if (sleep_queue[i] != NULL) {
                int index = sleep_queue[i]->cycle_index;
                sleep_queue[i]->seq_burst[index] -= 1;
            }
        }
        
        if (curr_proc == NULL) continue;
        
        int check = burst_check(curr_proc, curr_proc_id);
        if (check != 1) {
            curr_proc = NULL;
            curr_proc_id = 0;
            curr_queue = -1;
        } else {
            if (t_quantum == 0) {
                curr_queue = curr_queue < 2 ? curr_queue + 1 : 2 ;
                curr_proc->queue = curr_queue;
                if (push_queue(curr_proc) == -1)
                    return -1;
                curr_proc = NULL;
                curr_proc_id = 0;
                curr_queue = -1;
            }
        }
    }
    return 0;
}

void delete_queue(void) {
    free(job_queue);
    free(ready_queue0);
    free(ready_queue1);
    free(ready_queue2);
    free(sleep_queue);
    free(proc_table);
}
