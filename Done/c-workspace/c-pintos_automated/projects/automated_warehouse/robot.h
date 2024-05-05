#ifndef _PROJECTS_PROJECT1_ROBOT_H__
#define _PROJECTS_PROJECT1_ROBOT_H__

#include <stdbool.h>

#include "projects/automated_warehouse/aw_message.h"

typedef struct Payload {
    char current;
    char required;
} Payload;

typedef struct Robot {
    const char* name;
    int row;
    int col;
    int required;
    int current;
    int nop;
} Robot;

void set_robot(Robot* _robot, const char* name, int row, int col, int required, int current);
int move_robot(Robot* robots, int idx, int number_of_robots, Message* msg);


#endif