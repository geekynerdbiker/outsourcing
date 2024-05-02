//
//  main.c
//  c-mfq
//
//  Created by Jacob An on 2022/10/06.
//

#include "main.h"

static void print_table(void) {
    double ATT;
    double AWT;

    ATT = 0;
    AWT = 0;
    
    printf("proc table:\n");
    printf("+-------+-------------------+----------------+\n");
    printf("|  PID  |  Turnaround Time  |  Waiting Time  |\n");
    printf("+-------+-------------------+----------------+\n");
    
    for (int i = 0; i < proc_num; i++) {
        ATT += proc_table[i][0];
        AWT += proc_table[i][1];
        printf("| %5d | %17d | %14d |\n", i+1, proc_table[i][0], proc_table[i][1]);
    }
    
    printf("+-------+-------------------+----------------+\n");
    printf("\n");
    
    ATT /= proc_num;
    AWT /= proc_num;
    
    printf("Average Turnaround Time : %.2lf\nAverage Wating Time     : %.2lf\n", ATT, AWT);
}

int main() {
    if (set_sim() == -1) return -1;
    if (start_sim() == -1) return -1;
    
    print_table();
    delete_queue();
    
    return 0;
}
