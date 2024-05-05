#include <stdio.h>

#include "projects/automated_warehouse/robot.h"
#include "projects/automated_warehouse/aw_message.h"
#include "projects/automated_warehouse/aw_manager.h"

/**
 * A function setting up robot structure
 */
void set_robot(Robot* _robot, const char* name, int row, int col, int required, int current) {
    _robot->name = name;
    _robot->row = row;
    _robot->col = col;
    _robot->required = required;
    _robot->current = current;
    INFO("robot", "set robot %s at (%d, %d) with required: %c, current: %c", name, row, col, required, current);
}

bool robot_is_unloaded(Robot* robot) {
    bool is_pos_alpha = map[robot->row][robot->col] >= 'A' && map[robot->row][robot->col] <= 'Z';
    bool is_pos_current = robot->current == map[robot->row][robot->col];
    return is_pos_alpha && is_pos_current;
}

void update_msg(Message* msg, Robot* robot) {
    msg->row = robot->row;
    msg->col = robot->col;
    msg->current = robot->current;
    msg->required = robot->required;
    INFO("robot", "update msg row: %d, col: %d, current: %c, required: %c", msg->row, msg->col, msg->current, msg->required);
}


bool isOutOfBound(int row, int col) {
    return row < ROW_MIN || row > ROW_MAX || col < COL_MIN || col > COL_MAX;
}

bool isWall(int row, int col) {
    return map[row][col] == 'X';
}

bool isAnotherCurrentPayload(int row, int col, int current) {
    return map[row][col] >= '0' && map[row][col] <= '9' && 
        map[row][col] != current;
}

bool isAnotherRequiredPayload(int row, int col, int current) {
    return map[row][col] >= 'A' && map[row][col] <= 'Z' && 
        map[row][col] != 'W' && map[row][col] != 'S' && 
        map[row][col] != current;
}

bool isAnotherRobot(Robot* robots, int number_of_robots, int idx, int row, int col) {
    for (int robotIdx = 0; robotIdx < number_of_robots; robotIdx++){
        if (robotIdx == idx) {
            continue;
        }
        Robot* robot = &robots[robotIdx];
        if (robot->col == col && robot->row == row){
            return true;
        }
    }
    return false;
}

Command find_movable_direction(Robot* robots, int idx, int number_of_robots) {
    Robot* robot = &robots[idx];
   
    int row = robot->row;
    int col = robot->col;
    char current = robot->current;
    char required = robot->required;

    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};

    for (int i = 0; i < 4; i++) {
        int new_row = row + dr[i];
        int new_col = col + dc[i];
        if (isOutOfBound(new_row, new_col) || isWall(new_row, new_col) || isAnotherRobot(robots, number_of_robots, idx, new_row, new_col)) {
            continue;
        }
        
        if (isAnotherCurrentPayload(new_row, new_col, current) || isAnotherRequiredPayload(new_row, new_col, current)) {
            continue;
        }

        switch (i) {
            case 0:
                INFO("robot", "robot %s can move up", robot->name);
                return CMD_UP;
            case 1:
                INFO("robot", "robot %s can move down", robot->name);
                return CMD_DOWN;
            case 2:
                INFO("robot", "robot %s can move left", robot->name);
                return CMD_LEFT;
            case 3:
                INFO("robot", "robot %s can move right", robot->name);
                return CMD_RIGHT;
        }
    }

    return CMD_NOP;
}

int move_robot(Robot* robots, int idx, int number_of_robots, Message* msg) {
    Robot* robot = &robots[idx];

    if (robot->current > robot->required && map[robot->row][robot->col] == robot->current) {
        return 0;
    }

    Command cmd = msg->cmd;
    if (robot->nop > 5) {
        robot->nop = 0;
        cmd = find_movable_direction(robots, idx, number_of_robots);
    }

    int new_row = robot->row;
    int new_col = robot->col;

    switch (cmd) {
        case CMD_UP:
            new_row--;
            break;
        case CMD_DOWN:
            new_row++;
            break;
        case CMD_LEFT:
            new_col--;
            break;
        case CMD_RIGHT:
            new_col++;
            break;
        case CMD_NOP:
            robot->nop++;
            break;
        default:
            ERROR("robot", "robot %s received invalid command %d", robot->name, cmd);
            update_msg(msg, robot);
            return -1; // Invalid command
    }
    
    char new_pos = map[new_row][new_col];

    if (isOutOfBound(new_row, new_col)) {
        ERROR("robot", "robot %s out of bound at (%d, %d)", robot->name, new_row, new_col);
        robot->nop++;
        update_msg(msg, robot);
        return 0;
    }

    if (isWall(new_row, new_col)) {
        ERROR("robot", "robot %s hit the wall at (%d, %d)", robot->name, new_row, new_col);
        robot->nop++;
        update_msg(msg, robot);
        return 0;
    }

    if (isAnotherCurrentPayload(new_row, new_col, robot->current)) {
        ERROR("robot", "robot %s hit the wrong payload at (%d, %d)", robot->name, new_row, new_col);
        robot->nop++;
        update_msg(msg, robot);
        return 0;
    }

    if (isAnotherRequiredPayload(new_row, new_col, robot->current)) {
        ERROR("robot", "robot %s required %c hit the wrong required payload at (%d, %d)", robot->name, robot->required, new_row, new_col);
        robot->nop++;
        update_msg(msg, robot);
        return 0;
    }

    for (int robotIdx = 0; robotIdx < number_of_robots; robotIdx++){
        if (robotIdx == idx) {
            continue;
        }
        Robot* __robot = &robots[robotIdx];
        if (__robot->col == new_col && __robot->row == new_row){
            if (robot_is_unloaded(__robot)) {
                continue;
            }
            WARN("robot", "robot %s hit another robot %s at (%d, %d)", robot->name, __robot->name, new_row, new_col);
            robot->nop++;
            update_msg(msg, robot);
            return 0;
        }
    }
    
    robot->row = new_row;
    robot->col = new_col;
    INFO("robot", "new position: (%d, %d), current: %c", new_row, new_col, robot->current);
    
    if (new_pos == robot->current) {
            if (robot_is_unloaded(robot)) {
                INFO("robot", "robot %s unloaded %c at (%d, %d)", robot->name, robot->current, new_row, new_col);
            } else {
                INFO("robot", "robot %s loaded %c at (%d, %d)", robot->name, robot->current, new_row, new_col);
                int tmp = robot->current;
                robot->current = robot->required;
                robot->required = tmp;
            }            
    }

    update_msg(msg, robot);
    INFO("robot", "move %s to (%d, %d)", robot->name, new_row, new_col);
    return 0;
}