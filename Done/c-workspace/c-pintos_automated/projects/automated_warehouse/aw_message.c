#include <stdio.h>
#include <stdlib.h>

#include "projects/automated_warehouse/aw_message.h"


int initialize_message_boxes(int num_robots) {
        NUM_ROBOTS = num_robots;

        boxes_from_node = malloc(sizeof(MesssageBox) * num_robots);
        if (boxes_from_node == NULL) {
                printf("Memory allocation failed\n");
                return -1;
        }
        for (int i = 0; i < num_robots; i++) {
                boxes_from_node[i].dirtyBit = 1;
        }

        boxes_from_robots = malloc(sizeof(MesssageBox) * num_robots);
        if (boxes_from_robots == NULL) {
                printf("Memory allocation failed\n");
                return -1;
        }

        for (int i = 0; i < num_robots; i++) {
                boxes_from_robots[i].dirtyBit = 0;
        }

        return 0;
}

int send(int robotIdx, Message * msg, MessageEndpoint endpoint)
{
        if (robotIdx < 0 || robotIdx >= NUM_ROBOTS) {
                printf("Invalid robot index: %d\n", robotIdx);
                return -1;
        }

        if (endpoint == ROBOT) {
                return send_to_node(robotIdx, msg);
        } else if (endpoint == CENTRAL_CONTROL) {
                return send_to_robot(robotIdx, msg);
        } else {
                printf("Invalid message endpoint\n");
                return -1;
        }
}

int receive(int robotIdx, Message * msg, MessageEndpoint endpoint)
{
        if (endpoint == ROBOT) {
                return receive_from_node(robotIdx, msg);
        } else if (endpoint == CENTRAL_CONTROL) {
                return receive_from_robot(robotIdx, msg);
        } else {
                printf("Invalid message endpoint\n");
                return -1;
        }
}

int send_to_node(int robotIdx, Message* msg) {
        if (boxes_from_robots[robotIdx].dirtyBit == 1) {
                printf("Message box is already written by others\n");
                return -1;
        }

        boxes_from_robots[robotIdx].msg.row = msg->row;
        boxes_from_robots[robotIdx].msg.col = msg->col;
        boxes_from_robots[robotIdx].msg.current = msg->current;
        boxes_from_robots[robotIdx].msg.required = msg->required;
        boxes_from_robots[robotIdx].dirtyBit = 1;
        INFO("msg", "send robot2cnt row: %d, col: %d, current: %c, required: %c", boxes_from_robots[robotIdx].msg.row, boxes_from_robots[robotIdx].msg.row, boxes_from_robots[robotIdx].msg.current, boxes_from_robots[robotIdx].msg.required);
        return 0;
}

int send_to_robot(int robotIdx, Message* msg) {
        if (boxes_from_node[robotIdx].dirtyBit == 1) {
                printf("Message box is already written by others\n");
                return -1;
        }

        boxes_from_node[robotIdx].msg.cmd = msg->cmd;
        boxes_from_node[robotIdx].dirtyBit = 1;
        
        INFO("msg", "send cnt2robot cmd: %d", boxes_from_node[robotIdx].msg.cmd);
        return 0;
}

int receive_from_node(int robotIdx, Message* msg) {
        if (boxes_from_node[robotIdx].dirtyBit == 0) {
                printf("Message box is not written yet\n");
                return -1;
        }
        
        msg->cmd = boxes_from_node[robotIdx].msg.cmd;
        boxes_from_node[robotIdx].dirtyBit = 0;
        
        INFO("msg", "recv cnt2robot cmd: %d", msg->cmd);
        return 0;
}

int receive_from_robot(int robotIdx, Message* msg) {
        if (boxes_from_robots[robotIdx].dirtyBit == 0) {
                printf("Message box is not written yet\n");
                return -1;
        }

        msg->row = boxes_from_robots[robotIdx].msg.row;
        msg->col = boxes_from_robots[robotIdx].msg.col;
        msg->current = boxes_from_robots[robotIdx].msg.current;
        msg->required = boxes_from_robots[robotIdx].msg.required;
        boxes_from_robots[robotIdx].dirtyBit = 0;

        INFO("msg", "recv robot2cnt row: %d, col: %d, current: %c, required: %c", msg->row, msg->col, msg->current, msg->required);
        return 0;
}

void set_command(Message* msg, Command cmd) {
        msg->cmd = cmd;
}