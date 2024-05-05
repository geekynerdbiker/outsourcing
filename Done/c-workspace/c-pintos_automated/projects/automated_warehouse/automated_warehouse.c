#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "threads/init.h"
#include "threads/malloc.h"
#include "threads/synch.h"
#include "threads/thread.h"

#include "devices/timer.h"

#include "projects/automated_warehouse/automated_warehouse.h"
#include "projects/automated_warehouse/aw_manager.h"
#include "projects/automated_warehouse/aw_message.h"
#include "projects/automated_warehouse/node.h"

Robot* robots;
int num_robots;

/** message boxes from central control node to each robot */
MesssageBox* boxes_from_node;
/** message boxes from robots to central control node */
MesssageBox* boxes_from_robots;

// test code for central control node thread
void test_cnt(void){
        bool *received = malloc(sizeof(bool) * num_robots);
        for (int i = 0; i < num_robots; i++) {
                received[i] = false;
        }

        while(1){
                print(robots, num_robots);
                thread_sleep(100);
                bool received_all = false;
                while (!received_all) {
                        received_all = true;
                        for (int i = 0; i < num_robots; i++) {
                                if (received[i]) {      
                                        continue;
                                }
                                received_all = false;
                                Message msg;
                                int res = receive(i, &msg, CENTRAL_CONTROL);
                                if (res == 0) {
                                        Command cmd = find_path(&msg);
                                        set_command(&msg, cmd);
                                        send(i, &msg, CENTRAL_CONTROL);
                                        received[i] = true;
                                } 
                                
                        }
                }
                for (int i = 0; i < num_robots; i++) {
                        received[i] = false;
                }
                increase();
                unblock_threads();
        }
}

// test code for robot thread
void test_thread(void* aux){
        int idx = *((int *)aux);
        int test = 0;
        int res = 0;
        
        Message msg;
        msg.cmd = CMD_NOP;
        move_robot(robots, idx, num_robots, &msg);
        send(idx, &msg, ROBOT);
        for (int i = 0; i < idx * 5; i++) {
                if (i != idx) {
                        res = receive(idx, &msg, ROBOT);
                                if(res == 0){
                                msg.cmd = CMD_NOP;
                                move_robot(robots, idx, num_robots, &msg);
                                send(idx, &msg, ROBOT);
                        }
                }
        }
        while(1){
                memset(&msg, 0, sizeof(Message));
                printf("thread %d : %d\n", idx, test++);
                
                res = receive(idx, &msg, ROBOT);
                if(res == 0){
                        move_robot(robots, idx, num_robots, &msg);
                        send(idx, &msg, ROBOT);
                }
                block_thread();
        }
}

int parse_args(char *payload_list, Payload *payloads) {
        char *saveptr;
        char *token = strtok_r(payload_list, ":", &saveptr);
        int count = 0;

        while (token != NULL) {
                char number = token[0];
                char letter = token[1];

                if (count >= num_robots) {
                        printf("Too many robots\n");
                        return -1;
                }

                if (number < '0' || number > '9') {
                        printf("Invalid number format: %s\n", token);
                        return -2; 
                }
                
                if (letter < 'A' || letter > 'Z') {
                        printf("Invalid letter format: %s\n", token);
                        return -3;
                }

                if (token[2]) {
                        printf("Invalid format: %s\n", token);
                        return -4;
                }

                payloads[count].current = number;
                payloads[count].required = letter;
                count++;

                token = strtok_r(NULL, ":", &saveptr);
        }

        for (int i = 0; i < count; i++) {
                printf("%c%c\n", payloads[i].current, payloads[i].required);
        }

        return 0;
}

int initialize_robots(Payload *payloads) {
        robots = malloc(sizeof(Robot) * num_robots);
        tid_t* threads = malloc(sizeof(tid_t) * num_robots);
        char * rnames = malloc(sizeof(char) * num_robots * 3);
        int * robot_idxs = malloc(sizeof(int) * num_robots);

        for (int i = 0; i < num_robots; i++) {
                robot_idxs[i] = i;
                snprintf(rnames, 3, "R%d", i + 1);
                set_robot(&robots[i], rnames, ROW_W, COL_W, payloads[i].required, payloads[i].current);
                threads[i] = thread_create(rnames, 0, &test_thread, &robot_idxs[i]);
                if (threads[i] == TID_ERROR) {
                        printf("Thread creation failed\n");
                        return -1;
                }
                rnames += 3;
        }

        return 0;
}

int initialize_node() {
        tid_t* cnt_thread = thread_create("CNT", 0, &test_cnt, NULL);
        if (cnt_thread == TID_ERROR) {
                printf("Thread creation failed\n");
                return -1;
        }

        return 0;
}

void run_automated_warehouse(char **argv)
{
        init_automated_warehouse(argv);

        num_robots = atoi(argv[1]);
        char *payload_list = argv[2];

        Payload* payloads = malloc(sizeof(Payload) * num_robots);
        if (payloads == NULL) {
                printf("Memory allocation failed\n");
                return -1;
        }

        int res = parse_args(payload_list, payloads);
        if (res < 0) {
                printf("Parsing failed\n");
                return;
        }

        res = initialize_message_boxes(num_robots);
        if (res < 0) {
                printf("Message box initialization failed\n");
                return;
        }

        res = initialize_node();
        if (res < 0) {
                printf("Central control node initialization failed\n");
                return;
        }
        res = initialize_robots(payloads);
        if (res < 0) {
                printf("Robot initialization failed\n");
                return;
        }
}