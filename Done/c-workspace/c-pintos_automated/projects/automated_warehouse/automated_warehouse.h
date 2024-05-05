#ifndef __PROJECTS_AUTOMATED_WAREHOUSE_H__
#define __PROJECTS_AUTOMATED_WAREHOUSE_H__

#include "projects/automated_warehouse/robot.h"

void test_cnt(void);

void test_thread(void* aux);

int parse_args(char *task_list, Payload *payloads);

int initialize_robots(Payload *payloads);

int initialize_node();

void run_automated_warehouse(char **argv);

#endif 
